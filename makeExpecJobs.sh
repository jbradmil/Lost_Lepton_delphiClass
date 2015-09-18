#!/bin/bash

SAMPLE=$1
#OUTDIR=$3

INDIR=/hadoop/cms/store/user/jbradmil/trees_911/${SAMPLE}/
NFILES=$(ls -l ${INDIR}*root | wc -l)
echo "Creating ${NFILES} jobs"
IMAX=$(($NFILES-1))

rm logs/jobExecCondor_${SAMPLE}_*exp*
rm condor/*${SAMPLE}*exp*

OUTDIR=/hadoop/cms/store/user/jbradmil/trees_911/Expectation/${SAMPLE}/
mkdir -p $OUTDIR

for IND in $(seq 0 $IMAX)
do
    JOBNAME=condor/jobExecCondor_${SAMPLE}_${IND}_exp.jdl
    LOGNAME=logs/jobExecCondor_${SAMPLE}_${IND}_exp
    INFILE=root://cmsxrootd.fnal.gov///store/user/jbradmil/trees_911/${SAMPLE}/${SAMPLE}_${IND}.root

    sed -e 's|CMSSWVER|'${CMSSW_VERSION}'|g' -e 's~INFILE~'${INFILE}'~g' -e 's~OUTDIR~'${OUTDIR}'~g' -e 's~LOGDIR~'${LOGNAME}'~g' < condor/jobExecCondor_exp.jdl > ${JOBNAME}
    condor_submit $JOBNAME
done

