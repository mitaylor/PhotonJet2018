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

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

#include <memory>
#include <string>
#include <vector>
#include <ctime>

using namespace std::literals::string_literals;
using namespace std::placeholders;

int remove_extra_bins(char const* config, char const* output) {
    auto conf = new configurer(config);

    auto victim = conf->get<std::string>("victim");
    auto labels = conf->get<std::vector<std::string>>("labels");

    auto rdrr = conf->get<std::vector<float>>("drr_range");
    auto rdphir = conf->get<std::vector<float>>("dphir_range");
    auto rptr = conf->get<std::vector<float>>("ptr_range");

    auto idrr = new interval(rdrr);
    auto idphir = new interval(rdphir);
    auto iptr = new interval(rptr);

    auto mdr = new multival(*idrr, *iptr);
    auto mdphi = new multival(*idphir, *iptr);

    /* manage memory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    TFile* f = new TFile(victim.data(), "read");
    std::vector<history<TH1F>*> new_hists(labels.size(), nullptr);

    /* prepare output */
    TFile* fout = new TFile(output, "recreate");

    for (auto label : labels) {
        auto hist = new history<TH1F>(f, label);
        auto new_hist = new history<TH1F>(*hist, "");

        for (int64_t i = 0; i < hist->size(); ++i) {
            auto name = (*hist)[i]->GetName();


            std::cout << (*hist)[0]->GetNbinsX() << " " << mdr->size() << " " << mdphi->size() << std::endl;
            
            if ((*hist)[0]->GetNbinsX() == 240) {
                auto temp = new TH1F(name, ";index;", mdr->size(), 0, mdr->size());

                for (int j = 0; j < mdr->size(); ++j) {
                    temp->SetBinContent(j + 1, (*hist)[i]->GetBinContent((*hist)[i]->GetNbinsX() - mdr->size() + j + 1));
                    temp->SetBinError(j + 1, (*hist)[i]->GetBinError((*hist)[i]->GetNbinsX() - mdr->size() + j + 1));
                }

                delete (*new_hist)[i];
                (*new_hist)[i] = (TH1F*) temp;
            }
            if ((*hist)[0]->GetNbinsX() == 224) {
                auto temp = new TH1F(name, ";index;", mdphi->size(), 0, mdphi->size());

                for (int j = 0; j < mdphi->size(); ++j) {
                    temp->SetBinContent(j + 1, (*hist)[i]->GetBinContent((*hist)[i]->GetNbinsX() - mdphi->size() + j + 1));
                    temp->SetBinError(j + 1, (*hist)[i]->GetBinError((*hist)[i]->GetNbinsX() - mdphi->size() + j + 1));
                }

                delete (*new_hist)[i];
                (*new_hist)[i] = (TH1F*) temp;
            }
        }

        new_hist->rename(label);
        new_hist->save();
    }

    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return remove_extra_bins(argv[1], argv[2]);

    printf("usage: %s [config] [output]\n", argv[0]);
    return 1;
}
