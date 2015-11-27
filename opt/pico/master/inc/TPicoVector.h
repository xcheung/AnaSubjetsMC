#ifndef TPICOVECTOR_H
#define TPICOVECTOR_H

#include <TObject.h>

class TPicoVector : public TObject {

 public :

  TPicoVector();
  TPicoVector(Double_t dPt, Double_t dEta, Double_t dPhi);
  TPicoVector(const TPicoVector &src);
  TPicoVector& operator=(const TPicoVector &src);
  virtual ~TPicoVector();
//=============================================================================

  Double_t Pt()   const { return fPt;  }
  Double_t Eta()  const { return fEta; }
  Double_t Phi()  const { return fPhi; }
//=============================================================================

 private :

  Double_t fPt;
  Double_t fEta;
  Double_t fPhi;
//=============================================================================

  ClassDef(TPicoVector, 1)
};

#endif
