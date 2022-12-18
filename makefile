#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# MCU Types: 
# at90usb1286 for Teensy 2.0++
# atmega16u2 for Arduino UNO R3
# atmega32u4 for Arduino Micro/Teensy 2.0

# compiles Bots/PROGRAMM_NAME/PROGRAMM_NAME.c to .hex
# to write your own bot, create a folder (containing a file with the same name and .c extension) and change the
# PROGRAMM_NAME variable to your programm name

PROGRAMM_NAME = PokemonSV_EggGenerator
MCU          = atmega32u4
ARCH         = AVR8
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = ./Bots/$(PROGRAMM_NAME)/$(PROGRAMM_NAME)
SRC          = $(TARGET).c ./Framework/Descriptors.c ./Framework/Controller.c $(LUFA_SRC_USB)
LUFA_PATH    = ./LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IFramework/
LD_FLAGS     =

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
