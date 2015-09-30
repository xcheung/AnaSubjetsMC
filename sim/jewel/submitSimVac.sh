#!/bin/bash
#
RunPath=`pwd`
SrcType="vac"
SrcName="jewel-2.0.2-${SrcType}"
#
declare -a PtHatA=(5 11 21 36 57 84 117 152 -1)
PtHatN=$((${#PtHatA[@]} - 2))
#
for ((i=0; i<=PtHatN; i++))
do
  PtHatMin=${PtHatA[i]}
  PtHatMax=${PtHatA[i+1]}
  BinsName="${RunPath}/sim/${SrcType}/dPtJet_$((1000 + ${PtHatMin}))_$((1000 + ${PtHatMax}))"
  mkdir -p ${BinsName}
#
  echo "#!/bin/bash"                                                      > ${BinsName}/${SrcName}.sh
  echo "source /usr/share/modules/3.2.10/Modules/3.2.10/init/sh"         >> ${BinsName}/${SrcName}.sh
  echo "module use-apped /usr/common/usg/Modules/modulefiles"            >> ${BinsName}/${SrcName}.sh
  echo "module use-apped /project/projectdirs/alice/xmzhang/modulefiles" >> ${BinsName}/${SrcName}.sh
  echo "module load gcc/4.8.1"                                           >> ${BinsName}/${SrcName}.sh
  echo "module load xmzhang/jewel/2.0.2"                                 >> ${BinsName}/${SrcName}.sh
  echo "cd ${BinsName}"                                                  >> ${BinsName}/${SrcName}.sh
  echo "SGE_USER_ID=\`expr \${SGE_TASK_ID} + 10\`"                       >> ${BinsName}/${SrcName}.sh
  echo "echo \"NJOB \${SGE_USER_ID}\"                      >> param_\${SGE_USER_ID}.dat" >> ${BinsName}/${SrcName}.sh
  echo "echo \"LOGFILE out_\${SGE_USER_ID}.log\"           >> param_\${SGE_USER_ID}.dat" >> ${BinsName}/${SrcName}.sh
  echo "echo \"HEPMCFILE out_\${SGE_USER_ID}.hepmc\"       >> param_\${SGE_USER_ID}.dat" >> ${BinsName}/${SrcName}.sh
  echo "echo \"SPLITINTFILE splitint_\${SGE_USER_ID}.dat\" >> param_\${SGE_USER_ID}.dat" >> ${BinsName}/${SrcName}.sh
  echo "echo \"PDFFILE pdfs_\${SGE_USER_ID}.dat\"          >> param_\${SGE_USER_ID}.dat" >> ${BinsName}/${SrcName}.sh
  echo "echo \"XSECFILE xsecs_\${SGE_USER_ID}.dat\"        >> param_\${SGE_USER_ID}.dat" >> ${BinsName}/${SrcName}.sh
  echo "echo \"PTMIN ${PtHatMin}.\" >> param_\${SGE_USER_ID}.dat" >> ${BinsName}/${SrcName}.sh
  echo "echo \"PTMAX ${PtHatMax}.\" >> param_\${SGE_USER_ID}.dat" >> ${BinsName}/${SrcName}.sh
  echo "echo \"ETAMAX 2.5\"         >> param_\${SGE_USER_ID}.dat" >> ${BinsName}/${SrcName}.sh
  echo "${SrcName} param_\${SGE_USER_ID}.dat" >> ${BinsName}/${SrcName}.sh
  echo "exit 0"                               >> ${BinsName}/${SrcName}.sh
#
# qsub -t 1-100:1 -l gscratchio=1 -l projectio=1 -l h_vmem=4G -P alice -o ${BinsName} -e ${BinsName} ${BinsName}/${SrcName}.sh
done
#
exit 0
