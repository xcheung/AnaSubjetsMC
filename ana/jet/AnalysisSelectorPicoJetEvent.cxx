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

  TPicoVector *pTrg = Leading(); if (!pTrg) return kTRUE;
  Double_t dEta = pTrg->Eta(); if (TMath::Abs(dEta)>2.6) return kFALSE;

  TH1D *hLtkPt = dynamic_cast<TH1D*>(fOutput->FindObject("hLtkPt")); if (!hLtkPt) return kTRUE;
  Double_t dTrg = pTrg->Pt(); hLtkPt->Fill(dTrg,dNorm); if (dTrg<10.) return kFALSE;
//=============================================================================

  TH2D *hR10Dsz = dynamic_cast<TH2D*>(fOutput->FindObject("hR10Dsz")); if (!hR10Dsz) return kTRUE;
  TH2D *hR15Dsz = dynamic_cast<TH2D*>(fOutput->FindObject("hR15Dsz")); if (!hR15Dsz) return kTRUE;
  TH2D *hR20Dsz = dynamic_cast<TH2D*>(fOutput->FindObject("hR20Dsz")); if (!hR20Dsz) return kTRUE;
  TH2D *hR30Dsz = dynamic_cast<TH2D*>(fOutput->FindObject("hR30Dsz")); if (!hR30Dsz) return kTRUE;

  TH2D *hR10Phi = dynamic_cast<TH2D*>(fOutput->FindObject("hR10Phi")); if (!hR10Phi) return kTRUE;
  TH2D *hR15Phi = dynamic_cast<TH2D*>(fOutput->FindObject("hR15Phi")); if (!hR15Phi) return kTRUE;
  TH2D *hR20Phi = dynamic_cast<TH2D*>(fOutput->FindObject("hR20Phi")); if (!hR20Phi) return kTRUE;
  TH2D *hR30Phi = dynamic_cast<TH2D*>(fOutput->FindObject("hR30Phi")); if (!hR30Phi) return kTRUE;

  TH2D *hR10Phl = dynamic_cast<TH2D*>(fOutput->FindObject("hR10Phl")); if (!hR10Phl) return kTRUE;
  TH2D *hR15Phl = dynamic_cast<TH2D*>(fOutput->FindObject("hR15Phl")); if (!hR15Phl) return kTRUE;
  TH2D *hR20Phl = dynamic_cast<TH2D*>(fOutput->FindObject("hR20Phl")); if (!hR20Phl) return kTRUE;
  TH2D *hR30Phl = dynamic_cast<TH2D*>(fOutput->FindObject("hR30Phl")); if (!hR30Phl) return kTRUE;

  TH2D *hR10Phh = dynamic_cast<TH2D*>(fOutput->FindObject("hR10Phh")); if (!hR10Phh) return kTRUE;
  TH2D *hR15Phh = dynamic_cast<TH2D*>(fOutput->FindObject("hR15Phh")); if (!hR15Phh) return kTRUE;
  TH2D *hR20Phh = dynamic_cast<TH2D*>(fOutput->FindObject("hR20Phh")); if (!hR20Phh) return kTRUE;
  TH2D *hR30Phh = dynamic_cast<TH2D*>(fOutput->FindObject("hR30Phh")); if (!hR30Phh) return kTRUE;
//=============================================================================

  const Double_t dThr = -0.5 * TMath::Pi();
  const Double_t dCut = TMath::TwoPi() / 3.;
  TVector3 vJet, vTrg; vTrg.SetPtEtaPhi(dTrg, dEta, pTrg->Phi());
