#include "../include/lambdas.h"

#include "../git/config/include/configurer.h"

#include "../git/history/include/interval.h"
#include "../git/history/include/multival.h"
#include "../git/history/include/history.h"

#include "../git/paper-and-pencil/include/paper.h"
#include "../git/paper-and-pencil/include/pencil.h"

#include "../git/tricks-and-treats/include/trunk.h"
#include "../git/tricks-and-treats/include/zip.h"

#include "TDecompSVD.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TSpline.h"
#include "TVectorT.h"

#include "TUnfoldBinning.h"
#include "TUnfoldDensity.h"

#include <string>
#include <vector>

using namespace std::literals::string_literals;
using namespace std::placeholders;

template <typename... T>
void zero_error(T*... args) {
    (void)(int [sizeof...(T)]) { (args->apply([](TH2* obj) {
        for (int64_t i = 1; i <= obj->GetNbinsX(); ++i) {
            for (int64_t j = 1; j <= obj->GetNbinsY(); ++j) {
                obj->SetBinError(i, j, 0);
            }
        }
    }), 0)... };
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

template <std::size_t N>
TH1F* fold(TH1* flat, TH2* covariance, multival const* m, int64_t axis,
           std::array<int64_t, N> const& offsets) {
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

template <typename T>
TH2F* shade(T* flat, multival const* m, std::array<int64_t, 4> const& offset) {
    auto name = std::string(flat->GetName()) + "_shade";
    auto hshade = m->book<TH2F, 4>(0, name, "", offset);

    for (int64_t i = 0; i < m->size(); ++i) {
        auto indices = m->indices_for(i);
        indices[0] = indices[0] - offset[0];
        indices[1] = indices[1] - offset[2];

        if (indices[0] < 0 || indices[0] >= hshade->GetNbinsX()
                || indices[1] < 0 || indices[1] >= hshade->GetNbinsY()) {
            continue; }

        hshade->SetBinContent(indices[0] + 1, indices[1] + 1,
            flat->GetBinContent(i + 1));
        hshade->SetBinError(indices[0] + 1, indices[1] + 1,
            flat->GetBinError(i + 1));
    }

    hshade->Scale(1., "width");

    return hshade;
}

std::vector<float> widths(multival* m, int64_t d) {
    auto size = m->shape()[d];
    auto axis = m->axis(d);

    auto width = std::vector<float>(size, 0);
    for (int64_t i = 0; i < size; ++i)
        width[i] = axis.width(i);

    return width;
}

std::vector<float> deltas(multival* m, int64_t d) {
    auto size = m->shape()[d];
    auto axis = m->axis(d);

    auto delta = std::vector<float>(size, 0);
    for (int64_t i = 0; i < size; ++i) {
        auto edges = axis.edges(i);
        delta[i] = (edges[0] + edges[1]) / 2.;
    }

    for (int64_t i = 0; i < size - 1; ++i)
        delta[i] = delta[i + 1] - delta[i];
    delta.pop_back();

    return delta;
}

float averages(std::vector<float> const& w) {
    return std::accumulate(std::begin(w), std::end(w), 0.f) / w.size();
}

template <TUnfold::ERegMode M>
void pattern(TUnfoldDensity* u, multival* m);

template <> // try kRegModeDerivative and kRegModeSize
void pattern<TUnfold::ERegMode::kRegModeCurvature>(TUnfoldDensity* u,
                                                   multival* m) {
    std::array<std::vector<float>, 2> ws = { widths(m, 0), widths(m, 1) };
    std::array<std::vector<float>, 2> ds = { deltas(m, 0), deltas(m, 1) };
    std::array<float, 2> as = { averages(ws[0]), averages(ws[1]) };

    auto shape = m->shape();

    for (int64_t i = 0; i < shape[0]; ++i) {
        auto step = m->index_for(x{0, 1});
        for (int64_t j = 0; j < shape[1] - 2; ++j) {
            auto index = m->index_for(x{i, j});

            auto common = as[1] * as[1] / (ds[1][j] + ds[1][j + 1]);
            u->RegularizeCurvature(index, index + step, index + step + step,
                common / ds[1][j], common / ds[1][j + 1]);
        }
    }

    for (int64_t j = 0; j < shape[1]; ++j) {
        auto step = m->index_for(x{1, 0});
        for (int64_t i = 0; i < shape[0] - 2; ++i) {
            auto index = m->index_for(x{i, j});

            auto common = -as[0] * as[0] / (ds[0][i] + ds[0][i + 1]);
            u->RegularizeCurvature(index, index + step, index + step + step,
                common / ds[0][i], common / ds[0][i + 1]);
        }
    }
}

double condition(TH2* h) {
    double cond = -1;

    auto rows = h->GetNbinsX();
    auto cols = h->GetNbinsY();

    auto m = new TMatrixT<double>(rows, cols);
    for (int64_t i = 0; i < rows; ++i)
        for (int64_t j = 0; j < cols; ++j)
            (*m)[i][j] = h->GetBinContent(i + 1, j + 1);

    auto svd = new TDecompSVD(*m);
    if (svd->Decompose()) {
        auto s = svd->GetSig();
        cond = s[0] / s[cols - 1];
    }

    delete m;
    delete svd;

    return cond;
}

int undulate(char const* config, char const* output) {
    auto conf = new configurer(config);

    auto input = conf->get<std::string>("input");
    auto system = conf->get<std::string>("system");
    auto tag = conf->get<std::string>("tag");
    auto type = conf->get<std::string>("type");
    auto observable = conf->get<std::string>("observable");
    auto xlabel = conf->get<std::string>("xlabel");

    auto victim = conf->get<std::string>("victim");
    auto label = conf->get<std::string>("label");
    auto reference = conf->get<std::string>("reference");

    auto extensions = conf->get<std::vector<int64_t>>("extensions");
    auto dimensions = conf->get<std::vector<int64_t>>("dimensions");
    auto divisions = conf->get<std::vector<int64_t>>("divisions");

    auto points = conf->get<int64_t>("points");
    auto taus = conf->get<std::vector<float>>("taus");
    auto scale = conf->get<std::vector<float>>("scale");

    auto rdrr = conf->get<std::vector<float>>("drr_range");
    auto rdrg = conf->get<std::vector<float>>("drg_range");
    auto rptr = conf->get<std::vector<float>>("ptr_range");
    auto rptg = conf->get<std::vector<float>>("ptg_range");

    auto rfold0 = conf->get<std::vector<float>>("fold0_range");

    auto dpt = conf->get<std::vector<float>>("pt_diff");
    auto dhf = conf->get<std::vector<float>>("hf_diff");
    auto dcent = conf->get<std::vector<int32_t>>("cent_diff");

    auto mpthf = new multival(dpt, dhf);

    auto idrr = new interval(xlabel, rdrr);
    auto iptr = new interval("p_{T}^{j}"s, rptr);
    auto idrg = new interval(xlabel, rdrg);
    auto iptg = new interval("p_{T}^{j}"s, rptg);

    auto mr = new multival(*idrr, *iptr);
    auto mg = new multival(*idrg, *iptg);

    if (reference.empty()) { reference = label; }

    /* manage memory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    /* load input, victims, and references */
    TFile* fi = new TFile(input.data(), "read");
    auto matrices = new history<TH2F>(fi, tag + "_c");
    zero_error(matrices);

    TFile* fv = new TFile(victim.data(), "read");
    auto victims = new history<TH1F>(fv, label);
    auto ref = new history<TH1F>(fv, reference);

    /* shrink the victim to remove the jet pt 20 bin */
    if ((*victims)[0]->GetNbinsX() > mr->size()) {
        for (int64_t i = 0; i < victims->size(); ++i) {
            auto name = (*victims)[i]->GetName();

            auto temp = new TH1F(name, ";index;", mr->size(), 0, mr->size());
            
            for (int j = 0; j < mr->size(); ++j) {
                std::cout << j + 1 << " " << (*victims)[i]->GetNbinsX() - mr->size() + j + 1 << std::endl;
                temp->SetBinContent(j + 1, (*victims)[i]->GetBinContent((*victims)[i]->GetNbinsX() - mr->size() + j + 1));
                temp->SetBinError(j + 1, (*victims)[i]->GetBinError((*victims)[i]->GetNbinsX() - mr->size() + j + 1));

                // if (temp->GetBinContent(j+1) < 0) {
                //     temp->SetBinContent(j+1, 0);
                //     temp->SetBinError(j+1, 0);
                //     std::cout << "Histogram " << i << " bin " << j+1 << " set to 0" << std::endl;
                // }
            }

            delete (*victims)[i];
            (*victims)[i] = (TH1F*) temp;
        }
    }

    zip([&](int64_t extension, int64_t dimension) {
        matrices = matrices->extend("ext"s + std::to_string(extension),
            extension, dimension); }, extensions, dimensions);

    auto shape = victims->shape();

    /* prepare density vectors */
    auto density = [](multival* m) {
        auto s = new TVectorD(m->size()); *s = 1.;
        for (int64_t i = 0; i < m->size(); ++i) {
            auto axes = m->axes();
            auto indices = m->indices_for(i);

            zip([&](interval const& axis, int64_t index) {
                (*s)[i] = (*s)[i] / axis.width(index);
            }, axes, indices);
        }

        return s;
    };

    auto sr = density(mr);
    auto sg = density(mg);

    /* prepare objects for unfolding */
    auto fbr = [&](int64_t i, std::string const&, std::string const&) {
        return new TUnfoldBinning(*(*matrices)[i]->GetXaxis(), 0, 0); };
    auto fbg = [&](int64_t i, std::string const&, std::string const&) {
        return new TUnfoldBinning(*(*matrices)[i]->GetYaxis(), 0, 0); };

    auto br = new history<TUnfoldBinning>("br"s, "", fbr, shape);
    auto bg = new history<TUnfoldBinning>("bg"s, "", fbg, shape);

    auto factory = [&](int64_t i, std::string const&, std::string const&) {
        return new TUnfoldDensity((*matrices)[i],
            TUnfold::EHistMap::kHistMapOutputVert,
            TUnfold::ERegMode::kRegModeNone,
            TUnfold::EConstraint::kEConstraintNone,
            TUnfoldDensity::EDensityMode::kDensityModeUser,
            (*bg)[i],
            (*br)[i]
        );
    }; // try kRegModeDerivative, kRegModeCurvature, kEConstraintArea, kDensityModeBinWidth

    auto uf = new history<TUnfoldDensity>("uf"s, "", factory, shape);

    auto pmatrix = new history<TH2>("pmatrix"s, "", null<TH2>, shape);
    auto ematrix = new history<TH2>("ematrix"s, "", null<TH2>, shape);
    auto lmatrix = new history<TH2>("lmatrix"s, "", null<TH2>, shape);
    auto bias = new history<TH1>("bias"s, "", null<TH1>, shape);

    auto logtaur = new history<TGraph>("logtaur"s, "", null<TGraph>, shape);
    auto logtaux = new history<TGraph>("logtaux"s, "", null<TGraph>, shape);
    auto logtauy = new history<TGraph>("logtauy"s, "", null<TGraph>, shape);
    auto lcurve = new history<TGraph>("lcurve"s, "", null<TGraph>, shape);

    auto shaded = new history<TH2F>(label + "_shade", "", null<TH2F>, shape);
    auto side0 = new history<TH1F>(label + "_side0", "", null<TH1F>, shape);
    auto side1 = new history<TH1F>(label + "_side1", "", null<TH1F>, shape);

    auto error = new history<TH2>("error"s, "", null<TH2>, shape);
    auto result = new history<TH1>("result"s, "", null<TH1>, shape);
    auto refold = new history<TH1>("refold"s, "", null<TH1>, shape);

    auto sresult = new history<TH2F>("sresult"s, "", null<TH2F>, shape);
    auto srefold = new history<TH2F>("srefold"s, "", null<TH2F>, shape);

    auto fold0 = new history<TH1F>("fold0"s, "", null<TH1F>, shape);
    auto fold1 = new history<TH1F>("fold1"s, "", null<TH1F>, shape);

    std::array<int64_t, 4> osg = { 0, 0, 2, 0 };
    std::array<int64_t, 4> osr = { 0, 0, 0, 1 };

    /* info text */
    std::function<void(int64_t, float)> pt_info = [&](int64_t x, float pos) {
        info_text(x, pos, "%.0f < p_{T}^{#gamma} < %.0f", dpt, false); };

    std::function<void(int64_t, float)> hf_info = [&](int64_t x, float pos) {
        info_text(x, pos, "%i - %i%%", dcent, true); };

    auto pthf_info = [&](int64_t index) {
        stack_text(index, 0.75, 0.04, mpthf, pt_info, hf_info); };

    auto system_info = system + " #sqrt{s_{NN}} = 5.02 TeV";

    /* figures */
    auto hb = new pencil();
    hb->category("type", "data", "unfolded", "refolded", "optimal", "bias",
                         "truth");
    hb->category("bins", "gen", "reco");

    hb->alias("gen", "");
    hb->alias("reco", "");

    std::vector<paper*> cs(18, nullptr);
    zip([&](paper*& c, std::string const& title) {
        c = new paper(tag + "_" + type + "_" + observable + "_" + title, hb);
        apply_style(c, system_info);
        c->accessory(pthf_info);
        c->divide(divisions[0], divisions[1]);
    }, cs, (std::initializer_list<std::string> const) {
        "matrices"s, "pmatrix"s, "ematrix"s, "lmatrix"s,
        "logtaur"s, "logtaux"s, "logtauy"s, "lcurve"s,
        "unfold"s, "refold"s, "sresult"s, "srefold"s,
        "fold0"s, "fold1"s, "error"s, "shaded"s, "closure"s,
        "ratio"s });

    cs[12]->format(std::bind(default_formatter, _1, rfold0[0], rfold0[1]));
    cs[13]->format(std::bind(default_formatter, _1, -0.001, 0.02));

    /* unfold */
    uf->apply([&](TUnfoldDensity* u, int64_t i) {
        if (u->SetInput((*victims)[i], scale[i]) > 9999) {
            printf("  [!] error: set input\n"); //exit(1);
        }

        /* calculate condition number */
        auto cond = condition((*matrices)[i]);
        printf("condition: %f\n", cond);

        /* set density factors */
        (*br)[i]->SetBinFactorFunction(1., (TF1*)sr);
        (*bg)[i]->SetBinFactorFunction(1., (TF1*)sg);

        /* set regularisation pattern */
        pattern<TUnfold::ERegMode::kRegModeCurvature>(u, mg);

        TSpline* slogtaur;
        TSpline* slogtaux;
        TSpline* slogtauy;

        /* scan global correlation coefficient */
        auto knot = u->ScanTau(points, taus[0], taus[1], &slogtaur,
                               TUnfoldDensity::kEScanTauRhoAvg, 0, 0,
                               &(*lcurve)[i], &slogtaux, &slogtauy);

        /* results */
        (*error)[i] = u->GetEmatrixTotal(nullptr);
        (*result)[i] = u->GetOutput(nullptr);
        (*refold)[i] = u->GetFoldedOutput(nullptr);

        (*sresult)[i] = shade((*result)[i], mg, osg);
        (*srefold)[i] = shade((*refold)[i], mr, osr);

        (*fold0)[i] = fold((*result)[i], (*error)[i], mg, 0, osg);
        (*fold1)[i] = fold((*result)[i], (*error)[i], mg, 1, osg);

        /* information and settings */
        printf("chi2/ndf: (%f [A] + %f [L]) / %i\n", u->GetChi2A(),
            u->GetChi2L(), u->GetNdf());

        (*pmatrix)[i] = u->GetProbabilityMatrix(nullptr);
        (*ematrix)[i] = u->GetEmatrixInput(nullptr);
        (*lmatrix)[i] = u->GetL(nullptr);
        (*bias)[i] = u->GetBias(nullptr);

        double t;
        double r;
        double x;
        double y;

        slogtaur->GetKnot(knot, t, r);
        slogtaux->GetKnot(knot, t, x);
        slogtauy->GetKnot(knot, t, y);

        auto mark = [](double const& x, double const& y) {
            auto marker = new TGraph(1, &x, &y);
            marker->SetMarkerStyle(21);

            return marker;
        };

        auto opt_logtaur = mark(t, r);
        auto opt_logtaux = mark(t, x);
        auto opt_logtauy = mark(t, y);
        auto opt_lcurve = mark(x, y);

        auto trace = [](TSpline const* s, int64_t n) {
            auto x = new double[n];
            auto y = new double[n];

            for (int64_t i = 0; i < n; ++i)
                s->GetKnot(i, x[i], y[i]);

            return new TGraph(n, x, y);
        };

        (*logtaur)[i] = trace(slogtaur, points);
        (*logtaux)[i] = trace(slogtaux, points);
        (*logtauy)[i] = trace(slogtauy, points);

        /* input folds */
        (*shaded)[i] = shade((*victims)[i], mr, osr);
        (*side0)[i] = fold((*victims)[i], nullptr, mr, 0, osr);
        (*side1)[i] = fold((*victims)[i], nullptr, mr, 1, osr);

        /* normalise to unity */
        (*fold0)[i]->Scale(1. / (*fold0)[i]->Integral("width"));
        (*side0)[i]->Scale(1. / (*side0)[i]->Integral("width"));

        /* closure ratio plot */
        TH1F* closure = (TH1F*) (*result)[i]->Clone("closure");
        closure->Divide((*ref)[i]);

        /* set titles */
        (*logtaur)[i]->SetTitle(";log_{10}#tau;#rho");
        (*logtaux)[i]->SetTitle(";log_{10}#tau;log_{10}L_{1}");
        (*logtauy)[i]->SetTitle(";log_{10}#tau;log_{10}L_{2}/#tau^{2}");
        (*lcurve)[i]->SetTitle(";log_{10}L_{1};log_{10}L_{2}/#tau^{2}");
        (*result)[i]->SetTitle("");

        /* figures */
        cs[0]->add((*matrices)[i]);
        cs[0]->adjust((*matrices)[i], "colz", "");

        cs[1]->add((*pmatrix)[i]);
        cs[1]->adjust((*pmatrix)[i], "colz", "");

        cs[2]->add((*ematrix)[i]);
        cs[2]->adjust((*ematrix)[i], "colz", "");

        cs[3]->add((*lmatrix)[i]);
        cs[3]->adjust((*lmatrix)[i], "colz", "");

        cs[4]->add((*logtaur)[i]);
        cs[4]->adjust((*logtaur)[i], "al", "");
        cs[4]->stack(opt_logtaur, "optimal");
        cs[4]->adjust(opt_logtaur, "p", "");

        cs[5]->add((*logtaux)[i]);
        cs[5]->adjust((*logtaux)[i], "al", "");
        cs[5]->stack(opt_logtaux, "optimal");
        cs[5]->adjust(opt_logtaux, "p", "");

        cs[6]->add((*logtauy)[i]);
        cs[6]->adjust((*logtauy)[i], "al", "");
        cs[6]->stack(opt_logtauy, "optimal");
        cs[6]->adjust(opt_logtauy, "p", "");

        cs[7]->add((*lcurve)[i]);
        cs[7]->adjust((*lcurve)[i], "al", "");
        cs[7]->stack(opt_lcurve, "optimal");
        cs[7]->adjust(opt_lcurve, "p", "");

        cs[8]->add((*result)[i], "unfolded");

        cs[9]->add((*victims)[i], "data");
        cs[9]->stack((*refold)[i], "refolded");

        cs[10]->add((*sresult)[i]);
        cs[10]->adjust((*sresult)[i], "colz", "");
        cs[11]->add((*srefold)[i]);
        cs[11]->adjust((*srefold)[i], "colz", "");

        cs[12]->add((*side0)[i], "data", "reco");
        cs[12]->stack((*fold0)[i], "unfolded", "gen");
        cs[13]->add((*side1)[i], "data", "reco");
        cs[13]->stack((*fold1)[i], "unfolded", "gen");

        cs[14]->add((*error)[i]);
        cs[14]->adjust((*error)[i], "colz", "");

        cs[15]->add((*shaded)[i]);
        cs[15]->adjust((*shaded)[i], "colz", "");

        cs[16]->add((*result)[i], "unfolded");
        cs[16]->stack((*bias)[i], "bias");
        cs[16]->stack((*ref)[i], "truth");

        cs[17]->add(closure);
    });

    hb->set_binary("bins");
    hb->sketch();

    for (auto c : cs)
        c->draw("pdf");

    /* save output */
    in(output, [&]() {
        matrices->save();
        victims->save();

        shaded->saveas();
        side0->saveas();
        side1->saveas();

        pmatrix->saveby(tag);
        ematrix->saveby(tag);
        lmatrix->saveby(tag);
        bias->saveby(tag);

        logtaur->saveby(tag);
        logtaux->saveby(tag);
        logtauy->saveby(tag);
        lcurve->saveby(tag);

        error->saveby(tag);
        result->saveby(tag);
        refold->saveby(tag);
        sresult->saveby(tag);
        srefold->saveby(tag);
        fold0->saveby(tag);
        fold1->saveby(tag);
    });

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return undulate(argv[1], argv[2]);

    return 0;
}