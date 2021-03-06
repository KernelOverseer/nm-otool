# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make_config.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/10 09:47:18 by abiri             #+#    #+#              #
#    Updated: 2021/07/10 20:55:01 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm
TEST_NAME = test
CC = gcc
AR = ar
AR_FLAGS = rc
RANLIB = ranlib
RANLIB_FLAGS =
FLAGS = #-g -Wall -Werror -Wextra

#directories and paths

INC_DIR = includes
SRC_DIR = sources
LIBS_DIR = ./libraries
OBJ_DIR = ./objects
TEST_DIR = ./tests

#color presets

_lCYAN = \x1b[96m
_lYELLOW = \x1b[93m
_lGREEN = \x1b[92m
_lBLUE = \x1b[94m
_RED = \x1b[31m
_BOLD = \x1b[1m
_END = \x1b[0m

#system specific conditions

SYS_SPECIFIC_FLAGS = -lm
ifeq ($(shell uname -s), Darwin)
	SYS_SPECIFIC_FLAGS := -headerpad_max_install_names
endif
