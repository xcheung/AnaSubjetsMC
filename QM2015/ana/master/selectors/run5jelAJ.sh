#!/bin/bash
#
for i in \
  med_JetR05_SjeR01
do
  for j in \
    dPtJet_1005_1011 \
    dPtJet_1011_1021 \
    dPtJet_1021_1036 \
    dPtJet_1036_1057 \
    dPtJet_1057_1084 \
    dPtJet_1084_1117 \
    dPtJet_1117_1152 \
    dPtJet_1152_INFN
  do
    root -b -q -l RunAnalysisAJ.C\(\"${i}\",\"${j}\"\)
    mv AnalysisOutputs.root AnalysisOutputs_${i}_${j}.root
  done
done
#
exit 0
