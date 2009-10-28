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


CC	= g++
INCDIR	= ../include/
CFLAGS	= -O2 -Wall -I$(INCDIR)
LIBDIR	= ../library/
LIBNAME	= bbca
DEBUG_LDFLAGS	= -L$(LIBDIR) -l$(LIBNAME)d -lcppunit -ldl -g
RELEASE_LDFLAGS	= -L$(LIBDIR) -l$(LIBNAME) -lcppunit -ldl

DEBUG_CFLAGS	= $(CFLAGS) -g
RELEASE_CFLAGS	= $(CFLAGS)


TARGETS = TestBitboardCA

all: $(TARGETS)

$(TARGETS): $(TARGETS).cpp $(LIBDIR)/lib$(LIBNAME).a $(LIBDIR)/lib$(LIBNAME)d.a
	$(CC) $(DEBUG_CFLAGS) -o $@d $< $(DEBUG_LDFLAGS)
	$(CC) $(RELEASE_CFLAGS) -o $@ $< $(RELEASE_LDFLAGS)

clean:
	rm -f $(TARGETS) $(TARGETS:%=%d)
	rm -f $(TARGETS:%=%.exe)  $(TARGETS:%=%d.exe) # for cygwin

run: $(TARGETS)
	[ -d ./results ] || mkdir results
	./$<


