#!/bin/bash
#
RunPath=`pwd`
RecPath="${RunPath}/rec"
SimPath="${RunPath}/prod/qp6"
#
ParJetR="JetR05"
ParSjeR="SjeR01"
ExeFile="AnaSjeQpyInclIAA"
#
sTOOL="sed"
#
for sPtBin in \
  dPtHard_00005_00011 \
  dPtHard_00011_00021 \
  dPtHard_00021_00036 \
  dPtHard_00036_00057 \
  dPtHard_00057_00084 \
  dPtHard_00084_00117 \
  dPtHard_00117_00152 \
  dPtHard_00152_00191 \
  dPtHard_00191_00234 \
  dPtHard_00234_INFTY
do
#
  Dataset="${SimPath}/${sPtBin}.txt"
  nJOBS=`wc -l ${Dataset} | awk '{print $1}'`
#
  JobPath="${RecPath}/qp6_${ParJetR}_${ParSjeR}_${ExeFile}/${sPtBin}"
  mkdir -p ${JobPath}
#
  cp ${RunPath}/bin/${ExeFile} ${JobPath}/
#
  echo "#!/bin/bash"                                                      > ${JobPath}/${ExeFile}.sh
  echo "source /usr/share/modules/3.2.10/Modules/3.2.10/init/sh"         >> ${JobPath}/${ExeFile}.sh
  echo "module use-apped /usr/common/usg/Modules/modulefiles"            >> ${JobPath}/${ExeFile}.sh
  echo "module use-apped /project/projectdirs/alice/xmzhang/modulefiles" >> ${JobPath}/${ExeFile}.sh
  echo "module load gcc/4.8.1"                                           >> ${JobPath}/${ExeFile}.sh
  echo "module load xmzhang/pythia/8.2.09"                               >> ${JobPath}/${ExeFile}.sh
  echo "module load xmzhang/alisoft/vAN"                                 >> ${JobPath}/${ExeFile}.sh
  echo "cd ${JobPath}"                                                   >> ${JobPath}/${ExeFile}.sh
  echo "DataPath=\`${sTOOL} -n \${SGE_TASK_ID}p ${Dataset}\`"            >> ${JobPath}/${ExeFile}.sh
  echo "./${ExeFile} \"\${DataPath}\" \\"                                >> ${JobPath}/${ExeFile}.sh
  echo "             out_\${SGE_TASK_ID} \\"                             >> ${JobPath}/${ExeFile}.sh
  echo "             ${ParJetR} \\"                                      >> ${JobPath}/${ExeFile}.sh
  echo "             ${ParSjeR}"                                         >> ${JobPath}/${ExeFile}.sh
  echo "exit 0"                                                          >> ${JobPath}/${ExeFile}.sh
#
# qsub -t 1-${nJOBS}:1 -l gscratchio=1 -l projectio=1 -P alice -o ${JobPath} -e ${JobPath} ${JobPath}/${ExeFile}.sh
# qsub -t 1-${nJOBS}:1 -l gscratchio=1 -l projectio=1 -l h_vmem=4G -P alice -o ${JobPath} -e ${JobPath} ${JobPath}/${ExeFile}.sh
done
#
exit 0
