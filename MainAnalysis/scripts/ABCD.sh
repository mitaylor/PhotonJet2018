#!/usr/bin/env bash

set=$1

run_pp() {
    tag=$1

    echo "nohup ./bin/abcd configs/tessellate/tessellate_${tag}.conf configs/analysis/${set}/analysis_pp.conf data/arc/${set}/abcd_${tag}.root > log/${set}_abcd_${tag}.txt 2>&1 &"
}

run_aa() {
    tag=$1

    echo "nohup ./bin/abcd configs/tessellate/tessellate_${tag}.conf configs/analysis/${set}/analysis_aa.conf data/arc/${set}/abcd_${tag}.root > log/${set}_abcd_${tag}.txt 2>&1 &"
}

samples=(pp)

for sample in ${samples[@]}; do
    run_pp ${sample}

    for syst in loose tight qcd; do
        run_pp ${sample}_${syst}
    done
done

samples=(aa)

for sample in ${samples[@]}; do
    run_aa ${sample}

    for syst in loose tight qcd cent_up cent_down; do
        run_aa ${sample}_${syst}
    done
done