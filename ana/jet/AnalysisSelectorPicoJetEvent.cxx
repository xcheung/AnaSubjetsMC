#define AnalysisSelectorPicoJetEvent_cxx

// The class definition in AnalysisSelectorPicoJetEvent.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("AnalysisSelectorPicoJetEvent.C")
// Root > T->Process("AnalysisSelectorPicoJetEvent.C","some options")
// Root > T->Process("AnalysisSelectorPicoJetEvent.C+")
//

#include <iostream>

#include <TSystem.h>
#include <TStopwatch.h>
#include <TString.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TMath.h>
#include <TVector3.h>

#include "TPicoVector.h"
#include "TPicoPiece.h"

#include "AnalysisSelectorPicoJetEvent.h"
//=============================================================================

//_____________________________________________________________________________
AnalysisSelectorPicoJetEvent::AnalysisSelectorPicoJetEvent(TTree */*tree*/) :
fChain(0),
fEvent(0),
fFile(0),
fTimer(new TStopwatch()),
fWsum(-1.),
fNorm(-1.)
{
//
//  AnalysisSelectorPicoJetEvent::AnalysisSelectorPicoJetEvent
//

  new TSystem();
}

//_____________________________________________________________________________
AnalysisSelectorPicoJetEvent::~AnalysisSelectorPicoJetEvent()
{
//
//  AnalysisSelectorPicoJetEvent::~AnalysisSelectorPicoJetEvent
//

  if (fChain) { delete fChain; fChain = 0; }
  if (fEvent) { delete fEvent; fEvent = 0; }

  if (fFile)  { delete fFile;  fFile  = 0; }

  if (fTimer)  { delete fTimer;  fTimer  = 0; }
  if (gSystem) { delete gSystem; gSystem = 0; }
}

//_____________________________________________________________________________
void AnalysisSelectorPicoJetEvent::Init(TTree *tree)
{
// The Init() function is called when the selector needs to initialize
// a new tree or chain. Typically here the branch addresses and branch
// pointers of the tree will be set.
// It is normally not necessary to make changes to the generated
// code, but the routine can be extended by the user if needed.
// Init() will be called many times when running on PROOF
// (once per file to be processed).

  if (!tree) return;

  fChain = tree;
  fChain->GetEntries();
//fChain->SetMakeClass(1);
  if (fEvent) { delete fEvent; fEvent = 0;}
//=============================================================================

  fEvent = new TPicoJetEvent();
  fEvent->ReadFromTree(fChain);
//=============================================================================

  return;
}

