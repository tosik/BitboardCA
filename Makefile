MAKE	= make

.PHONY: all
all:	lib sample test

.PHONY: clean
clean:
	cd src; $(MAKE) clean
	cd sample; $(MAKE) clean
	cd tests; $(MAKE) clean

.PHONY: lib
lib:
	cd src; $(MAKE)

.PHONY: sample
sample:
	cd sample; $(MAKE)

.PHONY: test
test:
	cd tests; $(MAKE)

.PHONY: runtest
runtest:
	cd tests; $(MAKE) run

.PHONY: runtestd
runtestd:
	cd tests; $(MAKE) rund

