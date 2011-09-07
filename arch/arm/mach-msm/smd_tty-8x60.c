/* arch/arm/mach-msm/smd_tty.c
 *
 * Copyright (C) 2007 Google, Inc.
 * Copyright (c) 2009-2010, Code Aurora Forum. All rights reserved.
 * Author: Brian Swetland <swetland@google.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/wakelock.h>
#include <linux/platform_device.h>

#include <linux/tty.h>
#include <linux/tty_driver.h>
#include <linux/tty_flip.h>

#include <mach/msm_smd.h>
#include <mach/peripheral-loader.h>

#include "smd_private.h"

#define MAX_SMD_TTYS 37
#define MAX_TTY_BUF_SIZE 2048

static DEFINE_MUTEX(smd_tty_lock);

static uint smd_tty_modem_wait;
module_param_named(modem_wait, smd_tty_modem_wait,
			uint, S_IRUGO | S_IWUSR | S_IWGRP);

struct smd_tty_info {
	smd_channel_t *ch;
	struct tty_struct *tty;
	struct wake_lock wake_lock;
	int open_count;
	struct tasklet_struct tty_tsklt;
	struct timer_list buf_req_timer;
	struct completion ch_allocated;
	struct platform_driver driver;
	void *pil;
};

static char *smd_ch_name[] = {
	[0] = "DS",
	[7] = "DATA1",
	/* Use DATA4 rather than DATA9 for modemlind on 8x60 */
	[9] = "DATA4",
#ifdef CONFIG_BUILD_OMA_DM
	[19] = "DATA3",
#endif
	[21] = "DATA21",
#ifdef CONFIG_BUILD_KDDI
	[25] = "DATA19",
#endif
#ifdef CONFIG_BUILD_CIQ
	[26] = "DATA20",
#endif
	[27] = "GPSNMEA",
	[36] = "LOOPBACK",
};


static struct smd_tty_info smd_tty[MAX_SMD_TTYS];

static void buf_req_retry(unsigned long param)
{
	struct smd_tty_info *info = (struct smd_tty_info *)param;
	tasklet_hi_schedule(&info->tty_tsklt);
}

static void smd_tty_read(unsigned long param)
{
	unsigned char *ptr;
	int avail;
	struct smd_tty_info *info = (struct smd_tty_info *)param;
	struct tty_struct *tty = info->tty;

	if (!tty)
		return;

	for (;;) {
		if (test_bit(TTY_THROTTLED, &tty->flags))
			break;
		avail = smd_read_avail(info->ch);
		if (avail == 0)
			break;

		if (avail > MAX_TTY_BUF_SIZE)
			avail = MAX_TTY_BUF_SIZE;

		avail = tty_prepare_flip_string(tty, &ptr, avail);
		if (avail <= 0) {
			if (!timer_pending(&info->buf_req_timer)) {
				init_timer(&info->buf_req_timer);
				info->buf_req_timer.expires = jiffies +
							((30 * HZ)/1000);
				info->buf_req_timer.function = buf_req_retry;
				info->buf_req_timer.data = param;
				add_timer(&info->buf_req_timer);
			}
			return;
		}

		if (smd_read(info->ch, ptr, avail) != avail) {
			/* shouldn't be possible since we're in interrupt
			** context here and nobody else could 'steal' our
			** characters.
			*/
			printk(KERN_ERR "OOPS - smd_tty_buffer mismatch?!");
		}

		wake_lock_timeout(&info->wake_lock, HZ / 2);
		tty_flip_buffer_push(tty);
	}

	/* XXX only when writable and necessary */
	tty_wakeup(tty);
}

static void smd_tty_notify(void *priv, unsigned event)
{
	struct smd_tty_info *info = priv;

	if (event != SMD_EVENT_DATA)
		return;

	tasklet_hi_schedule(&info->tty_tsklt);
}

static uint32_t is_modem_smsm_inited(void)
{
	uint32_t modem_state;
	modem_state = smsm_get_state(SMSM_MODEM_STATE);
	return modem_state & SMSM_INIT;
}

