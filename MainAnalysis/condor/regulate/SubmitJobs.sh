#!/usr/bin/env bash

folder=${1}
config_fragment=${2}
output_tag=${3}

cp /tmp/x509up_u168456 x509up_u168456

mkdir -p ${output_tag}
cd ${output_tag}
rm -f *
cp ../../../configs/regulate/${config_fragment} .

# find ${folder} -type f > ${output_tag}

# split the input files
folders=`xrdfs xrootd.cmsaf.mit.edu ls ${folder}`

for folder in ${folders}
do
    xrdfs xrootd.cmsaf.mit.edu ls ${folder} >> ${output_tag}
done

sed -i 's/^.*\/store/root:\/\/xrootd.cmsaf.mit.edu\/\/store/' ${output_tag}

## split -l 1 --numeric-suffixes=0 -a 3 ${output_tag} ${output_tag}_
## files=`find . -type f -name "${output_tag}_[0-9][0-9][0-9]" -printf '%f\n'`

awk -F "[_.]" -v OFS=", " '{print $(NF-1), $0}' ${output_tag} > ${output_tag}.list

cat ../SubmitCondor.condor | sed "s/__MASTER__/${output_tag}/g" > SubmitCondor.condor
sed -i "s/__CONFIG__/${config_fragment}/g" SubmitCondor.condor

condor_submit SubmitCondor.condor