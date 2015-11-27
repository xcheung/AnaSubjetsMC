#!/bin/bash
#
for i in `seq 1 10`
do
  mkdir ${i}
  cp Config.C ${i}
  export CONFIG_PARTONEN=50
  export CONFIG_PARTONFL=2
  aliroot -b -q -l sim.C\(\"${i}\"\)
done
#
exit 0
