#!/usr/bin/env bash

set=$1

run_pp() {
    tag=$1

    ./bin/speculate_centrality configs/speculate/speculate_${tag}.conf configs/analysis/${set}/analysis_pp.conf data/arc/${set}/speculate_${tag}.root > log/${set}_speculate_${tag}.txt 2>&1 &
}

run_aa() {
    tag=$1

    ./bin/speculate_centrality configs/speculate/speculate_${tag}.conf configs/analysis/${set}/analysis_aa.conf data/arc/${set}/speculate_${tag}.root > log/${set}_speculate_${tag}.txt 2>&1 &
}

samples=(pp pp_er)

for sample in ${samples[@]}; do
    run_pp ${sample}
done

samples=(aa aa_no_er)

for sample in ${samples[@]}; do
    run_aa ${sample}
done