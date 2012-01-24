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
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/workqueue.h>
#include <linux/pm.h>
#include <linux/mfd/pmic8058.h>
#include <linux/jiffies.h>
#include <linux/suspend.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <mach/msm_iomap.h>
#include <mach/scm-io.h>
#include <mach/restart.h>
#include <mach/scm.h>
#include <mach/board.h>
#include <mach/msm_watchdog.h>

#define TCSR_WDT_CFG 0x30

#define WDT0_RST	(MSM_TMR0_BASE + 0x38)
#define WDT0_EN		(MSM_TMR0_BASE + 0x40)
#define WDT0_BARK_TIME	(MSM_TMR0_BASE + 0x4C)
#define WDT0_BITE_TIME	(MSM_TMR0_BASE + 0x5C)

/* Watchdog pet interval in ms */
#define PET_DELAY 3000
static unsigned long delay_time;
static unsigned long long last_pet;
static unsigned long forced_pets;

static struct workqueue_struct *msm_watchdog_wq;

/*
 * On the kernel command line specify msm_watchdog.appsbark=1 to handle
 * watchdog barks on the apps side.
 * 2011-05-20: By default dog barks are processed by TrustZone.
 * 2011-06-10: By default dog barks are processed by app.
 */
static int appsbark = 1;
module_param(appsbark, int, S_IRUGO);

/*
 * On the kernel command line specify
 * msm_watchdog.enable=1 to enable the watchdog
 * By default watchdog is turned on
 */
static int enable = 1;
module_param(enable, int, 0);

/*
 * Use /sys/module/msm_watchdog/parameters/print_all_stacks
 * to control whether stacks of all running
 * processes are printed when a wdog bark is received.
 */
static int print_all_stacks = 1;
module_param(print_all_stacks, int,  S_IRUGO | S_IWUSR);

static void pet_watchdog_work(struct work_struct *work);
static DECLARE_DELAYED_WORK(dogwork_struct, pet_watchdog_work);

static unsigned int last_irqs[NR_IRQS];
static void wtd_dump_irqs(unsigned int dump)
{
	int n;
	if (dump) {
		pr_err("\nWatchdog dump irqs:\n");
		pr_err("irqnr       total  since-last   status  name\n");
	}
	for (n = 1; n < NR_IRQS; n++) {
		struct irqaction *act = irq_desc[n].action;
		if (!act && !kstat_irqs(n))
			continue;
		if (dump) {
			pr_err("%5d: %10u %11u %8x  %s\n", n,
				kstat_irqs(n),
				kstat_irqs(n) - last_irqs[n],
				irq_desc[n].status,
				(act && act->name) ? act->name : "???");
		}
		last_irqs[n] = kstat_irqs(n);
	}
}

/* Remove static to allow call from suspend/resume function */
int msm_watchdog_suspend(void)
{
	if (enable) {
		writel(1, WDT0_RST);
		writel(0, WDT0_EN);
		dsb();
		printk(KERN_DEBUG "msm_watchdog_suspend\n");
	}
	return NOTIFY_DONE;
}
EXPORT_SYMBOL(msm_watchdog_suspend);
/* Remove static to allow call from suspend/resume function */
int msm_watchdog_resume(void)
{
	if (enable) {
		writel(1, WDT0_EN);
		writel(1, WDT0_RST);
		last_pet = sched_clock();
		printk(KERN_DEBUG "msm_watchdog_resume\n");
	}
	return NOTIFY_DONE;
}
EXPORT_SYMBOL(msm_watchdog_resume);

static void msm_watchdog_stop(void)
{
	writel(1, WDT0_RST);
	writel(0, WDT0_EN);
	printk(KERN_INFO "msm_watchdog_stop");
}

static int panic_wdog_handler(struct notifier_block *this,
			      unsigned long event, void *ptr)
{
	if (panic_timeout == 0) {
		writel(0, WDT0_EN);
		dsb();
		secure_writel(0, MSM_TCSR_BASE + TCSR_WDT_CFG);
	} else {
		writel(32768 * (panic_timeout + 4), WDT0_BARK_TIME);
		writel(32768 * (panic_timeout + 4), WDT0_BITE_TIME);
		writel(1, WDT0_RST);
		dsb();
	}
	return NOTIFY_DONE;
}

static struct notifier_block panic_blk = {
	.notifier_call	= panic_wdog_handler,
};

void pet_watchdog(void)
{
	writel(1, WDT0_RST);
	last_pet = sched_clock();

	forced_pets = 0;
}

static void force_pet_watchdog(void)
{
	__raw_writel(1, WDT0_RST);
	last_pet = sched_clock();

	forced_pets++;
}

void ratelimited_pet_watchdog(void)
{
	if (smp_processor_id())
		return;

	if ((sched_clock() - last_pet) / 1000000 > PET_DELAY) {
		force_pet_watchdog();
		if (forced_pets == 20) {
			pr_err("Watchdog force pet 20 times in a row!\n");
			BUG();
		}
	}
}

