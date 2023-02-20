#!/usr/bin/env bash

# PPNominal: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/accumulate_pp_smear_10_30.root \
    --DataHistogram pp_smear_10_30_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/vacillate_pp_smear_10_30.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output Output/PPSmear30Nominal0.root

# PPWithoutEleRej: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/accumulate_pp_smear_10_30_wo_ele_rej.root \
    --DataHistogram pp_smear_10_30_wo_ele_rej_s_pure_wo_ele_rej_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/vacillate_pp_smear_10_30_wo_ele_rej.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output Output/PPSmear30WithoutEleRej0.root

# PPTightPurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/accumulate_pp_smear_10_30_tight_purity.root \
    --DataHistogram pp_smear_10_30_tight_purity_s_pure_tight_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/vacillate_pp_smear_10_30.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output Output/PPSmear30TightPurity0.root

# PPLoosePurity: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/accumulate_pp_smear_10_30_loose_purity.root \
    --DataHistogram pp_smear_10_30_loose_purity_s_pure_loose_purity_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/vacillate_pp_smear_10_30.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output Output/PPSmear30LoosePurity0.root

# PPQCD: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/accumulate_pp_smear_10_30_qcd.root \
    --DataHistogram pp_smear_10_30_qcd_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/vacillate_pp_smear_10_30_qcd.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output Output/PPSmear30QCD0.root

# PPQCDGenIso: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/accumulate_pp_smear_10_30_qcd_gen_iso.root \
    --DataHistogram pp_smear_10_30_qcd_gen_iso_s_pure_gen_iso_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/vacillate_pp_smear_10_30_qcd_gen_iso.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output Output/PPSmear30QCDGenIso0.root

# PPJEUUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/accumulate_pp_smear_10_30.root \
    --DataHistogram pp_smear_10_30_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/vacillate_pp_smear_10_30_jeu_up.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output Output/PPSmear30JEUUp0.root

# PPJEUDown: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/accumulate_pp_smear_10_30.root \
    --DataHistogram pp_smear_10_30_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/vacillate_pp_smear_10_30_jeu_down.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output Output/PPSmear30JEUDown0.root

# PPJERUp: Execute
./Execute --Data ../../MainAnalysis/data/preapproval/accumulate_pp_smear_10_30.root \
    --DataHistogram pp_smear_10_30_nominal_s_pure_raw_sub_pjet_u_dr_sum0_0 \
    --Response ../../MainAnalysis/data/preapproval/vacillate_pp_smear_10_30_jer_up.root \
    --ResponseHistogram pp_smear_10_30_c_0 \
    --ResponseTruth pp_smear_10_30_g_0 \
    --ResponseReco pp_smear_10_30_r_0 \
    --PrimaryRecoBins 0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.105,0.12,0.135,0.15,0.18,0.21,0.3 \
    --BinningRecoBins 20,30,35,40,45,50,55,60,70,80,90,100,120,150,200 \
    --PrimaryGenBins 0,0.015,0.03,0.045,0.06,0.08,0.1,0.12,0.15,0.2,0.3 \
    --BinningGenBins 20,30,40,50,60,70,80,100,120,200 \
    --Output Output/PPSmear30JERUp0.root