#include "../include/lambdas.h"

#include "../git/config/include/configurer.h"

#include "../git/history/include/interval.h"
#include "../git/history/include/multival.h"
#include "../git/history/include/history.h"

#include "../git/paper-and-pencil/include/paper.h"
#include "../git/paper-and-pencil/include/pencil.h"

#include "../git/tricks-and-treats/include/trunk.h"
#include "../git/tricks-and-treats/include/zip.h"

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"

using namespace std::literals::string_literals;
using namespace std::placeholders;

template <typename... T>
void title(std::function<void(TH1*)> f, T*&... args) {
    (void)(int [sizeof...(T)]) { (args->apply(f), 0)... };
}

template <typename... T>
void normalise_to_unity(T*&... args) {
    (void)(int [sizeof...(T)]) { (args->apply([](TH1* obj) {
        obj->Scale(1. / obj->Integral()); }), 0)... };
}

template <typename... T>
void scale_bin_width(T*... args) {
    (void)(int [sizeof...(T)]) { (args->apply([](TH1* obj) {
        obj->Scale(1., "width"); }), 0)... };
}

int compare_photon_pt_spectrum(char const* config, char const* selections, const char* output) {
    auto conf = new configurer(config);

    auto input_aa = conf->get<std::string>("input_aa");
    auto input_pp = conf->get<std::string>("input_pp");

    auto input_accumulate_aa = conf->get<std::string>("input_accumulate_aa");
    auto input_accumulate_pp = conf->get<std::string>("input_accumulate_pp");

    auto accumulate_label_aa = conf->get<std::string>("accumulate_label_aa");
    auto accumulate_label_pp = conf->get<std::string>("accumulate_label_pp");

    auto input_populate_aa = conf->get<std::string>("input_populate_aa");
    auto input_populate_pp = conf->get<std::string>("input_populate_pp");

    auto input_purity_aa = conf->get<std::string>("input_purity_aa");
    auto input_purity_pp = conf->get<std::string>("input_purity_pp");

    auto purity_label_aa = conf->get<std::string>("purity_label_aa");
    auto purity_label_pp = conf->get<std::string>("purity_label_pp");

    auto dhf = conf->get<std::vector<float>>("hf_diff");
    auto dcent = conf->get<std::vector<int32_t>>("cent_diff");

    /* selections */
    auto sel = new configurer(selections);

    auto set = sel->get<std::string>("set");
    auto base = sel->get<std::string>("base");

    // auto heavyion = sel->get<bool>("heavyion");

    auto dpt = sel->get<std::vector<float>>("photon_pt_diff");

    /* load history objects */
    TFile* f_aa = new TFile((base + input_aa).data(), "read");
    TFile* f_pp = new TFile((base + input_pp).data(), "read");

    TFile* f_accumulate_aa = new TFile((base + input_accumulate_aa).data(), "read");
    TFile* f_accumulate_pp = new TFile((base + input_accumulate_pp).data(), "read");

    TFile* f_populate_aa = new TFile((base + input_populate_aa).data(), "read");
    TFile* f_populate_pp = new TFile((base + input_populate_pp).data(), "read");

    TFile* f_purity_aa = new TFile((base + input_purity_aa).data(), "read");
    TFile* f_purity_pp = new TFile((base + input_purity_pp).data(), "read");

    auto h_aa_construct_populate = new history<TH1F>(f_aa, "raw_spectrum_photon");
    h_aa_construct_populate->rename("h_aa_construct_populate");
    auto h_pp_construct_populate = new history<TH1F>(f_pp, "raw_spectrum_photon");
    h_pp_construct_populate->rename("h_pp_construct_populate");

    auto h_aa_construct_vacillate = new history<TH1F>(f_aa, "raw_mc_spectrum_photon");
    h_aa_construct_vacillate->rename("h_aa_construct_vacillate");
    auto h_pp_construct_vacillate = new history<TH1F>(f_pp, "raw_mc_spectrum_photon");
    h_pp_construct_vacillate->rename("h_pp_construct_vacillate");

    auto h_aa_accumulate_nevt = new history<TH1F>(f_accumulate_aa, accumulate_label_aa);
    h_aa_accumulate_nevt->rename("h_aa_accumulate_nevt");
    auto h_pp_accumulate_nevt = new history<TH1F>(f_accumulate_pp, accumulate_label_pp);
    h_pp_accumulate_nevt->rename("h_pp_accumulate_nevt");

    auto h_aa_populate_nevt = new history<TH1F>(f_populate_aa, "raw_nevt");
    h_aa_populate_nevt->rename("h_aa_populate_nevt");
    auto h_pp_populate_nevt = new history<TH1F>(f_populate_pp, "raw_nevt");
    h_pp_populate_nevt->rename("h_pp_populate_nevt");

    auto h_aa_purity = new history<TH1F>(f_purity_aa, purity_label_aa + "_pthf");
    auto h_pp_purity = new history<TH1F>(f_purity_pp, purity_label_pp + "_pthf");

    /* create intervals and multivals */
    auto mpthf_long = new multival(dpt, dhf);

    dpt.pop_back();

    auto mpthf_trunc = new multival(dpt, dhf);
    auto ihf = new interval(dhf);
    auto ipt = new interval(dpt);

    auto fpt = std::bind(&interval::book<TH1F>, ipt, _1, _2, _3);

    auto h_aa_construct_accumulate = new history<TH1F>("h_aa_construct_accumulate"s, "", fpt, ihf->size());
    auto h_pp_construct_accumulate = new history<TH1F>("h_pp_construct_accumulate"s, "", fpt, 1);

    auto h_aa_accumulate = new history<TH1F>("h_aa_accumulate"s, "", fpt, ihf->size());
    auto h_pp_accumulate = new history<TH1F>("h_pp_accumulate"s, "", fpt, 1);

    auto h_aa_populate = new history<TH1F>("h_aa_populate"s, "", fpt, ihf->size());
    auto h_pp_populate = new history<TH1F>("h_pp_populate"s, "", fpt, 1);

    /* set histogram contents */
    for (int64_t i = 0; i < ihf->size(); ++i) {
        for (int j = 0; j < ipt->size(); ++j) {
            auto index_long = mpthf_long->index_for(x{j, i});
            auto index_trunc = mpthf_trunc->index_for(x{j, i});

            (*h_aa_construct_accumulate)[i]->SetBinContent(j+1, 
                    (*h_aa_construct_populate)[i]->GetBinContent(j+1) * (*h_aa_purity)[index_long]->GetBinContent(1));
            (*h_aa_construct_accumulate)[i]->SetBinError(j+1, 
                    (*h_aa_construct_populate)[i]->GetBinError(j+1) * (*h_aa_purity)[index_long]->GetBinContent(1));

            (*h_aa_accumulate)[i]->SetBinContent(j+1, (*h_aa_accumulate_nevt)[index_trunc]->GetBinContent(1));
            (*h_aa_accumulate)[i]->SetBinError(j+1, (*h_aa_accumulate_nevt)[index_trunc]->GetBinError(1));

            (*h_aa_populate)[i]->SetBinContent(j+1, (*h_aa_populate_nevt)[index_long]->GetBinContent(1));
            (*h_aa_populate)[i]->SetBinError(j+1, (*h_aa_populate_nevt)[index_long]->GetBinError(1));
        }
    }

    for (int64_t i = 0; i < 1; ++i) {
        for (int j = 0; j < ipt->size(); ++j) {
            auto index_long = mpthf_long->index_for(x{j, i});
            auto index_trunc = mpthf_trunc->index_for(x{j, i});

            (*h_pp_construct_accumulate)[i]->SetBinContent(j+1, 
                    (*h_pp_construct_populate)[i]->GetBinContent(j+1) * (*h_pp_purity)[index_long]->GetBinContent(1));
            (*h_pp_construct_accumulate)[i]->SetBinError(j+1, 
                    (*h_pp_construct_populate)[i]->GetBinError(j+1) * (*h_pp_purity)[index_long]->GetBinContent(1));

            (*h_pp_accumulate)[i]->SetBinContent(j+1, (*h_pp_accumulate_nevt)[index_trunc]->GetBinContent(1));
            (*h_pp_accumulate)[i]->SetBinError(j+1, (*h_pp_accumulate_nevt)[index_trunc]->GetBinError(1));

            (*h_pp_populate)[i]->SetBinContent(j+1, (*h_pp_populate_nevt)[index_long]->GetBinContent(1));
            (*h_pp_populate)[i]->SetBinError(j+1, (*h_pp_populate_nevt)[index_long]->GetBinError(1));
        }
    }

    /* create merged histograms */
    auto h_aa_construct_vacillate_merge = h_aa_construct_vacillate->extend("merge", 0, 1)->sum(1);
    auto h_pp_construct_vacillate_merge = h_pp_construct_vacillate->extend("merge", 0, 1)->sum(1);

    auto h_aa_construct_accumulate_merge = h_aa_construct_accumulate->extend("merge", 0, 1)->sum(1);
    auto h_pp_construct_accumulate_merge = h_pp_construct_accumulate->extend("merge", 0, 1)->sum(1);

    /* normalize */
    scale_bin_width(h_aa_construct_populate, h_pp_construct_populate);
    scale_bin_width(h_aa_construct_accumulate, h_pp_construct_accumulate);
    scale_bin_width(h_aa_construct_vacillate, h_pp_construct_vacillate);
    scale_bin_width(h_aa_accumulate, h_pp_accumulate);
    scale_bin_width(h_aa_populate, h_pp_populate);
    scale_bin_width(h_aa_construct_vacillate_merge, h_pp_construct_vacillate_merge);
    scale_bin_width(h_aa_construct_accumulate_merge, h_pp_construct_accumulate_merge);

    normalise_to_unity(h_aa_construct_populate, h_pp_construct_populate);
    normalise_to_unity(h_aa_construct_accumulate, h_pp_construct_accumulate);
    normalise_to_unity(h_aa_construct_vacillate, h_pp_construct_vacillate);
    normalise_to_unity(h_aa_accumulate, h_pp_accumulate);
    normalise_to_unity(h_aa_populate, h_pp_populate);
    normalise_to_unity(h_aa_construct_vacillate_merge, h_pp_construct_vacillate_merge);
    normalise_to_unity(h_aa_construct_accumulate_merge, h_pp_construct_accumulate_merge);

    /* create ratio */
    auto h_accumulate_ratio_merge = new history<TH1F>("h_accumulate_ratio_merge"s, "", fpt, 1);
    auto h_vacillate_ratio_merge = new history<TH1F>("h_vacillate_ratio_merge"s, "", fpt, 1);

    (*h_accumulate_ratio_merge)[0]->Divide((*h_aa_construct_accumulate_merge)[0], (*h_pp_construct_accumulate_merge)[0]);
    (*h_vacillate_ratio_merge)[0]->Divide((*h_aa_construct_vacillate_merge)[0], (*h_pp_construct_vacillate_merge)[0]);

    /* set up figures */
    auto system_tag = "  #sqrt{s_{NN}} = 5.02 TeV, 1.69 nb^{-1}"s;
    auto cms = "#bf{#scale[1.4]{CMS}} #it{#scale[1.2]{Preliminary}}"s;

    std::vector<int32_t> drange = { dcent.front(), dcent.back() };
    auto range_info = [&](int64_t index) {
        info_text(index, 0.70, "Cent. %i - %i%%", drange, true); };

    auto kinematics = [&](int64_t index) {
        if (index > 0) {
            TLatex* l = new TLatex();
            l->SetTextAlign(31);
            l->SetTextFont(43);
            l->SetTextSize(12);
            l->DrawLatexNDC(0.865, 0.70, "40 < p_{T}^{#gamma} < 200, |#eta^{#gamma}| < 1.44");
        }
    };

    auto hb = new pencil();
    hb->category("type", "aa", "pp", "ratio");

    auto p7 = new paper(set + "_mc_photon_spectra_vacillate_merge", hb);
    p7->set(paper::flags::logy);
    p7->set(paper::flags::logx);
    p7->accessory(range_info);
    p7->accessory(kinematics);
    apply_style(p7, cms, system_tag);
    p7->add((*h_aa_construct_vacillate_merge)[0], "aa");
    p7->stack((*h_pp_construct_vacillate_merge)[0], "pp");
    
    auto p8 = new paper(set + "_mc_photon_spectra_accumulate_merge", hb);
    p8->set(paper::flags::logy);
    p8->set(paper::flags::logx);
    p8->accessory(range_info);
    p8->accessory(kinematics);
    apply_style(p8, cms, system_tag);
    p8->add((*h_aa_construct_accumulate_merge)[0], "aa");
    p8->stack((*h_pp_construct_accumulate_merge)[0], "pp");

    auto p9 = new paper(set + "_mc_photon_spectra_accumulate_merge_ratio", hb);
    p9->accessory(range_info);
    p9->accessory(kinematics);
    apply_style(p9, cms, system_tag);
    p9->add((*h_accumulate_ratio_merge)[0], "ratio");

    auto p10 = new paper(set + "_mc_photon_spectra_vacillate_merge_ratio", hb);
    p10->accessory(range_info);
    p10->accessory(kinematics);
    apply_style(p10, cms, system_tag);
    p10->add((*h_vacillate_ratio_merge)[0], "ratio");

    hb->sketch();

    p7->draw("pdf");
    p8->draw("pdf");
    p9->draw("pdf");
    p10->draw("pdf");

    in(output, [&]() {
        h_aa_construct_populate->save();
        h_pp_construct_populate->save();

        h_aa_construct_vacillate->save();
        h_pp_construct_vacillate->save();

        h_aa_populate->save();
        h_pp_populate->save();

        h_aa_construct_accumulate->save();
        h_pp_construct_accumulate->save();

        h_aa_accumulate->save();
        h_pp_accumulate->save();

        h_aa_construct_accumulate_merge->save();
        h_pp_construct_accumulate_merge->save();

        h_aa_construct_vacillate_merge->save();
        h_pp_construct_vacillate_merge->save();

        h_accumulate_ratio_merge->save();
        h_vacillate_ratio_merge->save();
    });

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return compare_photon_pt_spectrum(argv[1], argv[2], argv[3]);

    printf("usage: %s [config] [selections] [output]\n", argv[0]);
    return 1;
}
