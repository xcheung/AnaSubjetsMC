#ifndef TPICOJETEVENT_H
#define TPICOJETEVENT_H

#include <TObject.h>
#include <TClonesArray.h>
#include <TTree.h>
//=============================================================================

class TList;
class TFolder;
class TPicoJet;
class TPicoHeader;
//=============================================================================

class TPicoJetEvent : public TObject {

 public :

  TPicoJetEvent();
  TPicoJetEvent(const TPicoJetEvent &src);
  TPicoJetEvent& operator=(const TPicoJetEvent &src);
  virtual ~TPicoJetEvent();
//=============================================================================

  TPicoHeader  *Header()  const { return fHeader; }
  TClonesArray *Jets()    const { return  fJetsClArr; }
  Int_t GetNumberOfJets() const { return (fJetsClArr ? fJetsClArr->GetEntriesFast() : 0); }
  TPicoJet *Jet(Int_t j)  const { return (fJetsClArr ? (TPicoJet*)fJetsClArr->At(j) : 0); }
//=============================================================================

  Int_t AddJet(const TPicoJet *pJet);

  void ReadFromTree(TTree *tree);
  void Write2Tree(TTree *tree) const { tree->Branch(fListObjects); }

  void Reset();
//=============================================================================

 private :

  void CreatePicoStructure();
//=============================================================================

  TList   *fListObjects;
  TFolder *fEventFolder;

  TPicoHeader  *fHeader;
  TClonesArray *fJetsClArr;
//=============================================================================

  ClassDef(TPicoJetEvent, 1);
};

#endif
