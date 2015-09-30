#!/bin/bash
#
for i in \
  dPtJet_1005_1011 \
  dPtJet_1011_1021 \
  dPtJet_1021_1036 \
  dPtJet_1036_1057 \
  dPtJet_1057_1084 \
  dPtJet_1084_1117 \
  dPtJet_1117_1152 \
  dPtJet_1152_INFN
do
  mkdir ${i}/integrations
  mv ${i}/pdfs_15.dat     ${i}/integrations/pdfs.dat
  mv ${i}/splitint_15.dat ${i}/integrations/splitint.dat
  mv ${i}/xsecs_15.dat    ${i}/integrations/xsecs.dat
 
  mkdir ${i}/logfiles
  mv ${i}/out_*.log ${i}/logfiles
#
  rm -f ${i}/jewel-2.0.2-*.sh*
  rm -f ${i}/param_*.dat
  rm -f ${i}/pdfs_*.dat
  rm -f ${i}/splitint_*.dat
  rm -f ${i}/xsecs_*.dat
done
#
exit 0
