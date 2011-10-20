/* Copyright (c) 2010, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/rtc.h>
#include <linux/mfd/pmic8058.h>
#include <linux/pm.h>
#include <linux/slab.h>
#include <linux/rtc/rtc-pm8058.h>
#include <linux/pm_runtime.h>
#include <mach/msm_rpcrouter-8x60.h>
#include <asm/atomic.h>
#include <linux/delay.h>
#include <linux/kthread.h>

#define PM8058_RTC_CTRL		0x1E8
	#define PM8058_RTC_ENABLE	BIT(7)
	#define PM8058_RTC_ALARM_ENABLE	BIT(1)
#define PM8058_RTC_ALARM_CTRL	0x1E9
#define PM8058_RTC_TEST		0x1F6
#define PM8058_RTC_READ_BASE	0x1EE
#define PM8058_RTC_WRITE_BASE	0x1EA
#define PM8058_RTC_ALARM_BASE	0x1F2

#ifdef CONFIG_BUILD_CIQ
#define TIMEREMOTE_PROCEEDURE_GET_MILLISECOND_TICK	100
#endif

#define APP_RTC_PROG			0x30000048
#define APP_RTC_VER			0x00040000
#define TIMEREMOTE_PROCEEDURE_SET_JULIAN	6

struct pm8058_rtc {
	struct rtc_device *rtc0;
	int rtc_irq;
	int rtc_alarm_irq;
	struct pm8058_chip *pm_chip;
};

struct rpc_time_julian {
	uint32_t year;
	uint32_t month;
	uint32_t day;
	uint32_t hour;
	uint32_t minute;
	uint32_t second;
	uint32_t day_of_week;
};

static struct msm_rpc_endpoint *ep;
static struct mutex rpc_setup_lock;
#ifdef CONFIG_MACH_HOLIDAY
int rtc_debug_flag = 0;
#endif

static int
pm8058_rtc_read_bytes(struct pm8058_rtc *rtc_dd, u8 *rtc_val, int base)
{
	int i, rc;

	/*
	 * Read the 32-bit RTC/Alarm Value.
	 * These values have to be read 8-bit at a time.
	 */
	for (i = 0; i < 4; i++) {
		rc = pm8058_read(rtc_dd->pm_chip, base + i, &rtc_val[i], 1);
		if (rc < 0) {
			pr_err("%s: PM8058 read failed\n", __func__);
			return rc;
		}
	}

	return 0;
}

static int
pm8058_rtc_write_bytes(struct pm8058_rtc *rtc_dd, u8 *rtc_val, int base)
{
	int i, rc;

	/*
	 * Write the 32-bit Value.
	 * These values have to be written 8-bit at a time.
	 */
	for (i = 0; i < 4; i++) {
		rc = pm8058_write(rtc_dd->pm_chip, base + i, &rtc_val[i], 1);
		if (rc < 0) {
			pr_err("%s: PM8058 read failed\n", __func__);
			return rc;
		}
	}

	return 0;
}

static int
pm8058_init_rpc(void)
{
	int rc = 0;
	mutex_lock(&rpc_setup_lock);
	if (!ep || (IS_ERR(ep))) {
		ep = msm_rpc_connect_compatible(APP_RTC_PROG, APP_RTC_VER, 0);
		if (IS_ERR(ep)) {
			pr_err("%s: init rpc failed! rc = %ld\n", __func__, PTR_ERR(ep));
			rc = -EIO;
		}
	}
	mutex_unlock(&rpc_setup_lock);
	return rc;
}

static int
pm8058_rtc_connect_to_mdm(struct rtc_time *tm)
{
	int ret = 0;

	struct timeremote_set_julian_req {
		struct rpc_request_hdr hdr;
		uint32_t opt_arg;

		struct rpc_time_julian time;
	} req;

	struct timeremote_set_julian_rep {
		struct rpc_reply_hdr hdr;
	} rep;

	if ((ret = pm8058_init_rpc()) < 0)
		return ret;

	req.opt_arg = cpu_to_be32(1);
	req.time.year = cpu_to_be32(tm->tm_year + 1900);
	req.time.month = cpu_to_be32(tm->tm_mon + 1);
	req.time.day = cpu_to_be32(tm->tm_mday);
	req.time.hour = cpu_to_be32(tm->tm_hour);
	req.time.minute = cpu_to_be32(tm->tm_min);
	req.time.second = cpu_to_be32(tm->tm_sec);
	req.time.day_of_week = cpu_to_be32(tm->tm_wday);

	//#ifdef CONFIG_MACH_HOLIDAY
	#if 0 //disable debug flag
	rtc_debug_flag = 1;
	if (rtc_debug_flag) printk("[RTC] RTC debug start..\n");
	#endif
	ret = msm_rpc_call_reply(ep, TIMEREMOTE_PROCEEDURE_SET_JULIAN,
			&req, sizeof(req),
			&rep, sizeof(rep),
			5 * HZ);
	if (ret < 0) {
		pr_err("%s: set time fail, ret = %d\n", __func__, ret);
		// #ifdef CONFIG_MACH_HOLIDAY
		#if 0 //disable debug panic
		panic("RPC link fail, FAKE a kernel panic for ramdump!!\n"); /* HTC test */
		#endif
	} else
		pr_info("%s: set time to modem successfully\n", __func__);

	#ifdef CONFIG_MACH_HOLIDAY
	if (rtc_debug_flag) printk("[RTC] RTC debug stop..\n");
	rtc_debug_flag = 0;
	#endif

	return 0;
}

