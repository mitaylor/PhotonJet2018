#include "../include/lambdas.h"
#include "../include/pjtree.h"
#include "../include/specifics.h"

#include "../git/config/include/configurer.h"

#include "../git/history/include/interval.h"
#include "../git/history/include/multival.h"
#include "../git/history/include/memory.h"

#include "../git/tricks-and-treats/include/trunk.h"
#include "../git/tricks-and-treats/include/zip.h"

#include "../git/paper-and-pencil/include/paper.h"
#include "../git/paper-and-pencil/include/pencil.h"

#include "TFile.h"
#include "TTree.h"
#include "TLatex.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom3.h"
#include "TProfile.h"
#include "TMath.h"

#include <memory>
#include <string>
#include <vector>
#include <ctime>

using namespace std::literals::string_literals;
using namespace std::placeholders;

static float dr2(float eta1, float eta2, float phi1, float phi2) {
    auto deta = eta1 - eta2;
    float dphi = std::abs(phi1 - phi2);
    if (dphi > TMath::Pi()) dphi = std::abs(dphi - 2*TMath::Pi());

    return deta * deta + dphi * dphi;
}

int estimate_hf(char const* config, char const* selections, char const* output) {
    auto conf = new configurer(config);

    auto input = conf->get<std::vector<std::string>>("input");
    
    auto tag = conf->get<std::string>("tag");
    auto type = conf->get<std::string>("type");

    auto ele_rej = conf->get<bool>("electron_rejection");
    auto apply_er = conf->get<bool>("apply_er");

    auto sel = new configurer(selections);

    auto set = sel->get<std::string>("set");
    auto base = sel->get<std::string>("base");

    auto const photon_pt_min = sel->get<float>("photon_pt_min");
    auto const photon_pt_max = sel->get<float>("photon_pt_max");
    auto const photon_eta_abs = sel->get<float>("photon_eta_abs");
    auto const hovere_max = sel->get<float>("hovere_max");
    auto const see_max = sel->get<float>("see_max");
    auto const iso_max = sel->get<float>("iso_max");

    auto dpt = sel->get<std::vector<float>>("photon_pt_diff");
    dpt.pop_back();

    /* create histograms */
    int max_hf = 70000;
    int max_avg_hf = 2500;

    auto ipt = new interval(dpt);
    auto ihf = new interval("Estimated HF"s, 20, 0, max_avg_hf);

    auto fhf = std::bind(&interval::book<TH1F>, ihf, _1, _2, _3);

    auto fnvtx = [&](int64_t, std::string const& name, std::string const& label) {
        return new TProfile(name.data(), (";nVtx;HF Energy;"s + label).data(), 18, 0, 18, 0, max_hf, "LE"); };
    auto fnpu = [&](int64_t, std::string const& name, std::string const& label) {
        return new TProfile(name.data(), (";nPU;HF Energy;"s + label).data(), 18, 0, 18, 0, max_hf, "LE"); };
    auto fpv = [&](int64_t, std::string const& name, std::string const& label) {
        return new TProfile(name.data(), (";nPU;nVtx;"s + label).data(), 11, -0.5, 10.5, 0, 16, "LE"); };

    auto hf_v1 = new history<TH1F>("hf_v1"s, "", fhf, ipt->size());
    auto hf_p0 = new history<TH1F>("hf_p0"s, "", fhf, ipt->size());

    auto nvtx = new history<TProfile>("nvtx"s, "", fnvtx, 1);
    auto npu = new history<TProfile>("npu"s, "", fnpu, 1);
    auto npv = new history<TProfile>("npv"s, "", fpv, 1);

    /* manage memory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    /* load input */
    for (auto const& file : input) {
        std::cout << file << std::endl;

        TFile* f = new TFile(file.data(), "read");
        TTree* t = (TTree*)f->Get("pj");
        auto pjt = new pjtree(type == "MC", false, false, t, { 1, 1, 1, 1, 1, 0, 0, 1, 1 });
        int64_t nentries = static_cast<int64_t>(t->GetEntries());

        for (int64_t i = 0; i < nentries; ++i) {
            if (i % (nentries/20) == 0) std::cout << i << " / " << nentries << std::endl;
            
            t->GetEntry(i);
            
            if (std::abs(pjt->vz) > 15) { continue; }
            
            int64_t photon_index = -1;
            float photon_pt = 0;

            for (int64_t j = 0; j < pjt->nPho; ++j) {
                auto temp_photon_pt = (*pjt->phoEt)[j];

                if (temp_photon_pt <= 30) { continue; }
                if (std::abs((*pjt->phoEta)[j]) >= photon_eta_abs) { continue; }
                if ((*pjt->phoHoverE)[j] > hovere_max) { continue; }
                if (apply_er) temp_photon_pt = (*pjt->phoEtEr)[j];

                if (temp_photon_pt < photon_pt_min || temp_photon_pt > photon_pt_max) { continue; }

                if (temp_photon_pt > photon_pt) {
                    photon_index = j;
                    photon_pt = temp_photon_pt;
                }
            }
            
            /* require leading photon */
            if (photon_index < 0) { continue; }
            if ((*pjt->phoSigmaIEtaIEta_2012)[photon_index] > see_max) { continue; }

            /* isolation requirement */
            if ((*pjt->pho_ecalClusterIsoR3)[photon_index] + (*pjt->pho_hcalRechitIsoR3)[photon_index] + (*pjt->pho_trackIsoR3PtCut20)[photon_index] > iso_max) { continue; }
            
            /* leading photon axis */
            auto photon_eta = (*pjt->phoEta)[photon_index];
            auto photon_phi = (*pjt->phoPhi)[photon_index];

            /* electron rejection */
            if (ele_rej) {
                bool electron = false;

                for (int64_t j = 0; j < pjt->nEle; ++j) {
                    if (std::abs((*pjt->eleEta)[j]) > 1.4442) { continue; }

                    auto dr = std::sqrt(dr2(photon_eta, (*pjt->eleEta)[j], photon_phi, (*pjt->elePhi)[j]));

                    if (dr < 0.1 && passes_electron_id<det::barrel, wp::loose, pjtree>(pjt, j, false)) {
                        electron = true; break;
                    }
                }

                if (electron) { continue; }
            }

            auto pt_x = ipt->index_for(photon_pt);

            float pf_sum = 0;

            for (size_t j = 0; j < pjt->pfEnergy->size(); ++j) {
                if (std::abs((*pjt->pfEta)[j]) > 3 && std::abs((*pjt->pfEta)[j]) < 5) {
                    pf_sum += (*pjt->pfEnergy)[j];
                }
            }
            
            if (pjt->nVtx == 1) { 
                // (*hf_v1)[pt_x]->Fill(pf_sum, pjt->w);
                (*hf_v1)[pt_x]->Fill(pf_sum);
            }
            
            if (type == "MC") {
                if ((*pjt->npus)[5] == 0) { 
                    // (*hf_p0)[pt_x]->Fill(pf_sum, pjt->w);
                    (*hf_p0)[pt_x]->Fill(pf_sum);
                }
            }

            (*nvtx)[0]->Fill(pjt->nVtx, pf_sum);
            if (type == "MC") { (*npu)[0]->Fill((*pjt->npus)[5], pf_sum); }
            if (type == "MC") { (*npv)[0]->Fill((*pjt->npus)[5], pjt->nVtx); }
        }
    }

    /* save histograms */
    in(output, [&]() {
        hf_v1->save(tag);
        nvtx->save(tag);

        if (type == "MC") { hf_p0->save(tag); }
        if (type == "MC") { npu->save(tag); }
        if (type == "MC") { npv->save(tag); }
    });

    /* plot histograms */
    auto pt_info = [&](int64_t index) {
        info_text(index, 0.75, "%.0f < p_{T}^{#gamma} < %.0f", dpt, false); };

    auto mean_info = [&](history<TH1F>* h, int64_t index) {
        char buffer[128] = { '\0' };
        sprintf(buffer, "mean: %.3f +- %.3f", (*h)[index - 1]->GetMean(1), (*h)[index - 1]->GetMeanError(1));

        TLatex* text = new TLatex();
        text->SetTextFont(43);
        text->SetTextSize(12);
        text->DrawLatexNDC(0.54, 0.75, buffer);
    };

    auto hb = new pencil();
    hb->category("type", "Data", "MC");
    
    auto c1 = new paper(set + "_" + tag + "_estimated_hf_nvtx_1", hb);
    apply_style(c1, "", "pp #sqrt{s} = 5.02 TeV"s);

    c1->accessory(pt_info);
    c1->accessory(std::bind(mean_info, hf_v1, _1));
    c1->divide(ipt->size(), -1);
    // c1->set(paper::flags::logy);

    for (int64_t j = 0; j < ipt->size(); ++j) {
        c1->add((*hf_v1)[j], type);
    }

    hb->sketch();
    c1->draw("pdf");

    if (type == "MC") {
        auto c2 = new paper(set + "_" + tag + "_estimated_hf_npu_0", hb);
        apply_style(c2, "", "pp #sqrt{s} = 5.02 TeV"s);

        c2->accessory(pt_info);
        c2->accessory(std::bind(mean_info, hf_p0, _1));
        c2->divide(ipt->size(), -1);

        for (int64_t j = 0; j < ipt->size(); ++j) {
            c2->add((*hf_p0)[j], type);
        }

        hb->sketch();
        c2->draw("pdf");
    }

    auto c3 = new paper(set + "_" + tag + "_nvtx_hf", hb);
    apply_style(c3, "", "pp #sqrt{s} = 5.02 TeV"s);

    c3->add((*nvtx)[0], type);

    hb->sketch();
    c3->draw("pdf");

    if (type == "MC") {
        auto c4 = new paper(set + "_" + tag + "_npu_hf", hb);
        apply_style(c4, "", "pp #sqrt{s} = 5.02 TeV"s);

        c4->add((*npu)[0], type);

        hb->sketch();
        c4->draw("pdf");

        auto c5 = new paper(set + "_" + tag + "_npv_hf", hb);
        apply_style(c5, "", "pp #sqrt{s} = 5.02 TeV"s);

        c5->add((*npv)[0], type);

        hb->sketch();
        c5->draw("pdf");
    }

    printf("destroying objects..\n");

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return estimate_hf(argv[1], argv[2], argv[3]);

    printf("usage: %s [config] [selections] [output]\n", argv[0]);
    return 1;
}