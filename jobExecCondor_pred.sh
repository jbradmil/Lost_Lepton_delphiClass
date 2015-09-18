#!/bin/bash

#
# variables from arguments string in jdl
#

#Tell us where we're running
echo "host: `hostname`" 

source /cvmfs/cms.cern.ch/cmsset_default.sh

CMSSWVER=$1
INPUT=$2
OUTDIR=$3

echo ""
echo "parameter set:"
echo "CMSSWVER:   $CMSSWVER"
echo "INPUT:      $INPUT"
echo "OUTDIR:     $OUTDIR"


pushd /cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/cmssw-patch/${CMSSWVER}/src/
eval `scramv1 runtime -sh`
echo "should be in cvmfs: $PWD"
popd

# run CMSSW
echo "root -b -q MakePrediction.C+(\"${INPUT}\");"
root -b -q MakePrediction.C\(\"${INPUT}\"\);

# copy output to eos
echo "copying output file"
#for FILE in *_Pred.root
#do
#    echo "xrdcp -f ${FILE} ${OUTDIR}"
#    xrdcp -f ${FILE} ${OUTDIR}
#    rm ${FILE}
#done

for FILE in *_Pred.root
do
    echo "lcg-cp -b -D srmv2 --vo cms --srm-timeout 2400 --sendreceive-timeout 2400 --connect-timeout 300 --verbose file:`pwd`/${FILE} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${OUTDIR}/${FILE}"
    lcg-cp -b -D srmv2 --vo cms --srm-timeout 2400 --sendreceive-timeout 2400 --connect-timeout 300 --verbose file:`pwd`/${FILE} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${OUTDIR}/${FILE}
    rm ${FILE}
done


