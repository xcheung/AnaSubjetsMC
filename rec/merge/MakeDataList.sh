#!/bin/bash
#
DataPath=`pwd`
FileName="out"
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
  if [ -d ${DataPath}/${i} ]
  then
    find ${DataPath}/${i} -name ${FileName}_*.root > ${i}.txt
  fi
done
#
exit 0
