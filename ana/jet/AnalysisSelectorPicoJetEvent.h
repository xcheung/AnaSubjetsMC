//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Oct 25 01:50:28 2015 by ROOT version 5.34/32
// from TChain treePico/
//////////////////////////////////////////////////////////

#ifndef ANALYSISSELECTORPICOSIMEVENT_H
#define ANALYSISSELECTORPICOSIMEVENT_H

#include <TSelector.h>

#include "TPicoJet.h"
#include "TPicoHeader.h"
#include "TPicoJetEvent.h"
//=============================================================================

class TFile;
class TTree;
class TStopwatch;
class TClonesArray;

class TPicoVector;
class TPicoPiece;
//=============================================================================

class AnalysisSelectorPicoJetEvent : public TSelector {
 public :

  AnalysisSelectorPicoJetEvent(TTree *tree=0);
  virtual ~AnalysisSelectorPicoJetEvent();
//=============================================================================

  virtual Int_t  Version() const { return 2; }

  virtual void   Begin(TTree *tree);
  virtual void   SlaveBegin(TTree *tree);

  virtual void   Init(TTree *tree);
  virtual Bool_t Notify();

  virtual Bool_t Process(Long64_t entry);
  virtual Int_t  GetEntry(Long64_t entry, Int_t getall=0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }

  virtual void   SetOption(const char *option) { fOption = option; }
  virtual void   SetObject(TObject *obj) { fObject = obj; }

  virtual void   SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }

  virtual void   SlaveTerminate();
  virtual void   Terminate();
//=============================================================================

 protected :

  Bool_t CheckEvent(Long64_t entry);
  void   ResetEvent() { Event()->Reset(); }

  TPicoJetEvent *Event() const { return fEvent; }

  TPicoHeader  *Header() const { return (Event()  ? Event()->Header()   : 0); }
  TPicoVector *Leading() const { return (Header() ? Header()->Leading() : 0); }

  TClonesArray *Jets()   const { return  (Event() ? Event()->Jets()  : 0); }
  TPicoJet *Jet(Int_t j) const { return  (Event() ? Event()->Jet(j)  : 0); }
  Int_t Njets() const { return (Event() ? Event()->GetNumberOfJets() : 0); }

  Int_t Npieces(Int_t j) const { return (Jet(j) ? Jet(j)->GetNumberOfPieces() : 0); }
  Int_t Npieces(TPicoJet const *pJet) const { return (pJet ? pJet->GetNumberOfPieces() : 0); }

  TPicoPiece *Piece(Int_t i, Int_t j) const { return (Jet(j) ? Jet(j)->Piece(i) : 0); }
  TPicoPiece *Piece(Int_t i, TPicoJet const *pJet) const { return (pJet ? pJet->Piece(i) : 0); }

  Double_t WeightSum() const { return fWsum; }
  Double_t EventNorm() const { return fNorm; }
//=============================================================================

 private :

  AnalysisSelectorPicoJetEvent(const AnalysisSelectorPicoJetEvent &);
  AnalysisSelectorPicoJetEvent& operator=(const AnalysisSelectorPicoJetEvent &);
//=============================================================================

  void   MakeOutputsJet();
  Bool_t RunAnalysisJet();

  void   MakeOutputsDsj();
  Bool_t RunAnalysisDsj();

  void   MakeOutputsIAA();
  Bool_t RunAnalysisIAA();
//=============================================================================

  TTree *fChain;
  TPicoJetEvent *fEvent;

  TFile  *fFile;
  TStopwatch *fTimer;

  Double_t fWsum;
  Double_t fNorm;
//=============================================================================

  ClassDef(AnalysisSelectorPicoJetEvent,1);
};

#endif
