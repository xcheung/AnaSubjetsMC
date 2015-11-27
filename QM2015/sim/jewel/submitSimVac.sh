#!/bin/bash
#
GetPtHatName()
{
  dPtHat=$1
  sPtHat="INFN"
  if [ ${dPtHat} -gt 0 ]
  then
    sPtHat="000${dPtHat}"
  fi
#
  if [ ${dPtHat} -gt 10 ]
  then
    sPtHat="00${dPtHat}"
  fi
#
  if [ ${dPtHat} -gt 100 ]
  then
    sPtHat="0${dPtHat}"
  fi
#
  echo "${sPtHat}"
}
###############################################################################
#
RunPath=`pwd`
SrcName="jewel-2.0.2-vac"
#
declare -a aPtHatBin=(5 11 21 36 57 84 117 152 191 234 282 334 -1)
nPtHatBin=$((${#aPtHatBin[@]} - 1))
#
for ((i=0; i<${nPtHatBin}; i++))
do
  dPtHatMin=${aPtHatBin[i]}
  dPtHatMax=${aPtHatBin[i+1]}
  sPtHatMin=`GetPtHatName ${dPtHatMin}`
  sPtHatMax=`GetPtHatName ${dPtHatMax}`
  sTaskPath="${RunPath}/vac/dPtHat_${sPtHatMin}_${sPtHatMax}"
#
  if [ -d ${sTaskPath} ]
  then
    continue
  else
    echo    "${sTaskPath}"
    mkdir -p ${sTaskPath}
  fi
#
  echo "#!/bin/bash"                                                      > ${sTaskPath}/${SrcName}.sh
  echo "source /usr/share/modules/3.2.10/Modules/3.2.10/init/sh"         >> ${sTaskPath}/${SrcName}.sh
  echo "module use-apped /usr/common/usg/Modules/modulefiles"            >> ${sTaskPath}/${SrcName}.sh
  echo "module use-apped /project/projectdirs/alice/xmzhang/modulefiles" >> ${sTaskPath}/${SrcName}.sh
  echo "module load gcc/4.8.1"                                           >> ${sTaskPath}/${SrcName}.sh
  echo "module load xmzhang/jewel/2.0.2"                                 >> ${sTaskPath}/${SrcName}.sh
  echo "cd ${sTaskPath}"                                                 >> ${sTaskPath}/${SrcName}.sh
  echo "SGE_USER_ID=\`expr \${SGE_TASK_ID} +  0\`"                       >> ${sTaskPath}/${SrcName}.sh
  echo "echo \"NJOB \${SGE_USER_ID}\"                       > param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
  echo "echo \"LOGFILE out_\${SGE_USER_ID}.log\"           >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
  echo "echo \"HEPMCFILE out_\${SGE_USER_ID}.hepmc\"       >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
  echo "echo \"SPLITINTFILE splitint_\${SGE_USER_ID}.dat\" >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
  echo "echo \"PDFFILE pdfs_\${SGE_USER_ID}.dat\"          >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
  echo "echo \"XSECFILE xsecs_\${SGE_USER_ID}.dat\"        >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
  echo "echo \"PTMIN ${dPtHatMin}.\"                       >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
  echo "echo \"PTMAX ${dPtHatMax}.\"                       >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
  echo "${SrcName} param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
  echo "exit 0"                               >> ${sTaskPath}/${SrcName}.sh
#
# qsub -t 1-10:1 -l projectio=1 -l h_vmem=4G -P alice -o ${sTaskPath} -e ${sTaskPath} ${sTaskPath}/${SrcName}.sh
done
#
exit 0