static int smd_tty_open(struct tty_struct *tty, struct file *f)
{
	int res = 0;
	int n = tty->index;
	struct smd_tty_info *info;


	if (!smd_ch_name[n])
		return -ENODEV;

	info = smd_tty + n;

	mutex_lock(&smd_tty_lock);
	tty->driver_data = info;

	if (info->open_count++ == 0) {
		info->pil = pil_get("modem");
		if (IS_ERR(info->pil)) {
			res = PTR_ERR(info->pil);
			goto out;
		}

		/* Wait for the modem SMSM to be inited for the SMD
		 * Loopback channel to be allocated at the modem. Since
		 * the wait need to be done atmost once, using msleep
		 * doesn't degrade the performance.
		 */
		if (n == 36) {
			if (!is_modem_smsm_inited())
				msleep(5000);
			smsm_change_state(SMSM_APPS_STATE,
				0, SMSM_SMD_LOOPBACK);
			msleep(100);
		}


		/*
		 * Wait for a channel to be allocated so we know
		 * the modem is ready enough.
		 */
		if (smd_tty_modem_wait) {
			res = wait_for_completion_interruptible_timeout(
				&info->ch_allocated,
				msecs_to_jiffies(smd_tty_modem_wait * 1000));

			if (res == 0) {
				pr_err("Timed out waiting for SMD channel\n");
				res = -ETIMEDOUT;
				goto release_pil;
			} else if (res < 0) {
				pr_err("Error waiting for SMD channel: %d\n",
					res);
				goto release_pil;
			}

			res = 0;
		}


		info->tty = tty;
		tasklet_init(&info->tty_tsklt, smd_tty_read,
			     (unsigned long)info);
		wake_lock_init(&info->wake_lock, WAKE_LOCK_SUSPEND,
				smd_ch_name[n]);
		if (!info->ch) {
			res = smd_open(smd_ch_name[n], &info->ch, info,
				       smd_tty_notify);
		}
	}

release_pil:
	if (res < 0)
		pil_put(info->pil);
	else
		smd_disable_read_intr(info->ch);
out:
	mutex_unlock(&smd_tty_lock);

	return res;
}

static void smd_tty_close(struct tty_struct *tty, struct file *f)
{
	struct smd_tty_info *info = tty->driver_data;

	if (info == 0)
		return;

	mutex_lock(&smd_tty_lock);
	if (--info->open_count == 0) {
		if (info->tty) {
			tasklet_kill(&info->tty_tsklt);
			wake_lock_destroy(&info->wake_lock);
			info->tty = 0;
		}
		tty->driver_data = 0;
		del_timer(&info->buf_req_timer);
		if (info->ch) {
			smd_close(info->ch);
			info->ch = 0;
			pil_put(info->pil);
		}
	}
	mutex_unlock(&smd_tty_lock);
}

static int smd_tty_write(struct tty_struct *tty, const unsigned char *buf, int len)
{
	struct smd_tty_info *info = tty->driver_data;
	int avail;

	/* if we're writing to a packet channel we will
	** never be able to write more data than there
	** is currently space for
	*/
	avail = smd_write_avail(info->ch);
	if (len > avail) {
		printk(KERN_INFO "%s: buffer full. avail:%d, len:%d\n",
			__func__, avail, len);
		len = avail;
	}

	return smd_write(info->ch, buf, len);
}

static int smd_tty_write_room(struct tty_struct *tty)
{
	struct smd_tty_info *info = tty->driver_data;
	return smd_write_avail(info->ch);
}

static int smd_tty_chars_in_buffer(struct tty_struct *tty)
{
	struct smd_tty_info *info = tty->driver_data;
	return smd_read_avail(info->ch);
}

static void smd_tty_unthrottle(struct tty_struct *tty)
{
	struct smd_tty_info *info = tty->driver_data;
	tasklet_hi_schedule(&info->tty_tsklt);
	return;
}

static int smd_tty_tiocmget(struct tty_struct *tty, struct file *file)
{
	struct smd_tty_info *info = tty->driver_data;
	return smd_tiocmget(info->ch);
}

static int smd_tty_tiocmset(struct tty_struct *tty, struct file *file,
				unsigned int set, unsigned int clear)
{
	struct smd_tty_info *info = tty->driver_data;
	return smd_tiocmset(info->ch, set, clear);
}

static struct tty_operations smd_tty_ops = {
	.open = smd_tty_open,
	.close = smd_tty_close,
	.write = smd_tty_write,
	.write_room = smd_tty_write_room,
	.chars_in_buffer = smd_tty_chars_in_buffer,
	.unthrottle = smd_tty_unthrottle,
	.tiocmget = smd_tty_tiocmget,
	.tiocmset = smd_tty_tiocmset,
};

