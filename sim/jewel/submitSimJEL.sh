#!/bin/bash
#
RunPath=`pwd`
#rcType="vac"
SrcType="simple"
SrcName="jewel-2.0.2-${SrcType}"
#
BinsName="${RunPath}/sim/${SrcType}/dPtJet_1005_INFN"
mkdir -p ${BinsName}
#
echo "#!/bin/bash"                                                      > ${BinsName}/${SrcName}.sh
echo "source /usr/share/modules/3.2.10/Modules/3.2.10/init/sh"         >> ${BinsName}/${SrcName}.sh
echo "module use-apped /usr/common/usg/Modules/modulefiles"            >> ${BinsName}/${SrcName}.sh
echo "module use-apped /project/projectdirs/alice/xmzhang/modulefiles" >> ${BinsName}/${SrcName}.sh
echo "module load gcc/4.8.1"                                           >> ${BinsName}/${SrcName}.sh
echo "module load xmzhang/jewel/2.0.2"                                 >> ${BinsName}/${SrcName}.sh
echo "cd ${BinsName}"                                                  >> ${BinsName}/${SrcName}.sh
echo "echo \"NJOB \${SGE_TASK_ID}\"                      >> param_\${SGE_TASK_ID}.dat" >> ${BinsName}/${SrcName}.sh
echo "echo \"LOGFILE out_\${SGE_TASK_ID}.log\"           >> param_\${SGE_TASK_ID}.dat" >> ${BinsName}/${SrcName}.sh
echo "echo \"HEPMCFILE out_\${SGE_TASK_ID}.hepmc\"       >> param_\${SGE_TASK_ID}.dat" >> ${BinsName}/${SrcName}.sh
echo "echo \"SPLITINTFILE splitint_\${SGE_TASK_ID}.dat\" >> param_\${SGE_TASK_ID}.dat" >> ${BinsName}/${SrcName}.sh
echo "echo \"PDFFILE pdfs_\${SGE_TASK_ID}.dat\"          >> param_\${SGE_TASK_ID}.dat" >> ${BinsName}/${SrcName}.sh
echo "echo \"XSECFILE xsecs_\${SGE_TASK_ID}.dat\"        >> param_\${SGE_TASK_ID}.dat" >> ${BinsName}/${SrcName}.sh
echo "echo \"PTMIN 5.\"   >> param_\${SGE_TASK_ID}.dat" >> ${BinsName}/${SrcName}.sh
echo "echo \"PTMAX -1.\"  >> param_\${SGE_TASK_ID}.dat" >> ${BinsName}/${SrcName}.sh
echo "echo \"ETAMAX 2.5\" >> param_\${SGE_TASK_ID}.dat" >> ${BinsName}/${SrcName}.sh
echo "${SrcName} param_\${SGE_TASK_ID}.dat" >> ${BinsName}/${SrcName}.sh
echo "exit 0"                               >> ${BinsName}/${SrcName}.sh
#
#sub -t 1-50:1 -l gscratchio=1 -l projectio=1 -l h_vmem=4G -P alice -o ${BinsName} -e ${BinsName} ${BinsName}/${SrcName}.sh
#
exit 0
