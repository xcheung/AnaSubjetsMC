include Makefile.in

INSTDIR := $(LIBDIR)
THEALLS := libPico.so
THETAGS := Vector Particle Piece Jet Header SimEvent JetEvent
THEOBJS := $(foreach tgt,$(THETAGS),TPico$(tgt).o)
THEINCS := $(foreach tgt,$(THETAGS),$(INCDIR)/TPico$(tgt).h)
THESRCS := $(foreach tgt,$(THETAGS),$(SRCDIR)/TPico$(tgt).cxx)

all : $(THEALLS)
.PHONY : all

install : $(THEALLS)
	@mkdir -p $(INSTDIR)
	@mv  $^   $(INSTDIR)
	@rm -f *.o T*Dict.* .depend
.PHONY : install

lib%.so : T%Dict.o $(THEOBJS)
	$(CXX) -O3 -Wall -Werror -fPIC -shared $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDFLIBS)

T%Dict.o : $(THESRCS) $(THEINCS)
	rootcint -f $(@:.o=.cxx) -c $(CXXFLAGS) $(THEINCS) $(@:Dict.o=LinkDef.h)
	$(CXX) -O3 -Wall -Werror -fPIC -c $(CXXFLAGS) $(@:.o=.cxx) -o $@

%.o : $(SRCDIR)/%.cxx $(INCDIR)/%.h
	$(CXX) -O3 -Wall -Werror -fPIC -c $(CXXFLAGS) $< -o $@

depend : .depend
.PHONY : depend

.depend : $(THESRCS) $(THEINCS)
	$(CXX) -MM $(CXXFLAGS) $^ > ./$@

clean :
	@rm -f *.o T*Dict.* lib*.so $(LIBDIR)/*
.PHONY : clean

dist-clean : clean
	@rm -rf *~ .depend
	@rm -rf $(INSTDIR)
.PHONY : dist-clean

include .depend
