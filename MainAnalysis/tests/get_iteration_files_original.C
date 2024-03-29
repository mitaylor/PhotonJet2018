#include "../include/lambdas.h"

#include "../git/config/include/configurer.h"

#include "../git/history/include/interval.h"
#include "../git/history/include/multival.h"
#include "../git/history/include/history.h"

#include "../git/tricks-and-treats/include/trunk.h"
#include "../git/tricks-and-treats/include/zip.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std::literals::string_literals;
using namespace std::placeholders;

template <typename... T>
void normalise_to_unity(T*&... args) {
    (void)(int [sizeof...(T)]) { (args->apply([](TH1* obj) {
        obj->Scale(1. / obj->Integral("width")); }), 0)... };
}

template <typename T>
T* null(int64_t, std::string const&, std::string const&) {
    return nullptr;
}

TH2F* variance(TH1* flat, multival const* m) {
    auto cov = new TH2F("cov", "", m->size(), 0, m->size(),
        m->size(), 0, m->size());

    for (int64_t i = 0; i < m->size(); ++i) {
        auto err = flat->GetBinError(i + 1);
        cov->SetBinContent(i + 1, i + 1, err * err);
    }

    return cov;
}

TH1F* fold(TH1* flat, TH2* covariance, multival const* m, int64_t axis,
           std::vector<int64_t>& offsets) {
    auto name = std::string(flat->GetName()) + "_fold" + std::to_string(axis);
    auto hfold = m->axis(axis).book<TH1F, 2>(0, name, "",
        { offsets[axis << 1], offsets[(axis << 1) + 1] });

    auto shape = m->shape();

    auto front = std::vector<int64_t>(m->dims(), 0);
    auto back = std::vector<int64_t>(m->dims(), 0);
    for (int64_t i = 0; i < m->dims(); ++i) {
        front[i] = offsets[i << 1];
        back[i] = shape[i] - offsets[(i << 1) + 1];
    }

    auto size = back[axis] - front[axis];
    auto list = new std::vector<int64_t>[size];

    for (int64_t i = 0; i < m->size(); ++i) {
        auto indices = m->indices_for(i);

        bool flag = false;
        zip([&](int64_t index, int64_t f, int64_t b) {
            flag = flag || index < f || index >= b;
        }, indices, front, back);
        if (flag) { continue; }

        auto index = indices[axis] - front[axis];
        hfold->SetBinContent(index + 1, hfold->GetBinContent(index + 1)
            + flat->GetBinContent(i + 1));

        list[index].push_back(i);
    }

    auto cov = covariance ? (TH2F*)covariance->Clone() : variance(flat, m);

    for (int64_t i = 0; i < size; ++i) {
        auto indices = list[i];
        int64_t count = indices.size();

        auto error = 0.;
        for (int64_t j = 0; j < count; ++j) {
            auto j_x = indices[j] + 1;
            for (int64_t k = 0; k < count; ++k) {
                auto k_x = indices[k] + 1;
                error = error + cov->GetBinContent(j_x, k_x);
            }
        }

        hfold->SetBinError(i + 1, std::sqrt(error));
    }

    delete [] list;
    delete cov;

    hfold->Scale(1., "width");

    return hfold;
}

