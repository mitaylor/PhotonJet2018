#ifndef PJTREE_H
#define PJTREE_H

#include "../git/foliage/include/foliage.h"

#include "../git/foliage/include/event.h"
#include "../git/foliage/include/eggen.h"
#include "../git/foliage/include/electrons.h"
#include "../git/foliage/include/photons.h"
#include "../git/foliage/include/jets.h"
#include "../git/foliage/include/triggers.h"
#include "../git/foliage/include/evtrho.h"
#include "../git/foliage/include/pfcand.h"
#include "../git/foliage/include/tracks.h"

#include "TTree.h"

#include <array>
#include <vector>

#define B_VEC_JET_RECO(ACTION, ...)                                         \
    ACTION(sv<float>,       rawpt,                      ## __VA_ARGS__)     \
    ACTION(sv<float>,       jtpt,                       ## __VA_ARGS__)     \
    ACTION(sv<float>,       jteta,                      ## __VA_ARGS__)     \
    ACTION(sv<float>,       jtphi,                      ## __VA_ARGS__)     \
    ACTION(sv<float>,       WTAeta,                     ## __VA_ARGS__)     \
    ACTION(sv<float>,       WTAphi,                     ## __VA_ARGS__)     \

#define B_VEC_JET_GEN(ACTION, ...)                                          \
    ACTION(sv<float>,       genpt,                      ## __VA_ARGS__)     \
    ACTION(sv<float>,       geneta,                     ## __VA_ARGS__)     \
    ACTION(sv<float>,       genphi,                     ## __VA_ARGS__)     \
    ACTION(sv<float>,       WTAgeneta,                  ## __VA_ARGS__)     \
    ACTION(sv<float>,       WTAgenphi,                  ## __VA_ARGS__)     \

#define B_VEC_JET_REF(ACTION, ...)                                          \
    ACTION(sv<float>,       refpt,                      ## __VA_ARGS__)     \
    ACTION(sv<float>,       refeta,                     ## __VA_ARGS__)     \
    ACTION(sv<float>,       refphi,                     ## __VA_ARGS__)     \

#define B_VEC_TRG(ACTION, ...)                                              \
    ACTION(sv<int32_t>,     accepts,                    ## __VA_ARGS__)     \

#define B_VAL_EVT_EXT(ACTION, ...)                                          \
    ACTION(float,           w,                          ## __VA_ARGS__)     \

#define B_VEC_EVT_EXT(ACTION, ...)                                          \
    ACTION(sv<float>,       hfweight,                   ## __VA_ARGS__)     \

#define B_VEC_PHO_EXT(ACTION, ...)                                          \
    ACTION(sv<float>,       phoEtEr,                   ## __VA_ARGS__)     \
    ACTION(sv<float>,       phoEtErNew,                ## __VA_ARGS__)     \

#define B_VEC_JET_EXT(ACTION, ...)                                          \
    ACTION(sv<float>,       jtptCorScale,               ## __VA_ARGS__)     \
    ACTION(sv<float>,       jtptCor,                    ## __VA_ARGS__)     \

enum tt { evt, egm, pho, ele, jet, trg, rho, pf, trk, ntt };

class pjtree {
  public:
    pjtree(TTree* t, bool gen, bool hlt, bool hi,
           std::array<bool, tt::ntt> const& flags)
            : _gen(gen), _hlt(hlt), _hi(hi), _flags(flags) {
        B_VAL_EVT_RECO(SETMONE)
        B_VAL_EGM_RECO(SETMONE)
        B_VAL_TRK_RECO(SETMONE)
        B_VAL_PHO_RECO(SETMONE)
        B_VAL_ELE_RECO(SETMONE)
        B_VAL_JET_RECO(SETMONE)
        B_VEC_PHO_RECO(ALLOCOBJ)
        B_VEC_PF_RECO(ALLOCOBJ)
        B_VEC_ELE_RECO(ALLOCOBJ)
        B_VEC_JET_RECO(ALLOCOBJ)
        B_VEC_PHO_EXT(ALLOCOBJ)
        B_VEC_JET_EXT(ALLOCOBJ)

        if (_gen) {
            B_VAL_EVT_GEN(SETMONE)
            B_VAL_EGM_GEN(SETMONE)
            B_VAL_JET_GEN(SETMONE)
            B_VEC_EGM_GEN(ALLOCOBJ)
            B_VEC_JET_GEN(ALLOCOBJ)
            B_VEC_JET_REF(ALLOCOBJ)
            B_VEC_EVT_EXT(ALLOCOBJ)
        }

        if (_hlt) {
            B_VEC_TRG(ALLOCOBJ)
        }

        if (_hi) {
            B_VEC_RHO(ALLOCOBJ)
        }

        if (_gen && !_hi) {
            B_VEC_EVT_GEN(ALLOCOBJ)
        }

        B_VAL_EVT_EXT(SETMONE)

        branch(t);
    }

    pjtree(bool gen, bool hlt, bool hi, TTree* t,
           std::array<bool, tt::ntt> const& flags)
            : _gen(gen), _hlt(hlt), _hi(hi), _flags(flags) {
        t->SetBranchStatus("*", 0);  

        B_VAL_EVT_RECO(SETZERO)
        B_VAL_EGM_RECO(SETZERO)
        B_VAL_TRK_RECO(SETZERO)
        B_VAL_PHO_RECO(SETZERO)
        B_VAL_ELE_RECO(SETZERO)
        B_VAL_JET_RECO(SETZERO)
        B_VEC_PHO_RECO(SETZERO)
        B_VEC_PF_RECO(SETZERO)
        B_VEC_ELE_RECO(SETZERO)
        B_VEC_JET_RECO(SETZERO)
        B_VEC_PHO_EXT(SETZERO)
        B_VEC_JET_EXT(SETZERO)

        if (_gen) {
            B_VAL_EVT_GEN(SETZERO)
            B_VAL_EGM_GEN(SETZERO)
            B_VAL_JET_GEN(SETZERO)
            B_VEC_EGM_GEN(SETZERO)
            B_VEC_JET_GEN(SETZERO)
            B_VEC_JET_REF(SETZERO)
            B_VEC_EVT_EXT(SETZERO)
        }

        if (_hlt) {
            B_VEC_TRG(SETZERO)
        }

        if (_hi) {
            B_VEC_RHO(SETZERO)
        }

        if (_gen && !_hi) {
            B_VEC_EVT_GEN(SETZERO)
        }

        B_VAL_EVT_EXT(SETZERO)

        read(t);
    }

    ~pjtree() = default;

    void clear() {
        B_VEC_PHO_RECO(CLEAROBJ)
        B_VEC_PF_RECO(CLEAROBJ)
        B_VEC_ELE_RECO(CLEAROBJ)
        B_VEC_JET_RECO(CLEAROBJ)
        B_VEC_PHO_EXT(CLEAROBJ)
        B_VEC_JET_EXT(CLEAROBJ)

        if (_gen) {
            B_VEC_EGM_GEN(CLEAROBJ)
            B_VEC_JET_GEN(CLEAROBJ)
            B_VEC_JET_REF(CLEAROBJ)
            B_VEC_EVT_EXT(CLEAROBJ)
        }

        if (_hlt) {
            B_VEC_TRG(CLEAROBJ)
        }

        if (_hi) {
            B_VEC_RHO(CLEAROBJ)
        }

        if (_gen && !_hi) {
            B_VEC_EVT_GEN(CLEAROBJ)
        }
    }

    void copy(event* tevt, eggen* tegg, photons* tpho, electrons* tele,
              jets* tjet, triggers* thlt, evtrho* trho, pfcand* tpf, tracks* ttrk) {
        if (_flags[tt::evt]) {
            B_VAL_EVT_RECO(COPYVAL, tevt)

            if (_gen) {
                B_VAL_EVT_GEN(COPYVAL, tevt)
            }

            if (_gen && !_hi) {
                B_VEC_EVT_GEN(COPYOBJ, tevt)
            }
        }

        if (_flags[tt::egm]) {
            B_VAL_EGM_RECO(COPYVAL, tegg)
            
            if (_gen) {
                B_VAL_EGM_GEN(COPYVAL, tegg)
                B_VEC_EGM_GEN(COPYOBJ, tegg)
            }
        }

        if (_flags[tt::ele]) {
            B_VAL_ELE_RECO(COPYVAL, tele)
            B_VEC_ELE_RECO(COPYOBJ, tele)
        }

        if (_flags[tt::pho]) {
            B_VAL_PHO_RECO(COPYVAL, tpho)
            B_VEC_PHO_RECO(COPYOBJ, tpho)
        }

        if (_flags[tt::jet]) {
            B_VAL_JET_RECO(COPYVAL, tjet)
            B_VEC_JET_RECO(COPYPTR, tjet, nref)

            if (_gen) {
                B_VAL_JET_GEN(COPYVAL, tjet)
                B_VEC_JET_GEN(COPYPTR, tjet, ngen)
                B_VEC_JET_REF(COPYPTR, tjet, nref)
            }
        }

        if (_flags[tt::trg]) {
            if (_hlt) {
                B_VEC_TRG(COPYPTR, thlt, thlt->size())
            }
        }

        if (_flags[tt::rho]) {
            B_VEC_RHO(COPYOBJ, trho)
        }

        if (_flags[tt::pf]) {
            B_VEC_PF_RECO(COPYOBJ, tpf)
        }

        if (_flags[tt::trk]) {
            B_VAL_TRK_RECO(COPYVAL, ttrk)
        }
    }

    B_VAL_EVT_RECO(DECLVAL)
    B_VAL_EVT_GEN(DECLVAL)
    B_VEC_EVT_GEN(DECLPTR)
    B_VAL_EVT_EXT(DECLVAL)
    B_VAL_EGM_RECO(DECLVAL)
    B_VAL_EGM_GEN(DECLVAL)
    B_VEC_EGM_GEN(DECLPTR)
    B_VAL_PHO_RECO(DECLVAL)
    B_VAL_TRK_RECO(DECLVAL)
    B_VEC_PHO_RECO(DECLPTR)
    B_VEC_PF_RECO(DECLPTR)
    B_VEC_PHO_EXT(DECLPTR)
    B_VAL_ELE_RECO(DECLVAL)
    B_VEC_ELE_RECO(DECLPTR)
    B_VAL_JET_RECO(DECLVAL)
    B_VEC_JET_RECO(DECLPTR)
    B_VEC_JET_EXT(DECLPTR)
    B_VAL_JET_GEN(DECLVAL)
    B_VEC_JET_GEN(DECLPTR)
    B_VEC_JET_REF(DECLPTR)
    B_VEC_EVT_EXT(DECLPTR)
    B_VEC_TRG(DECLPTR)
    B_VEC_RHO(DECLPTR)

  private:
    void branch(TTree* t) {
        if (_flags[tt::evt]) {
            B_VAL_EVT_RECO(BRANCHVAL, t)

            if (_gen) {
                B_VAL_EVT_GEN(BRANCHVAL, t)
                B_VEC_EVT_EXT(BRANCHPTR, t)
            }

            if (_gen && !_hi) {
                B_VEC_EVT_GEN(BRANCHPTR, t)
            }

            B_VAL_EVT_EXT(BRANCHVAL, t)
        }

        if (_flags[tt::egm]) {
            B_VAL_EGM_RECO(BRANCHVAL, t)

            if (_gen) {
                B_VAL_EGM_GEN(BRANCHVAL, t)
                B_VEC_EGM_GEN(BRANCHPTR, t)
            }
        }

        if (_flags[tt::pho]) {
            B_VAL_PHO_RECO(BRANCHVAL, t)
            B_VEC_PHO_RECO(BRANCHPTR, t)
            B_VEC_PHO_EXT(BRANCHPTR, t)
        }

        if (_flags[tt::ele]) {
            B_VAL_ELE_RECO(BRANCHVAL, t)
            B_VEC_ELE_RECO(BRANCHPTR, t)
        }

        if (_flags[tt::jet]) {
            B_VAL_JET_RECO(BRANCHVAL, t)
            B_VEC_JET_RECO(BRANCHPTR, t)
            B_VEC_JET_EXT(BRANCHPTR, t)

            if (_gen) {
                B_VAL_JET_GEN(BRANCHVAL, t)
                B_VEC_JET_GEN(BRANCHPTR, t)
                B_VEC_JET_REF(BRANCHPTR, t)
            }
        }

        if (_flags[tt::trg]) {
            if (_hlt) {
                B_VEC_TRG(BRANCHPTR, t)
            }
        }

        if (_flags[tt::rho]) {
            B_VEC_RHO(BRANCHPTR, t)
        }

        if (_flags[tt::pf]) {
            B_VEC_PF_RECO(BRANCHPTR, t)
        }

        if (_flags[tt::trk]) {
            B_VAL_TRK_RECO(BRANCHVAL, t)
        }
    }

    void read(TTree* t) {
        if (_flags[tt::evt]) {
            B_VAL_EVT_RECO(SETVALADDR, t)

            if (_gen) {
                B_VAL_EVT_GEN(SETVALADDR, t)
                B_VEC_EVT_EXT(SETVALADDR, t)
            }

            if (_gen && !_hi) {
                B_VEC_EVT_GEN(SETVALADDR, t)
            }

            B_VAL_EVT_EXT(SETVALADDR, t)
        }

        if (_flags[tt::egm]) {
            B_VAL_EGM_RECO(SETVALADDR, t)

            if (_gen) {
                B_VAL_EGM_GEN(SETVALADDR, t)
                B_VEC_EGM_GEN(SETVALADDR, t)
            }
        }

        if (_flags[tt::pho]) {
            B_VAL_PHO_RECO(SETVALADDR, t)
            B_VEC_PHO_RECO(SETVALADDR, t)
            B_VEC_PHO_EXT(SETVALADDR, t)
        }

        if (_flags[tt::ele]) {
            B_VAL_ELE_RECO(SETVALADDR, t)
            B_VEC_ELE_RECO(SETVALADDR, t)
        }

        if (_flags[tt::jet]) {
            B_VAL_JET_RECO(SETVALADDR, t)
            B_VEC_JET_RECO(SETVALADDR, t)
            B_VEC_JET_EXT(SETVALADDR, t)

            if (_gen) {
                B_VAL_JET_GEN(SETVALADDR, t)
                B_VEC_JET_GEN(SETVALADDR, t)
                B_VEC_JET_REF(SETVALADDR, t)
            }
        }

        if (_flags[tt::trg]) {
            if (_hlt) {
                B_VEC_TRG(SETVALADDR, t)
            }
        }

        if (_flags[tt::rho]) {
            B_VEC_RHO(SETVALADDR, t)
        }

        if (_flags[tt::pf]) {
            B_VEC_PF_RECO(SETVALADDR, t)
        }

        if (_flags[tt::trk]) {
            B_VAL_TRK_RECO(SETVALADDR, t)
        }
    }

    bool _gen;
    bool _hlt;
    bool _hi;
    std::array<bool, tt::ntt> _flags;
};

#endif /* PJTREE_H */
