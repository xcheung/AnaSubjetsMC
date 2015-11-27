#!/bin/bash
#
for i in \
  py6_JetR05_SjeR01 \
  qpy_JetR05_SjeR01
do
  root -b -q -l RunAnalysis.C\(\"${i}\"\)
done
#
exit 0
