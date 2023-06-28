#!/usr/bin/env bash

set=$1

# AANominal: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AANominal0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AANominal1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AANominal2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AANominal3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_pure_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AANominalMerge.root

# AAWithoutEleRej: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_wo_ele_rej.root \
    --DataHistogram aa_wo_ele_rej_s_pure_wo_ele_rej_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_wo_ele_rej.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAWithoutEleRej0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_wo_ele_rej.root \
    --DataHistogram aa_wo_ele_rej_s_pure_wo_ele_rej_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_wo_ele_rej.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAWithoutEleRej1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_wo_ele_rej.root \
    --DataHistogram aa_wo_ele_rej_s_pure_wo_ele_rej_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_wo_ele_rej.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAWithoutEleRej2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_wo_ele_rej.root \
    --DataHistogram aa_wo_ele_rej_s_pure_wo_ele_rej_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_wo_ele_rej.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAWithoutEleRej3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_wo_ele_rej.root \
    --DataHistogram aa_wo_ele_rej_pure_wo_ele_rej_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_wo_ele_rej.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAWithoutEleRejMerge.root

# AATightPurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_tight_purity.root \
    --DataHistogram aa_tight_purity_s_pure_tight_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_tight_purity.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AATightPurity0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_tight_purity.root \
    --DataHistogram aa_tight_purity_s_pure_tight_purity_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_tight_purity.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AATightPurity1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_tight_purity.root \
    --DataHistogram aa_tight_purity_s_pure_tight_purity_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_tight_purity.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AATightPurity2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_tight_purity.root \
    --DataHistogram aa_tight_purity_s_pure_tight_purity_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_tight_purity.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AATightPurity3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_tight_purity.root \
    --DataHistogram aa_tight_purity_pure_tight_purity_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_tight_purity.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AATightPurityMerge.root

# AALoosePurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_loose_purity.root \
    --DataHistogram aa_loose_purity_s_pure_loose_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_loose_purity.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AALoosePurity0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_loose_purity.root \
    --DataHistogram aa_loose_purity_s_pure_loose_purity_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_loose_purity.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AALoosePurity1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_loose_purity.root \
    --DataHistogram aa_loose_purity_s_pure_loose_purity_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_loose_purity.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AALoosePurity2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_loose_purity.root \
    --DataHistogram aa_loose_purity_s_pure_loose_purity_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_loose_purity.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AALoosePurity3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_loose_purity.root \
    --DataHistogram aa_loose_purity_pure_loose_purity_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_loose_purity.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AALoosePurityMerge.root

# AAQCD: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd.root \
    --DataHistogram aa_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAQCD0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd.root \
    --DataHistogram aa_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAQCD1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd.root \
    --DataHistogram aa_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAQCD2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd.root \
    --DataHistogram aa_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAQCD3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd.root \
    --DataHistogram aa_qcd_nominal_pure_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAQCDMerge.root

# # AAQCDAll: Execute
# ./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd.root \
#     --DataHistogram aa_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
#     --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd_all.root \
#     --ResponseHistogram aa_c_0 \
#     --ResponseTruth aa_g_0 \
#     --ResponseReco aa_r_0 \
#     --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
#     --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
#     --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
#     --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
#     --Output OutputWeighted/${set}/AAQCDAll0.root
# ./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd.root \
#     --DataHistogram aa_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_1 \
#     --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd_all.root \
#     --ResponseHistogram aa_c_1 \
#     --ResponseTruth aa_g_1 \
#     --ResponseReco aa_r_1 \
#     --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
#     --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
#     --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
#     --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
#     --Output OutputWeighted/${set}/AAQCDAll1.root
# ./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd.root \
#     --DataHistogram aa_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_2 \
#     --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd_all.root \
#     --ResponseHistogram aa_c_2 \
#     --ResponseTruth aa_g_2 \
#     --ResponseReco aa_r_2 \
#     --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
#     --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
#     --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
#     --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
#     --Output OutputWeighted/${set}/AAQCDAll2.root
# ./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd.root \
#     --DataHistogram aa_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_3 \
#     --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd_all.root \
#     --ResponseHistogram aa_c_3 \
#     --ResponseTruth aa_g_3 \
#     --ResponseReco aa_r_3 \
#     --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
#     --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
#     --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
#     --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
#     --Output OutputWeighted/${set}/AAQCDAll3.root
# ./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd.root \
#     --DataHistogram aa_qcd_nominal_pure_raw_sub_pjet_u_dr_merge_0 \
#     --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd_all.root \
#     --ResponseHistogram aa_c_merge_0 \
#     --ResponseTruth aa_g_merge_0 \
#     --ResponseReco aa_r_merge_0 \
#     --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
#     --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
#     --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
#     --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
#     --Output OutputWeighted/${set}/AAQCDAllMerge.root

