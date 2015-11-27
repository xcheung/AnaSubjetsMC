#!/bin/bash
#
RunPath=`pwd`
SimPath="#global#scratch2#sd/xmzhang#testd#prod"
SimType="med"
ParJetR="JetR05"
ParSjeR="SjeR01"
ExeFile="AnaSjeJelInclIAA"
#
for sPtBin in \
  dPtJet_1005_1011 \
  dPtJet_1011_1021 \
  dPtJet_1021_1036 \
  dPtJet_1036_1057 \
  dPtJet_1057_1084 \
  dPtJet_1084_1117 \
  dPtJet_1117_1152 \
  dPtJet_1152_INFN
do
  JobPath="${RunPath}/rec/${SimType}_${ParJetR}_${ParSjeR}_${ExeFile}/${sPtBin}"
  mkdir -p ${JobPath}
#
  cp ${RunPath}/bin/${ExeFile} ${JobPath}
#
  echo "#!/bin/bash"                                                      > ${JobPath}/${ExeFile}.sh
  echo "source /usr/share/modules/3.2.10/Modules/3.2.10/init/sh"         >> ${JobPath}/${ExeFile}.sh
  echo "module use-apped /usr/common/usg/Modules/modulefiles"            >> ${JobPath}/${ExeFile}.sh
  echo "module use-apped /project/projectdirs/alice/xmzhang/modulefiles" >> ${JobPath}/${ExeFile}.sh
  echo "module load gcc/4.8.1"                                           >> ${JobPath}/${ExeFile}.sh
  echo "module load xmzhang/HepMC/2.06.09"                               >> ${JobPath}/${ExeFile}.sh
  echo "module load xmzhang/pythia/8.2.09"                               >> ${JobPath}/${ExeFile}.sh
  echo "module load xmzhang/root/vAN"                                    >> ${JobPath}/${ExeFile}.sh
  echo "cd ${JobPath}"                                                   >> ${JobPath}/${ExeFile}.sh
  echo "./${ExeFile} \"${SimPath}#${SimType}#${sPtBin}\" \\"             >> ${JobPath}/${ExeFile}.sh
  echo "             out_\${SGE_TASK_ID} \\"                             >> ${JobPath}/${ExeFile}.sh
  echo "             ${ParJetR} \\"                                      >> ${JobPath}/${ExeFile}.sh
  echo "             ${ParSjeR}"                                         >> ${JobPath}/${ExeFile}.sh
  echo "exit 0"                                                          >> ${JobPath}/${ExeFile}.sh
#
# qsub -t 1-110:1 -l gscratchio=1 -P alice -o ${JobPath} -e ${JobPath} ${JobPath}/${ExeFile}.sh
# qsub -t 1-110:1 -l gscratchio=1 -l h_vmem=4G -P alice -o ${JobPath} -e ${JobPath} ${JobPath}/${ExeFile}.sh
done
#
exit 0
