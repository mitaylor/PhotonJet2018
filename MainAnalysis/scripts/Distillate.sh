#!/usr/bin/env bash

run() {
    tag=$1
    echo $tag
    ./bin/distillate configs/distillate/distillate_${tag}_scale.conf data/arc/distillate_${tag}_scale.root
    ./bin/distillate_angle configs/distillate/distillate_${tag}_angle_dj.conf data/arc/distillate_${tag}_angle_dj.root
}

samples=(pp_smear_0_10_test pp_smear_10_30_test pp_smear_30_50_test pp_smear_50_90_test)

for sample in ${samples[@]}; do
    run ${sample}
done