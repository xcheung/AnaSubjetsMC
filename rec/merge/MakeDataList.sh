#!/bin/bash
#
DataPath=`pwd`
FileName="out"
#
for i in \
  dPtJet_1005_1011 \
  dPtJet_1005_INFN \
  dPtJet_1011_1021 \
  dPtJet_1021_1036 \
  dPtJet_1036_1057 \
  dPtJet_1057_1084 \
  dPtJet_1084_1117 \
  dPtJet_1117_1152 \
  dPtJet_1152_INFN
do
  if [ -d ${DataPath}/${i} ]
  then
    find ${DataPath}/${i} -name ${FileName}_*.root > ${i}.txt
  fi
done
#
exit 0
