#ifndef TPICOSIMEVENT_H
#define TPICOSIMEVENT_H

#include <TObject.h>
#include <TClonesArray.h>
#include <TTree.h>
//=============================================================================

class TList;
class TFolder;
class TPicoParticle;
class TPicoHeader;
//=============================================================================

class TPicoSimEvent : public TObject {

 public :

  TPicoSimEvent();
  TPicoSimEvent(const TPicoSimEvent &src);
  TPicoSimEvent& operator=(const TPicoSimEvent &src);
  virtual ~TPicoSimEvent();
//=============================================================================

  TPicoHeader  *Header()           const { return fHeader; }
  TClonesArray *Particles()        const { return  fParticlesClArr; }
  Int_t GetNumberOfParticles()     const { return (fParticlesClArr ? fParticlesClArr->GetEntriesFast()      : 0); }
  TPicoParticle *Particle(Int_t i) const { return (fParticlesClArr ? (TPicoParticle*)fParticlesClArr->At(i) : 0); }
//=============================================================================

  Int_t AddParticle(const TPicoParticle &p);

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
  TClonesArray *fParticlesClArr;
//=============================================================================

  ClassDef(TPicoSimEvent, 1);
};

#endif