//_____________________________________________________________________________
Bool_t AnalysisSelectorPicoJetEvent::Notify()
{
// The Notify() function is called when a new file is opened. This
// can be either for a new TTree in a TChain or when when a new TTree
// is started when using PROOF. It is normally not necessary to make changes
// to the generated code, but the routine can be extended by the
// user if needed. The return value is currently not used.

  TString sAna = fChain->GetCurrentFile()->GetName();
  cout << sAna.Data() << endl;

  TString sDir = gSystem->DirName(sAna.Data());
  TString sTop = gSystem->DirName(sDir.Data());
  sAna.ReplaceAll(Form("%s/out_",sDir.Data()), "wgt_");
  TString sWgt = Form("%s/wgt/%s",sTop.Data(),sAna.Data());
  cout << sWgt.Data() << endl;
//=============================================================================

  fWsum = -1.;
  TString sOpt = GetOption();
  TFile *file = TFile::Open(sWgt.Data(), "READ");
  if (sOpt.Contains("wgt")) {
    fWsum = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
  } else {
    Double_t dSumw = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
    Double_t dXsec = ((TProfile*)file->Get("hSigmaGen"))->GetBinContent(1);
    fWsum =  dSumw / dXsec;
  } file->Close();
//=============================================================================

  cout << "Weight sum = " << fWsum << " :: ";
  fTimer->Print(); fTimer->Start(kFALSE);

  if (fWsum<0.) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
void AnalysisSelectorPicoJetEvent::Begin(TTree * /*tree*/)
{
// The Begin() function is called at the start of the query.
// When running with PROOF Begin() is only called on the client.
// The tree argument is deprecated (on PROOF 0 is passed).

  fTimer->Start();
  TString sOpt = GetOption();
  fFile = TFile::Open("AnalysisOutputs.root", "NEW");
//=============================================================================

  if (sOpt.Contains("all") || sOpt.Contains("jet")) MakeOutputsJet();
  if (sOpt.Contains("all") || sOpt.Contains("Dsj")) MakeOutputsDsj();
  if (sOpt.Contains("all") || sOpt.Contains("IAA")) MakeOutputsIAA();
//=============================================================================

  return;
}

//_____________________________________________________________________________
void AnalysisSelectorPicoJetEvent::SlaveBegin(TTree * /*tree*/)
{
// The SlaveBegin() function is called after the Begin() function.
// When running with PROOF SlaveBegin() is called on each slave server.
// The tree argument is deprecated (on PROOF 0 is passed).

//TString sOpt = GetOption();

  return;
}

//_____________________________________________________________________________
Bool_t AnalysisSelectorPicoJetEvent::Process(Long64_t entry)
{
// The Process() function is called for each entry in the tree (or possibly
// keyed object in the case of PROOF) to be processed. The entry argument
// specifies which entry in the currently loaded tree is to be processed.
// It can be passed to either AnalysisSelectorPicoJetEvent::GetEntry() or TBranch::GetEntry()
// to read either all or the required parts of the data. When processing
// keyed objects with PROOF, the object is already loaded and is available
// via the fObject pointer.
//
// This function should contain the "body" of the analysis. It can contain
// simple or elaborate selection criteria, run algorithms on the data
// of the event and typically fill histograms.
//
// The processing can be stopped by calling Abort().
//
// Use fStatus to set the return value of TTree::Process().
//
// The return value is currently not used.

  if (CheckEvent(entry)) return kFALSE;
//=============================================================================

  TString sOpt = GetOption();
  if (sOpt.Contains("all") || sOpt.Contains("jet")) if (RunAnalysisJet()) return kFALSE;
  if (sOpt.Contains("all") || sOpt.Contains("Dsj")) if (RunAnalysisDsj()) return kFALSE;
  if (sOpt.Contains("all") || sOpt.Contains("IAA")) if (RunAnalysisIAA()) return kFALSE;
//=============================================================================

  ResetEvent();
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
void AnalysisSelectorPicoJetEvent::SlaveTerminate()
{
// The SlaveTerminate() function is called after all entries or objects
// have been processed. When running with PROOF SlaveTerminate() is called
// on each slave server.

  return;
}

//_____________________________________________________________________________
void AnalysisSelectorPicoJetEvent::Terminate()
{
// The Terminate() function is the last function to be called during
// a query. It always runs on the client, it can be used to present
// the results graphically or save the results to file.

  fFile->cd();
  fOutput->Print();
  fOutput->Write();
  fFile->Close();
//=============================================================================

  fTimer->Stop();
  fTimer->Print();
//=============================================================================

  return;
}

//_____________________________________________________________________________
Bool_t AnalysisSelectorPicoJetEvent::CheckEvent(Long64_t entry)
{
//
//  AnalysisSelectorPicoJetEvent::CheckEvent
//

  if (GetEntry(entry)<=0) return kTRUE;
//=============================================================================

  if (!Event())  return kTRUE;
  if (!Header()) return kTRUE;
//=============================================================================

  if (!Jets())    return kTRUE;
  if (Njets()<=0) return kTRUE;
//=============================================================================

  fNorm = 1. / WeightSum();
  TString sOpt = GetOption();
  if (sOpt.Contains("wgt")) fNorm *= Header()->Wevent();
  if (fNorm<0.) { cout << "Normalization factor = " << fNorm << " invalidated!!!" << endl; return kTRUE; }
//=============================================================================

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AnalysisSelectorPicoJetEvent::RunAnalysisJet()
{
//
//  AnalysisSelectorPicoJetEvent::RunAnalysisJet
//

  const Double_t dNorm = EventNorm(); if (dNorm<=0.) return kTRUE;
//=============================================================================

  TH2D *hJetPtEta = dynamic_cast<TH2D*>(fOutput->FindObject("hJetPtEta")); if (!hJetPtEta) return kTRUE;
  TH2D *hJetPtPhi = dynamic_cast<TH2D*>(fOutput->FindObject("hJetPtPhi")); if (!hJetPtPhi) return kTRUE;

  TH2D *hLjePtEta = dynamic_cast<TH2D*>(fOutput->FindObject("hLjePtEta")); if (!hLjePtEta) return kTRUE;
  TH2D *hLjePtPhi = dynamic_cast<TH2D*>(fOutput->FindObject("hLjePtPhi")); if (!hLjePtPhi) return kTRUE;

  TH2D *hNjePtEta = dynamic_cast<TH2D*>(fOutput->FindObject("hNjePtEta")); if (!hNjePtEta) return kTRUE;
  TH2D *hNjePtPhi = dynamic_cast<TH2D*>(fOutput->FindObject("hNjePtPhi")); if (!hNjePtPhi) return kTRUE;
//=============================================================================

  for (Int_t j=0; j<Njets(); j++) {
    TPicoJet *pJet = Jet(j); if (!pJet) continue;

    Double_t dJetPt  = pJet->Pt();
    Double_t dJetEta = pJet->Eta();
    Double_t dJetPhi = pJet->Phi();
    Double_t dCosPhi = TMath::Cos(dJetPhi);
    if (dCosPhi>=1.) dCosPhi = 1. - 1e-6;

    hJetPtEta->Fill(dJetPt,dJetEta,dNorm); hJetPtPhi->Fill(dJetPt,dCosPhi,dNorm);
    if (j==0) { hLjePtEta->Fill(dJetPt,dJetEta,dNorm); hLjePtPhi->Fill(dJetPt,dCosPhi,dNorm); }
    if (j==1) { hNjePtEta->Fill(dJetPt,dJetEta,dNorm); hNjePtPhi->Fill(dJetPt,dCosPhi,dNorm); }

    pJet = 0;
  }

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AnalysisSelectorPicoJetEvent::RunAnalysisDsj()
{
//
//  AnalysisSelectorPicoJetEvent::RunAnalysisDsj
//

  const Double_t dNorm = EventNorm(); if (dNorm<=0.) return kTRUE;
//=============================================================================

  TH2D *hJetNsj = dynamic_cast<TH2D*>(fOutput->FindObject("hJetNsj")); if (!hJetNsj) return kTRUE;

  TH2D *hJetIsj = dynamic_cast<TH2D*>(fOutput->FindObject("hJetIsj")); if (!hJetIsj) return kTRUE;
  TH2D *hJet1sj = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1sj")); if (!hJet1sj) return kTRUE;
  TH2D *hJet2sj = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2sj")); if (!hJet2sj) return kTRUE;
  TH2D *hJetDsj = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDsj")); if (!hJetDsj) return kTRUE;

  TH2D *hJetIsz = dynamic_cast<TH2D*>(fOutput->FindObject("hJetIsz")); if (!hJetIsz) return kTRUE;
  TH2D *hJet1sz = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1sz")); if (!hJet1sz) return kTRUE;
  TH2D *hJet2sz = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2sz")); if (!hJet2sz) return kTRUE;
  TH2D *hJetDsz = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDsz")); if (!hJetDsz) return kTRUE;
//=============================================================================

  for (Int_t j=0; j<Njets(); j++) {
    TPicoJet *pJet = Jet(j);  if (!pJet) continue;
    Int_t np = Npieces(pJet); if (np<=0) continue;

    Double_t dJet = pJet->Pt(); hJetNsj->Fill(dJet,np,dNorm);
//=============================================================================

    Double_t d1sj = -1.;
    Double_t d2sj = -1.;
    for (Int_t i=0; i<np; i++) {
      TPicoPiece *piece = Piece(i,pJet); if (!piece) continue;

      Double_t dIsj = piece->Pt();
      Double_t dIsz = dIsj / dJet;
      if (dIsz>=1.) dIsz = 1. - 1e-6;

      hJetIsj->Fill(dJet,dIsj,dNorm); hJetIsz->Fill(dJet,dIsz,dNorm);
      if (i==0) { hJet1sj->Fill(dJet,dIsj,dNorm); hJet1sz->Fill(dJet,dIsz,dNorm); d1sj = dIsj; }
      if (i==1) { hJet2sj->Fill(dJet,dIsj,dNorm); hJet2sz->Fill(dJet,dIsz,dNorm); d2sj = dIsj; }

      piece = 0;
    }
//=============================================================================

    if ((d1sj<0.) || (d2sj<0.)) { pJet = 0; continue; }
//=============================================================================

    Double_t dsj = d1sj - d2sj;
    Double_t dsz = dsj  / dJet;
    if (dsz>=1.) dsz = 1. - 1e-6;

    hJetDsj->Fill(dJet, dsj, dNorm);
    hJetDsz->Fill(dJet, dsz, dNorm);
//=============================================================================

    pJet = 0;
  }
//=============================================================================

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AnalysisSelectorPicoJetEvent::RunAnalysisIAA()
{
//
//  AnalysisSelectorPicoJetEvent::RunAnalysisIAA
//

  const Double_t dNorm = EventNorm(); if (dNorm<=0.) return kTRUE;
//=============================================================================

  TH1D *hTrgPt = dynamic_cast<TH1D*>(fOutput->FindObject("hTrgPt")); if (!hTrgPt) return kTRUE;

  TH2D *hR060Dsz = dynamic_cast<TH2D*>(fOutput->FindObject("hR060Dsz")); if (!hR060Dsz) return kTRUE;
  TH2D *hR100Dsz = dynamic_cast<TH2D*>(fOutput->FindObject("hR100Dsz")); if (!hR100Dsz) return kTRUE;
  TH2D *hR150Dsz = dynamic_cast<TH2D*>(fOutput->FindObject("hR150Dsz")); if (!hR150Dsz) return kTRUE;

  TH2D *hR060Phi = dynamic_cast<TH2D*>(fOutput->FindObject("hR060Phi")); if (!hR060Phi) return kTRUE;
  TH2D *hR100Phi = dynamic_cast<TH2D*>(fOutput->FindObject("hR100Phi")); if (!hR100Phi) return kTRUE;
  TH2D *hR150Phi = dynamic_cast<TH2D*>(fOutput->FindObject("hR150Phi")); if (!hR150Phi) return kTRUE;

  TH2D *hR060Phl = dynamic_cast<TH2D*>(fOutput->FindObject("hR060Phl")); if (!hR060Phl) return kTRUE;
  TH2D *hR100Phl = dynamic_cast<TH2D*>(fOutput->FindObject("hR100Phl")); if (!hR100Phl) return kTRUE;
  TH2D *hR150Phl = dynamic_cast<TH2D*>(fOutput->FindObject("hR150Phl")); if (!hR150Phl) return kTRUE;

  TH2D *hR060Phh = dynamic_cast<TH2D*>(fOutput->FindObject("hR060Phh")); if (!hR060Phh) return kTRUE;
  TH2D *hR100Phh = dynamic_cast<TH2D*>(fOutput->FindObject("hR100Phh")); if (!hR100Phh) return kTRUE;
  TH2D *hR150Phh = dynamic_cast<TH2D*>(fOutput->FindObject("hR150Phh")); if (!hR150Phh) return kTRUE;
//=============================================================================

  const Double_t dThr = -0.5 * TMath::Pi();
  const Double_t dCut = TMath::TwoPi() / 3.;
//=============================================================================

  TVector3 vJet, vTrg;
  for (Int_t t=0; t<Njets(); t++) {
    TPicoJet *pTrg = Jet(t); if (!pTrg) continue;
    Double_t  dTrg = pTrg->Pt(); hTrgPt->Fill(dTrg, dNorm);

    if (dTrg<60.) { pTrg = 0; continue; }
    vTrg.SetPtEtaPhi(dTrg, pTrg->Eta(), pTrg->Phi());
//=============================================================================

    for (Int_t j=0; j<Njets(); j++) if (j!=t) {
      TPicoJet *pJet = Jet(j);  if (!pJet) continue;
      Int_t np = Npieces(pJet); if (np<2) { pJet = 0; continue; }

      Double_t d1sj = -1.;
      Double_t d2sj = -1.;
      for (Int_t i=0; i<2; i++) {
        TPicoPiece *piece = Piece(i,pJet); if (!piece) continue;
        if (i==0) d1sj = piece->Pt();
        if (i==1) d2sj = piece->Pt();
        piece = 0;
      }

      if ((d1sj<0.) || (d2sj<0.)) { pJet = 0; continue; }
//=============================================================================

      Double_t dJet = pJet->Pt();
      vJet.SetPtEtaPhi(dJet, pJet->Eta(), pJet->Phi());
      Double_t dsz = (d1sj - d2sj) / dJet; if (dsz>=1.) dsz = 1. - 1e-6;

      Double_t dPhi = vJet.DeltaPhi(vTrg);
      Double_t dVar = ((dPhi<dThr) ? (dPhi + TMath::TwoPi()) : dPhi);
//=============================================================================

      Bool_t bPhl = (dsz<0.2);
      Bool_t bPhh = (dsz>0.8);
      Bool_t bPhd = (TMath::Abs(dPhi)>dCut);

      if (dTrg>60.) {
        hR060Phi->Fill(dJet, dVar, dNorm);
        if (bPhl) hR060Phl->Fill(dJet, dVar, dNorm);
        if (bPhh) hR060Phh->Fill(dJet, dVar, dNorm);
        if (bPhd) hR060Dsz->Fill(dJet, dsz,  dNorm);
      }

      if (dTrg>100.) {
        hR100Phi->Fill(dJet, dVar, dNorm);
        if (bPhl) hR100Phl->Fill(dJet, dVar, dNorm);
        if (bPhh) hR100Phh->Fill(dJet, dVar, dNorm);
        if (bPhd) hR100Dsz->Fill(dJet, dsz,  dNorm);
      }

      if (dTrg>150.) {
        hR150Phi->Fill(dJet, dVar, dNorm);
        if (bPhl) hR150Phl->Fill(dJet, dVar, dNorm);
        if (bPhh) hR150Phh->Fill(dJet, dVar, dNorm);
        if (bPhd) hR150Dsz->Fill(dJet, dsz,  dNorm);
      }

      pJet = 0;
    }
//=============================================================================

    pTrg = 0;
  }
//=============================================================================

  return kFALSE;
}

//_____________________________________________________________________________
void AnalysisSelectorPicoJetEvent::MakeOutputsJet()
{
//
//  AnalysisSelectorPicoJetEvent::MakeOutputsJet
//

  TH2D *hJetPtEta = new TH2D("hJetPtEta", "", 1000, 0., 1000., 60, -3., 3.); hJetPtEta->Sumw2(); fOutput->Add(hJetPtEta);
  TH2D *hJetPtPhi = new TH2D("hJetPtPhi", "", 1000, 0., 1000., 20, -1., 1.); hJetPtPhi->Sumw2(); fOutput->Add(hJetPtPhi);

  TH2D *hLjePtEta = new TH2D("hLjePtEta", "", 1000, 0., 1000., 60, -3., 3.); hLjePtEta->Sumw2(); fOutput->Add(hLjePtEta);
  TH2D *hLjePtPhi = new TH2D("hLjePtPhi", "", 1000, 0., 1000., 20, -1., 1.); hLjePtPhi->Sumw2(); fOutput->Add(hLjePtPhi);

  TH2D *hNjePtEta = new TH2D("hNjePtEta", "", 1000, 0., 1000., 60, -3., 3.); hNjePtEta->Sumw2(); fOutput->Add(hNjePtEta);
  TH2D *hNjePtPhi = new TH2D("hNjePtPhi", "", 1000, 0., 1000., 20, -1., 1.); hNjePtPhi->Sumw2(); fOutput->Add(hNjePtPhi);

  return;
}

//_____________________________________________________________________________
void AnalysisSelectorPicoJetEvent::MakeOutputsDsj()
{
//
//  AnalysisSelectorPicoJetEvent::MakeOutputsDsj
//

  TH2D *hJetNsj = new TH2D("hJetNsj", "", 1000, 0., 1000., 100, -0.5, 99.5); hJetNsj->Sumw2(); fOutput->Add(hJetNsj);

  TH2D *hJetIsj = new TH2D("hJetIsj", "", 1000, 0., 1000., 1000, 0., 1000.); hJetIsj->Sumw2(); fOutput->Add(hJetIsj);
  TH2D *hJet1sj = new TH2D("hJet1sj", "", 1000, 0., 1000., 1000, 0., 1000.); hJet1sj->Sumw2(); fOutput->Add(hJet1sj);
  TH2D *hJet2sj = new TH2D("hJet2sj", "", 1000, 0., 1000., 1000, 0., 1000.); hJet2sj->Sumw2(); fOutput->Add(hJet2sj);
  TH2D *hJetDsj = new TH2D("hJetDsj", "", 1000, 0., 1000., 1000, 0., 1000.); hJetDsj->Sumw2(); fOutput->Add(hJetDsj);

  TH2D *hJetIsz = new TH2D("hJetIsz", "", 1000, 0., 1000., 100, 0., 1.); hJetIsz->Sumw2(); fOutput->Add(hJetIsz);
  TH2D *hJet1sz = new TH2D("hJet1sz", "", 1000, 0., 1000., 100, 0., 1.); hJet1sz->Sumw2(); fOutput->Add(hJet1sz);
  TH2D *hJet2sz = new TH2D("hJet2sz", "", 1000, 0., 1000., 100, 0., 1.); hJet2sz->Sumw2(); fOutput->Add(hJet2sz);
  TH2D *hJetDsz = new TH2D("hJetDsz", "", 1000, 0., 1000., 100, 0., 1.); hJetDsz->Sumw2(); fOutput->Add(hJetDsz);

  return;
}

//_____________________________________________________________________________
void AnalysisSelectorPicoJetEvent::MakeOutputsIAA()
{
//
//  AnalysisSelectorPicoJetEvent::MakeOutputsIAA
//

  const Double_t dPhiMin = -0.5 * TMath::Pi();
  const Double_t dPhiMax =  1.5 * TMath::Pi();

  TH1D *hTrgPt = new TH1D("hTrgPt", "", 1000, 0., 1000.); hTrgPt->Sumw2(); fOutput->Add(hTrgPt);

  TH2D *hR060Phi = new TH2D("hR060Phi", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR060Phi->Sumw2(); fOutput->Add(hR060Phi);
  TH2D *hR100Phi = new TH2D("hR100Phi", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR100Phi->Sumw2(); fOutput->Add(hR100Phi);
  TH2D *hR150Phi = new TH2D("hR150Phi", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR150Phi->Sumw2(); fOutput->Add(hR150Phi);

  TH2D *hR060Phl = new TH2D("hR060Phl", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR060Phl->Sumw2(); fOutput->Add(hR060Phl);
  TH2D *hR100Phl = new TH2D("hR100Phl", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR100Phl->Sumw2(); fOutput->Add(hR100Phl);
  TH2D *hR150Phl = new TH2D("hR150Phl", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR150Phl->Sumw2(); fOutput->Add(hR150Phl);

  TH2D *hR060Phh = new TH2D("hR060Phh", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR060Phh->Sumw2(); fOutput->Add(hR060Phh);
  TH2D *hR100Phh = new TH2D("hR100Phh", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR100Phh->Sumw2(); fOutput->Add(hR100Phh);
  TH2D *hR150Phh = new TH2D("hR150Phh", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR150Phh->Sumw2(); fOutput->Add(hR150Phh);

  TH2D *hR060Dsz = new TH2D("hR060Dsz", "", 1000, 0., 1000., 100, 0., 1.); hR060Dsz->Sumw2(); fOutput->Add(hR060Dsz);
  TH2D *hR100Dsz = new TH2D("hR100Dsz", "", 1000, 0., 1000., 100, 0., 1.); hR100Dsz->Sumw2(); fOutput->Add(hR100Dsz);
  TH2D *hR150Dsz = new TH2D("hR150Dsz", "", 1000, 0., 1000., 100, 0., 1.); hR150Dsz->Sumw2(); fOutput->Add(hR150Dsz);

  return;
}
