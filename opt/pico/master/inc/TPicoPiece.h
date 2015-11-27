#ifndef TPICOPIECE_H
#define TPICOPIECE_H

#include "TPicoVector.h"

class TPicoPiece : public TPicoVector {

 public :

  TPicoPiece();
  TPicoPiece(Double_t dPt, Double_t dEta, Double_t dPhi, Int_t kLabel, Double_t dArea=-1., Double_t dMass=-1.);
  TPicoPiece(const TPicoPiece &src);
  TPicoPiece& operator=(const TPicoPiece &src);
  virtual ~TPicoPiece();
//=============================================================================

  Int_t   Label() const { return fLabel; }
  Double_t Area() const { return fArea;  }
  Double_t Mass() const { return fMass;  }
//=============================================================================

 private :

  Int_t    fLabel;
  Double_t fArea;
  Double_t fMass;
//=============================================================================

  ClassDef(TPicoPiece, 1)
};

#endif
