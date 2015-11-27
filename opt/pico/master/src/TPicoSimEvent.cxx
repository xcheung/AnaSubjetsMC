#include <iostream>

#include <TROOT.h>
#include <TNamed.h>
#include <TString.h>
#include <TList.h>
#include <TFolder.h>

#include "TPicoParticle.h"
#include "TPicoHeader.h"
#include "TPicoSimEvent.h"

ClassImp(TPicoSimEvent)

//_____________________________________________________________________________
TPicoSimEvent::TPicoSimEvent() :
TObject(),
fListObjects(0),
fEventFolder(0),
fHeader(new TPicoHeader()),
fParticlesClArr(new TClonesArray("TPicoParticle",0))
{
//
// TPicoSimEvent::TPicoSimEvent
//

  CreatePicoStructure();
}

//_____________________________________________________________________________
TPicoSimEvent::TPicoSimEvent(const TPicoSimEvent &src) :
TObject(src),
fListObjects(0),
fEventFolder(0),
fHeader(new TPicoHeader(*src.fHeader)),
fParticlesClArr(new TClonesArray(*src.fParticlesClArr))
{
//
// TPicoSimEvent::TPicoSimEvent
//

  CreatePicoStructure();
}

//_____________________________________________________________________________
TPicoSimEvent& TPicoSimEvent::operator=(const TPicoSimEvent &src)
{
//
// TPicoSimEvent::operator=
//

  if (&src==this) return *this;

  TObject::operator=(src);

  fHeader         = new TPicoHeader(*src.fHeader);
  fParticlesClArr = new TClonesArray(*src.fParticlesClArr);

  CreatePicoStructure();
  return *this;
}

//_____________________________________________________________________________
TPicoSimEvent::~TPicoSimEvent()
{
//
// TPicoSimEvent::~TPicoSimEvent
//

  if (fListObjects) { delete fListObjects; fListObjects = 0; }
  if (fEventFolder) { delete fEventFolder; fEventFolder = 0; }
}

//_____________________________________________________________________________
Int_t TPicoSimEvent::AddParticle(const TPicoParticle &p)
{
//
//  TPicoSimEvent::AddJet
//

  new ((*fParticlesClArr)[fParticlesClArr->GetEntriesFast()]) TPicoParticle(p);
  return fParticlesClArr->GetEntriesFast()-1;
}

//_____________________________________________________________________________
void TPicoSimEvent::ReadFromTree(TTree *tree)
{
//
//  TPicoSimEvent::ReadFromTree
//

  if (!tree->GetTree()) tree->LoadTree(0);
//=============================================================================

  TNamed *pNamed = 0;
  TIter next(fListObjects);
  while ((pNamed=(TNamed*)next())) {
    TString sbName = pNamed->GetName();
    TBranch *br = tree->GetTree()->GetBranch(sbName.Data());
    if (!br) br = tree->GetBranch(sbName.Data());
    if (!br) std::cout << "Can not load branch: " << sbName.Data() << std::endl;

    tree->SetBranchAddress(sbName.Data(), fListObjects->GetObjectRef(pNamed));
  }

  fHeader = (TPicoHeader*)fListObjects->FindObject("PicoSimHeader");
  fParticlesClArr = (TClonesArray*)fListObjects->FindObject("PicoParticles");
//=============================================================================

  fListObjects->SetOwner(kTRUE);
//=============================================================================

  return;
}

//_____________________________________________________________________________
void TPicoSimEvent::Reset()
{
  fHeader->Reset();
  if (fParticlesClArr->GetEntriesFast()>0) fParticlesClArr->Delete();

  return;
}

//_____________________________________________________________________________
void TPicoSimEvent::CreatePicoStructure()
{
//
//  TPicoSimEvent::CreatePicoStructure
//

  fHeader->SetName("PicoSimHeader");
  fParticlesClArr->SetName("PicoParticles");
//=============================================================================

  if (fListObjects) { delete fListObjects; fListObjects = 0; }
  fListObjects = new TList();
  fListObjects->AddLast(fHeader);
  fListObjects->AddLast(fParticlesClArr);
//=============================================================================

  if (fEventFolder) { delete fEventFolder; fEventFolder = 0; }
  fEventFolder = gROOT->GetRootFolder()->AddFolder("PicoSimEvent", "PicoSimEvent");
  fEventFolder->AddFolder("PicoSimHeader", "PicoSimHeader", 0);
  fEventFolder->AddFolder("PicoParticles", "PicoParticles", (TCollection*)fParticlesClArr);
//=============================================================================

  return;
}
