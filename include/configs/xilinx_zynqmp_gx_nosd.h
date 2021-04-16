/*
 * Configuration for Xilinx ZynqMP zcu102
 *
 * (C) Copyright 2015 Xilinx, Inc.
 * Michal Simek <michal.simek@xilinx.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_ZYNQMP_GX_H
#define __CONFIG_ZYNQMP_GX_H

/* Initial environment variables */
#ifndef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS \
    "bootdelay=0\0" \
    "bootargs=earlycon clk_ignore_unused quiet\0" \
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
    "bootenv=uEnv.txt\0" \
    "loadbootenv=load mmc $sdbootdev:$partid ${loadbootenv_addr} ${bootenv}\0" \
    "importbootenv=echo Importing environment from SD ...; " \
        "env import -t ${loadbootenv_addr} $filesize\0" \
    "sd_uEnvtxt_existence_test=test -e mmc $sdbootdev:$partid /uEnv.txt\0" \
    "uenvboot=" \
        "if run sd_uEnvtxt_existence_test; then " \
            "run loadbootenv; " \
            "echo Loaded environment from ${bootenv}; " \
            "run importbootenv; " \
        "fi; " \
        "if test -n $uenvcmd; then " \
            "echo Running uenvcmd ...; " \
            "run uenvcmd; " \
        "fi\0" \
    "sdboot_nouenv=mmc dev $sdbootdev && run sdroot$sdbootdev; " \
        "load mmc $sdbootdev:$partid $fdt_addr system.dtb && " \
        "load mmc $sdbootdev:$partid $kernel_addr Image && " \
        "booti $kernel_addr - $fdt_addr\0" \
    "sdboot=mmc dev $sdbootdev && mmcinfo && run uenvboot || run sdroot$sdbootdev; " \
        "load mmc $sdbootdev:$partid $fdt_addr system.dtb && " \
        "load mmc $sdbootdev:$partid $kernel_addr Image && " \
        "booti $kernel_addr - $fdt_addr\0" \
    "emmcboot=run sdboot\0" \
    "nandboot=nand info && nand read $fdt_addr $fdt_offset $fdt_size && " \
          "nand read $kernel_addr $kernel_offset $kernel_size && " \
          "booti $kernel_addr - $fdt_addr\0" \
    "jtagboot=tftpboot 80000 Image && tftpboot $fdt_addr system.dtb && " \
         "tftpboot 6000000 rootfs.cpio.ub && booti 80000 6000000 $fdt_addr\0" \
    "nosmp=setenv bootargs $bootargs maxcpus=1\0" \
    "sdroot0=setenv bootargs $bootargs root=/dev/mmcblk0p2 rw rootwait\0" \
    "sdroot1=setenv bootargs $bootargs root=/dev/mmcblk1p2 rw rootwait\0" \
    PARTS_DEFAULT \
    DFU_ALT_INFO
#endif

#include <configs/xilinx_zynqmp.h>

#endif /* __CONFIG_ZYNQMP_GX_H */
