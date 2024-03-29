#include "../include/lambdas.h"
#include "../include/pjtree.h"
#include "../include/specifics.h"

#include "../git/config/include/configurer.h"

#include "../git/history/include/interval.h"
#include "../git/history/include/multival.h"
#include "../git/history/include/memory.h"

#include "../git/tricks-and-treats/include/overflow_angles.h"
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

#include <memory>
#include <string>
#include <vector>
#include <ctime>

using namespace std::literals::string_literals;
using namespace std::placeholders;

int estimate_hf(char const* config, char const* output) {
    auto conf = new configurer(config);

    auto input = conf->get<std::vector<std::string>>("input");
    
    auto tag = conf->get<std::string>("tag");
    auto type = conf->get<std::string>("type");

    auto dpt = conf->get<std::vector<float>>("pt_diff");

    /* create histograms */
    int max_hf = 70000;
    int max_avg_hf = 2500;

    auto ipt = new interval(dpt);
    auto ihf = new interval("Estimated HF"s, 20, 0, max_avg_hf);

    auto fhf = std::bind(&interval::book<TH1F>, ihf, _1, _2, _3);

    auto fncoll = [&](int64_t, std::string const& name, std::string const& label) {
        return new TProfile(name.data(), (";Ncoll;HF Energy;"s + label).data(), 18, 0, 18, 0, max_hf, "LE"); };

    auto hf_p0 = new history<TH1F>("hf_p0"s, "", fhf, ipt->size());

    auto ncoll = new history<TProfile>("ncoll"s, "", fncoll, 1);

    /* manage memory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    /* load input */

    for (auto const& file : input) {
        std::cout << file << std::endl;

        TFile* f = new TFile(file.data(), "read");
        TTree* t = (TTree*)f->Get("pj");
        auto pjt = new pjtree(type == "MC", false, true, t, { 1, 1, 1, 1, 1, 0, 0, 1, 0 });

        int64_t nentries = static_cast<int64_t>(t->GetEntries());

        for (int64_t i = 0; i < nentries; ++i) {
            if (i % (nentries/20) == 0) std::cout << i << " / " << nentries << std::endl;
            
            t->GetEntry(i);
            
            if (std::abs(pjt->vz) > 15) { continue; }
            if (pjt->Ncoll > 18) { continue; }

            auto pt_x = ipt->index_for(100);

            float pf_sum = 0;

            for (size_t j = 0; j < pjt->pfEnergy->size(); ++j) {
                if ((*pjt->pfId)[j] >= 6) {
                    pf_sum += (*pjt->pfEnergy)[j];
                }
            }
            
            if (pjt->Ncoll == 0) { 
                // (*hf_p0)[pt_x]->Fill(pf_sum, pjt->w);
                (*hf_p0)[pt_x]->Fill(pf_sum);
            }
            
            // (*ncoll)[0]->Fill(pjt->Ncoll, pf_sum, pjt->w);
            (*ncoll)[0]->Fill(pjt->Ncoll, pf_sum);
        }
    }

    /* save histograms */
    in(output, [&]() {
        hf_p0->save(tag);
        ncoll->save(tag);
    });

    /* plot histograms */
    auto pt_info = [&](int64_t index) {
        info_text(index, 0.75, "%.0f < p_{T}^{#gamma} < %.0f", dpt, false); };

    auto mean_info_pu = [&](int64_t index) {
        char buffer[128] = { '\0' };
        sprintf(buffer, "mean: %.3f +- %.3f",
            (*hf_p0)[index - 1]->GetMean(1),
            (*hf_p0)[index - 1]->GetMeanError(1));

        TLatex* text = new TLatex();
        text->SetTextFont(43);
        text->SetTextSize(12);
        text->DrawLatexNDC(0.54, 0.75, buffer);
    };

    auto hb = new pencil();
    hb->category("type", "Data", "MC");

    auto c2 = new paper(tag + "_estimated_hf_ncoll_1", hb);
    apply_style(c2, "", "PbPb #sqrt{s} = 5.02 TeV"s);

    c2->accessory(pt_info);
    c2->accessory(mean_info_pu);
    c2->divide(ipt->size(), -1);

    for (int64_t j = 0; j < ipt->size(); ++j) {
        c2->add((*hf_p0)[j], type);
    }

    hb->sketch();
    c2->draw("pdf");

    auto c3 = new paper(tag + "_ncoll_hf", hb);
    apply_style(c3, "", "PbPb #sqrt{s} = 5.02 TeV"s);

    c3->add((*ncoll)[0], type);

    hb->sketch();
    c3->draw("pdf");

    printf("destroying objects..\n");

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return estimate_hf(argv[1], argv[2]);

    printf("usage: %s [config] [output]\n", argv[0]);
    return 1;
}
