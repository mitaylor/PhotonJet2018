#!/bin/sh

file=$1
output=$2
input=$3

WorkDir=`pwd`

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700

if [ -r CMSSW_10_3_3_patch1/src ] ; then
    echo release CMSSW_10_3_3_patch1 already exists
else
    scram p CMSSW CMSSW_10_3_3_patch1
fi

cd CMSSW_10_3_3_patch1/src
eval `scramv1 runtime -sh`

cd $WorkDir

export X509_USER_PROXY=/afs/cern.ch/user/m/mitaylor/physics/PhotonJet2018/MainAnalysis/lxplus/x509up_u117190

xrdcp ${input} input.root

./regulate $file $output

rm input.root