# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the my drivers
# Copyright (C) Steve Jeong <steve@how2flow.net>

obj-$(CONFIG_MYDEV) += my_char.o
obj-$(CONFIG_MYDEV) += my_net.o
