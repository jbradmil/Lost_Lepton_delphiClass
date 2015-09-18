#!/bin/bash

SAMPLE=$1

NFILES=$(ls -l condor/*${SAMPLE}*exp*jdl | wc -l)
echo "Checking for ${NFILES} files"
IMAX=$(($NFILES-1))

OUTDIR=/hadoop/cms/store/user/jbradmil/trees_911/Expectation/${SAMPLE}/

for IND in $(seq 0 $IMAX)
do
    if [ ! -e ${OUTDIR}${SAMPLE}_${IND}_Exp.root ]
    then
	echo "File ${OUTDIR}${SAMPLE}_${IND}.root does not exist...resubmitting"
	condor_submit condor/jobExecCondor_${SAMPLE}_${IND}_exp.jdl
    fi
done

