#include "../include/lambdas.h"

#include "../git/config/include/configurer.h"

#include "../git/history/include/interval.h"
#include "../git/history/include/multival.h"
#include "../git/history/include/history.h"

#include "../git/paper-and-pencil/include/paper.h"
#include "../git/paper-and-pencil/include/pencil.h"

#include "../git/tricks-and-treats/include/trunk.h"
#include "../git/tricks-and-treats/include/zip.h"

#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TLatex.h"

#include <functional>
#include <string>
#include <vector>

using namespace std::literals::string_literals;
using namespace std::placeholders;

template <typename... T>
void title(std::function<void(TH1*)> f, T*&... args) {
    (void)(int [sizeof...(T)]) { (args->apply(f), 0)... };
}

int obnubilate(char const* config, char const* output) {
    auto conf = new configurer(config);

    auto ref = conf->get<std::string>("ref");
    auto label = conf->get<std::string>("label");
    auto tag = conf->get<std::string>("tag");
    auto system = conf->get<std::string>("system");

    auto inputs = conf->get<std::vector<std::string>>("inputs");
    auto labels = conf->get<std::vector<std::string>>("labels");
    auto plots = conf->get<std::vector<int32_t>>("plots");
    auto legends = conf->get<std::vector<std::string>>("legends");
    auto legend_keys = conf->get<std::vector<std::string>>("legend_keys");
    auto figures = conf->get<std::vector<std::string>>("figures");
    auto columns = conf->get<std::vector<int32_t>>("columns");
    auto ranges = conf->get<std::vector<float>>("ranges");
    auto groups = conf->get<std::vector<int32_t>>("groups");

    auto dpt = conf->get<std::vector<float>>("pt_diff");
    auto dhf = conf->get<std::vector<float>>("hf_diff");
    auto dcent = conf->get<std::vector<int32_t>>("cent_diff");

    auto is_paper = conf->get<bool>("paper");

    /* manage memory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    /* open input files */
    TFile* f = new TFile(ref.data(), "read");

    std::vector<TFile*> files(inputs.size(), nullptr);
    zip([&](auto& file, auto const& input) {
        file = new TFile(input.data(), "read");
    }, files, inputs);

    /* prepare plots */
    auto hb = new pencil();
    hb->category("type", "total", legend_keys);

    zip([&](auto const& label, auto const& legend) {
        hb->alias(label, legend); }, legend_keys, legends);

    /* lambdas */
    std::function<void(TH1*)> square_ = [](TH1* h) {
        for_contents([](std::array<double, 1> v) {
            return v[0] * v[0]; }, h); };
    std::function<void(TH1*)> sqrt_ = [](TH1* h) {
        for_contents([](std::array<double, 1> v) {
            return std::sqrt(v[0]); }, h); };

    auto shader = [&](TH1* h, float max) {
        default_formatter(h, 0., max);
        auto col = h->GetLineColor();
        h->SetFillColorAlpha(col, 0.32);
        h->SetLineWidth(1);
    };

    auto hf_info = [&](int64_t index) {
        info_text(index, 0.75, "Cent. %i - %i%%", dcent, true); };

    auto kinematics = [&](int64_t index) {
        if (index > 0) {
            TLatex* l = new TLatex();
            l->SetTextAlign(31);
            l->SetTextFont(43);
            l->SetTextSize(13);
            l->DrawLatexNDC(0.865, 0.41, "40 < p_{T}^{#gamma} < 300, |#eta^{#gamma}| < 1.44");
            l->DrawLatexNDC(0.865, 0.37, "anti-k_{T} R = 0.3, 30 < p_{T}^{jet} < 120, |#eta^{jet}| < 1.6");
        }
    };

    /* prepare output */
    TFile* fout = new TFile(output, "recreate");

    std::string system_tag = "  #sqrt{s_{NN}} = 5.02 TeV"s;
    system_tag += (tag == "aa") ? ", 1.69 nb^{-1}"s : ", 3.02 pb^{-1}"s;
    auto cms = "#bf{#scale[1.4]{CMS}}"s;
    if (!is_paper) cms += " #it{#scale[1.2]{Preliminary}}"s;

    /* calculate variations */
    zip([&](auto const& figure, auto cols, auto range) {
        auto stub = "_"s + figure;

        auto c1 = new paper(tag + "_var"s + stub, hb);
        apply_style(c1, cms, system_tag, std::bind(shader, _1, range));
        c1->divide(cols, -1);

        auto c2 = new paper(tag + "_var_unfolding"s + stub, hb);
        apply_style(c2, cms, system_tag, std::bind(shader, _1, range));
        c2->divide(cols, -1);

        auto base = new history<TH1F>(f, tag + "_"s + label + stub, "base_"s + tag + "_"s + label + stub);
        title(std::bind(rename_axis, _1, "1/N^{#gammaj}dN/d#deltaj"), base);

        std::vector<history<TH1F>*> sets;

        std::vector<history<TH1F>*> batches(inputs.size(), nullptr);
        zip([&](auto& batch, auto file, auto const& label) {
            batch = new history<TH1F>(file, tag + "_" + label + stub, "batch_"s + tag + "_"s + label + stub);
            title(std::bind(rename_axis, _1, "1/N^{#gammaj}dN/d#deltaj"), batch);
        }, batches, files, labels);

        auto total = new history<TH1F>(*base, "total");
        title(std::bind(rename_axis, _1, "1/N^{#gammaj}dN/d#deltaj"), total);
        total->apply([](TH1* h) { h->Reset("MICES"); });

        for (auto const& batch : batches) {
            batch->add(*base, -1);

            for (int64_t i = 0; i < batch->size(); ++i) {
                std::vector<float> differences;

                for (int64_t j = 0; j < (*batch)[i]->GetNbinsX() - 2; ++j) {
                    differences.push_back(std::abs((*batch)[i]->GetBinContent(j + 1)));
                }

                float min = 10000;
                float max = 0;
                for (auto difference : differences) {
                    if (difference < min) { min = difference; }
                    if (difference > max) { max = difference; }
                }

                printf("%.2f-%.2f ", min, max);
            }
            std::cout << std::endl;

            batch->apply(square_);

            for (int64_t i = 0; i < batch->size(); ++i) {
                for (int64_t j = 0; j < (*batch)[i]->GetNbinsX(); ++j) {
                    if (j == 2) {
                        double value = std::abs((*batch)[i]->GetBinContent(j) - (*batch)[i]->GetBinContent(j + 4));
                        value = value * 3 / 4;
                        value += std::min((*batch)[i]->GetBinContent(j), (*batch)[i]->GetBinContent(j + 4));
                        (*batch)[i]->SetBinContent(j + 1, value);
                    }
                    if (j == 3) {
                        double value = std::abs((*batch)[i]->GetBinContent(j - 1) - (*batch)[i]->GetBinContent(j + 3));
                        value = value * 1 / 2;
                        value += std::min((*batch)[i]->GetBinContent(j - 1), (*batch)[i]->GetBinContent(j + 3));
                        (*batch)[i]->SetBinContent(j + 1, value);
                    }
                    if (j == 4) {
                        double value = std::abs((*batch)[i]->GetBinContent(j - 2) - (*batch)[i]->GetBinContent(j + 2));
                        value = value * 1 / 4;
                        value += std::min((*batch)[i]->GetBinContent(j - 2), (*batch)[i]->GetBinContent(j + 2));
                        (*batch)[i]->SetBinContent(j + 1, value);
                    }
                }
            }
        }

        zip([&](auto const& batch, auto group) {
            if (group == static_cast<int32_t>(sets.size())) {
                sets.push_back(new history<TH1F>(*batch, "set"));
            } else {
                sets[group]->apply([&](TH1* h, int64_t i) {
                    for_contents([](std::array<double, 2> v) -> float {
                        return std::max(v[0], v[1]);
                    }, h, (*batch)[i]); });
            }

            batch->apply(sqrt_);
        }, batches, groups);

        for (auto const& set : sets)
            total->add(*set, 1);

        total->apply(sqrt_);

        /* add plots */
        auto style1 = [&](TH1* h) { c1->adjust(h, "hist", "f"); };
        auto style2 = [&](TH1* h) { c2->adjust(h, "hist", "f"); };

        total->apply([&](TH1* h) { 
            c1->add(h, "total"); style1(h); 
            c2->add(h, "total"); style2(h); 
        });

        zip([&](auto& batch, auto const& label, auto const& plot) {
            if (plot == 1) {
                batch->apply([&](TH1* h, int64_t index) {
                    c1->stack(index + 1, h, label); style1(h);
                });
            }
            else {
                batch->apply([&](TH1* h, int64_t index) {
                    c2->stack(index + 1, h, label); style2(h);
                });
            }

            batch->save(tag);
        }, batches, legend_keys, plots);

        /* add info text */
        c1->accessory(hf_info); 
        c1->accessory(kinematics);
        c2->accessory(hf_info); 
        c2->accessory(kinematics);

        /* save histograms */
        for (auto const& set : sets)
            set->save(tag);

        base->save(tag);
        total->save(tag);

        hb->sketch();

        c1->draw("pdf");
        c2->draw("pdf");
    }, figures, columns, ranges);

    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return obnubilate(argv[1], argv[2]);

    return 0;
}