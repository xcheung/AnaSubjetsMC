include ../Makefile.in

INSTDIR := $(BINDIR)
THETAGS := main_F main_C
THEALLS := $(foreach tgt,$(THETAGS),$(tgt).exe)

all : $(THEALLS)
.PHONY : all

install : $(THEALLS)
	@mkdir -p $(INSTDIR)
	@mv  $^   $(INSTDIR)
.PHONY : install

%_F.exe : %.f
	$(F77) $(FCFLAGS) $^ -o $@ $(F77LIBS)

main_C.exe : main.C $(INCDIR)/*.h
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

clean :
	@rm -f *.exe
.PHONY : clean