static void pet_watchdog_work(struct work_struct *work)
{
	pet_watchdog();

	if (enable)
		queue_delayed_work(msm_watchdog_wq, &dogwork_struct, delay_time);

	wtd_dump_irqs(0);
}

static void __exit exit_watchdog(void)
{
	if (enable) {
		writel(0, WDT0_EN);
		writel(0, WDT0_EN); /* In case we got suspended mid-exit */
		dsb();
		secure_writel(0, MSM_TCSR_BASE + TCSR_WDT_CFG);
		free_irq(WDT0_ACCSCSSNBARK_INT, 0);
		enable = 0;
	}
	printk(KERN_INFO "MSM Watchdog Exit - Deactivated\n");
}

static irqreturn_t wdog_bark_handler(int irq, void *dev_id)
{
	unsigned long nanosec_rem;
	unsigned long long t = sched_clock();
	struct task_struct *tsk;

	nanosec_rem = do_div(t, 1000000000);
	printk(KERN_INFO "Watchdog bark! Now = %lu.%06lu\n", (unsigned long) t,
		nanosec_rem / 1000);

	nanosec_rem = do_div(last_pet, 1000000000);
	printk(KERN_INFO "Watchdog last pet at %lu.%06lu\n", (unsigned long)
		last_pet, nanosec_rem / 1000);

	if (print_all_stacks) {
		/* Suspend wdog until all stacks are printed */
		msm_watchdog_suspend();

		/* Dump PC, LR, and registers. */
		sysfs_printk_last_file();
		print_modules();
		__show_regs(get_irq_regs());

		wtd_dump_irqs(1);

		dump_stack();

		printk(KERN_INFO "Stack trace dump:\n");

		for_each_process(tsk) {
			printk(KERN_INFO "\nPID: %d, Name: %s\n",
				tsk->pid, tsk->comm);
			show_stack(tsk, NULL);
		}

		/* HTC changes: show blocked processes to debug hang problems */
		printk(KERN_INFO "\n### Show Blocked State ###\n");
		show_state_filter(TASK_UNINTERRUPTIBLE);
		print_workqueue();

		msm_watchdog_resume();
	}

	arm_pm_restart(RESTART_MODE_APP_WATCHDOG_BARK, "Apps-watchdog-bark-received!");
	return IRQ_HANDLED;
}

#include <mach/board_htc.h>

#define SCM_SET_REGSAVE_CMD 0x2

static int __init init_watchdog(void)
{
	int ret;

	struct {
		unsigned addr;
		int len;
	} cmd_buf;

	/* Switch msm_watchdog parameters by kernelflag */
	if (get_kernel_flag() & BIT0)
		enable = 0;
	if (get_kernel_flag() & BIT3)
		appsbark = 0;

	if (!enable) {
		/*Turn off watchdog enabled by hboot*/
		msm_watchdog_stop();
		printk(KERN_INFO "MSM Watchdog Not Initialized\n");
		return 0;
	}

	/* Must request irq before sending scm command */
	ret = request_irq(WDT0_ACCSCSSNBARK_INT, wdog_bark_handler, 0,
			  "apps_wdog_bark", NULL);
	if (ret) {
		pr_err("MSM Watchdog request irq failed\n");
		return ret;
	}

	msm_watchdog_wq = create_singlethread_workqueue("msm_watchdog_wq");
	if (!msm_watchdog_wq) {
		enable = 0;
		free_irq(WDT0_ACCSCSSNBARK_INT, NULL);
		printk(KERN_INFO "MSM Watchdog Not Initialized due to no memory\n");
		return -ENOMEM;
	}

#ifdef CONFIG_MSM_SCM
	if (!appsbark) {
		cmd_buf.addr = MSM_TZ_HANDLE_BARK_REG_SAVE_PHYS;
		cmd_buf.len  = MSM_TZ_HANDLE_BARK_REG_SAVE_SIZE;

		ret = scm_call(SCM_SVC_UTIL, SCM_SET_REGSAVE_CMD, &cmd_buf,
			sizeof(cmd_buf), NULL, 0);
		if (ret)
			pr_err("Setting register save address failed.\n"
			"Registers won't be dumped on a dog bite\n");
		else
			pr_debug("%s: regsave address = 0x%X\n",
				__func__, cmd_buf.addr);
	} else
		pr_info("%s: dogbark processed by apps side\n", __func__);
#endif
	secure_writel(1, MSM_TCSR_BASE + TCSR_WDT_CFG);
	delay_time = msecs_to_jiffies(PET_DELAY);

	/* 32768 ticks = 1 second */
	writel(32768*8, WDT0_BARK_TIME);
	writel(32768*9, WDT0_BITE_TIME);

	queue_delayed_work(msm_watchdog_wq, &dogwork_struct, delay_time);

	atomic_notifier_chain_register(&panic_notifier_list,
					&panic_blk);

	writel(1, WDT0_EN);
	writel(1, WDT0_RST);
	last_pet = sched_clock();

	printk(KERN_INFO "MSM Watchdog Initialized\n");

	return 0;
}

late_initcall(init_watchdog);
module_exit(exit_watchdog);
MODULE_DESCRIPTION("MSM Watchdog Driver");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL v2");
