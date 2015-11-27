#!/bin/bash
#
RunPath=`pwd`
ExeFile="AnaGenPythia8"
#
declare -a PtHatA=(5 11 21 36 57 84 117 152 -1)
PtHatN=$((${#PtHatA[@]} - 2))
#
for ((i=0; i<=PtHatN; i++))
do
  PtHatMin=${PtHatA[i]}
  PtHatMax=${PtHatA[i+1]}
  JobPath="${RunPath}/sim/py8/dPtHat_$((1000 + ${PtHatMin}))_$((1000 + ${PtHatMax}))"
  mkdir -p ${JobPath}
#
  cp ${RunPath}/bin/${ExeFile} ${JobPath}/
#
  echo "PhaseSpace:pTHatMin = ${PtHatMin}." >> ${JobPath}/${ExeFile}.cmnd
  echo "PhaseSpace:pTHatMax = ${PtHatMax}." >> ${JobPath}/${ExeFile}.cmnd
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
  echo "SGE_USER_ID=\`expr \${SGE_TASK_ID} + 10\`"                       >> ${JobPath}/${ExeFile}.sh
  echo "./${ExeFile} \"\${SGE_USER_ID}\""                                >> ${JobPath}/${ExeFile}.sh
  echo "exit 0"                                                          >> ${JobPath}/${ExeFile}.sh
#
#  qsub -t 1-50:1 -l gscratchio=1 -P alice -o ${JobPath} -e ${JobPath} ${JobPath}/${ExeFile}.sh
done
#
exit 0
