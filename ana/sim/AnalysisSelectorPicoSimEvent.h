//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Oct 25 01:50:28 2015 by ROOT version 5.34/32
// from TChain treePico/
//////////////////////////////////////////////////////////

#ifndef ANALYSISSELECTORPICOSIMEVENT_H
#define ANALYSISSELECTORPICOSIMEVENT_H

#include <TSelector.h>
//=============================================================================

class TFile;
class TTree;
class TClonesArray;

class TPicoVector;
class TPicoParticle;
class TPicoHeader;
class TPicoSimEvenet;
//=============================================================================

class AnalysisSelectorPicoSimEvent : public TSelector {
 public :

  AnalysisSelectorPicoSimEvent(TTree *tree=0);
  virtual ~AnalysisSelectorPicoSimEvent();
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

  TPicoSimEvent *Event()     const { return fEvent; }
  TPicoHeader   *Header()    const { return  Event()->Header();    }
  TClonesArray  *Particles() const { return  Event()->Particles(); }

  Int_t N() const { return Event()->GetNumberOfParticles(); }
  TPicoParticle *Particle(Int_t i) const { return Event()->Particle(i); }

  TPicoVector *Leading() const { return Header()->Leading(); }

//=============================================================================

 private :

  AnalysisSelectorPicoSimEvent(const AnalysisSelectorPicoSimEvent &);
  AnalysisSelectorPicoSimEvent& operator=(const AnalysisSelectorPicoSimEvent &);
//=============================================================================

  Double_t WeightSum() const { return fWsum; }
  Double_t EventNorm() const { return fNorm; }
//=============================================================================

  TTree *fChain;
  TPicoSimEvent *fEvent;

  TFile *fFile;

  Double_t fWsum;
  Double_t fNorm;
//=============================================================================

  ClassDef(AnalysisSelectorPicoSimEvent,0);
};

#endif