int get_iteration_files(char const* config, char const* selections, char const* output) {
    auto conf = new configurer(config);

    auto tag = conf->get<std::string>("tag");

    auto before = conf->get<std::string>("before");
    auto before_label = conf->get<std::string>("before_label");
    auto before_folds = conf->get<std::vector<std::string>>("before_folds");

    auto afters = conf->get<std::vector<std::string>>("afters");
    auto merge = conf->get<std::string>("merge");

    auto sel = new configurer(selections);

    auto set = sel->get<std::string>("set");
    auto base = sel->get<std::string>("base");

    auto rdrr = sel->get<std::vector<float>>("drr_range");
    auto rptr = sel->get<std::vector<float>>("ptr_range");

    auto osr = sel->get<std::vector<int64_t>>("osr");

    /* create intervals and multivals */
    auto idrr = new interval("#deltaj"s, rdrr);
    auto iptr = new interval("p_{T}^{j}"s, rptr);

    auto mr = new multival(*idrr, *iptr);

    /* manage memory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    TFile* fbefore = new TFile((base + before).data(), "read");

    std::vector<TFile*> fafters(afters.size(), nullptr);
    zip([&](auto& fafter, auto const& after) {
        fafter = new TFile(("unfolded/" + set + "/" + after).data(), "read");
    }, fafters, afters);

    auto fmerge = new TFile(("unfolded/" + set + "/" + merge).data(), "read");

    /* prepare output */
    TFile* fout = new TFile(output, "recreate");

    /* prepare fold from pre-unfolded data */
    for (size_t i = 0; i < before_folds.size(); ++i) {
        auto stub = "_"s + before_folds[i];

        auto hin = new history<TH1F>(fbefore, tag + "_"s + before_label + stub);
        auto shape = hin->shape();

        auto side0 = new history<TH1F>(tag + "_"s + before_label + stub + "_side0"s, "", null<TH1F>, shape);
        auto side1 = new history<TH1F>(tag + "_"s + before_label + stub + "_side1"s, "", null<TH1F>, shape);

        for (int64_t i = 0; i < hin->size(); ++i) {
            (*side0)[i] = fold((*hin)[i], nullptr, mr, 0, osr);
            (*side1)[i] = fold((*hin)[i], nullptr, mr, 1, osr);
        }

        normalise_to_unity(side0, side1);

        hin->rename(tag + "_"s + before_label + stub);
        side0->rename(tag + "_"s + before_label + stub + "_side0"s);
        side1->rename(tag + "_"s + before_label + stub + "_side1"s);

        hin->save();
        side0->save();
        side1->save();
    }

    /* prepare the refolded data */
    std::vector<int64_t> iteration {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 35, 40, 45, 50, 55, 60, 65, 70, 80, 90, 100, 125, 150, 200, 250};

    for (size_t i = 0; i < iteration.size(); ++i) {
        auto refolded = new history<TH1F>("refolded", "", null<TH1F>, (int64_t) afters.size());
        auto refolded_fold0 = new history<TH1F>("refolded_fold0", "", null<TH1F>, (int64_t) afters.size());
        auto refolded_fold1 = new history<TH1F>("refolded_fold1", "", null<TH1F>, (int64_t) afters.size());

        for (size_t j = 0; j < fafters.size(); ++j) {
            std::string refold_name = "HRefoldedBayes" + std::to_string(iteration[i]);
            auto HRefolded = (TH1F*) fafters[j]->Get(refold_name.data());

            (*refolded)[j] = HRefolded;
            (*refolded_fold0)[j] = fold(HRefolded, nullptr, mr, 0, osr);
            (*refolded_fold1)[j] = fold(HRefolded, nullptr, mr, 1, osr);
        }

        normalise_to_unity(refolded_fold0, refolded_fold1);

        refolded->rename(tag + "_"s + before_label + "_raw_sub_pjet_u_dr_sum0_refolded"s + std::to_string(iteration[i]));
        refolded_fold0->rename(tag + "_"s + before_label + "_raw_sub_pjet_u_dr_sum0_refolded_fold0"s + std::to_string(iteration[i]));
        refolded_fold1->rename(tag + "_"s + before_label + "_raw_sub_pjet_u_dr_sum0_refolded_fold1"s + std::to_string(iteration[i]));

        refolded->save();
        refolded_fold0->save();
        refolded_fold1->save();
    }

    for (size_t i = 0; i < iteration.size(); ++i) {
        auto refolded_merge = new history<TH1F>("refolded_merge", "", null<TH1F>, 1);
        auto refolded_merge_fold0 = new history<TH1F>("refolded_merge_fold0", "", null<TH1F>, 1);
        auto refolded_merge_fold1 = new history<TH1F>("refolded_merge_fold1", "", null<TH1F>, 1);

        std::string refold_name = "HRefoldedBayes" + std::to_string(iteration[i]);
        auto HRefolded = (TH1F*) fmerge->Get(refold_name.data());


        (*refolded_merge)[0] = HRefolded;
        (*refolded_merge_fold0)[0] = fold(HRefolded, nullptr, mr, 0, osr);
        (*refolded_merge_fold1)[0] = fold(HRefolded, nullptr, mr, 1, osr);

        normalise_to_unity(refolded_merge_fold0, refolded_merge_fold1);


        refolded_merge->rename(tag + "_"s + before_label + "_raw_sub_pjet_u_dr_merge_refolded"s + std::to_string(iteration[i]));
        refolded_merge_fold0->rename(tag + "_"s + before_label + "_raw_sub_pjet_u_dr_merge_refolded_fold0"s + std::to_string(iteration[i]));
        refolded_merge_fold1->rename(tag + "_"s + before_label + "_raw_sub_pjet_u_dr_merge_refolded_fold1"s + std::to_string(iteration[i]));

        refolded_merge->save();
        refolded_merge_fold0->save();
        refolded_merge_fold1->save();
    }

    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return get_iteration_files(argv[1], argv[2], argv[3]);

    printf("usage: %s [config] [selections] [output]\n", argv[0]);
    return 1;
}
