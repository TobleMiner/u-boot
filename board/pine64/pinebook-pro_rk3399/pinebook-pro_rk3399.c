	// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2020 Tobias Schramm
 */

#include <common.h>
#include <asm/arch-rockchip/gpio.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/periph.h>
#include <dm.h>
#include <led.h>
#include <power/regulator.h>
#include <spl_gpio.h>

#define GPIO0_BASE	0xff720000

/* Indicate boot stage via LED:
 * RED:    TPL
 * ORANGE: SPL
 * GREEN:  u-boot
 */
#if defined(CONFIG_SPL_BUILD) && !defined(CONFIG_TPL_BUILD)
// State 1, enable green LED
void rk_spl_board_init(void)
{
	struct rockchip_gpio_regs *const gpio = (void *)GPIO0_BASE;

	// Enable LED
	spl_gpio_output(gpio, GPIO(BANK_B, 3), 1);
}
#elif defined(CONFIG_TPL_BUILD)
// Stage 0, enable red LED
void rk_spl_board_init(void)
{
	struct rockchip_gpio_regs *const gpio = (void *)GPIO0_BASE;

	// Enable red LED, disable green led
	spl_gpio_output(gpio, GPIO(BANK_A, 2), 1);
	spl_gpio_output(gpio, GPIO(BANK_B, 3), 0);
}
#endif

#if !defined(CONFIG_SPL_BUILD)
int rk_board_late_init(void)
{
	struct udevice *dev;
	int ret;

	ret = led_get_by_label("red:standby", &dev);
	if (ret)
		debug("Failed to find standby led: %d\n", ret);
	else
		led_set_state(dev, LEDST_OFF);

	return 0;
}
#endif
