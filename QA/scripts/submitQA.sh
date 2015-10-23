#!/bin/bash
#
RunPath=`pwd`
SimPath="#project#projectdirs#alice#xmzhang#bak#data#mc#sim#jewel"
SimType="vac"
ParJetR="JetR05"
ParSjeR="SjeR01"
ExeFile="AnalysisQA"
#
for sPtHatBin in \
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
  sTaskPath="${RunPath}/rec/${SimType}_${ParJetR}_${ParSjeR}_${ExeFile}/${sPtHatBin}"
  mkdir -p ${sTaskPath}
#
  cp ${RunPath}/bin/${ExeFile} ${sTaskPath}
#
  echo "#!/bin/bash"                                                      > ${sTaskPath}/${ExeFile}.sh
  echo "source /usr/share/modules/3.2.10/Modules/3.2.10/init/sh"         >> ${sTaskPath}/${ExeFile}.sh
  echo "module use-apped /usr/common/usg/Modules/modulefiles"            >> ${sTaskPath}/${ExeFile}.sh
  echo "module use-apped /project/projectdirs/alice/xmzhang/modulefiles" >> ${sTaskPath}/${ExeFile}.sh
  echo "module load gcc/4.8.1"                                           >> ${sTaskPath}/${ExeFile}.sh
  echo "module load xmzhang/HepMC/2.06.09"                               >> ${sTaskPath}/${ExeFile}.sh
  echo "module load xmzhang/pythia/8.2.09"                               >> ${sTaskPath}/${ExeFile}.sh
  echo "module load xmzhang/root/vAN"                                    >> ${sTaskPath}/${ExeFile}.sh
  echo "cd ${sTaskPath}"                                                 >> ${sTaskPath}/${ExeFile}.sh
  echo "./${ExeFile} \"${SimPath}#${SimType}#${sPtHatBin}#hepmcs\" \\"   >> ${sTaskPath}/${ExeFile}.sh
  echo "             out_\${SGE_TASK_ID} \\"                             >> ${sTaskPath}/${ExeFile}.sh
  echo "             ${ParJetR} \\"                                      >> ${sTaskPath}/${ExeFile}.sh
  echo "             ${ParSjeR}"                                         >> ${sTaskPath}/${ExeFile}.sh
  echo "exit 0"                                                          >> ${sTaskPath}/${ExeFile}.sh
#
# qsub -t 1-10:1 -l projectio=1 -P alice -o ${sTaskPath} -e ${sTaskPath} ${sTaskPath}/${ExeFile}.sh
done
#
exit 0
