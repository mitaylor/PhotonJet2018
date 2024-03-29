#!/usr/bin/env bash

run() {
    tag=$1

    ./bin/fabulate_angle_smeared configs/fabulate/fabulate_${tag}_test.conf \
        data/fabulate_${tag}_smear_test.root
    ./bin/distillate_angle configs/distillate/distillate_${tag}_dj_smear_test.conf \
        data/distillate_${tag}_dj_smear_test.root
}

samples=(pp_angle_smear_0_10 pp_angle_smear_10_30 pp_angle_smear_30_50 pp_angle_smear_50_90)

for sample in ${samples[@]}; do
    run $sample
done
