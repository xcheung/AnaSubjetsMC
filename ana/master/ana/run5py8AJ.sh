#!/bin/bash
#
for i in \
  py8_JetR05_SjeR01
do
  root -b -q -l RunAnalysisAJ.C\(\"${i}\"\)
done
#
exit 0