# AAQCDGenIso: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd_gen_iso.root \
    --DataHistogram aa_qcd_gen_iso_s_pure_gen_iso_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd_gen_iso.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAQCDGenIso0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd_gen_iso.root \
    --DataHistogram aa_qcd_gen_iso_s_pure_gen_iso_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd_gen_iso.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAQCDGenIso1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd_gen_iso.root \
    --DataHistogram aa_qcd_gen_iso_s_pure_gen_iso_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd_gen_iso.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAQCDGenIso2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd_gen_iso.root \
    --DataHistogram aa_qcd_gen_iso_s_pure_gen_iso_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd_gen_iso.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAQCDGenIso3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_qcd_gen_iso.root \
    --DataHistogram aa_qcd_gen_iso_pure_gen_iso_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_qcd_gen_iso.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAQCDGenIsoMerge.root

# AAJEUUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jeu_up.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJEUUp0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jeu_up.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJEUUp1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jeu_up.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJEUUp2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jeu_up.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJEUUp3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_pure_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jeu_up.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJEUUpMerge.root

# AAJEUDown: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jeu_down.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJEUDown0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jeu_down.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJEUDown1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jeu_down.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJEUDown2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jeu_down.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJEUDown3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_pure_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jeu_down.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJEUDownMerge.root

# AAJERUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jer_up.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJERUp0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jer_up.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJERUp1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jer_up.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJERUp2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_s_pure_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jer_up.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJERUp3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa.root \
    --DataHistogram aa_nominal_pure_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_jer_up.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AAJERUpMerge.root

# AACentUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_cent_up.root \
    --DataHistogram aa_cent_up_s_pure_cent_up_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_cent_up.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AACentUp0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_cent_up.root \
    --DataHistogram aa_cent_up_s_pure_cent_up_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_cent_up.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AACentUp1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_cent_up.root \
    --DataHistogram aa_cent_up_s_pure_cent_up_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_cent_up.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AACentUp2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_cent_up.root \
    --DataHistogram aa_cent_up_s_pure_cent_up_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_cent_up.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AACentUp3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_cent_up.root \
    --DataHistogram aa_cent_up_pure_cent_up_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_cent_up.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AACentUpMerge.root

# AACentDown: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_cent_down.root \
    --DataHistogram aa_cent_down_s_pure_cent_down_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_cent_down.root \
    --ResponseHistogram aa_c_0 \
    --ResponseTruth aa_g_0 \
    --ResponseReco aa_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AACentDown0.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_cent_down.root \
    --DataHistogram aa_cent_down_s_pure_cent_down_raw_sub_pjet_u_dr_sum0_1 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_cent_down.root \
    --ResponseHistogram aa_c_1 \
    --ResponseTruth aa_g_1 \
    --ResponseReco aa_r_1 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AACentDown1.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_cent_down.root \
    --DataHistogram aa_cent_down_s_pure_cent_down_raw_sub_pjet_u_dr_sum0_2 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_cent_down.root \
    --ResponseHistogram aa_c_2 \
    --ResponseTruth aa_g_2 \
    --ResponseReco aa_r_2 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AACentDown2.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_cent_down.root \
    --DataHistogram aa_cent_down_s_pure_cent_down_raw_sub_pjet_u_dr_sum0_3 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_cent_down.root \
    --ResponseHistogram aa_c_3 \
    --ResponseTruth aa_g_3 \
    --ResponseReco aa_r_3 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AACentDown3.root
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_aa_cent_down.root \
    --DataHistogram aa_cent_down_pure_cent_down_raw_sub_pjet_u_dr_merge_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_aa_cent_down.root \
    --ResponseHistogram aa_c_merge_0 \
    --ResponseTruth aa_g_merge_0 \
    --ResponseReco aa_r_merge_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/AACentDownMerge.root

# PPNominal: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp.root \
    --DataHistogram pp_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp.root \
    --ResponseHistogram pp_c_0 \
    --ResponseTruth pp_g_0 \
    --ResponseReco pp_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPNominal0.root

# PPWithoutEleRej: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_wo_ele_rej.root \
    --DataHistogram pp_wo_ele_rej_s_pure_wo_ele_rej_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_wo_ele_rej.root \
    --ResponseHistogram pp_c_0 \
    --ResponseTruth pp_g_0 \
    --ResponseReco pp_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPWithoutEleRej0.root

# PPTightPurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_tight_purity.root \
    --DataHistogram pp_tight_purity_s_pure_tight_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_tight_purity.root \
    --ResponseHistogram pp_c_0 \
    --ResponseTruth pp_g_0 \
    --ResponseReco pp_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPTightPurity0.root

# PPLoosePurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_loose_purity.root \
    --DataHistogram pp_loose_purity_s_pure_loose_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_loose_purity.root \
    --ResponseHistogram pp_c_0 \
    --ResponseTruth pp_g_0 \
    --ResponseReco pp_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPLoosePurity0.root

# PPQCD: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_qcd.root \
    --DataHistogram pp_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_qcd.root \
    --ResponseHistogram pp_c_0 \
    --ResponseTruth pp_g_0 \
    --ResponseReco pp_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPQCD0.root

# PPQCDGenIso: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_qcd_gen_iso.root \
    --DataHistogram pp_qcd_gen_iso_s_pure_gen_iso_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_qcd_gen_iso.root \
    --ResponseHistogram pp_c_0 \
    --ResponseTruth pp_g_0 \
    --ResponseReco pp_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPQCDGenIso0.root

# PPJEUUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp.root \
    --DataHistogram pp_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_jeu_up.root \
    --ResponseHistogram pp_c_0 \
    --ResponseTruth pp_g_0 \
    --ResponseReco pp_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPJEUUp0.root

# PPJEUDown: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp.root \
    --DataHistogram pp_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_jeu_down.root \
    --ResponseHistogram pp_c_0 \
    --ResponseTruth pp_g_0 \
    --ResponseReco pp_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPJEUDown0.root

# PPJERUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp.root \
    --DataHistogram pp_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_jer_up.root \
    --ResponseHistogram pp_c_0 \
    --ResponseTruth pp_g_0 \
    --ResponseReco pp_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPJERUp0.root

# PPNominal: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_50_90.root \
    --DataHistogram pp_smear_50_90_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_50_90.root \
    --ResponseHistogram pp_smear_50_90_c_0 \
    --ResponseTruth pp_smear_50_90_g_0 \
    --ResponseReco pp_smear_50_90_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear90Nominal0.root

# PPWithoutEleRej: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_50_90_wo_ele_rej.root \
    --DataHistogram pp_smear_50_90_wo_ele_rej_s_pure_wo_ele_rej_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_50_90_wo_ele_rej.root \
    --ResponseHistogram pp_smear_50_90_c_0 \
    --ResponseTruth pp_smear_50_90_g_0 \
    --ResponseReco pp_smear_50_90_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear90WithoutEleRej0.root

# PPTightPurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_50_90_tight_purity.root \
    --DataHistogram pp_smear_50_90_tight_purity_s_pure_tight_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_50_90_tight_purity.root \
    --ResponseHistogram pp_smear_50_90_c_0 \
    --ResponseTruth pp_smear_50_90_g_0 \
    --ResponseReco pp_smear_50_90_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear90TightPurity0.root

# PPLoosePurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_50_90_loose_purity.root \
    --DataHistogram pp_smear_50_90_loose_purity_s_pure_loose_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_50_90_loose_purity.root \
    --ResponseHistogram pp_smear_50_90_c_0 \
    --ResponseTruth pp_smear_50_90_g_0 \
    --ResponseReco pp_smear_50_90_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear90LoosePurity0.root

# PPQCD: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_50_90_qcd.root \
    --DataHistogram pp_smear_50_90_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_50_90_qcd.root \
    --ResponseHistogram pp_smear_50_90_c_0 \
    --ResponseTruth pp_smear_50_90_g_0 \
    --ResponseReco pp_smear_50_90_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear90QCD0.root

# PPQCDGenIso: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_50_90_qcd_gen_iso.root \
    --DataHistogram pp_smear_50_90_qcd_gen_iso_s_pure_gen_iso_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_50_90_qcd_gen_iso.root \
    --ResponseHistogram pp_smear_50_90_c_0 \
    --ResponseTruth pp_smear_50_90_g_0 \
    --ResponseReco pp_smear_50_90_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear90QCDGenIso0.root

# PPJEUUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_50_90.root \
    --DataHistogram pp_smear_50_90_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_50_90_jeu_up.root \
    --ResponseHistogram pp_smear_50_90_c_0 \
    --ResponseTruth pp_smear_50_90_g_0 \
    --ResponseReco pp_smear_50_90_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear90JEUUp0.root

