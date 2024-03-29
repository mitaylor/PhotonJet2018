#include "../include/lambdas.h"
#include "../include/pjtree.h"
#include "../include/specifics.h"

#include "../git/config/include/configurer.h"

#include "../git/history/include/interval.h"
#include "../git/history/include/multival.h"
#include "../git/history/include/history.h"

#include "../git/paper-and-pencil/include/paper.h"
#include "../git/paper-and-pencil/include/pencil.h"

#include "../git/tricks-and-treats/include/trunk.h"

#include "TMath.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TProfile.h"
#include "TLatex.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std::literals::string_literals;
using namespace std::placeholders;

static float dr2(float eta1, float eta2, float phi1, float phi2) {
    auto deta = eta1 - eta2;
    float dphi = std::abs(phi1 - phi2);
    if (dphi > TMath::Pi()) dphi = std::abs(dphi - 2*TMath::Pi());

    return deta * deta + dphi * dphi;
}

int hf_shift(char const* config, char const* selections, char const* output) {
    auto conf = new configurer(config);

    auto hp_input = conf->get<std::vector<std::string>>("hp_input");
    auto mb_input = conf->get<std::vector<std::string>>("mb_input");

    auto tag = conf->get<std::string>("tag");

    auto sel = new configurer(selections);

    auto set = sel->get<std::string>("set");

    auto const photon_pt_min = sel->get<float>("photon_pt_min");
    auto const photon_pt_max = sel->get<float>("photon_pt_max");
    auto const photon_eta_abs = sel->get<float>("photon_eta_abs");
    auto const hovere_max = sel->get<float>("hovere_max");
    auto const see_max = sel->get<float>("see_max");
    auto const iso_max = sel->get<float>("iso_max");

    TH1::SetDefaultSumw2();
    
    /* define histograms */
    auto irho = new interval("#rho"s, 100, 0, 400);
    auto ihf = new interval("HF Energy"s, 100, 0, 1000000); 
    auto in = new interval("Ncoll"s, 100, 1.712, 2100);

    auto mhn = new multival(*ihf, *in);
    auto mrn = new multival(*irho, *in);

    auto fhn = std::bind(&multival::book<TH2F>, mhn, _1, _2, _3); // hf:ncoll
    auto frn = std::bind(&multival::book<TH2F>, mrn, _1, _2, _3); // rho:ncoll

    auto hp_hn = new history<TH2F>("hp_hn"s, "Pythia+Hydjet", fhn, 1);
    auto mb_hn = new history<TH2F>("mb_hn"s, "Hydjet", fhn, 1);

    auto hp_rn = new history<TH2F>("hp_rn"s, "Pythia+Hydjet", frn, 1);
    auto mb_rn = new history<TH2F>("mb_rn"s, "Hydjet", frn, 1);

    auto fhnp = [&](int64_t, std::string const& name, std::string const& label) {
        return new TProfile(name.data(), (";Ncoll;HF Energy;"s + label).data(), 100, 1.712, 2100, 0, 1000000, "LE"); };
    auto frnp = [&](int64_t, std::string const& name, std::string const& label) {
        return new TProfile(name.data(), (";Ncoll;#rho;"s + label).data(), 100, 1.712, 2100, 0, 400, "LE"); };

    auto hp_hn_p = new history<TProfile>("hp_hn_p"s, "Pythia+Hydjet", fhnp, 1);
    auto mb_hn_p = new history<TProfile>("mb_hn_p"s, "Hydjet", fhnp, 1);

    auto hp_rn_p = new history<TProfile>("hp_rn_p"s, "Pythia+Hydjet", frnp, 1);
    auto mb_rn_p = new history<TProfile>("mb_rn_p"s, "Hydjet", frnp, 1);

    /* read input files */
    for (auto const& file : hp_input) {
        std::cout << file << std::endl;

        TFile* hp_f = new TFile(file.data(), "read");
        TTree* hp_t = (TTree*) hp_f->Get("pj");
        auto hp_pjt = new pjtree(true, false, true, hp_t, { 1, 1, 1, 1, 1, 0, 1, 1, 0 });
        int64_t nentries = static_cast<int64_t>(hp_t->GetEntries());

        for (int64_t i = 0; i < nentries; ++i) {
            if (i % 10000 == 0) printf("entry: %li/%li\n", i, nentries);

            hp_t->GetEntry(i);

            if (std::abs(hp_pjt->vz) > 15) { continue; }

            int64_t photon_index = -1;
            float photon_pt = 0;

            for (int64_t j = 0; j < hp_pjt->nPho; ++j) {
                auto temp_photon_pt = (*hp_pjt->phoEt)[j];

                if (temp_photon_pt <= 30) { continue; }
                if (std::abs((*hp_pjt->phoEta)[j]) >= photon_eta_abs) { continue; }
                if ((*hp_pjt->phoHoverE)[j] > hovere_max) { continue; }

                temp_photon_pt = (*hp_pjt->phoEtErNew)[j];

                if (temp_photon_pt < photon_pt_min || temp_photon_pt > photon_pt_max) { continue; }
                
                if (temp_photon_pt > photon_pt) {
                    photon_index = j;
                    photon_pt = temp_photon_pt;
                }
            }

            /* require leading photon */
            if (photon_index < 0) { continue; }
            if ((*hp_pjt->phoSigmaIEtaIEta_2012)[photon_index] > see_max) { continue; }

            /* hem failure region exclusion */
            if (in_pho_failure_region(hp_pjt, photon_index)) { continue; }

            /* isolation requirement */
            if ((*hp_pjt->pho_ecalClusterIsoR3)[photon_index] + (*hp_pjt->pho_hcalRechitIsoR3)[photon_index] + (*hp_pjt->pho_trackIsoR3PtCut20)[photon_index] > iso_max) { continue; }

            /* leading photon axis */
            auto photon_eta = (*hp_pjt->phoEta)[photon_index];
            auto photon_phi = (*hp_pjt->phoPhi)[photon_index];

            /* electron rejection */
            bool electron = false;

            for (int64_t j = 0; j < hp_pjt->nEle; ++j) {
                if (std::abs((*hp_pjt->eleEta)[j]) > 1.4442) { continue; }

                auto dr = std::sqrt(dr2(photon_eta, (*hp_pjt->eleEta)[j], photon_phi, (*hp_pjt->elePhi)[j]));

                if (dr < 0.1 && passes_electron_id<det::barrel, wp::loose, pjtree>(hp_pjt, j, true)) {
                    electron = true; break;
                }
            }

            if (electron) { continue; }

            auto avg_rho = get_avg_rho(hp_pjt, -photon_eta_abs, photon_eta_abs);
            float pf_sum = 0;

            for (size_t j = 0; j < hp_pjt->pfEnergy->size(); ++j) {
                if (std::abs((*hp_pjt->pfEta)[j]) > 3 && std::abs((*hp_pjt->pfEta)[j]) < 5) {
                    pf_sum += (*hp_pjt->pfEnergy)[j];
                }
            }

            (*hp_hn)[0]->Fill(pf_sum, hp_pjt->Ncoll, hp_pjt->w);
            (*hp_rn)[0]->Fill(avg_rho, hp_pjt->Ncoll, hp_pjt->w);

            (*hp_hn_p)[0]->Fill(hp_pjt->Ncoll, pf_sum, hp_pjt->w);
            (*hp_rn_p)[0]->Fill(hp_pjt->Ncoll, avg_rho, hp_pjt->w);
        }

        hp_f->Close();
    }

    for (auto const& file : mb_input) {
        std::cout << file << std::endl;

        TFile* mb_f = new TFile(file.data(), "read");
        TTree* mb_t = (TTree*) mb_f->Get("pj");
        auto mb_pjt = new pjtree(true, false, true, mb_t, { 1, 1, 1, 1, 1, 0, 1, 1, 0 });
        int64_t nentries = static_cast<int64_t>(mb_t->GetEntries());

        for (int64_t i = 0; i < nentries; ++i) {
            if (i % 10000 == 0) printf("entry: %li/%li\n", i, nentries);

            mb_t->GetEntry(i);

            auto avg_rho = get_avg_rho(mb_pjt, -photon_eta_abs, photon_eta_abs);
            float pf_sum = 0;

            for (size_t j = 0; j < mb_pjt->pfEnergy->size(); ++j) {
                if (std::abs((*mb_pjt->pfEta)[j]) > 3 && std::abs((*mb_pjt->pfEta)[j]) < 5) {
                    pf_sum += (*mb_pjt->pfEnergy)[j];
                }
            }

            (*mb_hn)[0]->Fill(pf_sum, mb_pjt->Ncoll, mb_pjt->w);
            (*mb_rn)[0]->Fill(avg_rho, mb_pjt->Ncoll, mb_pjt->w);

            (*mb_hn_p)[0]->Fill(mb_pjt->Ncoll, pf_sum, mb_pjt->w);
            (*mb_rn_p)[0]->Fill(mb_pjt->Ncoll, avg_rho, mb_pjt->w);
        }

        mb_f->Close();
    }

    /* subtract distributions */
    auto hp_hn_h = new TH1F("hp_hn_h", ";;Orange - Purple", 100, 1.712, 2100);
    auto hp_rn_h = new TH1F("hp_rn_h", ";;Orange - Purple", 100, 1.712, 2100);

    auto mb_hn_h = new TH1F("mb_hn_h", ";;Orange - Purple", 100, 1.712, 2100);
    auto mb_rn_h = new TH1F("mb_rn_h", ";;Orange - Purple", 100, 1.712, 2100);

    for (int i = 1; i <= hp_hn_h->GetNbinsX(); ++i) {
        hp_hn_h->SetBinContent(i, (*hp_hn_p)[0]->GetBinContent(i));
        hp_hn_h->SetBinError(i, (*hp_hn_p)[0]->GetBinError(i));
        hp_rn_h->SetBinContent(i, (*hp_rn_p)[0]->GetBinContent(i));
        hp_rn_h->SetBinError(i, (*hp_rn_p)[0]->GetBinError(i));
        mb_hn_h->SetBinContent(i, (*mb_hn_p)[0]->GetBinContent(i));
        mb_hn_h->SetBinError(i, (*mb_hn_p)[0]->GetBinError(i));
        mb_rn_h->SetBinContent(i, (*mb_rn_p)[0]->GetBinContent(i));
        mb_rn_h->SetBinError(i, (*mb_rn_p)[0]->GetBinError(i));
    }

    if (!(hp_hn_h->GetSumw2N() > 0)) hp_hn_h->Sumw2(true);
    if (!(hp_rn_h->GetSumw2N() > 0)) hp_rn_h->Sumw2(true);

    hp_hn_h->Add(mb_hn_h, -1);
    hp_rn_h->Add(mb_rn_h, -1);

    hp_hn_h->SetMaximum(10000);
    hp_hn_h->SetMinimum(-100);
    hp_rn_h->SetMaximum(10);
    hp_rn_h->SetMinimum(-1);

    /* fit to a constant function */
    hp_hn_h->Fit("pol0", "", "", 1.712, 1737.0);
    hp_rn_h->Fit("pol0", "", "", 1.712, 1737.0);

    auto hp_hn_h_fit = hp_hn_h->GetFunction("pol0");
    auto hp_rn_h_fit = hp_rn_h->GetFunction("pol0");

    auto hp_hn_h_mean = hp_hn_h_fit->GetParameter(0);
    auto hp_hn_h_error = hp_hn_h_fit->GetParError(0);
    auto hp_rn_h_mean = hp_rn_h_fit->GetParameter(0);
    auto hp_rn_h_error = hp_rn_h_fit->GetParError(0);

    std::cout << "HF difference: " << hp_hn_h->GetMean(2) << " - " << mb_hn_h->GetMean(2) << std::endl;
    std::cout << "HF error: " << hp_hn_h->GetMeanError(2) << " - " << mb_hn_h->GetMeanError(2) << std::endl;
    std::cout << "Fit HF difference: " << hp_hn_h_mean << std::endl;
    std::cout << "Fit HF error: " << hp_hn_h_error << std::endl;

    std::cout << "Rho difference: " << hp_rn_h->GetMean(2) << " - " << mb_rn_h->GetMean(2) << std::endl;
    std::cout << "Rho error: " << hp_rn_h->GetMeanError(2) << " - " << mb_rn_h->GetMeanError(2) << std::endl;
    std::cout << "Fit Rho difference: " << hp_rn_h_mean << std::endl;
    std::cout << "Fit Rho error: " << hp_rn_h_error << std::endl;

    auto hn_fit_info = [&](int64_t index) {
        if (index == 2) {
            char buffer[128] = { '\0' };
            sprintf(buffer, "Mean = %.3f +- %.3f", hp_hn_h_mean, hp_hn_h_error);

            TLatex* hn_mean = new TLatex();
            hn_mean->SetTextFont(43);
            hn_mean->SetTextSize(12);

            hn_mean->DrawLatexNDC(0.2, 0.2, buffer);
        }
    };

    auto rn_fit_info = [&](int64_t index) {
        if (index == 2) {
            char buffer[128] = { '\0' };
            sprintf(buffer, "Mean = %.3f +- %.3f", hp_rn_h_mean, hp_rn_h_error);

            TLatex* rn_mean = new TLatex();
            rn_mean->SetTextFont(43);
            rn_mean->SetTextSize(12);

            rn_mean->DrawLatexNDC(0.2, 0.2, buffer);
        }
    };

    /* draw rho distributions */
    /* draw distributions */
    auto system_tag = "PbPb #sqrt{s_{NN}} = 5.02 TeV"s; 
    auto cms = "#bf{#scale[1.4]{CMS}} #it{#scale[1.2]{Simulation}}"s;

    auto hb = new pencil();
    hb->category("type", "Pythia+Hydjet", "Hydjet"); 

    auto c3 = new paper(set + "_" + tag + "_pythia_hydjet_hf_v_ncoll", hb); 
    apply_style(c3, cms, system_tag);
    c3->set(paper::flags::logz);
    c3->add((*hp_hn)[0], "Pythia+Hydjet");
    c3->adjust((*hp_hn)[0], "col", "");

    auto c4 = new paper(set + "_" + tag + "_hydjet_hf_v_ncoll", hb);
    apply_style(c4, cms, system_tag);
    c4->set(paper::flags::logz);
    c4->add((*mb_hn)[0], "Hydjet");
    c4->adjust((*mb_hn)[0], "col", "");

    auto c5 = new paper(set + "_" + tag + "_pythia_hydjet_rho_v_ncoll", hb); 
    apply_style(c5, cms, system_tag);
    c5->set(paper::flags::logz);
    c5->add((*hp_rn)[0], "Pythia+Hydjet");
    c5->adjust((*hp_rn)[0], "col", "");

    auto c6 = new paper(set + "_" + tag + "_hydjet_rho_v_ncoll", hb);
    apply_style(c6, cms, system_tag);
    c6->set(paper::flags::logz);
    c6->add((*mb_rn)[0], "Hydjet");
    c6->adjust((*mb_rn)[0], "col", "");

    auto c8 = new paper(set + "_" + tag + "_comp_hf_v_ncoll", hb);
    c8->divide(1, -1);
    apply_style(c8, cms, system_tag);
    c8->add((*mb_hn_p)[0], "Hydjet");
    c8->stack((*hp_hn_p)[0], "Pythia+Hydjet");
    c8->add(hp_hn_h);
    c8->accessory(hn_fit_info);

    auto c9 = new paper(set + "_" + tag + "_comp_rho_v_ncoll", hb);
    c9->divide(1, -1);
    apply_style(c9, cms, system_tag);
    c9->add((*mb_rn_p)[0], "Hydjet");
    c9->stack((*hp_rn_p)[0], "Pythia+Hydjet");
    c9->add(hp_rn_h);
    c9->accessory(rn_fit_info);

    auto hp_style = [](TH1* h) {
        h->SetMarkerStyle(34);
        h->SetMarkerColor(95);
        h->SetMarkerSize(0.60);
    };

    auto mb_style = [](TH1* h) {
        h->SetMarkerStyle(34);
        h->SetMarkerColor(51);
        h->SetMarkerSize(0.60);
    };

    hb->style("Hydjet", mb_style);
    hb->style("Pythia+Hydjet", hp_style);

    hb->sketch();
    c3->draw("pdf");
    c4->draw("pdf");
    c5->draw("pdf");
    c6->draw("pdf");
    c8->draw("pdf");
    c9->draw("pdf");

    auto fout = new TFile(output, "recreate");

    hp_hn->save();
    hp_rn->save();
    mb_hn->save();
    mb_rn->save();
    hp_hn_h->Write();
    hp_rn_h->Write();

    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return hf_shift(argv[1], argv[2], argv[3]);

    printf("usage: %s [config] [selections] [output]\n", argv[0]);
    return 1;
}