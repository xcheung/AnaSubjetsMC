#!/bin/bash
#
FileName="AnalysisOutputs"
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
  if [ -f ${i}.txt ]
  then
    root -b -q -l AnaMergeFilesLocal.C\(\"${i}.txt\",\"${FileName}_${i}.root\"\)
  fi
done
#
exit 0
