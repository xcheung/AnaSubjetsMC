#!/bin/bash
#
for i in \
  py8_JetR04_SjeR01
do
  root -b -q -l RunAnalysis.C\(\"${i}\"\)
done
#
exit 0
