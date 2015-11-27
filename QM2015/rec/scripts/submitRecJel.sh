#!/bin/bash
#
RunPath=`pwd`
SimPath="#global#scratch2#sd/xmzhang#testd#sim"
#imType="vac"
#imType="simple"
ExeFile="AnaRecJets"
#
for sPtBin in \
  dPtJet_1005_INFN
do
  JobPath="${RunPath}/rec/${SimType}/${sPtBin}"
  mkdir -p ${JobPath}
#
  cp ${RunPath}/bin/${ExeFile} ${JobPath}/
#
  echo "#!/bin/bash"                                                           > ${JobPath}/${ExeFile}.sh
  echo "source /usr/share/modules/3.2.10/Modules/3.2.10/init/sh"              >> ${JobPath}/${ExeFile}.sh
  echo "module use-apped /usr/common/usg/Modules/modulefiles"                 >> ${JobPath}/${ExeFile}.sh
  echo "module use-apped /project/projectdirs/alice/xmzhang/modulefiles"      >> ${JobPath}/${ExeFile}.sh
  echo "module load gcc/4.8.1"                                                >> ${JobPath}/${ExeFile}.sh
  echo "module load xmzhang/HepMC/2.06.09"                                    >> ${JobPath}/${ExeFile}.sh
  echo "module load xmzhang/pythia/8.2.09"                                    >> ${JobPath}/${ExeFile}.sh
  echo "module load xmzhang/root/vAN"                                         >> ${JobPath}/${ExeFile}.sh
  echo "cd ${JobPath}"                                                        >> ${JobPath}/${ExeFile}.sh
  echo "./${ExeFile} \"${SimPath}#${SimType}#${sPtBin}\" out_\${SGE_TASK_ID}" >> ${JobPath}/${ExeFile}.sh
  echo "exit 0"                                                               >> ${JobPath}/${ExeFile}.sh
#
# qsub -t 1-50:1 -l gscratchio=1 -P alice -o ${JobPath} -e ${JobPath} ${JobPath}/${ExeFile}.sh
done
#
exit 0
