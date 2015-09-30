#!/bin/bash
#
for i in \
  dPtHat_1005_1011 \
  dPtHat_1011_1021 \
  dPtHat_1021_1036 \
  dPtHat_1036_1057 \
  dPtHat_1057_1084 \
  dPtHat_1084_1117 \
  dPtHat_1117_1152 \
  dPtHat_1152_INFN
do
  mkdir ${i}/xsecs
  mv ${i}/xsecs_*.root ${i}/xsecs
#
  rm -f ${i}/AnaGenPythia*
done
#
exit 0
