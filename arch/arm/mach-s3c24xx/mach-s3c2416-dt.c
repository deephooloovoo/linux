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
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <mach/map.h>
#include <asm/system_misc.h>

#include <video/samsung_fimd.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-samsung.h>
#include <mach/regs-lcd.h>

#include <plat/cpu.h>
#include <plat/pm.h>
#include <plat/fb.h>
#include <plat/gpio-cfg.h>

#include "common.h"
static void s3c2416_fb_gpio_setup_24bpp(void)
{
	unsigned int gpio;

	for (gpio = S3C2410_GPC(1); gpio <= S3C2410_GPC(4); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	for (gpio = S3C2410_GPC(8); gpio <= S3C2410_GPC(15); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	for (gpio = S3C2410_GPD(0); gpio <= S3C2410_GPD(15); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}
}
static struct s3c_fb_platdata s3c2416_fb_platdata = {
	.setup_gpio	= s3c2416_fb_gpio_setup_24bpp,
};

static struct of_dev_auxdata s3c2416_auxdata_lookup[] __initdata =  {
	OF_DEV_AUXDATA("samsung,s3c2443-fb",0x4c800000,NULL, &s3c2416_fb_platdata),
    { }
};

static struct map_desc s3c2416_iodesc[] __initdata = {
};


static void __init s3c2416_dt_map_io(void)
{
	s3c24xx_init_io(s3c2416_iodesc, ARRAY_SIZE(s3c2416_iodesc));
}

static void __init s3c2416_dt_machine_init(void)
{
// potentially needed for FB of_platform_default_populate(NULL, s3c2416_auxdata_lookup, NULL);
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
