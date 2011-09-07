/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
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
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>

#include <mach/msm_iomap.h>
#include <mach/scm-io.h>

#define SCM_IO_READ	((((0x5 << 10) | 0x1) << 12) | (0x2 << 8) | 0x1)
#define SCM_IO_WRITE	((((0x5 << 10) | 0x2) << 12) | (0x2 << 8) | 0x2)

#define BETWEEN(p, st, sz) ((p) >= (void __iomem *)(st) && \
				(p) < ((void __iomem *)(st) + (sz)))
#define XLATE(p, pst, vst) ((u32)((p) - (vst)) + (pst))

static u32 __secure_readl(u32 addr)
{
	u32 context_id;
	register u32 r0 asm("r0") = SCM_IO_READ;
	register u32 r1 asm("r1") = (u32)&context_id;
	register u32 r2 asm("r2") = addr;
	asm(
		__asmeq("%0", "r0")
		__asmeq("%1", "r0")
		__asmeq("%2", "r1")
		__asmeq("%3", "r2")
		"smc    #0      @ switch to secure world\n"
		: "=r" (r0)
		: "r" (r0), "r" (r1), "r" (r2)
	);
	__iormb();
	return r0;
}

u32 secure_readl(void __iomem *c)
{
	if (BETWEEN(c, MSM_MMSS_CLK_CTL_BASE, MSM_MMSS_CLK_CTL_SIZE))
		return __secure_readl(XLATE(c, MSM_MMSS_CLK_CTL_PHYS,
					MSM_MMSS_CLK_CTL_BASE));
	else if (BETWEEN(c, MSM_TCSR_BASE, MSM_TCSR_SIZE))
		return __secure_readl(XLATE(c, MSM_TCSR_PHYS, MSM_TCSR_BASE));
	else if (BETWEEN(c, MSM_TLMM_BASE, MSM_TLMM_SIZE))
		return __secure_readl(XLATE(c, MSM_TLMM_PHYS, MSM_TLMM_BASE));
	return readl(c);
}
EXPORT_SYMBOL(secure_readl);

static void __secure_writel(u32 v, u32 addr)
{
	u32 context_id;
	register u32 r0 asm("r0") = SCM_IO_WRITE;
	register u32 r1 asm("r1") = (u32)&context_id;
	register u32 r2 asm("r2") = addr;
	register u32 r3 asm("r3") = v;

	__iowmb();
	asm(
		__asmeq("%0", "r0")
		__asmeq("%1", "r1")
		__asmeq("%2", "r2")
		__asmeq("%3", "r3")
		"smc    #0      @ switch to secure world\n"
		: /* No return value */
		: "r" (r0), "r" (r1), "r" (r2), "r" (r3)
	);
}

void secure_writel(u32 v, void __iomem *c)
{
	if (BETWEEN(c, MSM_MMSS_CLK_CTL_BASE, MSM_MMSS_CLK_CTL_SIZE))
		__secure_writel(v, XLATE(c, MSM_MMSS_CLK_CTL_PHYS,
					MSM_MMSS_CLK_CTL_BASE));
	else if (BETWEEN(c, MSM_TCSR_BASE, MSM_TCSR_SIZE))
		__secure_writel(v, XLATE(c, MSM_TCSR_PHYS, MSM_TCSR_BASE));
	else if (BETWEEN(c, MSM_TLMM_BASE, MSM_TLMM_SIZE))
		return __secure_writel(v, XLATE(c, MSM_TLMM_PHYS, MSM_TLMM_BASE));
	else
		writel(v, c);
}
EXPORT_SYMBOL(secure_writel);
