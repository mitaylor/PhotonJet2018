#include "../include/lambdas.h"
#include "../include/pjtree.h"
#include "../include/specifics.h"

#include "../git/config/include/configurer.h"

#include "../git/history/include/interval.h"
#include "../git/history/include/multival.h"
#include "../git/history/include/memory.h"

#include "../git/tricks-and-treats/include/overflow_angles.h"
#include "../git/tricks-and-treats/include/trunk.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"

#include <memory>
#include <string>
#include <vector>

using namespace std::literals::string_literals;
using namespace std::placeholders;

float weight_for(std::vector<int32_t> const& divisions,
                 std::vector<float> const& weights, float value) {
    int64_t index = -1;
    for (auto edge : divisions)
        if (value > edge)
            ++index;

    return weights[index];
}

int plot_qcd(char const* config, char const* output) {
    auto conf = new configurer(config);

    auto files = conf->get<std::vector<std::string>>("files");
    auto pthat = conf->get<std::vector<int32_t>>("pthat");
    auto pthatw = conf->get<std::vector<float>>("pthatw");
    auto vzw = conf->get<std::vector<float>>("vzw");
    auto tag = conf->get<std::string>("tag");

    /* manage memory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    auto ipthat = new interval("pthat"s, 50, 0, 1000);
    auto ijetpt = new interval("jet pT (GeV)"s, 50, 0, 500);
    auto injets = new interval("#jets"s, 50, 0, 50);
    auto iphopt = new interval("photon pT (GeV)"s, 50, 0, 250);

    auto fpthat = std::bind(&interval::book<TH1F>, ipthat, _1, _2, _3);
    auto fjetpt = std::bind(&interval::book<TH1F>, ijetpt, _1, _2, _3);
    auto fnjets = std::bind(&interval::book<TH1F>, injets, _1, _2, _3);
    auto fphopt = std::bind(&interval::book<TH1F>, iphopt, _1, _2, _3);

    auto h_pthat = new history<TH1F>("h_pthat"s, "", fpthat, 1, 1);
    auto h_jetpt = new history<TH1F>("h_jetpt"s, "", fjetpt, 1, 1);
    auto h_njets = new history<TH1F>("h_njets"s, "", fnjets, 1, 1);

    auto h_refpt = new history<TH1F>("h_refpt"s, "", fjetpt, 1, 1);
    auto h_nrefs = new history<TH1F>("h_nrefs"s, "", fnjets, 1, 1);
    auto h_phopt = new history<TH1F>("h_phopt"s, "", fphopt, 1, 1);

    TF1* fweight = new TF1("fweight", "(gaus(0))/(gaus(3))");
    fweight->SetParameters(vzw[0], vzw[1], vzw[2], vzw[3], vzw[4], vzw[5]); 

    /* load input */
    for (auto const& file : files) {
        TFile* f = new TFile(file.data(), "read");
        TTree* t = (TTree*)f->Get("pj");
        auto pjt = new pjtree(true, true, true, t, { 1, 1, 1, 1, 1, 1, 0, 0, 0 });

        int64_t nentries = static_cast<int64_t>(t->GetEntries());
        for (int64_t i = 0; i < nentries; ++i) {
            if (i % 100000 == 0) { printf("entry: %li/%li\n", i, nentries); }

            t->GetEntry(i);

            int64_t leading = -1;
            float leading_pt = 0;
            for (int64_t j = 0; j < pjt->nPho; ++j) {
                if ((*pjt->phoEt)[j] <= 30) { continue; }
                if (std::abs((*pjt->phoSCEta)[j]) >= 1.442) { continue; }
                if ((*pjt->phoHoverE)[j] > 0.119947) { continue; }

                auto pho_et = (*pjt->phoEtErNew)[j];
                if (pho_et < 40) { continue; }

                if (pho_et > leading_pt) {
                    leading = j;
                    leading_pt = pho_et;
                }
            }

            /* require leading photon */
            if (leading < 0) { continue; }

            if ((*pjt->phoSigmaIEtaIEta_2012)[leading] > 0.010392
                    || (*pjt->phoSigmaIEtaIEta_2012)[leading] < 0)
                continue;

            /* hem failure region exclusion */
            if (in_pho_failure_region(pjt, leading)) { continue; }

            /* isolation requirement */
            float isolation = (*pjt->pho_ecalClusterIsoR3)[leading]
                    + (*pjt->pho_hcalRechitIsoR3)[leading]
                    + (*pjt->pho_trackIsoR3PtCut20)[leading];
            
            if (isolation > 2.099277) { continue; }

            float weight = fweight->Eval(pjt->vz) * weight_for(pthat, pthatw, pjt->pthat) * pjt->weight;

            int njet = 0;
            int nref = 0;

            (*h_pthat)[0]->Fill(pjt->pthat, weight);
            (*h_phopt)[0]->Fill(leading_pt, weight);

            for (int64_t j = 0; j < pjt->nref; ++j) {
                if (std::abs((*pjt->jteta)[j]) < 1.6 && (*pjt->jtpt)[j] > 5) {
                    (*h_jetpt)[0]->Fill((*pjt->jtpt)[j], weight);
                    njet++;

                    if ((*pjt->refpt)[j] > 0) { 
                        (*h_refpt)[0]->Fill((*pjt->refpt)[j], weight);
                        nref++; 
                    }
                }
            }

            (*h_njets)[0]->Fill(njet, weight);
            (*h_nrefs)[0]->Fill(nref, weight);
        }
    }

    (*h_pthat)[0]->Scale(1. / (*h_pthat)[0]->Integral());
    (*h_njets)[0]->Scale(1. / (*h_njets)[0]->Integral());
    (*h_jetpt)[0]->Scale(1. / (*h_jetpt)[0]->Integral());
    (*h_nrefs)[0]->Scale(1. / (*h_nrefs)[0]->Integral());
    (*h_refpt)[0]->Scale(1. / (*h_refpt)[0]->Integral());
    (*h_phopt)[0]->Scale(1. / (*h_phopt)[0]->Integral());

    in(output, [&]() {
        h_pthat->save(tag);
        h_njets->save(tag);
        h_jetpt->save(tag);
        h_nrefs->save(tag);
        h_refpt->save(tag);
        h_phopt->save(tag);
    });

    printf("destroying objects..\n");

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return plot_qcd(argv[1], argv[2]);

    printf("usage: %s [config] [output]\n", argv[0]);
    return 1;
}