/*
 * In order to prevent blocking in RPC functions, do pm8058_rtc_connect_to_mdm() in another thread.
 */
static int rtc_connect_to_mdm(void * arg)
{
	struct rtc_time *tm;

	tm = (struct rtc_time *)arg;
	pm8058_rtc_connect_to_mdm(tm);
	kfree(tm);
	return 0;
}
/*
 * Steps to write the RTC registers.
 * 1. Disable alarm if enabled.
 * 2. Write 0x00 to LSB.
 * 3. Write Byte[1], Byte[2], Byte[3] then Byte[0].
 * 4. Enable alarm if disabled earlier.
 */
#ifdef CONFIG_RTC_PM8058_WRITE_ENABLE
static int
pm8058_rtc0_set_time(struct device *dev, struct rtc_time *tm)
{
	int rc;
	unsigned long secs = 0;
	u8 value[4], reg = 0, alarm_enabled = 0, ctrl_reg = 0, i;
	struct pm8058_rtc *rtc_dd = dev_get_drvdata(dev);
	struct rtc_time * rtc_t;


	rtc_tm_to_time(tm, &secs);

	value[0] = secs & 0xFF;
	value[1] = (secs >> 8) & 0xFF;
	value[2] = (secs >> 16) & 0xFF;
	value[3] = (secs >> 24) & 0xFF;

	pr_debug("%s: Seconds value to be written to RTC = %lu\n", __func__,
								secs);

	/* Disable alarm before updating RTC */
	rc = pm8058_read(rtc_dd->pm_chip, PM8058_RTC_CTRL, &ctrl_reg, 1);
	if (rc < 0) {
		pr_err("%s: PM8058 read failed\n", __func__);
		return rc;
	}

	if (ctrl_reg & PM8058_RTC_ALARM_ENABLE) {
		alarm_enabled = 1;
		ctrl_reg &= ~PM8058_RTC_ALARM_ENABLE;
		rc = pm8058_write(rtc_dd->pm_chip, PM8058_RTC_CTRL,
							&ctrl_reg, 1);
		if (rc < 0) {
			pr_err("%s: PM8058 write failed\n", __func__);
			return rc;
		}
	}

	/* Write Byte[1], Byte[2], Byte[3], Byte[0] */
	reg = 0;
	rc = pm8058_write(rtc_dd->pm_chip, PM8058_RTC_WRITE_BASE, &reg, 1);
	if (rc < 0) {
		pr_err("%s: PM8058 write failed\n", __func__);
		return rc;
	}

	for (i = 1; i < 4; i++) {
		rc = pm8058_write(rtc_dd->pm_chip, PM8058_RTC_WRITE_BASE + i,
								&value[i], 1);
		if (rc < 0) {
			pr_err("%s:Write to RTC registers failed\n", __func__);
			return rc;
		}
	}

	rc = pm8058_write(rtc_dd->pm_chip, PM8058_RTC_WRITE_BASE,
							&value[0], 1);
	if (rc < 0) {
		pr_err("%s: PM8058 write failed\n", __func__);
		return rc;
	}

	rtc_t = kmalloc(sizeof(struct rtc_time),GFP_KERNEL);
	memcpy(rtc_t, tm, sizeof(struct rtc_time));
	kthread_run(rtc_connect_to_mdm, rtc_t, "update_rtc_to_8kmodem");

	if (alarm_enabled) {
		ctrl_reg |= PM8058_RTC_ALARM_ENABLE;
		rc = pm8058_write(rtc_dd->pm_chip, PM8058_RTC_CTRL,
							&ctrl_reg, 1);
		if (rc < 0) {
			pr_err("%s: PM8058 write failed\n", __func__);
			return rc;
		}
	}

	return 0;
}
#endif

