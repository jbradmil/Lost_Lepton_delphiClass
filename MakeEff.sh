
source /cvmfs/cms.cern.ch/cmsset_default.sh
pushd /cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/cmssw-patch/CMSSW_7_4_6_patch6/src/
eval `scramv1 runtime -sh`
echo "should be in cvmfs: $PWD"
popd

root -b -q MakeEff.C
