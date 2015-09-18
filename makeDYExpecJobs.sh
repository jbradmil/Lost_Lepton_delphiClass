#!/bin/bash

SAMPLE=13TeV_25ns20PU.DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM
#OUTDIR=$3

INDIR=/hadoop/cms/store/user/jbradmil/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_UCSD_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_UCSD_MINIAODSIM/150914_050837/0000/
NFILES=$(ls -l ${INDIR}*root | wc -l)
echo "Creating ${NFILES} jobs"
IMAX=$NFILES

rm logs/jobExecCondor_${SAMPLE}_*exp*
rm condor/*${SAMPLE}*exp*

OUTDIR=/hadoop/cms/store/user/jbradmil/trees_911/Expectation/${SAMPLE}/
mkdir -p $OUTDIR

for IND in $(seq 1 $IMAX)
do
    JOBNAME=condor/jobExecCondor_${SAMPLE}_${IND}_exp.jdl
    LOGNAME=logs/jobExecCondor_${SAMPLE}_${IND}_exp
    INFILE=${INDIR}RA2AnalysisTree_${IND}.root

    sed -e 's|CMSSWVER|'${CMSSW_VERSION}'|g' -e 's~INFILE~'${INFILE}'~g' -e 's~OUTDIR~'${OUTDIR}'~g' -e 's~LOGDIR~'${LOGNAME}'~g' < condor/jobExecCondor_exp.jdl > ${JOBNAME}
    #condor_submit $JOBNAME
done