# PPJEUDown: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_50_90.root \
    --DataHistogram pp_smear_50_90_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_50_90_jeu_down.root \
    --ResponseHistogram pp_smear_50_90_c_0 \
    --ResponseTruth pp_smear_50_90_g_0 \
    --ResponseReco pp_smear_50_90_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear90JEUDown0.root

# PPJERUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_50_90.root \
    --DataHistogram pp_smear_50_90_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_50_90_jer_up.root \
    --ResponseHistogram pp_smear_50_90_c_0 \
    --ResponseTruth pp_smear_50_90_g_0 \
    --ResponseReco pp_smear_50_90_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear90JERUp0.root

# PPNominal: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_30_50.root \
    --DataHistogram pp_smear_30_50_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_30_50.root \
    --ResponseHistogram pp_smear_30_50_c_0 \
    --ResponseTruth pp_smear_30_50_g_0 \
    --ResponseReco pp_smear_30_50_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear50Nominal0.root

# PPWithoutEleRej: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_30_50_wo_ele_rej.root \
    --DataHistogram pp_smear_30_50_wo_ele_rej_s_pure_wo_ele_rej_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_30_50_wo_ele_rej.root \
    --ResponseHistogram pp_smear_30_50_c_0 \
    --ResponseTruth pp_smear_30_50_g_0 \
    --ResponseReco pp_smear_30_50_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear50WithoutEleRej0.root

# PPTightPurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_30_50_tight_purity.root \
    --DataHistogram pp_smear_30_50_tight_purity_s_pure_tight_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_30_50_tight_purity.root \
    --ResponseHistogram pp_smear_30_50_c_0 \
    --ResponseTruth pp_smear_30_50_g_0 \
    --ResponseReco pp_smear_30_50_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear50TightPurity0.root

# PPLoosePurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_30_50_loose_purity.root \
    --DataHistogram pp_smear_30_50_loose_purity_s_pure_loose_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_30_50_loose_purity.root \
    --ResponseHistogram pp_smear_30_50_c_0 \
    --ResponseTruth pp_smear_30_50_g_0 \
    --ResponseReco pp_smear_30_50_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear50LoosePurity0.root

# PPQCD: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_30_50_qcd.root \
    --DataHistogram pp_smear_30_50_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_30_50_qcd.root \
    --ResponseHistogram pp_smear_30_50_c_0 \
    --ResponseTruth pp_smear_30_50_g_0 \
    --ResponseReco pp_smear_30_50_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear50QCD0.root

# PPQCDGenIso: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_30_50_qcd_gen_iso.root \
    --DataHistogram pp_smear_30_50_qcd_gen_iso_s_pure_gen_iso_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_30_50_qcd_gen_iso.root \
    --ResponseHistogram pp_smear_30_50_c_0 \
    --ResponseTruth pp_smear_30_50_g_0 \
    --ResponseReco pp_smear_30_50_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear50QCDGenIso0.root

# PPJEUUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_30_50.root \
    --DataHistogram pp_smear_30_50_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_30_50_jeu_up.root \
    --ResponseHistogram pp_smear_30_50_c_0 \
    --ResponseTruth pp_smear_30_50_g_0 \
    --ResponseReco pp_smear_30_50_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear50JEUUp0.root

# PPJEUDown: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_30_50.root \
    --DataHistogram pp_smear_30_50_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_30_50_jeu_down.root \
    --ResponseHistogram pp_smear_30_50_c_0 \
    --ResponseTruth pp_smear_30_50_g_0 \
    --ResponseReco pp_smear_30_50_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear50JEUDown0.root

# PPJERUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_30_50.root \
    --DataHistogram pp_smear_30_50_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_30_50_jer_up.root \
    --ResponseHistogram pp_smear_30_50_c_0 \
    --ResponseTruth pp_smear_30_50_g_0 \
    --ResponseReco pp_smear_30_50_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear50JERUp0.root

# PPNominal: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_10_30.root \
    --DataHistogram pp_smear_10_30_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_10_30.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear30Nominal0.root

# PPWithoutEleRej: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_10_30_wo_ele_rej.root \
    --DataHistogram pp_smear_10_30_wo_ele_rej_s_pure_wo_ele_rej_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_10_30_wo_ele_rej.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear30WithoutEleRej0.root

# PPTightPurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_10_30_tight_purity.root \
    --DataHistogram pp_smear_10_30_tight_purity_s_pure_tight_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_10_30_tight_purity.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear30TightPurity0.root

# PPLoosePurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_10_30_loose_purity.root \
    --DataHistogram pp_smear_10_30_loose_purity_s_pure_loose_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_10_30_loose_purity.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear30LoosePurity0.root

# PPQCD: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_10_30_qcd.root \
    --DataHistogram pp_smear_10_30_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_10_30_qcd.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear30QCD0.root

# PPQCDGenIso: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_10_30_qcd_gen_iso.root \
    --DataHistogram pp_smear_10_30_qcd_gen_iso_s_pure_gen_iso_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_10_30_qcd_gen_iso.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear30QCDGenIso0.root

# PPJEUUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_10_30.root \
    --DataHistogram pp_smear_10_30_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_10_30_jeu_up.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear30JEUUp0.root

# PPJEUDown: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_10_30.root \
    --DataHistogram pp_smear_10_30_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_10_30_jeu_down.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear30JEUDown0.root

# PPJERUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_10_30.root \
    --DataHistogram pp_smear_10_30_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_10_30_jer_up.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear30JERUp0.root

# PPNominal: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_0_10.root \
    --DataHistogram pp_smear_0_10_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_0_10.root \
    --ResponseHistogram pp_smear_0_10_c_0 \
    --ResponseTruth pp_smear_0_10_g_0 \
    --ResponseReco pp_smear_0_10_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear10Nominal0.root

# PPWithoutEleRej: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_0_10_wo_ele_rej.root \
    --DataHistogram pp_smear_0_10_wo_ele_rej_s_pure_wo_ele_rej_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_0_10_wo_ele_rej.root \
    --ResponseHistogram pp_smear_0_10_c_0 \
    --ResponseTruth pp_smear_0_10_g_0 \
    --ResponseReco pp_smear_0_10_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear10WithoutEleRej0.root

# PPTightPurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_0_10_tight_purity.root \
    --DataHistogram pp_smear_0_10_tight_purity_s_pure_tight_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_0_10_tight_purity.root \
    --ResponseHistogram pp_smear_0_10_c_0 \
    --ResponseTruth pp_smear_0_10_g_0 \
    --ResponseReco pp_smear_0_10_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear10TightPurity0.root

# PPLoosePurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_0_10_loose_purity.root \
    --DataHistogram pp_smear_0_10_loose_purity_s_pure_loose_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_0_10_loose_purity.root \
    --ResponseHistogram pp_smear_0_10_c_0 \
    --ResponseTruth pp_smear_0_10_g_0 \
    --ResponseReco pp_smear_0_10_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear10LoosePurity0.root

# PPQCD: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_0_10_qcd.root \
    --DataHistogram pp_smear_0_10_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_0_10_qcd.root \
    --ResponseHistogram pp_smear_0_10_c_0 \
    --ResponseTruth pp_smear_0_10_g_0 \
    --ResponseReco pp_smear_0_10_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear10QCD0.root

# PPQCDGenIso: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_0_10_qcd_gen_iso.root \
    --DataHistogram pp_smear_0_10_qcd_gen_iso_s_pure_gen_iso_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_0_10_qcd_gen_iso.root \
    --ResponseHistogram pp_smear_0_10_c_0 \
    --ResponseTruth pp_smear_0_10_g_0 \
    --ResponseReco pp_smear_0_10_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear10QCDGenIso0.root

# PPJEUUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_0_10.root \
    --DataHistogram pp_smear_0_10_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_0_10_jeu_up.root \
    --ResponseHistogram pp_smear_0_10_c_0 \
    --ResponseTruth pp_smear_0_10_g_0 \
    --ResponseReco pp_smear_0_10_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear10JEUUp0.root

# PPJEUDown: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_0_10.root \
    --DataHistogram pp_smear_0_10_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_0_10_jeu_down.root \
    --ResponseHistogram pp_smear_0_10_c_0 \
    --ResponseTruth pp_smear_0_10_g_0 \
    --ResponseReco pp_smear_0_10_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear10JEUDown0.root

# PPJERUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/${set}/accumulate_pp_smear_0_10.root \
    --DataHistogram pp_smear_0_10_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/${set}/vacillate_weight_pp_smear_0_10_jer_up.root \
    --ResponseHistogram pp_smear_0_10_c_0 \
    --ResponseTruth pp_smear_0_10_g_0 \
    --ResponseReco pp_smear_0_10_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output OutputWeighted/${set}/PPSmear10JERUp0.root