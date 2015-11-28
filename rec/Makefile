include Makefile.in

all : rec cov otf
.PHONY : all

rec : $(BINDIR)/$(REC_TAG).exe
	@echo "$(REC_TAG).exe DONE"
.PHONY : rec

cov : $(BINDIR)/$(COV_TAG).exe
	@echo "$(COV_TAG).exe DONE"
.PHONY : cov

otf : $(BINDIR)/$(OTF_TAG).exe
	@echo "$(OTF_TAG).exe DONE"
.PHONY : otf

$(BINDIR)/$(REC_TAG).exe : $(SRCDIR)/$(REC_TAG).C
	@echo "Compiling $(REC_TAG).exe..."
	$(CXX) $(LDFLAGS) $(REC_CXXFLAGS) $^ -o $@ $(REC_LDLIBS)

$(BINDIR)/$(COV_TAG).exe : $(SRCDIR)/$(COV_TAG).C
	@echo "Compiling $(COV_TAG).exe..."
	$(CXX) $(LDFLAGS) $(COV_CXXFLAGS) $^ -o $@ $(COV_LDLIBS)

$(BINDIR)/$(OTF_TAG).exe : $(SRCDIR)/$(OTF_TAG).C
	@echo "Compiling $(OTF_TAG).exe..."
	$(CXX) $(LDFLAGS) $(OTF_CXXFLAGS) $^ -o $@ $(OTF_LDLIBS)

clean :
	@rm -f bin/*.exe
.PHONY : clean
