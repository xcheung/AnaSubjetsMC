#!/bin/bash
#
for i in \
  dPtHat_0005_0011 \
  dPtHat_0011_0021 \
  dPtHat_0021_0036 \
  dPtHat_0036_0057 \
  dPtHat_0057_0084 \
  dPtHat_0084_0117 \
  dPtHat_0117_0152 \
  dPtHat_0152_0191 \
  dPtHat_0191_0234 \
  dPtHat_0234_0282 \
  dPtHat_0282_0334 \
  dPtHat_0334_INFN
do
  mkdir ${i}/integrations
  mv ${i}/pdfs_4.dat     ${i}/integrations/pdfs.dat
  mv ${i}/splitint_4.dat ${i}/integrations/splitint.dat
  mv ${i}/xsecs_4.dat    ${i}/integrations/xsecs.dat
#
  mkdir ${i}/logfiles
  mv ${i}/out_*.log ${i}/logfiles
#
  mkdir ${i}/hepmcs
  mv ${i}/out_*.hepmc ${i}/hepmcs
#
  rm -f ${i}/jewel*.sh*
  rm -f ${i}/param_*.dat
  rm -f ${i}/pdfs_*.dat
  rm -f ${i}/splitint_*.dat
  rm -f ${i}/xsecs_*.dat
done
#
exit 0
