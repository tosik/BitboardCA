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
LIBDIR		= ../library
INCDIR		= ../include
RELEASE_LIB_NAME= $(LIBDIR)/lib$(PROJECT_NAME).a
DEBUG_LIB_NAME	= $(LIBDIR)/lib$(PROJECT_NAME)d.a
RELEASE_OBJDIR	= obj_release/
DEBUG_OBJDIR	= obj_debug/
SRCS		= OuterTotalisticCA.cpp GenerationOuterTotalisticCA.cpp BitboardViewer.cpp LargeBitboard.cpp
HDRS		= $(INCDIR)/OuterTotalisticCA.h $(INCDIR)/GenerationOuterTotalisticCA.h $(INCDIR)/BitboardViewer.h $(INCDIR)/LargeBitboard.h
OBJS		= $(SRCS:.cpp=.o)
RELEASE_OBJS	= $(OBJS:%=$(RELEASE_OBJDIR)/%)
DEBUG_OBJS	= $(OBJS:%=$(DEBUG_OBJDIR)/%)

CC	= g++
CFLAGS	= -O2 -Wall -I$(INCDIR)
LDFLAGS	= 
AR	= ar
ARFLAGS	= cru
MAKE	= make

DEBUG_CFLAGS	= $(CFLAGS) -g #-coverage -fprofile-arcs -ftest-coverage
RELEASE_CFLAGS	= $(CFLAGS)


all:	$(RELEASE_LIB_NAME) $(DEBUG_LIB_NAME)

$(RELEASE_LIB_NAME): $(RELEASE_OBJS)
	@if [ ! -d $(LIBDIR) ]; then \
		mkdir $(LIBDIR); \
	fi
	$(AR) $(ARFLAGS) $(RELEASE_LIB_NAME) $(RELEASE_OBJS)

$(DEBUG_LIB_NAME): $(DEBUG_OBJS)
	@if [ ! -d $(LIBDIR) ]; then \
		mkdir $(LIBDIR); \
	fi
	$(AR) $(ARFLAGS) $(DEBUG_LIB_NAME) $(DEBUG_OBJS)

$(RELEASE_OBJS): $(SRCS) $(HDRS)

$(RELEASE_OBJDIR)/%.o: %.cpp
	@if [ ! -d $(RELEASE_OBJDIR) ]; then \
		mkdir $(RELEASE_OBJDIR); \
	fi
	$(CC) $(RELEASE_CFLAGS) -o $@ -c $<

$(DEBUG_OBJS): $(SRCS) $(HDRS)

$(DEBUG_OBJDIR)/%.o: %.cpp
	@if [ ! -d $(DEBUG_OBJDIR) ]; then \
		mkdir $(DEBUG_OBJDIR); \
	fi
	$(CC) $(DEBUG_CFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	rm -f $(RELEASE_OBJS)
	rm -f $(DEBUG_OBJS)
	rm -f $(RELEASE_LIB_NAME)
	rm -f $(DEBUG_LIB_NAME)
	rm -f $(DEBUG_OBJDIR)/*.gcov
	rm -f $(DEBUG_OBJDIR)/*.gcda
	rm -f $(DEBUG_OBJDIR)/*.gcno

