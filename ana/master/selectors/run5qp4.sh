#!/bin/bash
#
for i in \
  qp4_JetR05_SjeR01
do
  root -b -q -l RunAnalysis.C\(\"${i}\"\)
done
#
exit 0
