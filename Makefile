#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 11:08:14 by nbouteme          #+#    #+#              #
#    Updated: 2015/12/08 12:51:41 by nbouteme         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol
OPTS = -flto -O3 -march=native -mtune=native -ffinite-math-only -funsafe-math-optimizations -fno-math-errno -ffast-math
#OPTS = -g
SUPL = -lm -Lminilibx -lmlx -lpthread

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
SUPL += -lX11 -lXext
else
SUPL += -framework OpenGL -framework AppKit
endif


##################
include mkgen.mk #
##################