static int smd_tty_dummy_probe(struct platform_device *pdev)
{
	if (!strcmp(pdev->name, smd_ch_name[0]))
		complete_all(&smd_tty[0].ch_allocated);
	else if (!strcmp(pdev->name, smd_ch_name[7]))
		complete_all(&smd_tty[7].ch_allocated);
	else if (!strcmp(pdev->name, smd_ch_name[9]))
		complete_all(&smd_tty[9].ch_allocated);
#ifdef CONFIG_BUILD_OMA_DM
	else if (!strcmp(pdev->name, smd_ch_name[19]))
		complete_all(&smd_tty[19].ch_allocated);
#endif
	else if (!strcmp(pdev->name, smd_ch_name[21]))
		complete_all(&smd_tty[21].ch_allocated);
#ifdef CONFIG_BUILD_KDDI
	else if (!strcmp(pdev->name, smd_ch_name[25]))
		complete_all(&smd_tty[25].ch_allocated);
#endif
#ifdef CONFIG_BUILD_CIQ
	else if (!strcmp(pdev->name, smd_ch_name[26]))
		complete_all(&smd_tty[26].ch_allocated);
#endif
	else if (!strcmp(pdev->name, smd_ch_name[27]))
		complete_all(&smd_tty[27].ch_allocated);
	else if (!strcmp(pdev->name, "LOOPBACK_TTY"))
		complete_all(&smd_tty[36].ch_allocated);

	return 0;
}

static struct tty_driver *smd_tty_driver;

