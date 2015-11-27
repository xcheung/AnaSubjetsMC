#include <iostream>

#include <TROOT.h>
#include <TNamed.h>
#include <TString.h>
#include <TList.h>
#include <TFolder.h>

#include "TPicoVector.h"
#include "TPicoJet.h"
#include "TPicoHeader.h"
#include "TPicoJetEvent.h"

ClassImp(TPicoJetEvent)

//_____________________________________________________________________________
TPicoJetEvent::TPicoJetEvent() :
TObject(),
fListObjects(0),
fEventFolder(0),
fHeader(new TPicoHeader()),
fJetsClArr(new TClonesArray("TPicoJet",0))
{
//
// TPicoJetEvent::TPicoJetEvent
//

  CreatePicoStructure();
}

//_____________________________________________________________________________
TPicoJetEvent::TPicoJetEvent(const TPicoJetEvent &src) :
TObject(src),
fListObjects(0),
fEventFolder(0),
fHeader(new TPicoHeader(*src.fHeader)),
fJetsClArr(new TClonesArray(*src.fJetsClArr))
{
//
// TPicoJetEvent::TPicoJetEvent
//

  CreatePicoStructure();
}

//_____________________________________________________________________________
TPicoJetEvent& TPicoJetEvent::operator=(const TPicoJetEvent &src)
{
//
// TPicoJetEvent::operator=
//

  if (&src==this) return *this;

  TObject::operator=(src);

  fHeader    = new TPicoHeader(*src.fHeader);
  fJetsClArr = new TClonesArray(*src.fJetsClArr);

  CreatePicoStructure();
  return *this;
}

//_____________________________________________________________________________
TPicoJetEvent::~TPicoJetEvent()
{
//
// TPicoJetEvent::~TPicoJetEvent
//

  if (fListObjects) { delete fListObjects; fListObjects = 0; }
  if (fEventFolder) { delete fEventFolder; fEventFolder = 0; }
}

//_____________________________________________________________________________
Int_t TPicoJetEvent::AddJet(const TPicoJet *pJet)
{
//
//  TPicoJetEvent::AddJet
//

  if (!pJet) return -1;
  new ((*fJetsClArr)[fJetsClArr->GetEntriesFast()]) TPicoJet(*pJet);
  return fJetsClArr->GetEntriesFast()-1;
}

//_____________________________________________________________________________
void TPicoJetEvent::ReadFromTree(TTree *tree)
{
//
//  TPicoJetEvent::ReadFromTree
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

  fHeader = (TPicoHeader*)fListObjects->FindObject("PicoJetHeader");
  fJetsClArr = (TClonesArray*)fListObjects->FindObject("PicoJets");
//=============================================================================

  fListObjects->SetOwner(kTRUE);
//=============================================================================

  return;
}

//_____________________________________________________________________________
void TPicoJetEvent::Reset()
{
  fHeader->Reset();
  if (fJetsClArr->GetEntriesFast()>0) fJetsClArr->Delete();

  return;
}

//_____________________________________________________________________________
void TPicoJetEvent::CreatePicoStructure()
{
//
//  TPicoJetEvent::CreatePicoStructure
//

  fHeader->SetName("PicoJetHeader");
  fJetsClArr->SetName("PicoJets");
//=============================================================================

  if (fListObjects) { delete fListObjects; fListObjects = 0; }
  fListObjects = new TList();
  fListObjects->AddLast(fHeader);
  fListObjects->AddLast(fJetsClArr);
//=============================================================================

  if (fEventFolder) { delete fEventFolder; fEventFolder = 0; }
  fEventFolder = gROOT->GetRootFolder()->AddFolder("PicoJetEvent", "PicoJetEvent");
  fEventFolder->AddFolder("PicoJetHeader", "PicoJetHeader", 0);
  fEventFolder->AddFolder("PicoJets",      "PicoJets", (TCollection*)fJetsClArr);
//=============================================================================

  return;
}
