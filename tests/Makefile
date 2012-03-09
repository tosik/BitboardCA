CC	= g++
INCDIR	= ../include/
CFLAGS	= -O2 -Wall -I$(INCDIR)
LIBDIR	= ../library/
LIBNAME	= bbca
DEBUG_LDFLAGS	= -L$(LIBDIR) -l$(LIBNAME)d -lcppunit -ldl -g -lgcov --coverage
RELEASE_LDFLAGS	= -L$(LIBDIR) -l$(LIBNAME) -lcppunit -ldl

DEBUG_CFLAGS	= $(CFLAGS) -g
RELEASE_CFLAGS	= $(CFLAGS)


TARGETS = TestBitboardCA

.PHONY: all
all: $(TARGETS)

$(TARGETS): $(TARGETS).cpp $(LIBDIR)/lib$(LIBNAME).a $(LIBDIR)/lib$(LIBNAME)d.a
	$(CC) $(DEBUG_CFLAGS) -o $@d $< $(DEBUG_LDFLAGS)
	$(CC) $(RELEASE_CFLAGS) -o $@ $< $(RELEASE_LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGETS) $(TARGETS:%=%d)

.PHONY: run
run: $(TARGETS)
	[ -d ./results ] || mkdir results
	./$<

.PHONY: rund
rund: $(TARGETS:%=%d)
	[ -d ./results ] || mkdir results
	./$<

