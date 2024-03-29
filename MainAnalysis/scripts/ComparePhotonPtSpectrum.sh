#!/usr/bin/env bash

set=$1

run_pp() {
    tag=$1

    ./bin/compare_photon_pt_spectrum configs/compare_photon_pt_spectrum/compare_photon_pt_spectrum_pp.conf configs/analysis/${set}/analysis_pp.conf data/arc/${set}/photon_pt_weight_pp.root
    ./bin/compare_photon_pt_spectrum configs/compare_photon_pt_spectrum/compare_photon_pt_spectrum_pp_loose_purity.conf configs/analysis/${set}/analysis_pp.conf data/arc/${set}/photon_pt_weight_pp_loose_purity.root
    ./bin/compare_photon_pt_spectrum configs/compare_photon_pt_spectrum/compare_photon_pt_spectrum_pp_tight_purity.conf configs/analysis/${set}/analysis_pp.conf data/arc/${set}/photon_pt_weight_pp_tight_purity.root
    ./bin/compare_photon_pt_spectrum configs/compare_photon_pt_spectrum/compare_photon_pt_spectrum_pp_er.conf configs/analysis/${set}/analysis_pp.conf data/arc/${set}/photon_pt_weight_pp_er.root
}

run_aa() {
    tag=$1

    ./bin/compare_photon_pt_spectrum configs/compare_photon_pt_spectrum/compare_photon_pt_spectrum_aa.conf configs/analysis/${set}/analysis_aa.conf data/arc/${set}/photon_pt_weight_aa.root
    ./bin/compare_photon_pt_spectrum configs/compare_photon_pt_spectrum/compare_photon_pt_spectrum_aa_loose_purity.conf configs/analysis/${set}/analysis_aa.conf data/arc/${set}/photon_pt_weight_aa_loose_purity.root
    ./bin/compare_photon_pt_spectrum configs/compare_photon_pt_spectrum/compare_photon_pt_spectrum_aa_tight_purity.conf configs/analysis/${set}/analysis_aa.conf data/arc/${set}/photon_pt_weight_aa_tight_purity.root
    ./bin/compare_photon_pt_spectrum configs/compare_photon_pt_spectrum/compare_photon_pt_spectrum_aa_no_er.conf configs/analysis/${set}/analysis_aa.conf data/arc/${set}/photon_pt_weight_aa_no_er.root
}

samples=(pp)

for sample in ${samples[@]}; do
    run_pp ${sample}
done

samples=(aa)

for sample in ${samples[@]}; do
    run_aa ${sample}
done

./bin/compare_photon_pt_spectrum_mc configs/compare_photon_pt_spectrum/compare_photon_pt_spectrum_mc.conf configs/analysis/${set}/analysis_pp.conf data/arc/photon_pt_weight_mc.root