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

#include <configs/xilinx_zynqmp.h>

#endif /* __CONFIG_ZYNQMP_EIGER2_H */
