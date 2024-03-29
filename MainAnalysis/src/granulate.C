#include "../git/config/include/configurer.h"

#include "../git/history/include/history.h"

#include "../git/tricks-and-treats/include/trunk.h"
#include "../git/tricks-and-treats/include/zip.h"

#include "TFile.h"
#include "TH1.h"

#include <functional>
#include <string>
#include <vector>

using namespace std::literals::string_literals;
using namespace std::placeholders;

int granulate(char const* config, char const* selections, char const* output) {
    auto conf = new configurer(config);

    auto file = conf->get<std::string>("file");
    auto label = conf->get<std::string>("label");
    auto tag = conf->get<std::string>("tag");

    auto refs = conf->get<std::vector<std::string>>("refs");
    auto vars = conf->get<std::vector<std::string>>("vars");
    auto lrefs = conf->get<std::vector<std::string>>("lrefs");
    auto lvars = conf->get<std::vector<std::string>>("lvars");
    auto values = conf->get<std::vector<float>>("values");
    auto figures = conf->get<std::vector<std::string>>("figures");

    auto use_rstubs = conf->get<std::vector<bool>>("ref_stubs");
    auto use_vstubs = conf->get<std::vector<bool>>("var_stubs");

    auto sel = new configurer(selections);

    auto set = sel->get<std::string>("set");
    auto base = sel->get<std::string>("base");

    /* manage memory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    /* load input files */
    TFile* f = new TFile((base + file).data(), "read");

    std::vector<TFile*> frefs(refs.size(), nullptr);
    std::vector<TFile*> fvars(vars.size(), nullptr);
    
    zip([&](auto& fref, auto& fvar, auto const& ref, auto const& var) {
        fref = new TFile((base + ref).data(), "read");
        fvar = new TFile((base + var).data(), "read");
    }, frefs, fvars, refs, vars);

    /* prepare output */
    TFile* fout = new TFile(output, "recreate");

    /* calculate variations */
    zip([&](auto const& figure) {
        auto stub = "_"s + figure;

        auto base = new history<TH1F>(f, tag + "_"s + label + stub);

        std::vector<history<TH1F>*> references(refs.size(), nullptr);
        std::vector<history<TH1F>*> variations(vars.size(), nullptr);

        zip([&](auto& ref, auto& var, auto fref, auto fvar,
                auto const& lref, auto const& lvar, auto value, 
                auto use_rstub, auto use_vstub) {
            auto rstub = use_rstub ? stub : "";
            auto vstub = use_vstub ? stub : "";

            ref = new history<TH1F>(fref, tag + "_"s + lref + rstub);
            var = new history<TH1F>(fvar, tag + "_"s + lvar + stub);

            if ((*ref)[0]->GetNbinsX() == (*var)[0]->GetNbinsX()) {
                var->apply([&](TH1* h, int64_t index) {
                    h->Divide((*ref)[index]); });

                /* scale uncertainties */
                if (value != 0) { var->apply([&](TH1* h) {
                    for_contents([&](std::array<double, 1> val) -> float {
                        return 1. + value * (val[0] - 1.); }, h); }); }

                /* apply uncertainty to base */
                var->apply([&](TH1* h, int64_t index) {
                    h->Multiply((*base)[index]); });

                /* save histograms */
                var->save(tag + "_mod");
            }
        }, references, variations, frefs, fvars, lrefs, lvars, values, use_rstubs, use_vstubs);
    }, figures);

    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return granulate(argv[1], argv[2], argv[3]);

    printf("usage: %s [config] [selections] [output]\n", argv[0]);
    return 1;
}