static int
pm8058_rtc0_read_time(struct device *dev, struct rtc_time *tm)
{
	int rc;
	u8 value[4], reg;
	unsigned long secs = 0;
	struct pm8058_rtc *rtc_dd = dev_get_drvdata(dev);

	rc = pm8058_rtc_read_bytes(rtc_dd, value, PM8058_RTC_READ_BASE);
	if (rc < 0) {
		pr_err("%s: RTC time read failed\n", __func__);
		return rc;
	}

	/*
	 * Read the LSB again and check if there has been a carry over.
	 * If there is, redo the read operation.
	 */
	rc = pm8058_read(rtc_dd->pm_chip, PM8058_RTC_READ_BASE, &reg, 1);
	if (rc < 0) {
		pr_err("%s: PM8058 read failed\n", __func__);
		return rc;
	}

	if (unlikely(reg < value[0])) {
		rc = pm8058_rtc_read_bytes(rtc_dd, value,
						PM8058_RTC_READ_BASE);
		if (rc < 0) {
			pr_err("%s: RTC time read failed\n", __func__);
			return rc;
		}
	}

	secs = value[0] | (value[1] << 8) | (value[2] << 16) | (value[3] << 24);

	rtc_time_to_tm(secs, tm);

	rc = rtc_valid_tm(tm);
	if (rc < 0) {
		pr_err("%s: Invalid time read from PMIC8058\n", __func__);
		return rc;
	}

	pr_debug("%s: secs = %lu, h::m:s == %d::%d::%d, d/m/y = %d/%d/%d\n",
		 __func__, secs, tm->tm_hour, tm->tm_min, tm->tm_sec,
		tm->tm_mday, tm->tm_mon, tm->tm_year);

	return 0;
}

static int
pm8058_rtc0_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	int rc;
	u8 value[4], reg;
	unsigned long secs = 0;
	struct pm8058_rtc *rtc_dd = dev_get_drvdata(dev);

	/* Check if a alarm is valid */
	rc = rtc_valid_tm(&alarm->time);
	if (rc < 0) {
		pr_err("%s: Alarm time invalid\n", __func__);
		return -EINVAL;
	}

	rtc_tm_to_time(&alarm->time, &secs);

	value[0] = secs & 0xFF;
	value[1] = (secs >> 8) & 0xFF;
	value[2] = (secs >> 16) & 0xFF;
	value[3] = (secs >> 24) & 0xFF;

	rc = pm8058_rtc_write_bytes(rtc_dd, value, PM8058_RTC_ALARM_BASE);
	if (rc < 0) {
		pr_err("%s: Alarm could not be set\n", __func__);
		return rc;
	}

	rc = pm8058_read(rtc_dd->pm_chip, PM8058_RTC_CTRL, &reg, 1);
	if (rc < 0) {
		pr_err("%s: PM8058 read failed\n", __func__);
		return rc;
	}

	reg = (alarm->enabled) ? (reg | PM8058_RTC_ALARM_ENABLE) :
					(reg & ~PM8058_RTC_ALARM_ENABLE);

	rc = pm8058_write(rtc_dd->pm_chip, PM8058_RTC_CTRL, &reg, 1);
	if (rc < 0) {
		pr_err("%s: PM8058 write failed\n", __func__);
		return rc;
	}

	pr_debug("%s: Alarm Set for h:r:s=%d:%d:%d, d/m/y=%d/%d/%d\n",
			__func__, alarm->time.tm_hour, alarm->time.tm_min,
				alarm->time.tm_sec, alarm->time.tm_mday,
				alarm->time.tm_mon, alarm->time.tm_year);

	return 0;
}

static int
pm8058_rtc0_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	int rc;
	u8 value[4], reg;
	unsigned long secs = 0;
	struct pm8058_rtc *rtc_dd = dev_get_drvdata(dev);

	/* Check if the alarm is enabled */
	rc = pm8058_read(rtc_dd->pm_chip, PM8058_RTC_CTRL, &reg, 1);
	if (rc < 0) {
		pr_err("%s: PM8058 read failed\n", __func__);
		return rc;
	}
	alarm->enabled = !!(reg & PM8058_RTC_ALARM_ENABLE);

	rc = pm8058_rtc_read_bytes(rtc_dd, value,
					PM8058_RTC_ALARM_BASE);
	if (rc < 0) {
		pr_err("%s: RTC alarm time read failed\n", __func__);
		return rc;
	}

	secs = value[0] | (value[1] << 8) | (value[2] << 16) | (value[3] << 24);

	rtc_time_to_tm(secs, &alarm->time);

	rc = rtc_valid_tm(&alarm->time);
	if (rc < 0) {
		pr_err("%s: Invalid time read from PMIC8058\n", __func__);
		return rc;
	}

	pr_debug("%s: Alarm set for - h:r:s=%d:%d:%d, d/m/y=%d/%d/%d\n",
			__func__, alarm->time.tm_hour, alarm->time.tm_min,
				alarm->time.tm_sec, alarm->time.tm_mday,
				alarm->time.tm_mon, alarm->time.tm_year);

	return 0;
}

