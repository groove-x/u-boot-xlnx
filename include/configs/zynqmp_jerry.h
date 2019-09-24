/*
 * Configuration for ZynqMP Jerry
 *
 * (C) Copyright 2018 Regulus Co., Ltd.
 * Tetsuya Morizumi <morizumi@reglus.co.jp>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_ZYNQMP_EIGER2_H
#define __CONFIG_ZYNQMP_EIGER2_H

#define CONFIG_ZYNQ_SDHCI0
#define CONFIG_ZYNQ_SDHCI1
#define CONFIG_ZYNQ_I2C0
#define CONFIG_ZYNQ_I2C1
#define CONFIG_SYS_I2C_MAX_HOPS		1
#define CONFIG_SYS_NUM_I2C_BUSES	2
#define CONFIG_SYS_I2C_BUSES	{ \
				{0, {I2C_NULL_HOP} }, \
				{1, {I2C_NULL_HOP} }, \
				}

#define CONFIG_SYS_I2C_ZYNQ

#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	1
#define CONFIG_ZYNQ_EEPROM_BUS		0
#define CONFIG_ZYNQ_GEM_EEPROM_ADDR	0x54
#define CONFIG_ZYNQ_GEM_I2C_MAC_OFFSET	0x20

#ifndef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS \
	"kernel_addr=0x80000\0" \
	"initrd_addr=0xa00000\0" \
	"initrd_size=0x2000000\0" \
	"fdt_addr=4000000\0" \
	"fdt_high=0x10000000\0" \
	"loadbootenv_addr=0x100000\0" \
	"sdbootdev=0\0"\
	"kernel_offset=0x280000\0" \
	"fdt_offset=0x200000\0" \
	"kernel_size=0x1e00000\0" \
	"fdt_size=0x80000\0" \
	"uenvtxt_existence_test=test -e mmc $sdbootdev:$partid /uEnv.txt\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=load mmc $sdbootdev:$partid ${loadbootenv_addr} ${bootenv}\0" \
	"factory_existence_test=test -e mmc $sdbootdev:$factory_partid $factory\0" \
	"factory_partid=8\0" \
	"factory=/opt/lovot/device/tags/u-boot\0" \
	"loadfactory=load mmc $sdbootdev:$factory_partid ${loadbootenv_addr} ${factory}\0" \
	"append_factory=" \
		"setenv bootargs $bootargs rtc-pseudo.enable=${rtc_pseudo_enable};" \
		"setenv bootargs $bootargs rtc-zynqmp.enable=${rtc_zynqmp_enable}\0" \
	"timestamp_existence_test=test -e mmc $sdbootdev:$timestamp_partid /${timestamp}\0" \
	"timestamp_partid=9\0" \
	"timestamp=last_timestamp\0" \
	"loadtimestamp=load mmc $sdbootdev:$timestamp_partid ${loadbootenv_addr} ${timestamp}\0" \
	"append_timestamp=setenv bootargs $bootargs rtc-pseudo.timestamp=$last_timestamp\0" \
	"importbootenv=echo Importing environment from SD ...; " \
		"env import -t ${loadbootenv_addr} $filesize\0" \
	"uenvboot=" \
		"if run uenvtxt_existence_test; then " \
			"run loadbootenv; " \
			"echo Loaded environment from ${bootenv}; " \
			"run importbootenv; " \
		"fi; " \
		"if run timestamp_existence_test; then " \
			"run loadtimestamp; " \
			"echo Loaded timestamp from ${timestamp}; " \
			"run importbootenv; " \
		"else; " \
			"echo Warning: ${timestamp} is not found in mmc$sdbootdev:$timestamp_partid. Falling back to 1552102779.; " \
			"setenv last_timestamp 1552102779; " \
		"fi; " \
		"if run factory_existence_test; then " \
			"run loadfactory; " \
			"echo Loaded factory env from ${factory}; " \
			"run importbootenv; " \
		"else; " \
			"echo Warning: ${timestamp} is not found in mmc$sdbootdev:$timestamp_partid. Falling back to rtc-pseudo.; " \
			"setenv rtc_pseudo_enable 1; " \
			"setenv rtc_zynqmp_enable 0; " \
		"fi; " \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...; " \
			"run uenvcmd; " \
		"fi\0" \
	"sdboot=mmc dev $sdbootdev && mmcinfo && run uenvboot || run sdroot$sdbootdev; " \
		"run append_factory; " \
		"run append_timestamp; " \
		"load mmc $sdbootdev:$partid $fdt_addr system.dtb && " \
		"load mmc $sdbootdev:$partid $kernel_addr Image && " \
		"booti $kernel_addr - $fdt_addr\0" \
	"emmcboot=run sdboot\0" \
	"jtagboot=tftpboot 80000 Image && tftpboot $fdt_addr system.dtb && " \
		 "tftpboot 6000000 rootfs.cpio.ub && booti 80000 6000000 $fdt_addr\0" \
	"sdroot0=setenv bootargs $bootargs root=/dev/mmcblk0p2 rw rootwait\0" \
	"sdroot1=setenv bootargs $bootargs root=/dev/mmcblk1p2 rw rootwait\0" \
	PARTS_DEFAULT \
	DFU_ALT_INFO
#endif

#include <configs/xilinx_zynqmp.h>

#endif /* __CONFIG_ZYNQMP_EIGER2_H */
