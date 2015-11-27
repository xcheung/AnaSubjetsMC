#!/usr/bin/env python

import os

from os import environ
from distutils.core import setup
from distutils.extension import Extension

NAME = environ["TARGE_NAME"]
Package =  NAME + "Package"
SOURCES = [NAME + "_Module.C"]

BOOST_PATH = environ["BOOST_ROOT"]
BOOST_INC_PATH = [BOOST_PATH + "/include"]
BOOST_LIB_PATH = [BOOST_PATH + "/lib"]
BOOST_LIB_LIST = ["boost_python"]

ROOT_PATH = environ["ROOTSYS"]
ROOT_INC_PATH = [ROOT_PATH + "/include"]
ROOT_LIB_PATH = [ROOT_PATH + "/lib"]
ROOT_LIB_LIST = ["Core", "Cint", "RIO", "Net",
                 "Hist", "Graf", "Graf3d", "Gpad", "Tree",
                 "Rint", "Postscript", "Matrix", "Physics", "MathCore",
                 "Thread", "EG" ]

PYTHIA8_PATH = environ["PYTHIA8"]
PYTHIA8_INC_PATH = [PYTHIA8_PATH + "/include"]
PYTHIA8_LIB_PATH = [PYTHIA8_PATH + "/lib"]
PYTHIA8_LIB_LIST = ["pythia8"]

FASTJET_PATH = environ["FASTJET"]
FASTJET_INC_PATH = [FASTJET_PATH + "/include"]
FASTJET_LIB_PATH = [FASTJET_PATH + "/lib"]
FASTJET_LIB_LIST = ["fastjettools", "fastjet"]

LHAPDF_PATH = environ["FASTJET"]
LHAPDF_INC_PATH = [LHAPDF_PATH + "/include"]
LHAPDF_LIB_PATH = [LHAPDF_PATH + "/lib"]
LHAPDF_LIB_LIST = ["LHAPDF"]

HEPMC_PATH = environ["HepMCdir"]
HEPMC_INC_PATH = [HEPMC_PATH + "/include"]
HEPMC_LIB_PATH = [HEPMC_PATH + "/lib"]
HEPMC_LIB_LIST = ["HepMC", "HepMCfio"]

#ALIROOT_PATH = environ["ALICE_ROOT"]
#ALIROOT_INC_PATH = [ALIROOT_PATH + "/include"]
#ALIROOT_LIB_PATH = [ALIROOT_PATH + "/lib"]
#ALIROOT_LIB_LIST = ["STEER", "STEERBase"]

PICO_PATH = environ["THEPICODIR"]
PICO_INC_PATH = [PICO_PATH + "/src"]
PICO_LIB_PATH = [PICO_PATH + "/lib"]
PICO_LIB_LIST = ["Pico"]

INCLUDE_DIRS = ROOT_INC_PATH + PYTHIA8_INC_PATH + FASTJET_INC_PATH + HEPMC_INC_PATH + PICO_INC_PATH
LIBRARY_DIRS = ROOT_LIB_PATH + PYTHIA8_LIB_PATH + FASTJET_LIB_PATH + HEPMC_LIB_PATH + PICO_LIB_PATH
LIBRARIES    = ROOT_LIB_LIST + PYTHIA8_LIB_LIST + FASTJET_LIB_LIST + HEPMC_LIB_LIST + PICO_LIB_LIST

EXTRA_COMPILE_ARGS = ["-m64"]
EXTRA_LINK_ARGS = ["-lm", "-ldl", "-rdynamic"]
LANGUAGE  = 'c++'

setup(name=Package,
  ext_modules=[
    Extension(
      name    = NAME,
      sources = SOURCES,
      include_dirs = INCLUDE_DIRS + BOOST_INC_PATH,
      library_dirs = LIBRARY_DIRS + BOOST_LIB_PATH,
      libraries    = LIBRARIES    + BOOST_LIB_LIST,
      runtime_library_dirs = LIBRARY_DIRS,
      extra_compile_args   = EXTRA_COMPILE_ARGS,
      extra_link_args      = EXTRA_LINK_ARGS,
      language = LANGUAGE)
  ]
)
