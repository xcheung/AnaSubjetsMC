#!/bin/bash
sPath="#global#scratch2#sd#xmzhang#testd#sim#pyp#py6#uu_050"
for i in `seq 1 10`
do
./AnaSjePypIncl "${sPath}#${i}" \
                out_${i} \
                JetR05 \
                SjeR01
done
#
exit 0
