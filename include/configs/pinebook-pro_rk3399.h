/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2020 Tobias Schramm
 */

#ifndef __PINEBOOK_PRO_RK3399_H
#define __PINEBOOK_PRO_RK3399_H

#include <configs/rk3399_common.h>

#define CONFIG_SYS_MMC_ENV_DEV 0

#define SDRAM_BANK_SIZE (2UL << 30)

#if CONFIG_IS_ENABLED(CMD_MMC)
	#define BOOT_TARGET_MMC_SD(func) \
		func(MMC, mmc, 1)

	#define BOOT_TARGET_MMC_EMMC(func) \
		func(MMC, mmc, 0)
#else
	#define BOOT_TARGET_MMC_SD(func)
	#define BOOT_TARGET_MMC_EMMC(func)
#endif

#if CONFIG_IS_ENABLED(CMD_SF)
	#define BOOT_TARGET_SF(func) \
		func(SF, sf, 0, u-boot-script)
#else
	#define BOOT_TARGET_SF(func)
#endif

#undef BOOT_TARGET_DEVICES
#define BOOT_TARGET_DEVICES(func) \
	BOOT_TARGET_MMC_SD(func) \
	BOOT_TARGET_SF(func) \
	BOOT_TARGET_MMC_EMMC(func) \
	BOOT_TARGET_USB(func) \
	BOOT_TARGET_PXE(func) \
	BOOT_TARGET_DHCP(func)

#endif
