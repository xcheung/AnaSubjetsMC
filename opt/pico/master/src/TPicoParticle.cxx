#include "TPicoParticle.h"

ClassImp(TPicoParticle)

//_____________________________________________________________________________
TPicoParticle::TPicoParticle() :
TPicoVector(),
fPDG(-1),
fStat(-1)
{
//
// TPicoParticle::TPicoParticle
//
}

//_____________________________________________________________________________
TPicoParticle::TPicoParticle(Double_t dPt, Double_t dEta, Double_t dPhi, Int_t kPDG, Int_t kStat) :
TPicoVector(dPt,dEta,dPhi),
fPDG(kPDG),
fStat(kStat)
{
//
// TPicoParticle::TPicoParticle
//
}

//_____________________________________________________________________________
TPicoParticle::TPicoParticle(const TPicoParticle &src) :
TPicoVector(src),
fPDG(src.fPDG),
fStat(src.fStat)
{
//
// TPicoParticle::TPicoParticle
//
}

//_____________________________________________________________________________
TPicoParticle& TPicoParticle::operator=(const TPicoParticle &src)
{
//
// TPicoParticle::operator=
//

  if (&src==this) return *this;

  TPicoVector::operator=(src);

  fPDG  = src.fPDG;
  fStat = src.fStat;

  return *this;
}

//_____________________________________________________________________________
TPicoParticle::~TPicoParticle()
{
//
// TPicoParticle::~TPicoParticle
//
}
