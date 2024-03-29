#include "../include/lambdas.h"
#include "../include/specifics.h"
#include "../include/text.h"

#include "../git/config/include/configurer.h"

#include "../git/history/include/interval.h"
#include "../git/history/include/multival.h"
#include "../git/history/include/history.h"

#include "../git/paper-and-pencil/include/paper.h"
#include "../git/paper-and-pencil/include/pencil.h"

#include "../git/tricks-and-treats/include/overflow_angles.h"
#include "../git/tricks-and-treats/include/trunk.h"
#include "../git/tricks-and-treats/include/zip.h"

#include "TFile.h"
#include "TH1.h"

using namespace std::literals::string_literals;
using namespace std::placeholders;

template <typename... T>
void scale_bin_width(T*... args) {
    (void)(int [sizeof...(T)]) { (args->apply([](TH1* obj) {
        obj->Scale(1., "width"); }), 0)... };
}

void set_range(history<TH1F>* arg1, history<TH1F>* arg2) {
    arg1->apply([&](TH1* h1, int64_t index) {
        auto min = std::min(h1->GetMinimum(), (*arg2)[index]->GetMinimum());
        min = std::min(min, 0.0);

        auto max = std::max(h1->GetMaximum(), (*arg2)[index]->GetMaximum());

        default_formatter(h1, min*1.3, max*1.3); 
        default_formatter((*arg2)[index], min*1.3, max*1.3); 
    });
}

