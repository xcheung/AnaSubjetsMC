#ifndef TPICOHEADER_H
#define TPICOHEADER_H

#include <TNamed.h>
#include <TClonesArray.h>
//=============================================================================

class TPicoVector;
//=============================================================================

class TPicoHeader : public TNamed {

 public :

  TPicoHeader();
  TPicoHeader(const TPicoHeader &src);
  TPicoHeader& operator=(const TPicoHeader &src);
  virtual ~TPicoHeader();
//=============================================================================

  Double_t PtHat()  const { return fPtHat;  }
  Double_t Xsect()  const { return fXsect;  }
  Double_t Weight() const { return fWeight; }
  Double_t BkgRho() const { return fBkgRho; }

  Double_t Wevent() const { return (fXsect*fWeight); }

  TPicoVector *Leading() const { return fLeading; }

  void Reset();
  void Set(const TPicoVector &pLeading, Double_t dPtHat, Double_t dWeight=1., Double_t dXsect=1., Double_t dBkgPho=-1.);
//=============================================================================

 private :

  Double_t fPtHat;
  Double_t fXsect;
  Double_t fWeight;
  Double_t fBkgRho;

  TPicoVector *fLeading;
//=============================================================================

  ClassDef(TPicoHeader, 1);
};

#endif
