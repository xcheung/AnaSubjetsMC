#include "TPicoPiece.h"

ClassImp(TPicoPiece)

//_____________________________________________________________________________
TPicoPiece::TPicoPiece() :
TPicoVector(),
fLabel(-1),
fArea(-1.),
fMass(-1.)
{
//
// TPicoPiece::TPicoPiece
//
}

//_____________________________________________________________________________
TPicoPiece::TPicoPiece(Double_t dPt, Double_t dEta, Double_t dPhi, Int_t kLabel, Double_t dArea, Double_t dMass) :
TPicoVector(dPt,dEta,dPhi),
fLabel(kLabel),
fArea(dArea),
fMass(dMass)
{
//
// TPicoPiece::TPicoPiece
//
}

//_____________________________________________________________________________
TPicoPiece::TPicoPiece(const TPicoPiece &src) :
TPicoVector(src),
fLabel(src.fLabel),
fArea(src.fArea),
fMass(src.fMass)
{
//
// TPicoPiece::TPicoPiece
//
}

//_____________________________________________________________________________
TPicoPiece& TPicoPiece::operator=(const TPicoPiece &src)
{
//
// TPicoPiece::operator=
//

  if (&src==this) return *this;

  TPicoVector::operator=(src);

  fLabel = src.fLabel;
  fArea  = src.fArea;
  fMass  = src.fMass;

  return *this;
}

//_____________________________________________________________________________
TPicoPiece::~TPicoPiece()
{
//
// TPicoPiece::~TPicoPiece
//
}
