#!/usr/bin/env bash

set=$1

run_pp() {
    tag=$1

    echo ${tag}

    ./bin/choose_iteration_study configs/quantitate/quantitate_${tag}.conf configs/analysis/${set}/analysis_pp.conf data/preapproval/${set}/choose_iteration_${tag}.root
}

run_aa() {
    tag=$1

    echo ${tag}

    ./bin/choose_iteration_study configs/quantitate/quantitate_${tag}.conf configs/analysis/${set}/analysis_aa.conf data/preapproval/${set}/choose_iteration_${tag}.root
}

samples=(pp pp_smear_0_10 pp_smear_10_30 pp_smear_30_50 pp_smear_50_90)

for sample in ${samples[@]}; do
    run_pp ${sample}
done

samples=(aa)

for sample in ${samples[@]}; do
    run_aa ${sample}
done