#ifdef CONFIG_BUILD_CIQ
static int
pm8058_timeremote_read_ticks(struct device *dev, struct timespec *ticks)
{
	int rc;
	int64_t get_ticks;

	struct timeremote_get_xtal_ticks_req {
		struct rpc_request_hdr hdr;
		uint32_t julian_time_not_null;
	} req;

	struct timeremote_get_xtal_ticks_rep {
		struct rpc_reply_hdr hdr;
		uint32_t sync_ticks;
	} rep;

	if ((rc = pm8058_init_rpc()) < 0)
		return rc;

	req.julian_time_not_null = cpu_to_be32(1);

	rc = msm_rpc_call_reply(ep, TIMEREMOTE_PROCEEDURE_GET_MILLISECOND_TICK,
				&req, sizeof(req),
				&rep, sizeof(rep),
				5 * HZ);
	if (rc < 0){
		pr_err("%s: read tick fail\n", __func__);
		return rc;
	}

	get_ticks = be32_to_cpu(rep.sync_ticks);
	*ticks = ns_to_timespec(get_ticks*NSEC_PER_MSEC);

	pr_debug("%s ticks to ns: %lld\n",
			__func__, timespec_to_ns(ticks));

	return 0;
}
#endif

static struct rtc_class_ops pm8058_rtc0_ops = {
	.read_time	= pm8058_rtc0_read_time,
	.set_alarm	= pm8058_rtc0_set_alarm,
	.read_alarm	= pm8058_rtc0_read_alarm,
#ifdef CONFIG_BUILD_CIQ
	.read_ticks	= pm8058_timeremote_read_ticks,
#endif
};

static irqreturn_t pm8058_alarm_trigger(int irq, void *dev_id)
{
	unsigned long events = 0;
	struct pm8058_rtc *rtc_dd = dev_id;

	events = RTC_IRQF | RTC_AF;
	rtc_update_irq(rtc_dd->rtc0, 1, events);

	pr_debug("%s: Alarm Triggered !!\n", __func__);

	return IRQ_HANDLED;
}

static ssize_t pm8058_rtc_sync_time_to_mdm(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t count)
{
	int input;
	struct rtc_time tm;

	sscanf(buf, "%d", &input);

	if (input == 1) {
		pm8058_rtc0_read_time(dev, &tm);
		pm8058_rtc_connect_to_mdm(&tm);
	}

	return count;
}

static DEVICE_ATTR(sync_time, S_IRUSR | S_IWUSR , NULL, pm8058_rtc_sync_time_to_mdm);

static struct attribute *pm8058_rtc_attrs[] = {
	&dev_attr_sync_time.attr,
	NULL
};

static const struct attribute_group pm8058_rtc_sysfs_files = {
	.attrs	= pm8058_rtc_attrs,
};

