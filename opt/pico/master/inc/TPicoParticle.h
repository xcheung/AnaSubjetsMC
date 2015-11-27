#ifndef TPICOPARTICLE_H
#define TPICOPARTICLE_H

#include "TPicoVector.h"

class TPicoParticle : public TPicoVector {

 public :

  TPicoParticle();
  TPicoParticle(Double_t dPt, Double_t dEta, Double_t dPhi, Int_t kPDG, Int_t kStat=1);
  TPicoParticle(const TPicoParticle &src);
  TPicoParticle& operator=(const TPicoParticle &src);
  virtual ~TPicoParticle();
//=============================================================================

  Int_t PDG()  const { return fPDG;  }
  Int_t Stat() const { return fStat; }
//=============================================================================

 private :

  Int_t fPDG;
  Int_t fStat;
//=============================================================================

  ClassDef(TPicoParticle, 1)
};

#endif
