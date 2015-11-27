#include <TList.h>

#include "TPicoVector.h"
#include "TPicoJet.h"
#include "TPicoHeader.h"

ClassImp(TPicoHeader)

//_____________________________________________________________________________
TPicoHeader::TPicoHeader() :
TNamed("PicoHeader", "PicoHeader"),
fPtHat(-1.),
fXsect(-1.),
fWeight(-1.),
fBkgRho(-1.),
fLeading(0)
{
//
// TPicoHeader::TPicoHeader
//
}

//_____________________________________________________________________________
TPicoHeader::TPicoHeader(const TPicoHeader &src) :
TNamed(src),
fPtHat(src.fPtHat),
fXsect(src.fXsect),
fWeight(src.fWeight),
fBkgRho(src.fBkgRho),
fLeading(new TPicoVector(*src.fLeading))
{
//
// TPicoHeader::TPicoHeader
//
}

//_____________________________________________________________________________
TPicoHeader& TPicoHeader::operator=(const TPicoHeader &src)
{
//
// TPicoHeader::operator=
//

  if (&src==this) return *this;

  TNamed::operator=(src);

  fPtHat  = src.fPtHat;
  fXsect  = src.fXsect;
  fWeight = src.fWeight;
  fBkgRho = src.fBkgRho;

  fLeading = new TPicoVector(*src.fLeading);

  return *this;
}

//_____________________________________________________________________________
TPicoHeader::~TPicoHeader()
{
//
// TPicoHeader::~TPicoHeader
//

  if (fLeading) { delete fLeading; fLeading = 0; }
}

//_____________________________________________________________________________
void TPicoHeader::Set(const TPicoVector &pLeading, Double_t dPtHat, Double_t dWeight, Double_t dXsect, Double_t dBkgPho)
{
//
//  TPicoHeader::Set
//

  fPtHat  = dPtHat;
  fXsect  = dXsect;
  fWeight = dWeight;
  fBkgRho = dBkgPho;

  if (fLeading) { delete fLeading; fLeading = 0; }
  fLeading = new TPicoVector(pLeading);

  return;
}

//_____________________________________________________________________________
void TPicoHeader::Reset()
{
  fXsect  = -1.;
  fWeight = -1.;
  fPtHat  = -1.;
  fBkgRho = -1.;

  if (fLeading) { delete fLeading; fLeading = 0; }
  return;
}
