#include "../include/multival.h"

#include "TH2.h"
#include "TH3.h"

using namespace std::literals::string_literals;

std::vector<int64_t> multival::indices_for(int64_t index) const {
    std::vector<int64_t> indices(_dims);
    for (int64_t i = 0; i < _dims; ++i) {
        indices[i] = index % _shape[i];
        index = index / _shape[i];
    }

    return indices;
}

/* template specialisations */
template <>
TH2F* multival::book<TH2F>(int64_t, std::string const& name,
                           std::string const& ordinate) const {
    auto title = ";"s + _intervals[0].abscissa() + ";"s
        + _intervals[1].abscissa() + ";"s + ordinate;

    return new TH2F(name.data(), title.data(),
        _intervals[0].size(), _intervals[0].edges(),
        _intervals[1].size(), _intervals[1].edges());
}

template <>
TH2D* multival::book<TH2D>(int64_t, std::string const& name,
                           std::string const& ordinate) const {
    auto title = ";"s + _intervals[0].abscissa() + ";"s
        + _intervals[1].abscissa() + ";"s + ordinate;

    return new TH2D(name.data(), title.data(),
        _intervals[0].size(), _intervals[0].edges(),
        _intervals[1].size(), _intervals[1].edges());
}

template <>
TH3F* multival::book<TH3F>(int64_t, std::string const& name,
                           std::string const&) const {
    auto title = ";"s + _intervals[0].abscissa() + ";"s
        + _intervals[1].abscissa() + ";"s + _intervals[2].abscissa();

    return new TH3F(name.data(), title.data(),
        _intervals[0].size(), _intervals[0].edges(),
        _intervals[1].size(), _intervals[1].edges(),
        _intervals[2].size(), _intervals[2].edges());
}

template <>
TH2F* multival::book<TH2F, 4>(int64_t, std::string const& name,
                              std::string const& ordinate,
                              std::array<int64_t, 4> const& offset) const {
    auto title = ";"s + _intervals[0].abscissa() + ";"s
        + _intervals[1].abscissa() + ";"s + ordinate;

    return new TH2F(name.data(), title.data(),
        _intervals[0].size() - offset[0] - offset[1],
        _intervals[0].edges() + offset[0],
        _intervals[1].size() - offset[2] - offset[3],
        _intervals[1].edges() + offset[2]);
}

template <>
TH2D* multival::book<TH2D, 4>(int64_t, std::string const& name,
                              std::string const& ordinate,
                              std::array<int64_t, 4> const& offset) const {
    auto title = ";"s + _intervals[0].abscissa() + ";"s
        + _intervals[1].abscissa() + ";"s + ordinate;

    return new TH2D(name.data(), title.data(),
        _intervals[0].size() - offset[0] - offset[1],
        _intervals[0].edges() + offset[0],
        _intervals[1].size() - offset[2] - offset[3],
        _intervals[1].edges() + offset[2]);
}

template <>
TH3F* multival::book<TH3F, 6>(int64_t, std::string const& name,
                              std::string const&,
                              std::array<int64_t, 6> const& offset) const {
    auto title = ";"s + _intervals[0].abscissa() + ";"s
        + _intervals[1].abscissa() + ";"s + _intervals[2].abscissa();

    return new TH3F(name.data(), title.data(),
        _intervals[0].size() - offset[0] - offset[1],
        _intervals[0].edges() + offset[0],
        _intervals[1].size() - offset[2] - offset[3],
        _intervals[1].edges() + offset[2],
        _intervals[2].size() - offset[4] - offset[5],
        _intervals[2].edges() + offset[4]);
}

/* explicit instantiations */
template TH2F*
multival::book<TH2F>(int64_t, std::string const&, std::string const&) const;
template TH2D*
multival::book<TH2D>(int64_t, std::string const&, std::string const&) const;
template TH3F*
multival::book<TH3F>(int64_t, std::string const&, std::string const&) const;
template TH2F*
multival::book<TH2F, 4>(int64_t, std::string const&, std::string const&,
                        std::array<int64_t, 4> const&) const;
template TH2D*
multival::book<TH2D, 4>(int64_t, std::string const&, std::string const&,
                        std::array<int64_t, 4> const&) const;
template TH3F*
multival::book<TH3F, 6>(int64_t, std::string const&, std::string const&,
                        std::array<int64_t, 6> const&) const;