#include "../git/config/include/configurer.h"

#include "../git/history/include/history.h"

#include "../git/tricks-and-treats/include/zip.h"

#include <string>
#include <unordered_map>
#include <vector>

#include "TFile.h"
#include "TH1.h"
#include "TNamed.h"

using namespace std::literals::string_literals;

int manipulate(char const* config, char const* selections, char const* output) {
    auto conf = new configurer(config);

    auto purity = conf->get<std::string>("purity");
    auto type = conf->get<std::string>("type");
    auto inputs = conf->get<std::vector<std::string>>("inputs");
    auto groups = conf->get<std::vector<std::string>>("groups");
    auto labels = conf->get<std::vector<std::string>>("labels");
    auto tag = conf->get<std::string>("tag");

    auto sel = new configurer(selections);

    auto base = sel->get<std::string>("base");

    /* manage meory manually */
    TH1::AddDirectory(false);
    TH1::SetDefaultSumw2();

    /* load input */
    TFile* fp = new TFile((base + purity).data(), "read");

    auto purities = new history<TH1F>(fp, type);
    auto impurities = new history<TH1F>(*purities, "im"s);

    std::vector<TFile*> files(inputs.size(), nullptr);
    zip([&](auto& file, auto const& input) {
        file = new TFile((base + input).data(), "read");
    }, files, inputs);

    /* prepare output */
    TFile* fout = new TFile(output, "recreate");

    /* load nevt and do purity scaling */
    auto nevt = new history<TH1F>(files[0], "raw_nevt");
    nevt->multiply(*purities);
    nevt->save(tag);

    /* scale purities and impurities for easy use */
    purities->apply([](TH1* h) {
        auto purity = h->GetBinContent(1);
        h->SetBinContent(1, 1. / purity);
    });
    impurities->apply([](TH1* h) {
        auto purity = h->GetBinContent(1);
        h->SetBinContent(1, 1. - 1. / purity);
    });

    /* load histograms and perform purity subtraction */
    for (auto const& label : labels) {
        std::vector<history<TH1F>*> histograms(groups.size(), nullptr);
        zip([&](auto const file, auto const& group, auto& hist) {
            auto name = group + "_"s + label;
            hist = new history<TH1F>(file, name);

            auto factors = group.find("raw") != std::string::npos
                ? purities : impurities;

            /* scale by appropriate (im)purity values */
            hist->multiply(*factors);
        }, files, groups, histograms);

        /* subtract scaled histograms */
        histograms[0]->add(*histograms[1], 1);
        histograms[0]->save(tag);
    }

    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return manipulate(argv[1], argv[2], argv[3]);

    printf("usage: %s [config] [selections] [output]\n", argv[0]);
    return 1;
}