//=============================================================================

  for (Int_t j=0; j<Njets(); j++) {
    TPicoJet *pJet = Jet(j); if (!pJet) continue;
    Int_t np = Npieces(pJet); if (np<2) { pJet = 0; continue; }
//=============================================================================

    Double_t d1sj = -1.;
    Double_t d2sj = -1.;
    for (Int_t i=0; i<2; i++) {
      TPicoPiece *piece = Piece(i,pJet); if (!piece) continue;

      if (i==0) d1sj = piece->Pt();
      if (i==1) d2sj = piece->Pt();

      piece = 0;
    }
//=============================================================================

    if ((d1sj<0.) || (d2sj<0.)) { pJet = 0; continue; }
//=============================================================================

    Double_t dJet = pJet->Pt();
    Double_t dsz = (d1sj - d2sj) / dJet; if (dsz>=1.) dsz = 1. - 1e-6;
//=============================================================================

    vJet.SetPtEtaPhi(dJet, pJet->Eta(), pJet->Phi());

    Double_t dPhi = vTrg.DeltaPhi(vJet);
    Double_t dVar = ((dPhi<dThr) ? (dPhi + TMath::TwoPi()) : dPhi);
//=============================================================================

    Bool_t bPhl = (dsz<0.2);
    Bool_t bPhh = (dsz>0.8);
    Bool_t bPhd = (TMath::Abs(dPhi)>dCut);

    if (dTrg>10.) {
      hR10Phi->Fill(dJet, dVar, dNorm);
      if (bPhl) hR10Phl->Fill(dJet, dVar, dNorm);
      if (bPhh) hR10Phh->Fill(dJet, dVar, dNorm);
      if (bPhd) hR10Dsz->Fill(dJet, dsz,  dNorm);
    }

    if (dTrg>15.) {
      hR15Phi->Fill(dJet, dVar, dNorm);
      if (bPhl) hR15Phl->Fill(dJet, dVar, dNorm);
      if (bPhh) hR15Phh->Fill(dJet, dVar, dNorm);
      if (bPhd) hR15Dsz->Fill(dJet, dsz,  dNorm);
    }

    if (dTrg>20.) {
      hR20Phi->Fill(dJet, dVar, dNorm);
      if (bPhl) hR20Phl->Fill(dJet, dVar, dNorm);
      if (bPhh) hR20Phh->Fill(dJet, dVar, dNorm);
      if (bPhd) hR20Dsz->Fill(dJet, dsz,  dNorm);
    }

    if (dTrg>30.) {
      hR30Phi->Fill(dJet, dVar, dNorm);
      if (bPhl) hR30Phl->Fill(dJet, dVar, dNorm);
      if (bPhh) hR30Phh->Fill(dJet, dVar, dNorm);
      if (bPhd) hR30Dsz->Fill(dJet, dsz,  dNorm);
    }
//=============================================================================

    pJet = 0;
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

  TH1D *hLtkPt = new TH1D("hLtkPt", "", 1000, 0., 1000.); hLtkPt->Sumw2(); fOutput->Add(hLtkPt);

  TH2D *hR10Phi = new TH2D("hR10Phi", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR10Phi->Sumw2(); fOutput->Add(hR10Phi);
  TH2D *hR15Phi = new TH2D("hR15Phi", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR15Phi->Sumw2(); fOutput->Add(hR15Phi);
  TH2D *hR20Phi = new TH2D("hR20Phi", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR20Phi->Sumw2(); fOutput->Add(hR20Phi);
  TH2D *hR30Phi = new TH2D("hR30Phi", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR30Phi->Sumw2(); fOutput->Add(hR30Phi);

  TH2D *hR10Phl = new TH2D("hR10Phl", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR10Phl->Sumw2(); fOutput->Add(hR10Phl);
  TH2D *hR15Phl = new TH2D("hR15Phl", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR15Phl->Sumw2(); fOutput->Add(hR15Phl);
  TH2D *hR20Phl = new TH2D("hR20Phl", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR20Phl->Sumw2(); fOutput->Add(hR20Phl);
  TH2D *hR30Phl = new TH2D("hR30Phl", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR30Phl->Sumw2(); fOutput->Add(hR30Phl);

  TH2D *hR10Phh = new TH2D("hR10Phh", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR10Phh->Sumw2(); fOutput->Add(hR10Phh);
  TH2D *hR15Phh = new TH2D("hR15Phh", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR15Phh->Sumw2(); fOutput->Add(hR15Phh);
  TH2D *hR20Phh = new TH2D("hR20Phh", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR20Phh->Sumw2(); fOutput->Add(hR20Phh);
  TH2D *hR30Phh = new TH2D("hR30Phh", "", 1000, 0., 1000., 200, dPhiMin, dPhiMax); hR30Phh->Sumw2(); fOutput->Add(hR30Phh);

  TH2D *hR10Dsz = new TH2D("hR10Dsz", "", 1000, 0., 1000., 100, 0., 1.); hR10Dsz->Sumw2(); fOutput->Add(hR10Dsz);
  TH2D *hR15Dsz = new TH2D("hR15Dsz", "", 1000, 0., 1000., 100, 0., 1.); hR15Dsz->Sumw2(); fOutput->Add(hR15Dsz);
  TH2D *hR20Dsz = new TH2D("hR20Dsz", "", 1000, 0., 1000., 100, 0., 1.); hR20Dsz->Sumw2(); fOutput->Add(hR20Dsz);
  TH2D *hR30Dsz = new TH2D("hR30Dsz", "", 1000, 0., 1000., 100, 0., 1.); hR30Dsz->Sumw2(); fOutput->Add(hR30Dsz);

  return;
}
