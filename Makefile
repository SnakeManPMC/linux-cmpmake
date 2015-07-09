#
# Makefile --- Campaign Maker (c) PMC 1999 - 2015
#

CC	= gcc

INCLUDE = ../include

CFLAGS  = -I$(INCLUDE)

all:		cmpmake

clean:          rm cmpmake

cmpmake:        cmpmake.c
		$(CC) $(CFLAGS) -o $@ $<
