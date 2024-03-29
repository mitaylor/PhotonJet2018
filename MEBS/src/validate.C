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

void set_range(history<TH1F>* arg1, history<TH1F>* arg2, float xmin, float xmax) {
    arg1->apply([&](TH1* h1, int64_t index) {
        auto ymin = std::min(h1->GetMinimum(), (*arg2)[index]->GetMinimum());
        ymin = std::min(ymin, 0.0);

        auto ymax = std::max(h1->GetMaximum(), (*arg2)[index]->GetMaximum());

        default_formatter(h1, ymin*1.3, ymax*1.3); 
        default_formatter((*arg2)[index], ymin*1.3, ymax*1.3); 

        h1->GetXaxis()->SetRangeUser(xmin, xmax);
        (*arg2)[index]->GetXaxis()->SetRangeUser(xmin, xmax);
    });
}

int validate(char const* config, char const* selections, char const* output) {
    auto conf = new configurer(config);

    auto input_nominal = conf->get<std::string>("input_nominal");
    auto input_compare = conf->get<std::string>("input_compare");

    auto label_nominal = conf->get<std::string>("label_nominal");
    auto label_compare = conf->get<std::string>("label_compare");

    auto system = conf->get<std::string>("system");
    auto tag = conf->get<std::string>("tag");
    auto scan = conf->get<std::string>("scan");

    auto dhf = conf->get<std::vector<float>>("hf_diff");
    auto dcent = conf->get<std::vector<int32_t>>("cent_diff");

    auto labels = conf->get<std::vector<std::string>>("labels");
    auto minimums = conf->get<std::vector<float>>("minimums");
    auto maximums = conf->get<std::vector<float>>("maximums");

    auto jpt = conf->get<bool>("jpt");
    auto eta = conf->get<bool>("eta");
    auto dphi = conf->get<bool>("dphi");

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
    TFile* n = new TFile((base + input_nominal).data(), "read");
    TFile* f = new TFile((base + input_compare).data(), "read");

    TH1::SetDefaultSumw2();

    /* define plotting accessories */
    auto hf_info = [&](int64_t index) {
        info_text(index, 0.75, "Cent. %i - %i%%", dcent, true); };

    auto hb = new pencil();
    hb->category("type", label_nominal, label_compare);

    auto system_tag = system + "  #sqrt{s_{NN}} = 5.02 TeV"s;
    auto cms = "#bf{#scale[1.4]{CMS}} #it{#scale[1.2]{Preliminary}}"s;

    zip([&](auto const& label, auto& min, auto& max) {
        std::cout << label << std::endl;

        auto name = "raw_"s + scan + "_"s + label;
        auto hist_nominal = new history<TH1F>(n, name); 
        auto hist_compare = new history<TH1F>(f, name); 

        auto name_mix = "raw_mix_"s + scan + "_"s + label;
        auto hist_mix_nominal = new history<TH1F>(n, name_mix);
        auto hist_mix_compare = new history<TH1F>(f, name_mix);

        auto name_sub = "raw_sub_"s + scan + "_"s + label;
        auto hist_sub_nominal = new history<TH1F>(n, name_sub);
        auto hist_sub_compare = new history<TH1F>(f, name_sub);

        hist_compare->rename(label);
        hist_mix_compare->rename("mix_"s + label);
        hist_sub_compare->rename("sub_"s + label);

        scale_bin_width(hist_nominal, hist_mix_nominal, hist_sub_nominal);
        scale_bin_width(hist_compare, hist_mix_compare, hist_sub_compare);

        set_range(hist_nominal, hist_compare, min, max);
        set_range(hist_mix_nominal, hist_mix_compare, min, max);
        set_range(hist_sub_nominal, hist_sub_compare, min, max);

        auto shape = hist_nominal->shape(); // photon pt, scan (optional), centrality
        
        if (shape.size() == 2) {
            auto cuts_info = [&](int64_t index) {
                if (index > 0) {
                    auto photon_selections = "p_{T}^{#gamma} > "s + to_text(photon_pt_min) + " GeV, |#eta^{#gamma}| < "s + to_text(photon_eta_abs);
                    if (jpt || eta) photon_selections += ", #Delta#phi_{j#gamma} > "s + to_text(dphi_min_numerator) + "#pi/"s + to_text(dphi_min_denominator);
                    auto jet_selections = "anti-k_{T} R = 0.3, |#eta^{jet}| < "s + to_text(jet_eta_abs) + ", " + to_text(jet_pt_min) + " < p_{T}^{jet} < "s + to_text(jet_pt_max) + " GeV";

                    TLatex* l = new TLatex();
                    l->SetTextAlign(31);
                    l->SetTextFont(43);
                    l->SetTextSize(11);
                    l->DrawLatexNDC(0.86, 0.65, photon_selections.data());
                    l->DrawLatexNDC(0.86, 0.60, jet_selections.data());
                }
            };

            auto c1 = new paper(set + "_validate_"s + tag + "_raw_"s + label, hb);
            apply_style(c1, cms, system_tag);
            c1->accessory(std::bind(line_at, _1, 0.f, min, max));
            c1->accessory(hf_info);
            c1->accessory(cuts_info);
            c1->divide(ihf->size() , -1);

            auto c2 = new paper(set + "_validate_"s + tag + "_mixed_"s + label, hb);
            apply_style(c2, cms, system_tag);
            c2->accessory(std::bind(line_at, _1, 0.f, min, max));
            c2->accessory(hf_info);
            c2->accessory(cuts_info);
            c2->divide(ihf->size() , -1);

            auto c3 = new paper(set + "_validate_"s + tag + "_sub_"s + label, hb);
            apply_style(c3, cms, system_tag);
            c3->accessory(std::bind(line_at, _1, 0.f, min, max));
            c3->accessory(hf_info);
            c3->accessory(cuts_info);
            c3->divide(ihf->size() , -1);

            for (int64_t i = 0; i < hist_nominal->size(); ++i) {
                c1->add((*hist_compare)[i], label_compare);
                c1->stack((*hist_nominal)[i], label_nominal);
                c2->add((*hist_mix_compare)[i], label_compare);
                c2->stack((*hist_mix_nominal)[i], label_nominal);
                c3->add((*hist_sub_compare)[i], label_compare);
                c3->stack((*hist_sub_nominal)[i], label_nominal);
            }

            hb->sketch();
            c1->draw("pdf");
            c2->draw("pdf");
            c3->draw("pdf");
            delete c1; delete c2; delete c3;
        }

        if (shape.size() == 3) {
            std::vector<paper*> cs1(shape[1], nullptr);
            std::vector<paper*> cs2(shape[1], nullptr);
            std::vector<paper*> cs3(shape[1], nullptr);

            auto range_info = [&](int64_t index, int64_t step) {
                if (index > 0) {
                    if (jpt) { info_text(step, 0.71, "%g < p_{T}^{jet} < %g GeV", rjpt, false); }
                    if (eta) { info_text(step, 0.71, "%g < #eta^{jet} < %g", reta, false); }
                    if (dphi) { info_text(step, 0.71, "%g#pi < #Delta#phi_{j#gamma} < %g#pi", rdphi, false); }
                }
            };

            auto cuts_info = [&](int64_t index) {
                if (index > 0) {
                    auto photon_selections = "p_{T}^{#gamma} > "s + to_text(photon_pt_min) + " GeV, |#eta^{#gamma}| < "s + to_text(photon_eta_abs);
                    if (jpt || eta) photon_selections += ", #Delta#phi_{j#gamma} > "s + to_text(dphi_min_numerator) + "#pi/"s + to_text(dphi_min_denominator);
                    auto jet_selections = "anti-k_{T} R = 0.3"s;
                    if (dphi || jpt) jet_selections += ", |#eta^{jet}| < "s + to_text(jet_eta_abs);
                    if (dphi || eta) jet_selections += ", "s + to_text(jet_pt_min) + " < p_{T}^{jet} < "s + to_text(jet_pt_max) + " GeV"s;

                    TLatex* l = new TLatex();
                    l->SetTextAlign(31);
                    l->SetTextFont(43);
                    l->SetTextSize(11);
                    l->DrawLatexNDC(0.86, 0.65, photon_selections.data());
                    l->DrawLatexNDC(0.86, 0.60, jet_selections.data());
                }
            };

            for (int64_t i = 0; i < shape[1]; ++i) {
                cs1[i] = new paper(set + "_validate_"s + tag + "_raw_"s + label + "_"s + to_text(i), hb);
                apply_style(cs1[i], cms, system_tag);
                cs1[i]->accessory(std::bind(line_at, _1, 0.f, min, max));
                cs1[i]->accessory(std::bind(range_info, _1, i+1));
                cs1[i]->accessory(hf_info);
                cs1[i]->accessory(cuts_info);
                cs1[i]->divide(ihf->size() , -1);

                cs2[i] = new paper(set + "_validate_"s + tag + "_mixed_"s + label + "_"s + to_text(i), hb);
                apply_style(cs2[i], cms, system_tag);
                cs2[i]->accessory(std::bind(line_at, _1, 0.f, min, max));
                cs2[i]->accessory(std::bind(range_info, _1, i+1));
                cs2[i]->accessory(hf_info);
                cs2[i]->accessory(cuts_info);
                cs2[i]->divide(ihf->size() , -1);

                cs3[i] = new paper(set + "_validate_"s + tag + "_sub_"s + label + "_"s + to_text(i), hb);
                apply_style(cs3[i], cms, system_tag);
                cs3[i]->accessory(std::bind(line_at, _1, 0.f, min, max));
                cs3[i]->accessory(std::bind(range_info, _1, i+1));
                cs3[i]->accessory(hf_info);
                cs3[i]->accessory(cuts_info);
                cs3[i]->divide(ihf->size() , -1);

                for (int64_t j = 0; j < shape[2]; ++j) {
                    std::vector<int64_t> index = {0, i, j};

                    cs1[i]->add((*hist_compare)[index], label_compare);
                    cs1[i]->stack((*hist_nominal)[index], label_nominal);
                    cs2[i]->add((*hist_mix_compare)[index], label_compare);
                    cs2[i]->stack((*hist_mix_nominal)[index], label_nominal);
                    cs3[i]->add((*hist_sub_compare)[index], label_compare);
                    cs3[i]->stack((*hist_sub_nominal)[index], label_nominal);
                }
            }

            hb->sketch();

            for (int64_t i = 0; i < shape[1]; ++i) {
                cs1[i]->draw("pdf");
                cs2[i]->draw("pdf");
                cs3[i]->draw("pdf");

                delete cs1[i]; delete cs2[i]; delete cs3[i];
            }
        }
    }, labels, minimums, maximums);

    /* save output */
    in(output, []() {});

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return validate(argv[1], argv[2], argv[3]);

    printf("usage: %s [config] [selections] [output]\n", argv[0]);
    return 1;
}