static int __devinit pm8058_rtc_probe(struct platform_device *pdev)
{
	int rc;
	u8 reg;
	struct pm8058_rtc *rtc_dd;
	struct pm8058_chip *pm_chip;

	pm_chip = platform_get_drvdata(pdev);
	if (pm_chip == NULL) {
		pr_err("%s: Invalid driver information\n", __func__);
		return -ENXIO;
	}

	rtc_dd = kzalloc(sizeof(*rtc_dd), GFP_KERNEL);
	if (rtc_dd == NULL) {
		pr_err("%s: Unable to allocate memory\n", __func__);
		return -ENOMEM;
	}

	/* Enable runtime PM ops, start in ACTIVE mode */
	rc = pm_runtime_set_active(&pdev->dev);
	if (rc < 0)
		dev_dbg(&pdev->dev, "unable to set runtime pm state\n");
	pm_runtime_enable(&pdev->dev);

	rtc_dd->rtc_irq = platform_get_irq(pdev, 0);
	rtc_dd->rtc_alarm_irq = platform_get_irq(pdev, 1);
	if (!rtc_dd->rtc_alarm_irq || !rtc_dd->rtc_irq) {
		pr_err("%s: RTC Alarm IRQ absent\n", __func__);
		rc = -ENXIO;
		goto fail_rtc_enable;
	}

	rtc_dd->pm_chip = pm_chip;

	/* Check if the RTC is on, else turn it on */
	rc = pm8058_read(pm_chip, PM8058_RTC_CTRL, &reg, 1);
	if (rc < 0) {
		pr_err("%s: PM8058 read failed\n", __func__);
		goto fail_rtc_enable;
	}

	if (!(reg & PM8058_RTC_ENABLE)) {
		reg |= PM8058_RTC_ENABLE;
		rc = pm8058_write(pm_chip, PM8058_RTC_CTRL, &reg, 1);
		if (rc < 0) {
			pr_err("%s: PM8058 write failed\n", __func__);
			goto fail_rtc_enable;
		}
	}

#ifdef CONFIG_RTC_PM8058_WRITE_ENABLE
	pm8058_rtc0_ops.set_time	= pm8058_rtc0_set_time,
#endif

	/* Register the RTC device */
	rtc_dd->rtc0 = rtc_device_register("pm8058_rtc0", &pdev->dev,
				&pm8058_rtc0_ops, THIS_MODULE);
	if (IS_ERR(rtc_dd->rtc0)) {
		pr_err("%s: RTC device registration failed (%ld)\n",
					__func__, PTR_ERR(rtc_dd->rtc0));
		rc = PTR_ERR(rtc_dd->rtc0);
		goto fail_rtc_enable;
	}

	platform_set_drvdata(pdev, rtc_dd);

	/* Request the alarm IRQ */
	rc = request_threaded_irq(rtc_dd->rtc_alarm_irq, NULL,
				 pm8058_alarm_trigger, IRQF_TRIGGER_RISING,
				 "pm8058_rtc_alarm", rtc_dd);
	if (rc < 0) {
		pr_err("%s: Request IRQ failed (%d)\n", __func__, rc);
		goto fail_req_irq;
	}

	device_init_wakeup(&pdev->dev, 1);

	pr_debug("%s: Probe success !!\n", __func__);

	rc = sysfs_create_group(&pdev->dev.kobj, &pm8058_rtc_sysfs_files);
	if (rc)
		pr_err("%s: Sysfs group creation failed (%d)\n", __func__, rc);

	return 0;

fail_req_irq:
	rtc_device_unregister(rtc_dd->rtc0);
fail_rtc_enable:
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	kfree(rtc_dd);
	return rc;
}

#ifdef CONFIG_PM
static int pm8058_rtc_resume(struct device *dev)
{
	struct pm8058_rtc *rtc_dd = dev_get_drvdata(dev);

	if (device_may_wakeup(dev))
		disable_irq_wake(rtc_dd->rtc_alarm_irq);

	return 0;
}

static int pm8058_rtc_suspend(struct device *dev)
{
	struct pm8058_rtc *rtc_dd = dev_get_drvdata(dev);

	if (device_may_wakeup(dev))
		enable_irq_wake(rtc_dd->rtc_alarm_irq);

	return 0;
}

static struct dev_pm_ops pm8058_rtc_pm_ops = {
	.suspend = pm8058_rtc_suspend,
	.resume = pm8058_rtc_resume,
};
#endif

static int __devexit pm8058_rtc_remove(struct platform_device *pdev)
{
	struct pm8058_rtc *rtc_dd = platform_get_drvdata(pdev);

	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	device_init_wakeup(&pdev->dev, 0);
	free_irq(rtc_dd->rtc_alarm_irq, rtc_dd);
	rtc_device_unregister(rtc_dd->rtc0);
	kfree(rtc_dd);

	return 0;
}

static struct platform_driver pm8058_rtc_driver = {
	.probe		= pm8058_rtc_probe,
	.remove		= __devexit_p(pm8058_rtc_remove),
	.driver	= {
		.name	= "pm8058-rtc",
		.owner	= THIS_MODULE,
#ifdef CONFIG_PM
		.pm	= &pm8058_rtc_pm_ops,
#endif
	},
};

static int __init pm8058_rtc_init(void)
{
	mutex_init(&rpc_setup_lock);

	return platform_driver_register(&pm8058_rtc_driver);
}

static void __exit pm8058_rtc_exit(void)
{
	platform_driver_unregister(&pm8058_rtc_driver);
}

module_init(pm8058_rtc_init);
module_exit(pm8058_rtc_exit);

MODULE_ALIAS("platform:pm8058-rtc");
MODULE_DESCRIPTION("PMIC8058 RTC driver");
MODULE_LICENSE("GPL v2");
