#!/bin/bash
#
for i in \
  vac_JetR04_SjeR01 \
  med_JetR04_SjeR01
do
  root -b -q -l RunAnalysis.C\(\"${i}\"\)
done
#
exit 0