int jubilate(char const* config, char const* selections, char const* output) {
    auto conf = new configurer(config);

    auto input = conf->get<std::string>("input");
    auto system = conf->get<std::string>("system");
    auto tag = conf->get<std::string>("tag");

    auto comparison = conf->get<std::string>("comparison");
    auto scan = conf->get<std::string>("scan");

    auto dhf = conf->get<std::vector<float>>("hf_diff");
    auto dcent = conf->get<std::vector<int32_t>>("cent_diff");

    auto labels = conf->get<std::vector<std::string>>("labels");
    auto minimums = conf->get<std::vector<float>>("minimums");
    auto maximums = conf->get<std::vector<float>>("maximums");

    /* selections */
    auto sel = new configurer(selections);

    auto set = sel->get<std::string>("set");
    auto base = sel->get<std::string>("base");

    auto rjpt = sel->get<std::vector<float>>("jpt_range");
    auto reta = sel->get<std::vector<float>>("eta_range");
    auto rdphi = sel->get<std::vector<float>>("dphi_range");

    auto const photon_pt_min = sel->get<float>("photon_pt_min");
    auto const photon_eta_abs = sel->get<float>("photon_eta_abs");

    auto const jet_pt_min = sel->get<float>("jet_pt_min");
    auto const jet_pt_max = sel->get<float>("jet_pt_max");
    auto const jet_eta_abs = sel->get<float>("jet_eta_abs");
    
    auto const dphi_min_numerator = sel->get<float>("dphi_min_numerator");
    auto const dphi_min_denominator = sel->get<float>("dphi_min_denominator");

    auto ihf = new interval(dhf);

    /* load history objects */
    TFile* f = new TFile((base + input).data(), "read");
    TFile* t = new TFile((base + comparison).data(), "read");

    TH1::SetDefaultSumw2();

    /* define plotting accessories */
    auto hf_info = [&](int64_t index) {
        info_text(index, 0.75, "Cent. %i - %i%%", dcent, true); };

    auto hb = new pencil();
    hb->category("type", "raw", "mix", "sub", "reco", "raw/mix", "reco/mix", "sub/mix");

    auto system_tag = system + "  #sqrt{s_{NN}} = 5.02 TeV"s;
    auto cms = "#bf{#scale[1.4]{CMS}} #it{#scale[1.2]{Preliminary}}"s;

    zip([&](auto const& label, auto& min, auto& max) {
        std::cout << label << std::endl;

        auto name = "raw_"s + scan + "_"s + label;
        auto hist_raw = new history<TH1F>(f, name); 

        auto name_mix = "raw_mix_"s + scan + "_"s + label;
        auto hist_mix = new history<TH1F>(f, name_mix);

        auto name_sub = "raw_sub_"s + scan + "_"s + label;
        auto hist_sub = new history<TH1F>(f, name_sub);

        auto name_reco = "aa_reco_"s + scan + "_"s + label;
        auto hist_reco = new history<TH1F>(t, name_reco);

        auto hist_raw_ratio = new history<TH1F>(*hist_raw, "raw_ratio_"s);
        auto hist_reco_ratio = new history<TH1F>(*hist_reco, "reco_ratio_"s);
        auto hist_sub_ratio = new history<TH1F>(*hist_sub, "sub_ratio_"s);

        hist_raw_ratio->apply([&](TH1* h, int64_t index) {
            h->Divide((*hist_raw)[index], (*hist_mix)[index]);
            h->SetMaximum(1E5);
            h->SetMinimum(1E-3);
        });

        hist_reco_ratio->apply([&](TH1* h, int64_t index) {
            h->Divide((*hist_reco)[index], (*hist_mix)[index]);
            h->SetMaximum(1E5);
            h->SetMinimum(1E-3);
        });

        hist_sub_ratio->apply([&](TH1* h, int64_t index) {
            h->Divide((*hist_sub)[index], (*hist_mix)[index]);
            h->SetMaximum(1E5);
            h->SetMinimum(1E-3);
        });

        scale_bin_width(hist_raw, hist_mix, hist_sub, hist_reco);
        set_range(hist_raw, hist_mix);
        set_range(hist_sub, hist_reco);

        auto shape = hist_raw->shape(); // photon pt, scan (optional), centrality
        
        if (shape.size() == 2) {
            auto cuts_info = [&](int64_t index) {
                if (index > 0) {
                    auto photon_selections = "p_{T}^{#gamma} > "s + to_text(photon_pt_min) + " GeV, |#eta^{#gamma}| < "s + to_text(photon_eta_abs);
                    photon_selections += ", #Delta#phi_{j#gamma} > "s + to_text(dphi_min_numerator) + "#pi/"s + to_text(dphi_min_denominator);
                    auto jet_selections = "anti-k_{T} R = 0.3, |#eta^{jet}| < "s + to_text(jet_eta_abs) + ", " + to_text(jet_pt_min) + " < p_{T}^{jet} < "s + to_text(jet_pt_max) + " GeV";

                    TLatex* l = new TLatex();
                    l->SetTextAlign(31);
                    l->SetTextFont(43);
                    l->SetTextSize(11);
                    l->DrawLatexNDC(0.86, 0.65, photon_selections.data());
                    l->DrawLatexNDC(0.86, 0.60, jet_selections.data());
                }
            };

            auto c1 = new paper(set + "_"s + tag + "_mebs_"s + label, hb);
            apply_style(c1, cms, system_tag);
            c1->accessory(std::bind(line_at, _1, 0.f, min, max));
            c1->accessory(hf_info);
            c1->accessory(cuts_info);
            c1->divide(ihf->size() , -1);

            auto c2 = new paper(set + "_"s + tag + "_closure_"s + label, hb);
            apply_style(c2, cms, system_tag);
            c2->accessory(std::bind(line_at, _1, 0.f, min, max));
            c2->accessory(hf_info);
            c2->accessory(cuts_info);
            c2->divide(ihf->size() , -1);

            auto c3 = new paper(set + "_"s + tag + "_raw_to_bkg_"s + label, hb);
            apply_style(c3, cms, system_tag);
            c3->accessory(std::bind(line_at, _1, 0.f, min, max));
            c3->accessory(hf_info);
            c3->accessory(cuts_info);
            c3->divide(ihf->size() , -1);
            c3->set(paper::flags::logy);

            auto c4 = new paper(set + "_"s + tag + "_reco_to_bkg_"s + label, hb);
            apply_style(c4, cms, system_tag);
            c4->accessory(std::bind(line_at, _1, 0.f, min, max));
            c4->accessory(hf_info);
            c4->accessory(cuts_info);
            c4->divide(ihf->size() , -1);
            c4->set(paper::flags::logy);

            auto c5 = new paper(set + "_"s + tag + "_sub_to_bkg_"s + label, hb);
            apply_style(c5, cms, system_tag);
            c5->accessory(std::bind(line_at, _1, 0.f, min, max));
            c5->accessory(hf_info);
            c5->accessory(cuts_info);
            c5->divide(ihf->size() , -1);
            c5->set(paper::flags::logy);

            for (int64_t i = 0; i < hist_raw->size(); ++i) {
                c1->add((*hist_raw)[i], "raw");
                c1->stack((*hist_mix)[i], "mix");
                c2->add((*hist_sub)[i], "sub");
                c2->stack((*hist_reco)[i], "reco");
                c3->add((*hist_raw_ratio)[i], "raw/mix");
                c4->add((*hist_reco_ratio)[i], "reco/mix");
                c5->add((*hist_sub_ratio)[i], "sub/mix");
            }

            hb->sketch();
            c1->draw("pdf");
            c2->draw("pdf");
            c3->draw("pdf");
            c4->draw("pdf");
            c5->draw("pdf");
            delete c1; delete c2; delete c3; delete c4; delete c5;
        }
    }, labels, maximums, minimums);

    /* save output */
    in(output, []() {});

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return jubilate(argv[1], argv[2], argv[3]);

    printf("usage: %s [config] [selections] [output]\n", argv[0]);
    return 1;
}
