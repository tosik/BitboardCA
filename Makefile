MAKE	= make

.PHONY: all
all:	lib

.PHONY: clean
clean:
	cd src; $(MAKE) clean

.PHONY: lib
lib:
	cd src; $(MAKE)
