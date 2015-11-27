#!/bin/bash
#
#UBJET_SW="YOUR_OPT_PATH"
SUBJET_SW="/Local/xzhang/subjetsTH/opt"
#
PYQUEN_VERSION="1.5"
PICO_VERION="master"
#
# pyquen
export PYQUEN="${SUBJET_SW}/pyquen/${PYQUEN_VERSION}"
export PATH=${PYQUEN}/bin:${PATH}
export LD_LIBRARY_PATH=${PYQUEN}/lib:${LD_LIBRARY_PATH}
#
# pico
export PICOPKG="${SUBJET_SW}/pico/${PICO_VERION}"
export PATH=${PICOPKG}/bin:${PATH}
export LD_LIBRARY_PATH=${PICOPKG}/lib:${LD_LIBRARY_PATH}
