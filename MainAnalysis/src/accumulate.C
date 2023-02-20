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

#include "TFile.h"
#include "TH1.h"
#include "TLatex.h"
#include "TLine.h"

#include <string>
#include <vector>

using namespace std::literals::string_literals;
using namespace std::placeholders;

template <typename... T>
void normalise_to_unity(T*&... args) {
    (void)(int [sizeof...(T)]) { (args->apply([](TH1* obj) {
        obj->Scale(1. / obj->Integral("width")); }), 0)... };
}

template <typename... T>
void normalise_ia_to_unity(T*&... args) {
    (void)(int [sizeof...(T)]) { (args->apply([](TH1* obj) {
        auto width = revert_radian(obj->GetBinLowEdge(1)
            - obj->GetBinLowEdge(obj->GetNbinsX() + 1));
        obj->Scale(1. / (obj->Integral() * std::abs(width)));
    }), 0)... };
}

template <typename... T>
void title(std::function<void(TH1*)> f, T*&... args) {
    (void)(int [sizeof...(T)]) { (args->apply(f), 0)... };
}

int accumulate(char const* config, char const* output) {
    auto conf = new configurer(config);

    auto input = conf->get<std::string>("input");
    auto label = conf->get<std::string>("label");
    auto system = conf->get<std::string>("system");
    auto tag = conf->get<std::string>("tag");

    auto use_photon_60 = conf->get<bool>("use_photon_60");

    auto rjpt = conf->get<std::vector<float>>("jpt_range");
    auto rdphi = conf->get<std::vector<float>>("dphi_range");
    auto rdr = conf->get<std::vector<float>>("dr_range");

    auto rrdr = conf->get<std::vector<float>>("rdr_range");
    // auto rrdphi = conf->get<std::vector<float>>("rdphi_range");
    auto rrpt = conf->get<std::vector<float>>("rpt_range");

    auto dpt = conf->get<std::vector<float>>("pt_diff");
    auto dhf = conf->get<std::vector<float>>("hf_diff");

    auto dcent = conf->get<std::vector<int32_t>>("cent_diff");

    /* convert to integral angle units (cast to double) */
    convert_in_place_pi(rdphi);

    auto ihf = new interval(dhf);

    auto mdr = new multival(rrdr, rrpt);
    // auto mdphi = new multival(rrdphi, rrpt);

    /* manage memory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    /* open input files */
    TFile* f = new TFile(input.data(), "read");

    /* load histograms */
    auto nevt = new history<TH1F>(f, label + "_raw_nevt"s);

    auto pjet_es_f_dphi = new history<TH1F>(
        f, label + "_raw_sub_pjet_es_f_dphi"s);
    auto pjet_wta_f_dphi = new history<TH1F>(
        f, label + "_raw_sub_pjet_wta_f_dphi"s);
    auto pjet_f_dr = new history<TH1F>(
        f, label + "_raw_sub_pjet_f_dr"s);
    auto pjet_f_jpt = new history<TH1F>(
        f, label + "_raw_sub_pjet_f_jpt"s);

    auto pjet_es_u_dphi = new history<TH1F>(
        f, label + "_raw_sub_pjet_es_u_dphi"s);
    auto pjet_wta_u_dphi = new history<TH1F>(
        f, label + "_raw_sub_pjet_wta_u_dphi"s);
    auto pjet_u_dr = new history<TH1F>(
        f, label + "_raw_sub_pjet_u_dr"s);

    /* rescale by number of signal photons (events) */
    pjet_es_f_dphi->multiply(*nevt);
    pjet_wta_f_dphi->multiply(*nevt);
    pjet_f_dr->multiply(*nevt);
    pjet_f_jpt->multiply(*nevt);
    pjet_es_u_dphi->multiply(*nevt);
    pjet_wta_u_dphi->multiply(*nevt);
    pjet_u_dr->multiply(*nevt);

    /* discard overflow photon pt bin */
    auto discard = [](history<TH1F>*& h, int64_t axis) {
        auto shape = h->shape();
        shape[axis] = shape[axis] - 1;
        h = h->shrink("s", shape, std::vector<int64_t>(h->dims(), 0));
    };

    auto discard_low = [](history<TH1F>*& h, int64_t axis) {
        auto shape = h->shape();
        shape[axis] = shape[axis] - 2;
        std::vector<int64_t> offsets(h->dims(), 0);
        offsets[axis] = 2;

        h = h->shrink("s", shape, offsets);
    };

    discard(nevt, 0);
    discard(pjet_es_f_dphi, 0);
    discard(pjet_wta_f_dphi, 0);
    discard(pjet_f_dr, 0);
    discard(pjet_f_jpt, 0);
    discard(pjet_es_u_dphi, 0);
    discard(pjet_wta_u_dphi, 0);
    discard(pjet_u_dr, 0);

    if (use_photon_60) {
        dpt.erase(dpt.begin(), dpt.begin() + 2);
        
        discard_low(nevt, 0);
        discard_low(pjet_es_f_dphi, 0);
        discard_low(pjet_wta_f_dphi, 0);
        discard_low(pjet_f_dr, 0);
        discard_low(pjet_f_jpt, 0);
        discard_low(pjet_es_u_dphi, 0);
        discard_low(pjet_wta_u_dphi, 0);
        discard_low(pjet_u_dr, 0);
    }

    /* integrate histograms */
    auto nevt_d_pt = nevt->sum(1);
    auto nevt_d_hf = nevt->sum(0);

    auto pjet_es_f_dphi_d_pt = pjet_es_f_dphi->sum(1);
    auto pjet_es_f_dphi_d_hf = pjet_es_f_dphi->sum(0);
    auto pjet_wta_f_dphi_d_pt = pjet_wta_f_dphi->sum(1);
    auto pjet_wta_f_dphi_d_hf = pjet_wta_f_dphi->sum(0);
    auto pjet_f_dr_d_pt = pjet_f_dr->sum(1);
    auto pjet_f_dr_d_hf = pjet_f_dr->sum(0);
    auto pjet_f_jpt_d_pt = pjet_f_jpt->sum(1);
    auto pjet_f_jpt_d_hf = pjet_f_jpt->sum(0);
    auto pjet_es_u_dphi_d_pt = pjet_es_u_dphi->sum(1);
    auto pjet_es_u_dphi_d_hf = pjet_es_u_dphi->sum(0);
    auto pjet_wta_u_dphi_d_pt = pjet_wta_u_dphi->sum(1);
    auto pjet_wta_u_dphi_d_hf = pjet_wta_u_dphi->sum(0);
    auto pjet_u_dr_d_pt = pjet_u_dr->sum(1);
    auto pjet_u_dr_d_hf = pjet_u_dr->sum(0);

    /* normalise by number of signal photons (events) */
    pjet_es_f_dphi->divide(*nevt);
    pjet_wta_f_dphi->divide(*nevt);
    pjet_f_dr->divide(*nevt);
    pjet_f_jpt->divide(*nevt);
    pjet_es_u_dphi->divide(*nevt);
    pjet_wta_u_dphi->divide(*nevt);
    pjet_u_dr->divide(*nevt);

    pjet_es_f_dphi_d_pt->divide(*nevt_d_pt);
    pjet_es_f_dphi_d_hf->divide(*nevt_d_hf);
    pjet_wta_f_dphi_d_pt->divide(*nevt_d_pt);
    pjet_wta_f_dphi_d_hf->divide(*nevt_d_hf);
    pjet_f_dr_d_pt->divide(*nevt_d_pt);
    pjet_f_dr_d_hf->divide(*nevt_d_hf);
    pjet_f_jpt_d_pt->divide(*nevt_d_pt);
    pjet_f_jpt_d_hf->divide(*nevt_d_hf);
    pjet_es_u_dphi_d_pt->divide(*nevt_d_pt);
    pjet_es_u_dphi_d_hf->divide(*nevt_d_hf);
    pjet_wta_u_dphi_d_pt->divide(*nevt_d_pt);
    pjet_wta_u_dphi_d_hf->divide(*nevt_d_hf);
    pjet_u_dr_d_pt->divide(*nevt_d_pt);
    pjet_u_dr_d_hf->divide(*nevt_d_hf);

    /* normalise to unity */
    normalise_to_unity(
        pjet_f_dr,
        pjet_f_dr_d_pt,
        pjet_f_dr_d_hf);

    normalise_ia_to_unity(
        pjet_es_f_dphi,
        pjet_wta_f_dphi,
        pjet_es_f_dphi_d_pt,
        pjet_es_f_dphi_d_hf,
        pjet_wta_f_dphi_d_pt,
        pjet_wta_f_dphi_d_hf);

    title(std::bind(rename_axis, _1, "1/N^{#gammaj}dN/d#deltaj"),
        pjet_f_dr,
        pjet_f_dr_d_pt,
        pjet_f_dr_d_hf);

    title(std::bind(rename_axis, _1, "1/N^{#gammaj}dN/d#Delta#phi^{#gammaj}"),
        pjet_es_f_dphi,
        pjet_wta_f_dphi,
        pjet_es_f_dphi_d_pt,
        pjet_es_f_dphi_d_hf,
        pjet_wta_f_dphi_d_pt,
        pjet_wta_f_dphi_d_hf);

    /* save histograms */
    in(output, [&]() {
        nevt->save(tag);

        pjet_es_f_dphi->save(tag);
        pjet_wta_f_dphi->save(tag);
        pjet_f_dr->save(tag);
        pjet_f_jpt->save(tag);
        pjet_es_u_dphi->save(tag);
        pjet_wta_u_dphi->save(tag);
        pjet_u_dr->save(tag);

        pjet_es_f_dphi_d_pt->save(tag);
        pjet_es_f_dphi_d_hf->save(tag);
        pjet_wta_f_dphi_d_pt->save(tag);
        pjet_wta_f_dphi_d_hf->save(tag);
        pjet_f_dr_d_pt->save(tag);
        pjet_f_dr_d_hf->save(tag);
        pjet_f_jpt_d_pt->save(tag);
        pjet_f_jpt_d_hf->save(tag);
        pjet_es_u_dphi_d_pt->save(tag);
        pjet_es_u_dphi_d_hf->save(tag);
        pjet_wta_u_dphi_d_pt->save(tag);
        pjet_wta_u_dphi_d_hf->save(tag);
        pjet_u_dr_d_pt->save(tag);
        pjet_u_dr_d_hf->save(tag);
    });

    /* draw plots */
    printf("painting..\n");

    // auto redraw_dphi_axis = [&](TH1* h, int64_t) {
        // transform_axis(h, [](int64_t val) -> float {
        //     return std::abs(revert_radian(val)); }); };

    auto system_tag = system + "  #sqrt{s_{NN}} = 5.02 TeV"s;
    system_tag += (system == "PbPb") ? ", 1.69 nb^{-1}"s : ", 3.02 pb^{-1}"s;
    auto cms = "#bf{#scale[1.4]{CMS}}"s;
    cms += " #it{#scale[1.2]{Preliminary}}"s;
    cms += "                                                                   ";
    cms += "                                                                   ";
    cms += "anti-k_{T} R = 0.3, p_{T}^{jet} > 20 GeV, |#eta^{jet}| < 1.6, p_{T}^{#gamma} > 40 GeV, |#eta^{#gamma}| < 1.44, #Delta#phi_{j#gamma} < 7#pi/8";

    std::function<void(int64_t, float)> pt_info = [&](int64_t x, float pos) {
        info_text(x, pos, "%.0f < p_{T}^{#gamma} < %.0f", dpt, false); };

    std::function<void(int64_t, float)> hf_info = [&](int64_t x, float pos) {
        info_text(x, pos, "Cent. %i - %i%%", dcent, true); };

    auto pthf_info = [&](int64_t index) {
        stack_text(index, 0.75, 0.04, nevt, pt_info, hf_info); };

    auto hb = new pencil();
    hb->category("system", "PbPb", "pp");
    hb->category("axis", "na", "wta", "es");

    hb->alias("na", "");
    hb->alias("es", "E-Scheme");
    hb->alias("wta", "WTA");

    hb->ditto("es", "na");

    auto suffixes = { "d_pthf"s, "d_pt"s, "d_hf"s };
    auto texts = std::vector<std::function<void(int64_t)>> {
        pthf_info, std::bind(pt_info, _1, 0.75), std::bind(hf_info, _1, 0.75) };

    // std::vector<paper*> c1(3, nullptr);
    std::vector<paper*> c2(3, nullptr);
    std::vector<paper*> c3(3, nullptr);
    // std::vector<paper*> c4(3, nullptr);
    std::vector<paper*> c5(3, nullptr);
    std::vector<paper*> c6(3, nullptr);

    // zip([&](paper*& c, int64_t rows, std::string const& suffix,
    //         std::function<void(int64_t)> text) {
    //     c = new paper(tag + "_dphi_" + suffix, hb);
    //     c->divide(-1, rows);
    //     c->accessory(text);

    //     apply_style(c, collisions, -0.04, 0.24);
    //     c->accessory(std::bind(line_at, _1, 0.f, rdphi[0], rdphi[1]));
    //     c->jewellery(redraw_dphi_axis);
    // }, c1, x{ ihf->size(), 1L, 1L }, suffixes, texts);

    // nevt->apply([&](TH1*, int64_t index) {
    //     c1[0]->add((*pjet_es_f_dphi)[index], system, "es");
    //     c1[0]->stack((*pjet_wta_f_dphi)[index], system, "wta");
    // });

    // nevt_d_pt->apply([&](TH1*, int64_t index) {
    //     c1[1]->add((*pjet_es_f_dphi_d_pt)[index], system, "es");
    //     c1[1]->stack((*pjet_wta_f_dphi_d_pt)[index], system, "wta");
    // });

    // nevt_d_hf->apply([&](TH1*, int64_t index) {
    //     c1[2]->add((*pjet_es_f_dphi_d_hf)[index], system, "es");
    //     c1[2]->stack((*pjet_wta_f_dphi_d_hf)[index], system, "wta");
    // });

    zip([&](paper*& c, int64_t rows, std::string const& suffix,
            std::function<void(int64_t)> text) {
        c = new paper(tag + "_dr_" + suffix, hb);
        c->divide(-1, rows);
        c->accessory(text);

        apply_style(c, cms, system_tag, -2., 27.);
        c->accessory(std::bind(line_at, _1, 0.f, rdr[0], rdr[1]));
    }, c2, x{ ihf->size(), 1L, 1L }, suffixes, texts);

    pjet_f_dr->apply([&](TH1* h) { c2[0]->add(h, system); });
    pjet_f_dr_d_pt->apply([&](TH1* h) { c2[1]->add(h, system); });
    pjet_f_dr_d_hf->apply([&](TH1* h) { c2[2]->add(h, system); });

    zip([&](paper*& c, int64_t rows, std::string const& suffix,
            std::function<void(int64_t)> text) {
        c = new paper(tag + "_jpt_" + suffix, hb);
        c->divide(-1, rows);
        c->accessory(text);

        apply_style(c, cms, system_tag, -0.001, 0.02);
        c->accessory(std::bind(line_at, _1, 0.f, rjpt[0], rjpt[1]));
    }, c3, x{ ihf->size(), 1L, 1L }, suffixes, texts);

    pjet_f_jpt->apply([&](TH1* h) { c3[0]->add(h, system); });
    pjet_f_jpt_d_pt->apply([&](TH1* h) { c3[1]->add(h, system); });
    pjet_f_jpt_d_hf->apply([&](TH1* h) { c3[2]->add(h, system); });

    // zip([&](paper*& c, int64_t rows, std::string const& suffix,
    //         std::function<void(int64_t)> text) {
    //     c = new paper(tag + "_u_dphi_" + suffix, hb);
    //     c->divide(-1, rows);
    //     c->accessory(text);

    //     apply_style(c, collisions, -0.03, 0.15);
    //     c->accessory(std::bind(line_at, _1, 0.f, 0, mdphi->size()));
    // }, c4, x{ ihf->size(), 1L, 1L }, suffixes, texts);

    // nevt->apply([&](TH1*, int64_t index) {
    //     c4[0]->add((*pjet_es_u_dphi)[index], system, "es");
    //     c4[0]->stack((*pjet_wta_u_dphi)[index], system, "wta");
    // });

    // nevt_d_pt->apply([&](TH1*, int64_t index) {
    //     c4[1]->add((*pjet_es_u_dphi_d_pt)[index], system, "es");
    //     c4[1]->stack((*pjet_wta_u_dphi_d_pt)[index], system, "wta");
    // });

    // nevt_d_hf->apply([&](TH1*, int64_t index) {
    //     c4[2]->add((*pjet_es_u_dphi_d_hf)[index], system, "es");
    //     c4[2]->stack((*pjet_wta_u_dphi_d_hf)[index], system, "wta");
    // });

    zip([&](paper*& c, int64_t rows, std::string const& suffix,
            std::function<void(int64_t)> text) {
        c = new paper(tag + "_u_dr_" + suffix, hb);
        c->divide(-1, rows);
        c->accessory(text);

        apply_style(c, cms, system_tag, -0.01, 0.07);
        c->accessory(std::bind(line_at, _1, 0.f, 0, mdr->size()));
    }, c5, x{ ihf->size(), 1L, 1L }, suffixes, texts);

    pjet_u_dr->apply([&](TH1* h) { c5[0]->add(h, system); });
    pjet_u_dr_d_pt->apply([&](TH1* h) { c5[1]->add(h, system); });
    pjet_u_dr_d_hf->apply([&](TH1* h) { c5[2]->add(h, system); });

    hb->set_binary("system");
    hb->sketch();

    for (auto const& c : { c2, c3, c5 })
        for (auto p : c) { p->draw("pdf"); }

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return accumulate(argv[1], argv[2]);

    printf("usage: %s [config] [output]\n", argv[0]);
    return 1;
}