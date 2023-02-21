#include "../include/lambdas.h"
#include "../include/specifics.h"

#include "../git/config/include/configurer.h"

#include "../git/history/include/interval.h"
#include "../git/history/include/multival.h"
#include "../git/history/include/history.h"

#include "../git/paper-and-pencil/include/paper.h"
#include "../git/paper-and-pencil/include/pencil.h"

#include "../git/tricks-and-treats/include/overflow_angles.h"
#include "../git/tricks-and-treats/include/trunk.h"
#include "../git/tricks-and-treats/include/zip.h"

#include "TColor.h"
#include "TFile.h"
#include "TH1.h"
#include "TLatex.h"
#include "TLine.h"

#include <string>
#include <vector>

using namespace std::literals::string_literals;
using namespace std::placeholders;

static auto const red = TColor::GetColor("#f2777a");
static auto const blue = TColor::GetColor("#6699cc");

template <typename... T>
void title(std::function<void(TH1*)> f, T*&... args) {
    (void)(int [sizeof...(T)]) { (args->apply(f), 0)... };
}

int ratio(char const* config, char const* output) {
    auto conf = new configurer(config);

    auto inputs = conf->get<std::vector<std::string>>("inputs");
    auto tags = conf->get<std::vector<std::string>>("tags");
    auto figures = conf->get<std::vector<std::string>>("figures");
    auto prefix = conf->get<std::string>("prefix");

    auto corrections = conf->get<std::vector<std::string>>("corrections");
    auto truth_reco_iso_labels = conf->get<std::vector<std::string>>("truth_reco_iso_labels");
    auto qcd_after_labels = conf->get<std::vector<std::string>>("qcd_after_labels");

    auto xmins = conf->get<std::vector<float>>("xmin");
    auto xmaxs = conf->get<std::vector<float>>("xmax");
    auto ymins = conf->get<std::vector<float>>("ymin");
    auto ymaxs = conf->get<std::vector<float>>("ymax");
    auto oflows = conf->get<std::vector<bool>>("oflow");

    // auto dpt = conf->get<std::vector<float>>("pt_diff");
    auto dhf = conf->get<std::vector<float>>("hf_diff");
    auto dcent = conf->get<std::vector<int32_t>>("cent_diff");

    // auto is_paper = conf->get<bool>("paper");

    // auto ipt = new interval(dpt);
    auto ihf = new interval(dhf);

    /* manage memory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    /* open input files */
    std::vector<TFile*> files(inputs.size(), nullptr);
    zip([&](auto& file, auto const& input) {
        file = new TFile(input.data(), "read");
    }, files, inputs);

    std::vector<history<TH1F>*> truth_reco_isos(5, nullptr);
    std::vector<history<TH1F>*> unfolded_qcds(5, nullptr);

    zip([&](auto& truth_reco_iso, auto& unfolded_qcd, auto const correction, auto const& truth_reco_iso_label, auto const& qcd_after_label) {
            auto file = new TFile(correction.data(), "read");
            unfolded_qcd = new history<TH1F>(file, qcd_after_label);
            truth_reco_iso = new history<TH1F>(file, truth_reco_iso_label);
    }, truth_reco_isos, unfolded_qcds, corrections, truth_reco_iso_labels, qcd_after_labels);

    /* load histograms */
    std::vector<std::string> base_stubs(5);
    std::vector<std::string> syst_stubs(5);

    zip([&](auto& base, auto& syst, auto const& tag) {
        base = tag + "_base_" + tag + "_nominal_s_pure_raw_sub_";
        syst = tag + "_total_base_" + tag + "_nominal_s_pure_raw_sub_";
    }, base_stubs, syst_stubs, tags);

    /* prepare plots */
    auto hb = new pencil();
    hb->category("system", "pp", "aa");

    hb->alias("aa", "PbPb");

    auto decorator = [](std::string const& system, std::string const& extra = "") {
        TLatex* info = new TLatex();
        info->SetTextFont(42);
        info->SetTextSize(0.04);
        info->SetTextAlign(31);
        info->DrawLatexNDC(0.89, 0.92, system.data());

        TLatex* info_extra = new TLatex();
        info_extra->SetTextFont(42);
        info_extra->SetTextSize(0.04);
        info_extra->SetTextAlign(31);
        info_extra->DrawLatexNDC(0.89, 0.96, extra.data());
    };

    std::function<void(int64_t, float)> hf_info = [&](int64_t x, float pos) {
        info_text(x, pos, "Cent. %i - %i%%", dcent, true); };

    auto aa_info = [&](int64_t index, history<TH1F>* h) {
        stack_text(index, 0.73, 0.04, h, hf_info); };

    auto kinematics = [&](int64_t index) {
        if (index > 0) {
            TLatex* l = new TLatex();
            l->SetTextAlign(31);
            l->SetTextFont(43);
            l->SetTextSize(13);
            l->DrawLatexNDC(0.865, 0.41, "40 < p_{T}^{#gamma} < 200, |#eta^{#gamma}| < 1.44");
            l->DrawLatexNDC(0.865, 0.37, "anti-k_{T} R = 0.3, 30 < p_{T}^{jet} < 120, |#eta^{jet}| < 1.6");
        }
    };

    zip([&](auto const& figure, auto xmin, auto xmax, auto ymin, auto ymax,
            auto integral) {
        /* get histograms */ 
        std::vector<history<TH1F>*> hists(5, nullptr);
        std::vector<history<TH1F>*> systs(5, nullptr);

        zip([&](auto& hist, auto& syst, auto const file,
                auto const& base_stub, auto const& syst_stub) {
            hist = new history<TH1F>(file, base_stub + figure);
            title(std::bind(rename_axis, _1, "1/N^{#gammaj}dN/d#deltaj"), hist);
            syst = new history<TH1F>(file, syst_stub + figure);
        }, hists, systs, files, base_stubs, syst_stubs);

        for (size_t i = 2; i < files.size(); ++i) {
            std::string name1 = std::to_string(i) + std::string("happy");
            std::string name2 = std::to_string(i) + std::string("sad");
            hists[i]->rename(name1);
            systs[i]->rename(name2);
        }

        /* link histograms, uncertainties */
        std::unordered_map<TH1*, TH1*> links;
        zip([&](auto hist, auto syst, auto unfolded_qcd, auto truth_reco_iso) {
            hist->apply([&](TH1* h, int64_t index) {
                for (int64_t i = 1; i <= h->GetNbinsX(); ++i) {
                    double val = h->GetBinContent(i);
                    double err = h->GetBinError(i);
                    double correction = (*truth_reco_iso)[index]->GetBinContent(i);

                    if ((*unfolded_qcd)[index]->GetBinContent(i) > 0.001) {
                        correction /= (*unfolded_qcd)[index]->GetBinContent(i);
                    } else {
                        correction = 1;
                    }

                    correction = 1;
 
                    h->SetBinContent(i, val*correction);
                    h->SetBinError(i, err*correction);
                }});
            syst->apply([&](TH1* h, int64_t index) {
                for (int64_t i = 1; i <= h->GetNbinsX(); ++i) {
                    double val = h->GetBinContent(i);
                    double err = h->GetBinError(i);
                    double correction = (*truth_reco_iso)[index]->GetBinContent(i);

                    if ((*unfolded_qcd)[index]->GetBinContent(i) > 0.001) {
                        correction /= (*unfolded_qcd)[index]->GetBinContent(i);
                    } else {
                        correction = 1;
                    }

                    correction = 1;

                    h->SetBinContent(i, val*correction);
                    h->SetBinError(i, err*correction);
                }});

            /* scale everything by the truth gen iso vs reco iso difference */
            hist->apply([&](TH1* h, int64_t index) {
                links[h] = (*syst)[index]; });
        }, hists, systs, unfolded_qcds, truth_reco_isos);

        /* take the ratio */
        for (int64_t i = 0; i < hists[0]->size(); ++i) {
            std::cout << "Chi2 " << (*hists[0])[i]->Chi2Test((*hists[i+1])[0], "WW") << std::endl;
            std::cout << "K " << (*hists[0])[i]->KolmogorovTest((*hists[i+1])[0], "WW") << std::endl;

            for (int64_t j = 1; j <= (*hists[0])[0]->GetNbinsX(); ++j) {  
                auto aa_hist = (*hists[0])[i];
                auto pp_hist = (*hists[i+1])[0];

                double aa_val = aa_hist->GetBinContent(j);
                double aa_err = aa_hist->GetBinError(j);
                double aa_syst_err = links[aa_hist]->GetBinContent(j);
                auto aa_err_scale = aa_err/aa_val;

                double pp_val = pp_hist->GetBinContent(j);
                double pp_err = pp_hist->GetBinError(j);
                auto pp_err_scale = pp_err/pp_val;

                auto ratio = aa_val / pp_val;

                aa_err = ratio * std::sqrt(aa_err_scale * aa_err_scale + pp_err_scale * pp_err_scale);
                aa_syst_err /= pp_val;

                links[aa_hist]->SetBinContent(j, aa_syst_err);
                aa_hist->SetBinContent(j, ratio);
                aa_hist->SetBinError(j, aa_err);
            }
        }

        for (int64_t i = 0; i < hists[0]->size(); ++i) {
            for (int64_t j = 1; j <= (*hists[0])[0]->GetNbinsX(); ++j) {
                auto pp_hist = (*hists[i+1])[0];
                double pp_val = pp_hist->GetBinContent(j);
                double pp_syst_err = links[pp_hist]->GetBinContent(j);

                pp_syst_err /= pp_val;

                links[pp_hist]->SetBinContent(j, pp_syst_err);
                pp_hist->SetBinContent(j, 1);
                pp_hist->SetBinError(j, 0.00001);
            }
        } 

        std::unordered_map<TH1*, int32_t> colours; 
        hists[0]->apply([&](TH1* h) { colours[h] = 1; });

        /* uncertainty box */
        auto box = [&](TH1* h, int64_t) {
            TGraph* gr = new TGraph();
            gr->SetFillStyle(1001);
            gr->SetFillColorAlpha(colours[h] ? red : blue, 0.48);

            for (int i = 1; i <= h->GetNbinsX(); ++i) {
                if (h->GetBinError(i) == 0) continue;

                double x = h->GetBinCenter(i);
                double width = h->GetBinWidth(i);
                double val = h->GetBinContent(i);
                double err = links[h]->GetBinContent(i);

                gr->SetPoint(0, x - (width / 2), val - err);
                gr->SetPoint(1, x + (width / 2), val - err);
                gr->SetPoint(2, x + (width / 2), val + err);
                gr->SetPoint(3, x - (width / 2), val + err);

                gr->DrawClone("f");
            }
        };

        /* minor adjustments */
        if (integral) { xmin = convert_pi(xmin); xmax = convert_pi(xmax); }

        /* prepare papers */
        auto s = new paper(prefix + "_ratio_" + figure, hb);
        apply_style(s, "#bf{#scale[1.4]{CMS}}     #sqrt{s_{NN}} = 5.02 TeV"s, ""s, ymin, ymax);
        s->accessory(std::bind(decorator, "PbPb 1.69 nb^{-1}", "pp 302 pb^{-1}"));
        s->accessory(std::bind(line_at, _1, 1.f, xmin, xmax));
        s->accessory(std::bind(aa_info, _1, hists[0]));
        s->accessory(kinematics);
        s->jewellery(box);
        s->divide(ihf->size()/2, -1);

        /* draw histograms with uncertainties */
        hists[0]->apply([&](TH1* h) { 
            h->GetXaxis()->SetRangeUser(xmin, xmax);
            s->add(h, "aa"); 
        });
        for (int64_t i = 0; i < 4; ++i) {
            hists[i + 1]->apply([&](TH1* h, int64_t index) {
                s->stack(i + index + 1, h, "pp");
            });
        }

        auto pp_style = [](TH1* h) {
            h->SetLineColor(1);
            h->SetMarkerStyle(25);
            h->SetMarkerSize(0.60);
        };

        auto aa_style = [](TH1* h) {
            h->SetLineColor(1);
            h->SetMarkerStyle(20);
            h->SetMarkerSize(0.60);
        };

        hb->style("pp", pp_style);
        hb->style("aa", aa_style);
        hb->sketch();

        s->draw("pdf");
    }, figures, xmins, xmaxs, ymins, ymaxs, oflows);

    in(output, []() {});

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return ratio(argv[1], argv[2]);

    printf("usage: %s [config] [output]\n", argv[0]);
    return 1;
}