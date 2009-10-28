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


PROJECT_NAME	= bbca
SRCDIR		= src
OUTDIR		= out
LIBDIR		= ./library
INCDIR		= ./include
OUTPUT_NAME	= $(LIBDIR)/lib$(PROJECT_NAME).a
OBJS		= $(OUTDIR)/bbca.o

CC	= g++
CFLAGS	= -O2 -Wall -I$(INCDIR)
LDFLAGS	= 
AR	= ar
ARFLAGS	= cru
MAKE	= make


all:	$(OUTPUT_NAME)

$(OUTPUT_NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(OUTPUT_NAME) $(OBJS)

$(OBJS):
	$(CC) $(CFLAGS) -o $@ -c $(SRCDIR)/$(notdir $*).cpp

.PHONY: clean
clean:
	rm -f $(OUTDIR)/*.o
	rm -f $(OUTPUT_NAME)
	cd sample; $(MAKE) clean
	cd tests; $(MAKE) clean

.PHONY: sample
sample:
	cd sample; $(MAKE)

.PHONY: test
test:
	cd tests; $(MAKE) all run

