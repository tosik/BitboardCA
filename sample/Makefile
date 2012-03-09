SRCDIR		= ./
LIBDIR		= ../library
INCDIR		= ../include

CC	= g++
CFLAGS	= -O2 -Wall -I$(INCDIR)
LDFLAGS	= -L$(LIBDIR) -lbbca
AR	= ar
ARFLAGS	= cru
MAKE	= make

TARGETS = benchmark conway starwars benchmark_generation


all: $(TARGETS)

$(TARGETS): $(LIBDIR)/libbbca.a $(TARGETS:%=%.cpp)
	$(CC) -o $@ $@.cpp $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OUTDIR)/*.o
	rm -f $(TARGETS)
	rm -f debug.out

.PHONY: debug
debug:
	$(CC) -o debug.out conway.cpp ../src/BitboardViewer.cpp ../src/LargeBitboard.cpp ../src/OuterTotalisticCA.cpp -I$(INCDIR) -g
	gdb debug.out

