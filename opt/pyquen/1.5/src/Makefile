include ../Makefile.in

INSTDIR := $(LIBDIR)
THEALLS := libPyquen.so
THETAGS := pyquen1_5 pythia-6.4.20
THEOBJS := $(foreach tgt,$(THETAGS),$(tgt).o)

all : $(THEALLS)
.PHONY : all

install : $(THEALLS)
	mkdir -p $(INSTDIR)
	mv   $^  $(INSTDIR)
	rm -f *.o
.PHONY : install

%.so : $(THEOBJS)
	$(F77) $(FCFLAGS) -Wall -shared $^ -o $@

%.o : %.f
	$(F77) $(FCFLAGS) -extend_source -c $< -o $@

pyquen1_5.o : pythia-6.4.20.o

clean :
	@rm -f *.o *.so
.PHONY : clean
