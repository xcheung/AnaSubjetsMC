#include "TPicoJet.h"

ClassImp(TPicoJet)

//_____________________________________________________________________________
TPicoJet::TPicoJet() :
TPicoPiece(),
fLtk(-1.),
fPiecesClArr()
{
//
// TPicoJet::TPicoJet
//
}

//_____________________________________________________________________________
TPicoJet::TPicoJet(Double_t dPt, Double_t dEta, Double_t dPhi, Int_t kLabel, Double_t dLtk, Double_t dArea, Double_t dMass) :
TPicoPiece(dPt,dEta,dPhi,kLabel,dArea,dMass),
fLtk(dLtk),
fPiecesClArr("TPicoPiece",0)
{
//
// TPicoJet::TPicoJet
//

  fPiecesClArr.SetName("PicoPieces");
}

//_____________________________________________________________________________
TPicoJet::TPicoJet(const TPicoJet &src) :
TPicoPiece(src),
fLtk(src.fLtk),
fPiecesClArr(src.fPiecesClArr)
{
//
// TPicoJet::TPicoJet
//
}

//_____________________________________________________________________________
TPicoJet& TPicoJet::operator=(const TPicoJet &src)
{
//
// TPicoJet::operator=
//

  if (&src==this) return *this;

  TPicoPiece::operator=(src);

  fLtk = src.fLtk;
  fPiecesClArr = src.fPiecesClArr;

  return *this;
}

//_____________________________________________________________________________
TPicoJet::~TPicoJet()
{
//
// TPicoJet::~TPicoJet
//

  if (fPiecesClArr.GetEntriesFast()>0) fPiecesClArr.Delete();
}

//_____________________________________________________________________________
Int_t TPicoJet::AddPiece(const TPicoPiece &p)
{
//
//  TPicoJet::AddPiece
//

  new ((fPiecesClArr)[fPiecesClArr.GetEntriesFast()]) TPicoPiece(p);
  return fPiecesClArr.GetEntriesFast()-1;
}
