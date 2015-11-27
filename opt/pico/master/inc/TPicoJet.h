#ifndef TPICOJET_H
#define TPICOJET_H

#include <TClonesArray.h>

#include "TPicoPiece.h"
//=============================================================================

class TPicoJet : public TPicoPiece {

 public :

  TPicoJet();
  TPicoJet(Double_t dPt, Double_t dEta, Double_t dPhi, Int_t kLabel, Double_t dLtk=-1., Double_t dArea=-1., Double_t dMass=-1.);
  TPicoJet(const TPicoJet &src);
  TPicoJet& operator=(const TPicoJet &src);
  virtual ~TPicoJet();
//=============================================================================

  Double_t Leading() const { return fLtk; }

  Int_t  GetNumberOfPieces() const { return fPiecesClArr.GetEntriesFast(); }
  TPicoPiece *Piece(Int_t i) const { return (TPicoPiece*)fPiecesClArr.UncheckedAt(i); }
//=============================================================================

  Int_t AddPiece(const TPicoPiece &);
//=============================================================================

 private :

  Double_t fLtk;
  TClonesArray fPiecesClArr;
//=============================================================================

  ClassDef(TPicoJet, 1)
};

#endif
