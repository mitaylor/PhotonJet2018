#!/usr/bin/env bash

set=$1
n=$2

run_aa() {
    tag=$1

    ./RunPopulateOriginalMC.sh ${set} ${tag} ${n}
}

samples=(aa_qcd)

for sample in ${samples[@]}; do
    run_aa populate_${sample}_raw
    run_aa populate_${sample}_bkg

    for syst in gen_iso; do
        run_aa populate_${sample}_${syst}_raw
        run_aa populate_${sample}_${syst}_bkg
    done
done