static int __init smd_tty_init(void)
{
	int ret;

	smd_tty_driver = alloc_tty_driver(MAX_SMD_TTYS);
	if (smd_tty_driver == 0)
		return -ENOMEM;

	smd_tty_driver->owner = THIS_MODULE;
	smd_tty_driver->driver_name = "smd_tty_driver";
	smd_tty_driver->name = "smd";
	smd_tty_driver->major = 0;
	smd_tty_driver->minor_start = 0;
	smd_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	smd_tty_driver->subtype = SERIAL_TYPE_NORMAL;
	smd_tty_driver->init_termios = tty_std_termios;
	smd_tty_driver->init_termios.c_iflag = 0;
	smd_tty_driver->init_termios.c_oflag = 0;
	smd_tty_driver->init_termios.c_cflag = B38400 | CS8 | CREAD;
	smd_tty_driver->init_termios.c_lflag = 0;
	smd_tty_driver->flags = TTY_DRIVER_RESET_TERMIOS |
		TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	tty_set_operations(smd_tty_driver, &smd_tty_ops);

	ret = tty_register_driver(smd_tty_driver);
	if (ret)
		return ret;

	/* this should be dynamic */
	tty_register_device(smd_tty_driver, 0, 0);
	tty_register_device(smd_tty_driver, 7, 0);
	tty_register_device(smd_tty_driver, 9, 0);
#ifdef CONFIG_BUILD_OMA_DM
	tty_register_device(smd_tty_driver, 19, 0);
#endif
	tty_register_device(smd_tty_driver, 21, 0);
#ifdef CONFIG_BUILD_KDDI
	tty_register_device(smd_tty_driver, 25, 0);
#endif
#ifdef CONFIG_BUILD_CIQ
	tty_register_device(smd_tty_driver, 26, 0);
#endif
	tty_register_device(smd_tty_driver, 27, 0);
	tty_register_device(smd_tty_driver, 36, 0);

	init_completion(&smd_tty[0].ch_allocated);
	init_completion(&smd_tty[7].ch_allocated);
	init_completion(&smd_tty[9].ch_allocated);
#ifdef CONFIG_BUILD_OMA_DM
	init_completion(&smd_tty[19].ch_allocated);
#endif
	init_completion(&smd_tty[21].ch_allocated);
#ifdef CONFIG_BUILD_KDDI
	init_completion(&smd_tty[25].ch_allocated);
#endif
#ifdef CONFIG_BUILD_CIQ
	init_completion(&smd_tty[26].ch_allocated);
#endif
	init_completion(&smd_tty[27].ch_allocated);
	init_completion(&smd_tty[36].ch_allocated);

	smd_tty[0].driver.probe = smd_tty_dummy_probe;
	smd_tty[0].driver.driver.name = smd_ch_name[0];
	smd_tty[0].driver.driver.owner = THIS_MODULE;
	ret = platform_driver_register(&smd_tty[0].driver);
	if (ret)
		goto out;
	smd_tty[7].driver.probe = smd_tty_dummy_probe;
	smd_tty[7].driver.driver.name = smd_ch_name[7];
	smd_tty[7].driver.driver.owner = THIS_MODULE;
	ret = platform_driver_register(&smd_tty[7].driver);
	if (ret)
		goto unreg0;
	smd_tty[9].driver.probe = smd_tty_dummy_probe;
	smd_tty[9].driver.driver.name = smd_ch_name[9];
	smd_tty[9].driver.driver.owner = THIS_MODULE;
	ret = platform_driver_register(&smd_tty[9].driver);
	if (ret)
		goto unreg7;
	smd_tty[21].driver.probe = smd_tty_dummy_probe;
	smd_tty[21].driver.driver.name = smd_ch_name[21];
	smd_tty[21].driver.driver.owner = THIS_MODULE;
	ret = platform_driver_register(&smd_tty[21].driver);
	if (ret)
		goto unreg9;
	smd_tty[27].driver.probe = smd_tty_dummy_probe;
	smd_tty[27].driver.driver.name = smd_ch_name[27];
	smd_tty[27].driver.driver.owner = THIS_MODULE;
	ret = platform_driver_register(&smd_tty[27].driver);
	if (ret)
		goto unreg21;
#ifdef CONFIG_BUILD_OMA_DM
	smd_tty[19].driver.probe = smd_tty_dummy_probe;
	smd_tty[19].driver.driver.name = smd_ch_name[19];
	smd_tty[19].driver.driver.owner = THIS_MODULE;
	ret = platform_driver_register(&smd_tty[19].driver);
	if (ret)
		goto unreg27;
#endif
#ifdef CONFIG_BUILD_KDDI
	smd_tty[25].driver.probe = smd_tty_dummy_probe;
	smd_tty[25].driver.driver.name = smd_ch_name[25];
	smd_tty[25].driver.driver.owner = THIS_MODULE;
	ret = platform_driver_register(&smd_tty[25].driver);
	if (ret)
		goto unreg27;
#endif
#ifdef CONFIG_BUILD_CIQ
	smd_tty[26].driver.probe = smd_tty_dummy_probe;
	smd_tty[26].driver.driver.name = smd_ch_name[26];
	smd_tty[26].driver.driver.owner = THIS_MODULE;
	ret = platform_driver_register(&smd_tty[26].driver);
	if (ret)
		goto unreg27;
#endif
	smd_tty[36].driver.probe = smd_tty_dummy_probe;
	smd_tty[36].driver.driver.name = "LOOPBACK_TTY";
	smd_tty[36].driver.driver.owner = THIS_MODULE;
	ret = platform_driver_register(&smd_tty[36].driver);
	if (ret)
		goto unreg27;

	return 0;

unreg27:
#ifdef CONFIG_BUILD_CIQ
	platform_driver_unregister(&smd_tty[26].driver);
#endif
#ifdef CONFIG_BUILD_KDDI
	platform_driver_unregister(&smd_tty[25].driver);
#endif
#ifdef CONFIG_BUILD_OMA_DM
	platform_driver_unregister(&smd_tty[19].driver);
#endif
	platform_driver_unregister(&smd_tty[27].driver);
unreg21:
	platform_driver_unregister(&smd_tty[21].driver);
unreg9:
	platform_driver_unregister(&smd_tty[9].driver);
unreg7:
	platform_driver_unregister(&smd_tty[7].driver);
unreg0:
	platform_driver_unregister(&smd_tty[0].driver);
out:
	tty_unregister_device(smd_tty_driver, 0);
	tty_unregister_device(smd_tty_driver, 7);
	tty_unregister_device(smd_tty_driver, 9);
#ifdef CONFIG_BUILD_OMA_DM
	tty_unregister_device(smd_tty_driver, 19);
#endif
	tty_unregister_device(smd_tty_driver, 21);
#ifdef CONFIG_BUILD_KDDI
	tty_unregister_device(smd_tty_driver, 25);
#endif
#ifdef CONFIG_BUILD_CIQ
	tty_unregister_device(smd_tty_driver, 26);
#endif
	tty_unregister_device(smd_tty_driver, 27);
	tty_unregister_device(smd_tty_driver, 36);
	tty_unregister_driver(smd_tty_driver);
	put_tty_driver(smd_tty_driver);
	return ret;
}

module_init(smd_tty_init);
