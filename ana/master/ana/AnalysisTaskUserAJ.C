#define AnalysisTaskUserAJ_cxx
// The class definition in AnalysisTaskUserAJ.h has been generated automatically
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
// Root > T->Process("AnalysisTaskUserAJ.C")
// Root > T->Process("AnalysisTaskUserAJ.C","some options")
// Root > T->Process("AnalysisTaskUserAJ.C+")
//

#include <iostream>

#include <TStyle.h>
#include <TMath.h>
#include <TH2D.h>

#include "AnalysisTaskUserAJ.h"
//=============================================================================

void AnalysisTaskUserAJ::Begin(TTree * /*tree*/)
{
// The Begin() function is called at the start of the query.
// When running with PROOF Begin() is only called on the client.
// The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  TString sType;
  if (option.Contains("py8")) sType = "py8";
  if (option.Contains("py6")) sType = "py6";
  if (option.Contains("qpy")) sType = "qpy";
  if (option.Contains("qp6")) sType = "qp6";
  if (option.Contains("qp4")) sType = "qp4";
  if (option.Contains("vac")) sType = "vac";
  if (option.Contains("med")) sType = "med";

  TString sJetR;
  if (option.Contains("JetR05")) sJetR = "JetR05";
  if (option.Contains("JetR04")) sJetR = "JetR04";
  if (option.Contains("JetR03")) sJetR = "JetR03";
  if (option.Contains("JetR02")) sJetR = "JetR02";

  TString sSjeR;
  if (option.Contains("SjeR01")) sSjeR = "SjeR01";
  if (option.Contains("SjeR03")) sSjeR = "SjeR02";
  if (option.Contains("SjeR03")) sSjeR = "SjeR03";
  if (option.Contains("SjeR04")) sSjeR = "SjeR04";

  TString sFile = Form("AnalysisOutputs.root");
  cout << sFile.Data() << endl;

  fFile = TFile::Open(sFile.Data(), "NEW");
  if (option.Contains("DAJ")) MakeOutputDAJ();

  return;
}

//_____________________________________________________________________________
void AnalysisTaskUserAJ::SlaveBegin(TTree * /*tree*/)
{
// The SlaveBegin() function is called after the Begin() function.
// When running with PROOF SlaveBegin() is called on each slave server.
// The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  return;
}

//_____________________________________________________________________________
Bool_t AnalysisTaskUserAJ::Process(Long64_t entry)
{
// The Process() function is called for each entry in the tree (or possibly
// keyed object in the case of PROOF) to be processed. The entry argument
// specifies which entry in the currently loaded tree is to be processed.
// It can be passed to either AnalysisTaskUserAJ::GetEntry() or TBranch::GetEntry()
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

  if (GetEntry(entry)==0) return kFALSE;
//=============================================================================

  TString sOpt = GetOption();
  if (sOpt.Contains("DAJ")) if (AnalysisDAJ()) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
void AnalysisTaskUserAJ::SlaveTerminate()
{
// The SlaveTerminate() function is called after all entries or objects
// have been processed. When running with PROOF SlaveTerminate() is called
// on each slave server.

  return;
}

//_____________________________________________________________________________
void AnalysisTaskUserAJ::Terminate()
{
// The Terminate() function is the last function to be called during
// a query. It always runs on the client, it can be used to present
// the results graphically or save the results to file.

  fFile->cd();
  fOutput->Print();
  fOutput->Write();
  fFile->Close();

  return;
}

//_____________________________________________________________________________
//_____________________________________________________________________________
Bool_t AnalysisTaskUserAJ::AnalysisDAJ()
{
//
//  AnalysisTaskUser::AnalysisDAJ
//

  TH1D *hSum = dynamic_cast<TH1D*>(fOutput->FindObject("hSum")); if (!hSum) return kTRUE;
  TH2D *hAJ  = dynamic_cast<TH2D*>(fOutput->FindObject("hAJ"));  if (!hAJ) return kTRUE;
//=============================================================================

  if ((f1je<80.) || (f2je<25.) || (TMath::Abs(fDje)<1./2.*TMath::Pi())) return kTRUE;

  const Double_t dNorm = fWgt * fXsc;
//=============================================================================

  Double_t d1sj = (f21j>0. ? f21j : 0.);
  Double_t d2sj = (f22j>0. ? f22j : 0.);
  Double_t dDsz = (d1sj-d2sj) / f2je;
  Double_t dDAJ = (f1je-f2je) / (f1je+f2je);
//=============================================================================

  hSum->Fill(0.5, fWgt);
  hAJ->Fill(dDAJ, dDsz, dNorm);
//=============================================================================

  return kFALSE;
}

//_____________________________________________________________________________
void AnalysisTaskUserAJ::MakeOutputDAJ()
{
//
//  AnalysisTaskUser::MakeOutputDAJ
//

  if (!fOutput) return;
//=============================================================================

  TH1D *hSum = new TH1D("hSum", "", 1, 0., 1.); hSum->Sumw2(); fOutput->Add(hSum);
  TH2D *hAJ  = new TH2D("hAJ", "", 20, 0., 1.2, 100, 0., 1.); hAJ->Sumw2(); fOutput->Add(hAJ);

  return;
}
