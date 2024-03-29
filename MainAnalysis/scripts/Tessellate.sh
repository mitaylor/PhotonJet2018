#!/usr/bin/env bash

set=$1

run_pp() {
    tag=$1

    nohup ./bin/tessellate configs/tessellate/tessellate_${tag}.conf configs/analysis/${set}/analysis_pp.conf data/arc/${set}/tessellate_${tag}.root > log/${set}_tessellate_${tag}.txt 2>&1 &
}

run_aa() {
    tag=$1

    nohup ./bin/tessellate configs/tessellate/tessellate_${tag}.conf configs/analysis/${set}/analysis_aa.conf data/arc/${set}/tessellate_${tag}.root > log/${set}_tessellate_${tag}.txt 2>&1 &
}

samples=(pp)

for sample in ${samples[@]}; do
    run_pp ${sample}

    for syst in loose tight qcd er es; do
        run_pp ${sample}_${syst}
    done
done

samples=(aa)

for sample in ${samples[@]}; do
    run_aa ${sample}

    for syst in loose tight qcd cent_up cent_down no_er es; do
        run_aa ${sample}_${syst}
    done
done