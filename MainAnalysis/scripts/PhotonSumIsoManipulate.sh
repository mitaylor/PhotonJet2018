#!/usr/bin/env bash

set=$1

run_pp() {
    tag=$1

    ./bin/manipulate configs/manipulate/preapproval/manipulate_sumiso_${tag}.conf configs/analysis/${set}/analysis_pp.conf data/preapproval/${set}/manipulate_sumiso_${tag}.root
}

run_aa() {
    tag=$1

    ./bin/manipulate configs/manipulate/preapproval/manipulate_sumiso_${tag}.conf configs/analysis/${set}/analysis_aa.conf data/preapproval/${set}/manipulate_sumiso_${tag}.root
}

samples=(pp)

for sample in ${samples[@]}; do
    run_pp $sample

    for syst in qcd; do
        run_pp ${sample}_${syst}
    done
done

samples=(aa)

for sample in ${samples[@]}; do
    run_aa $sample

    for syst in qcd; do
        run_aa ${sample}_${syst}
    done
done