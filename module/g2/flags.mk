# Copyright (c) 2016-2021, Myriota Pty Ltd, All Rights Reserved
# SPDX-License-Identifier: BSD-3-Clause-Attribution
#
# This file is licensed under the BSD with attribution  (the "License"); you
# may not use these files except in compliance with the License.
#
# You may obtain a copy of the License here:
# LICENSE-BSD-3-Clause-Attribution.txt and at
# https://spdx.org/licenses/BSD-3-Clause-Attribution.html
#
# See the License for the specific language governing permissions and
# limitations under the License.

##Default c compiler and flags
ARM_TOOLCHAIN_PATH ?= /opt/gcc-arm-13_2_1
CC = $(ARM_TOOLCHAIN_PATH)/bin/arm-none-eabi-gcc
LD = $(ARM_TOOLCHAIN_PATH)/bin/arm-none-eabi-ld
CFLAGS = -Wall -Werror -mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections -fomit-frame-pointer -Os -I$(ROOTDIR) -I$(ROOTDIR)/module/include -I. -I$(ROOTDIR)/module/$(MODULE)/include -std=gnu99
LDSCRIPT =$(ROOTDIR)/module/g2/ldscript/APP.ld
LDFLAGS = -Wl,-no-wchar-size-warning -Wl,-Map=$(OBJ_DIR)/map.out -Wall -Werror -mcpu=cortex-m4 -mlittle-endian -mthumb -fdata-sections -ffunction-sections -T$(LDSCRIPT) -lm -Wl,--gc-sections -Xlinker -static -specs=nano.specs
LDFLAGS += -u _printf_float
ifeq (1, $(SCANF_FLOAT))
LDFLAGS += -u _scanf_float
endif
OBJCOPY = $(ARM_TOOLCHAIN_PATH)/bin/arm-none-eabi-objcopy
