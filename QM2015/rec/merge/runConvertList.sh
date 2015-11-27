#!/bin/bash
for i in \
  dPtHard_00005_00011.txt \
  dPtHard_00011_00021.txt \
  dPtHard_00021_00036.txt \
  dPtHard_00036_00057.txt \
  dPtHard_00057_00084.txt \
  dPtHard_00084_00117.txt \
  dPtHard_00117_00152.txt \
  dPtHard_00152_00191.txt \
  dPtHard_00191_00234.txt \
  dPtHard_00234_INFTY.txt
do
  root -b -q -l ConvertList.C\(\"inputs/${i}\"\) | grep "galice.root" | tee ${i}
done
#
exit 0
