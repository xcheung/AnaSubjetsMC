#include "TPicoVector.h"

ClassImp(TPicoVector)

//_____________________________________________________________________________
TPicoVector::TPicoVector() :
TObject(),
fPt(0.),
fEta(0.),
fPhi(0.)
{
//
// TPicoVector::TPicoVector
//
}

//_____________________________________________________________________________
TPicoVector::TPicoVector(Double_t dPt, Double_t dEta, Double_t dPhi) :
TObject(),
fPt(dPt),
fEta(dEta),
fPhi(dPhi)
{
//
// TPicoVector::TPicoVector
//
}

//_____________________________________________________________________________
TPicoVector::TPicoVector(const TPicoVector &src) :
TObject(src),
fPt(src.fPt),
fEta(src.fEta),
fPhi(src.fPhi)
{
//
// TPicoVector::TPicoVector
//
}

//_____________________________________________________________________________
TPicoVector& TPicoVector::operator=(const TPicoVector &src)
{
//
// TPicoVector::operator=
//

  if (&src==this) return *this;

  TObject::operator=(src);

  fPt   = src.fPt;
  fEta  = src.fEta;
  fPhi  = src.fPhi;

  return *this;
}

//_____________________________________________________________________________
TPicoVector::~TPicoVector()
{
//
// TPicoVector::~TPicoVector
//
}
