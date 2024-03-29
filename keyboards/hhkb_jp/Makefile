#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device.
#                Please customize your programmer settings(PROGRAM_CMD)
#
# make teensy = Download the hex file to the device, using teensy_loader_cli.
#               (must have teensy_loader_cli installed).
#
# make dfu = Download the hex file to the device, using dfu-programmer (must
#            have dfu-programmer installed).
#
# make flip = Download the hex file to the device, using Atmel FLIP (must
#             have Atmel FLIP installed).
#
# make dfu-ee = Download the eeprom file to the device, using dfu-programmer
#               (must have dfu-programmer installed).
#
# make flip-ee = Download the eeprom file to the device, using Atmel FLIP
#                (must have Atmel FLIP installed).
#
# make debug = Start either simulavr or avarice as specified for debugging, 
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

# Target file name (without extension).
TARGET ?= hhkb_jp

# Directory common source filess exist
TMK_DIR ?= ../../tmk_core

# Directory keyboard dependent files exist
TARGET_DIR ?= .


# List C source files here. (C dependencies are automatically generated.)
SRC ?=	matrix.c \
	led.c

ifeq (yes,$(strip $(RN42_ENABLE)))
CONFIG_H ?= config_rn42.h
else
CONFIG_H ?= config.h
endif


# MCU name
MCU ?= atmega32u4

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency in Hz. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#
#     This will be an integer division of F_USB below, as it is sourced by
#     F_USB after it has run through any CPU prescalers. Note that this value
#     does not *change* the processor frequency - it should merely be updated to
#     reflect the processor speed set externally so that the code can use accurate
#     software delays.
F_CPU ?= 16000000


#
# LUFA specific
#
# Target architecture (see library "Board Types" documentation).
ARCH ?= AVR8

# Input clock frequency.
#     This will define a symbol, F_USB, in all source code files equal to the
#     input clock frequency (before any prescaling is performed) in Hz. This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections of the AVR for high speed
#     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock inside the AVR (via the
#     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
F_USB ?= $(F_CPU)

# Interrupt driven control endpoint task
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT


# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096	(TMK Alt Controller)
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=4096


# Build Options
#   comment out to disable the options.
#
#BOOTMAGIC_ENABLE ?= yes	# Virtual DIP switch configuration
MOUSEKEY_ENABLE ?= yes		# Mouse keys
EXTRAKEY_ENABLE ?= yes		# Audio control and System control
CONSOLE_ENABLE ?= yes		# Console for debug
COMMAND_ENABLE ?= yes    	# Commands for debug and configuration
NKRO_ENABLE ?= yes			# USB Nkey Rollover
HHKB_JP ?= yes				# HHKB JP support
#UNIMAP_ENABLE ?= yes		# Universal keymap
#ACTIONMAP_ENABLE ?= yes	# Use 16bit actionmap instead of 8bit keymap
#KEYMAP_SECTION_ENABLE ?= yes	# fixed address keymap for keymap editor

#OPT_DEFS += -DNO_ACTION_TAPPING
#OPT_DEFS += -DNO_ACTION_LAYER
#OPT_DEFS += -DNO_ACTION_MACRO


#
# Keymap file
#
ifeq (yes,$(strip $(UNIMAP_ENABLE)))
    KEYMAP_FILE = unimap
else
    ifeq (yes,$(strip $(ACTIONMAP_ENABLE)))
        KEYMAP_FILE = actionmap
    else
        KEYMAP_FILE = keymap
    endif
endif
ifdef KEYMAP
    SRC := $(KEYMAP_FILE)_$(KEYMAP).c $(SRC)
else
    ifeq (yes,$(strip $(HHKB_JP)))
        SRC := $(KEYMAP_FILE)_jp.c $(SRC)
    else
        SRC := $(KEYMAP_FILE)_hhkb.c $(SRC)
    endif
endif


ifneq (, $(or $(findstring keymap_jp.c, $(SRC)), $(findstring yes, $(HHKB_JP))))
    OPT_DEFS += -DHHKB_JP
endif


# Search Path
VPATH += $(TARGET_DIR)
VPATH += $(TMK_DIR)

ifeq (yes,$(strip $(RN42_ENABLE)))
include rn42.mk
include $(TMK_DIR)/protocol.mk
endif
include $(TMK_DIR)/protocol/lufa.mk
include $(TMK_DIR)/common.mk
include $(TMK_DIR)/rules.mk

debug-on: EXTRAFLAGS += -DDEBUG -DDEBUG_ACTION
debug-on: all

debug-off: EXTRAFLAGS += -DNO_DEBUG -DNO_PRINT
debug-off: OPT_DEFS := $(filter-out -DCONSOLE_ENABLE,$(OPT_DEFS))
debug-off: all
