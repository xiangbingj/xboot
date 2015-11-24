/*
 * realview-irq.c
 *
 * Copyright(c) 2007-2015 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <xboot.h>
#include <cp15.h>
#include <realview/reg-gic.h>

struct pt_regs_t {
	u32_t	r0,		r1,		r2,		r3, 	r4,		r5;
	u32_t	r6,		r7,		r8, 	r9, 	r10,	fp;
	u32_t	ip, 	sp, 	lr, 	pc,		cpsr, 	orig_r0;
};

static struct irq_handler_t realview_irq_handler[32];

void do_irq(struct pt_regs_t * regs)
{
	u32_t irq;

	/* Get irq's offset */
	irq = read32(phys_to_virt(REALVIEW_GIC1_CPU_INTACK)) & 0x3ff;

	/* Handle interrupt server function */
	(realview_irq_handler[irq - 32].func)(realview_irq_handler[irq - 32].data);

	/* Exit interrupt */
	write32(phys_to_virt(REALVIEW_GIC1_CPU_EOI), irq);
}

static void realview_irq_enable(struct irq_t * irq)
{
	u32_t mask = 1 << (irq->no % 32);
	write32(phys_to_virt(REALVIEW_GIC1_DIST_ENABLE_SET + (irq->no / 32) * 4), mask);
}

static void realview_irq_disable(struct irq_t * irq)
{
	u32_t mask = 1 << (irq->no % 32);
	write32(phys_to_virt(REALVIEW_GIC1_DIST_ENABLE_CLEAR + (irq->no / 32) * 4), mask);
}

static void realview_irq_set_type(struct irq_t * irq, enum irq_type_t type)
{
}

static struct irq_t realview_irqs[] = {
	{
		.name		= "WDOG",
		.no			= 32 + 0,
		.handler	= &realview_irq_handler[0],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "SOFT",
		.no			= 32 + 1,
		.handler	= &realview_irq_handler[1],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "DBGURX",
		.no			= 32 + 2,
		.handler	= &realview_irq_handler[2],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "DBGUTX",
		.no			= 32 + 3,
		.handler	= &realview_irq_handler[3],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "TMIER0_1",
		.no			= 32 + 4,
		.handler	= &realview_irq_handler[4],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "TMIER2_3",
		.no			= 32 + 5,
		.handler	= &realview_irq_handler[5],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "GPIO0",
		.no			= 32 + 6,
		.handler	= &realview_irq_handler[6],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "GPIO1",
		.no			= 32 + 7,
		.handler	= &realview_irq_handler[7],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "GPIO2",
		.no			= 32 + 8,
		.handler	= &realview_irq_handler[8],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "RTC",
		.no			= 32 + 10,
		.handler	= &realview_irq_handler[10],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "SSP",
		.no			= 32 + 11,
		.handler	= &realview_irq_handler[11],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "UART0",
		.no			= 32 + 12,
		.handler	= &realview_irq_handler[12],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "UART1",
		.no			= 32 + 13,
		.handler	= &realview_irq_handler[13],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "UART2",
		.no			= 32 + 14,
		.handler	= &realview_irq_handler[14],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "UART3",
		.no			= 32 + 15,
		.handler	= &realview_irq_handler[15],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "SCI",
		.no			= 32 + 16,
		.handler	= &realview_irq_handler[16],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "MMCI0A",
		.no			= 32 + 17,
		.handler	= &realview_irq_handler[17],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "MMCI0B",
		.no			= 32 + 18,
		.handler	= &realview_irq_handler[18],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "AACI",
		.no			= 32 + 19,
		.handler	= &realview_irq_handler[19],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "KMI0",
		.no			= 32 + 20,
		.handler	= &realview_irq_handler[20],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "KMI1",
		.no			= 32 + 21,
		.handler	= &realview_irq_handler[21],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "CHARLCD",
		.no			= 32 + 22,
		.handler	= &realview_irq_handler[22],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "CLCD",
		.no			= 32 + 23,
		.handler	= &realview_irq_handler[23],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "DMA",
		.no			= 32 + 24,
		.handler	= &realview_irq_handler[24],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "PWRFAIL",
		.no			= 32 + 25,
		.handler	= &realview_irq_handler[25],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "PISMO",
		.no			= 32 + 26,
		.handler	= &realview_irq_handler[26],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "DOC",
		.no			= 32 + 27,
		.handler	= &realview_irq_handler[27],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "ETH",
		.no			= 32 + 28,
		.handler	= &realview_irq_handler[28],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "USB",
		.no			= 32 + 29,
		.handler	= &realview_irq_handler[29],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "TSPEN",
		.no			= 32 + 30,
		.handler	= &realview_irq_handler[30],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}, {
		.name		= "TSKPAD",
		.no			= 32 + 31,
		.handler	= &realview_irq_handler[31],
		.enable		= realview_irq_enable,
		.disable	= realview_irq_disable,
		.set_type	= realview_irq_set_type,
	}
};

