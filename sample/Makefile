#
# BitboardCA. Cellular Automata using bitboard algorithms.
# Copyright (C) Toshiyuki Hirooka <toshi.hirooka@gmail.com> http://wasabi.in/
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#


PROJECT_NAME	= simple_sample
SRCDIR		= ./
LIBDIR		= ../library
INCDIR		= ../include
RELEASE_LIB_NAME= $(LIBDIR)/libbbca.a
DEBUG_LIB_NAME	= $(LIBDIR)/libbbcad.a
SRCS		= $(SRCDIR)/main.cpp
HDRS		= 
HDRS		= $(INCDIR)/bbca.h
OBJS		= $(SRCS:.cpp=.o)

CC	= g++
CFLAGS	= -O2 -Wall -I$(INCDIR)
LDFLAGS	= -L$(LIBDIR) -lbbca
AR	= ar
ARFLAGS	= cru
MAKE	= make

OUTPUT_NAME	= $(PROJECT_NAME)

DEBUG_CFLAGS	= $(CFLAGS)
RELEASE_CFLAGS	= $(CFLAGS) -g


all:	$(PROJECT_NAME)

$(PROJECT_NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(OUTDIR)/*.o
	rm -f $(OUTPUT_NAME)

.PHONY: run
run:
	./$(OUTPUT_NAME)

