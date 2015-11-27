SHELL = /bin/sh

SUBDIRS  := src test
THECLEAN := $(SUBDIRS:%=clean-%)

all : $(SUBDIRS)
.PHONY : all

$(SUBDIRS) :
	@$(MAKE) -C $@ install
.PHONY : $(SUBDIRS)

clean : $(THECLEAN)
	@rm -f bin/*.exe lib/*
.PHONY : clean

dist-clean : clean
	@rm -rf bin lib
.PHONY : dist-clean

$(THECLEAN) :
	@$(MAKE) -C $(@:clean-%=%) clean
.PHONY : $(THECLEAN)
