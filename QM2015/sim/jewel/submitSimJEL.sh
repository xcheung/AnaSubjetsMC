#!/bin/bash
#
RunPath=`pwd`
#rcType="vac"
SrcType="simple"
SrcName="jewel-2.0.2-${SrcType}"
#
sTaskPath="${RunPath}/sim/${SrcType}/dPtHat_0005_INFN"
mkdir -p ${sTaskPath}
#
echo "#!/bin/bash"                                                      > ${sTaskPath}/${SrcName}.sh
echo "source /usr/share/modules/3.2.10/Modules/3.2.10/init/sh"         >> ${sTaskPath}/${SrcName}.sh
echo "module use-apped /usr/common/usg/Modules/modulefiles"            >> ${sTaskPath}/${SrcName}.sh
echo "module use-apped /project/projectdirs/alice/xmzhang/modulefiles" >> ${sTaskPath}/${SrcName}.sh
echo "module load gcc/4.8.1"                                           >> ${sTaskPath}/${SrcName}.sh
echo "module load xmzhang/jewel/2.0.2"                                 >> ${sTaskPath}/${SrcName}.sh
echo "cd ${sTaskPath}"                                                 >> ${sTaskPath}/${SrcName}.sh
echo "SGE_USER_ID=\`expr \${SGE_TASK_ID} +  0\`"                       >> ${sTaskPath}/${SrcName}.sh
#cho "SGE_USER_ID=\`expr \${SGE_TASK_ID} + 10\`"                       >> ${sTaskPath}/${SrcName}.sh
echo "echo \"NJOB \${SGE_USER_ID}\"                       > param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
echo "echo \"LOGFILE out_\${SGE_USER_ID}.log\"           >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
echo "echo \"HEPMCFILE out_\${SGE_USER_ID}.hepmc\"       >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
echo "echo \"SPLITINTFILE splitint_\${SGE_USER_ID}.dat\" >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
echo "echo \"PDFFILE pdfs_\${SGE_USER_ID}.dat\"          >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
echo "echo \"XSECFILE xsecs_\${SGE_USER_ID}.dat\"        >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
echo "echo \"PTMIN 5.\"                                  >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
echo "echo \"PTMAX -1.\"                                 >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
#cho "echo \"ETAMAX 2.5\"                                >> param_\${SGE_USER_ID}.dat" >> ${sTaskPath}/${SrcName}.sh
echo "${SrcName} param_\${SGE_USEUSER}.dat" >> ${sTaskPath}/${SrcName}.sh
echo "exit 0"                               >> ${sTaskPath}/${SrcName}.sh
#
#sub -t 1-50:1 -l gscratchio=1 -l projectio=1 -l h_vmem=4G -P alice -o ${sTaskPath} -e ${sTaskPath} ${sTaskPath}/${SrcName}.sh
#
exit 0
