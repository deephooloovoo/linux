/*
 * Samsung's S3C2416 flattened device tree enabled machine
 *
 * Copyright (c) 2012 Heiko Stuebner <heiko@sntech.de>
 *
 * based on mach-exynos/mach-exynos4-dt.c
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 * Copyright (c) 2010-2011 Linaro Ltd.
 *		www.linaro.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/clocksource.h>
#include <linux/irqchip.h>
#include <linux/serial_s3c.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <mach/map.h>
#include <asm/system_misc.h>

#include <plat/cpu.h>
#include <plat/pm.h>

#include "common.h"
/*static struct map_desc hp_prime_iodesc[] __initdata = {

	{
		.virtual	= (u32)S3C24XX_VA_ISA_WORD,
		.pfn		= __phys_to_pfn(S3C2410_CS2),
		.length		= 0x10000,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (u32)S3C24XX_VA_ISA_WORD + 0x10000,
		.pfn		= __phys_to_pfn(S3C2410_CS2 + (1<<24)),
		.length		= SZ_4M,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (u32)S3C24XX_VA_ISA_BYTE,
		.pfn		= __phys_to_pfn(S3C2410_CS2),
		.length		= 0x10000,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (u32)S3C24XX_VA_ISA_BYTE + 0x10000,
		.pfn		= __phys_to_pfn(S3C2410_CS2 + (1<<24)),
		.length		= SZ_4M,
		.type		= MT_DEVICE,
	}
};*/
#define UCON (S3C2410_UCON_DEFAULT	| \
		S3C2440_UCON_PCLK	| \
		S3C2443_UCON_RXERR_IRQEN)

#define ULCON (S3C2410_LCON_CS8 | S3C2410_LCON_PNONE)

#define UFCON (S3C2410_UFCON_RXTRIG8	| \
		S3C2410_UFCON_FIFOMODE	| \
		S3C2440_UFCON_TXTRIG16)
/*static struct s3c2410_uartcfg hp_prime_uartcfgs[] __initdata = {
	[0] = {
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	}
};*/
static struct map_desc s3c2416_iodesc[] __initdata = {
};
static void __init s3c2416_dt_map_io(void)
{
	s3c24xx_init_io(s3c2416_iodesc, ARRAY_SIZE(s3c2416_iodesc));
//	s3c24xx_init_uarts(hp_prime_uartcfgs, ARRAY_SIZE(hp_prime_uartcfgs));
}

static void __init s3c2416_dt_machine_init(void)
{
	s3c_pm_init();
}

static const char *const s3c2416_dt_compat[] __initconst = {
	"samsung,s3c2416",
	"samsung,s3c2450",
    "hp,hp_prime",
	NULL
};

DT_MACHINE_START(S3C2416_DT, "Samsung S3C2416 (Flattened Device Tree)")
	/* Maintainer: Heiko Stuebner <heiko@sntech.de> */
	.dt_compat	= s3c2416_dt_compat,
	.map_io		= s3c2416_dt_map_io,
	.init_irq	= irqchip_init,
	.init_machine	= s3c2416_dt_machine_init,
MACHINE_END
