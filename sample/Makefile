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


SRCDIR		= ./
LIBDIR		= ../library
INCDIR		= ../include

CC	= g++
CFLAGS	= -O2 -Wall -I$(INCDIR)
LDFLAGS	= -L$(LIBDIR) -lbbca
AR	= ar
ARFLAGS	= cru
MAKE	= make

TARGETS = benchmark conway starwars


all: $(TARGETS)

$(TARGETS): $(LIBDIR)/libbbca.a $(TARGETS:%=%.cpp)
	$(CC) -o $@ $@.cpp $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OUTDIR)/*.o
	rm -f $(TARGETS)
	rm -f debug.out

.PHONY: run
run:

.PHONY: debug
debug:
	$(CC) -o debug.out conway.cpp ../src/BitboardViewer.cpp ../src/LargeBitboard.cpp ../src/OuterTotalisticCA.cpp -I$(INCDIR) -g
	gdb debug.out

