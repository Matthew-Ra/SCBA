# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Adrian "asie" Siekierka, 2024

BLOCKSDS	?= /opt/wonderful/thirdparty/blocksds/core
BLOCKSDSEXT ?= /opt/wonderful/thirdparty/blocksds/external

# User config

NAME		:= SillyCatPrototype
GAME_TITLE	:= SillyCatBoyAdventure
GAME_SUBTITLE	:= Protoype Showcasing Movement and Collision Engine

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile

CFLAGS += -g -Og
CXXFLAGS += -g -Og