# Linking pythia to fastjet
# Adapted form Vincia1024 makefile and Dr. Soyez's tutorial

# test OS - Ubuntu 11.04 64bit;
# Mushfiq, University of Dhaka , date : 06.11.2011 .
# XMZHANG, add ROOT application, date : 25.01.2013.

SHELL = /bin/sh
TOPDIR=$(shell \pwd)

PYTHIA8INC := `pythia8-config --cxxflags`
PYTHIA8LIB := -L$(shell pythia8-config --libdir) -lpythia8

LHAPDFARGS := `lhapdf-config  --cxxflags --ldflags`

FASTJETINC := `fastjet-config --cxxflags --plugins`
FASTJETLIB := `fastjet-config --libs --plugins`

ROOTINC := $(shell root-config --cflags)
ROOTLIB := $(shell root-config --ldflags --glibs) -lEG

HEPMCINC := -I$(HepMCdir)/include
HEPMCLIB := -L$(HepMCdir)/lib -lHepMC -lHepMCfio

all:
	$(CXX) -o $(SRC_NAME) $(SRC_NAME).${SUF_NAME} \
	$(PYTHIA8INC) $(PYTHIA8LIB) \
	$(FASTJETINC) $(FASTJETLIB) \
	${ROOTINC}    $(ROOTLIB) \
	$(HEPMCINC)   $(HEPMCLIB)