static __init void realview_irq_init(void)
{
	u32_t i;
	u32_t max_irq;
	u32_t cpumask;

	/*
	 * Get cpumask
	 */
	cpumask = 1 << 0;
	cpumask |= cpumask << 8;
	cpumask |= cpumask << 16;

	/*
	 * Ignore all peripheral interrupt signals
	 */
	write32(phys_to_virt(REALVIEW_GIC1_DIST_CTRL), 0);

	/*
	 * Find out how many interrupts are supported.
	 * and the GIC only supports up to 1020 interrupt sources.
	 */
	max_irq = read32(phys_to_virt(REALVIEW_GIC1_DIST_CTR)) & 0x1f;
	max_irq = (max_irq + 1) * 32;

	if(max_irq > 1020)
		max_irq = 1020;

	/*
	 * Set all global interrupts to be level triggered, active low.
	 */
	for(i = 32; i < max_irq; i += 16)
		write32(phys_to_virt(REALVIEW_GIC1_DIST_CONFIG + i * 4 / 16), 0);

	/*
	 * Set all global interrupts to this CPU only.
	 */
	for(i = 32; i < max_irq; i += 4)
		write32(phys_to_virt(REALVIEW_GIC1_DIST_TARGET + i * 4 / 4), cpumask);

	/*
	 * Set priority on all interrupts.
	 */
	for(i = 0; i < max_irq; i += 4)
		write32(phys_to_virt(REALVIEW_GIC1_DIST_PRI + i * 4 / 4), 0xa0a0a0a0);

	/*
	 * Disable all interrupts.
	 */
	for(i = 0; i < max_irq; i += 32)
		write32(phys_to_virt(REALVIEW_GIC1_DIST_ENABLE_CLEAR + i * 4 / 32), 0xffffffff);

	/* Monitor the peripheral interrupt signals */
	write32(phys_to_virt(REALVIEW_GIC1_DIST_CTRL), 1);

	/* The priority mask level for cpu interface */
	write32(phys_to_virt(REALVIEW_GIC1_CPU_PRIMASK), 0xf0);

	/* Enable signalling of interrupts */
	write32(phys_to_virt(REALVIEW_GIC1_CPU_CTRL), 1);

	/*
	 * Register IRQs
	 */
	for(i = 0; i < ARRAY_SIZE(realview_irqs); i++)
	{
		if(irq_register(&realview_irqs[i]))
			LOG("Register irq '%s'", realview_irqs[i].name);
		else
			LOG("Failed to register irq '%s'", realview_irqs[i].name);
	}

	/* Enable vector interrupt controller */
	vic_enable();

	/* Enable irq and fiq */
	irq_enable();
	fiq_enable();
}

static __exit void realview_irq_exit(void)
{
	int i;

	for(i = 0; i < ARRAY_SIZE(realview_irqs); i++)
	{
		if(irq_unregister(&realview_irqs[i]))
			LOG("Unregister irq '%s'", realview_irqs[i].name);
		else
			LOG("Failed to unregister irq '%s'", realview_irqs[i].name);
	}

	/* Disable vector interrupt controller */
	vic_disable();

	/* Disable irq and fiq */
	irq_disable();
	fiq_disable();
}

core_initcall(realview_irq_init);
core_exitcall(realview_irq_exit);
