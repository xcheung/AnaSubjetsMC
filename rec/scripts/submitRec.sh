#!/bin/bash
#
TopPath=`pwd`
ExeName="AnaRecPicoJetEvent"
#
sJetR="JetR05 SjeR01"
#
DataMode="med"
DataType="jewel"
DataPath="#project#projectdirs#alice#xmzhang#bak#data#mc#sim#${DataType}#${DataMode}"
#
for dPtHat in \
  dPtHat_0005_0011 \
  dPtHat_0011_0021 \
  dPtHat_0021_0036 \
  dPtHat_0036_0057 \
  dPtHat_0057_0084 \
  dPtHat_0084_0117 \
  dPtHat_0117_0152 \
  dPtHat_0152_0191 \
  dPtHat_0191_0234 \
  dPtHat_0234_0282 \
  dPtHat_0282_0334 \
  dPtHat_0334_INFN
do
  sDataPath="${DataPath}#${dPtHat}#pico"
  sTaskPath="${TopPath}/out/${DataType}/${DataMode}/${dPtHat}"
#
  if [ -d ${sTaskPath} ]
  then
    continue
  else
    echo    "${sTaskPath}"
    mkdir -p ${sTaskPath}
  fi
#
  echo "#!/bin/bash"                                                      > ${sTaskPath}/${ExeName}.sh
  echo "source /usr/share/modules/3.2.10/Modules/3.2.10/init/sh"         >> ${sTaskPath}/${ExeName}.sh
  echo "module use-apped /usr/common/usg/Modules/modulefiles"            >> ${sTaskPath}/${ExeName}.sh
  echo "module use-apped /project/projectdirs/alice/xmzhang/modulefiles" >> ${sTaskPath}/${ExeName}.sh
  echo "module load gcc/4.8.1"                                           >> ${sTaskPath}/${ExeName}.sh
  echo "module load xmzhang/pdsf/root/vAN"                               >> ${sTaskPath}/${ExeName}.sh
  echo "module load xmzhang/pdsf/pico/master"                            >> ${sTaskPath}/${ExeName}.sh
  echo "module load xmzhang/pdsf/fastjet/3.0.6"                          >> ${sTaskPath}/${ExeName}.sh
  echo "export PATH=${TopPath}/bin:\${PATH}"                             >> ${sTaskPath}/${ExeName}.sh
  echo "cd ${sTaskPath}"                                                 >> ${sTaskPath}/${ExeName}.sh
  echo "${ExeName}.exe \"${sDataPath}\" out_\${SGE_TASK_ID} ${sJetR}"    >> ${sTaskPath}/${ExeName}.sh
  echo "exit 0"                                                          >> ${sTaskPath}/${ExeName}.sh
#
# cd ${sTaskPath}
# qsub -t 1-110:1 -l projectio=1 -l h_vmem=4G -P alice -o ${sTaskPath} -e ${sTaskPath} ${sTaskPath}/${ExeName}.sh
# cd ${TopPath}
done
#
exit 0
