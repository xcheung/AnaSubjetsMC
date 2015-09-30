#define AnalysisTaskUser_cxx
// The class definition in AnalysisTaskUser.h has been generated automatically
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
// Root > T->Process("AnalysisTaskUser.C")
// Root > T->Process("AnalysisTaskUser.C","some options")
// Root > T->Process("AnalysisTaskUser.C+")
//

#include <iostream>

#include <TStyle.h>
#include <TMath.h>
#include <TH2D.h>

#include "AnalysisTaskUser.h"
//=============================================================================

void AnalysisTaskUser::Begin(TTree * /*tree*/)
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

  TString sFile = Form("AnalysisOutputs_%s_%s_%s.root",sType.Data(),sJetR.Data(),sSjeR.Data());
  cout << sFile.Data() << endl;

  fFile = TFile::Open(sFile.Data(), "NEW");
  if (option.Contains("Dsj")) MakeOutputDsj();
  if (option.Contains("Dsm")) MakeOutputDsm();
  if (option.Contains("Rje")) MakeOutputRje();

  return;
}

//_____________________________________________________________________________
void AnalysisTaskUser::SlaveBegin(TTree * /*tree*/)
{
// The SlaveBegin() function is called after the Begin() function.
// When running with PROOF SlaveBegin() is called on each slave server.
// The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  return;
}

//_____________________________________________________________________________
Bool_t AnalysisTaskUser::Process(Long64_t entry)
{
// The Process() function is called for each entry in the tree (or possibly
// keyed object in the case of PROOF) to be processed. The entry argument
// specifies which entry in the currently loaded tree is to be processed.
// It can be passed to either AnalysisTaskUser::GetEntry() or TBranch::GetEntry()
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
  if (sOpt.Contains("Dsj")) if (AnalysisDsj()) return kFALSE;
  if (sOpt.Contains("Dsm")) if (AnalysisDsm()) return kFALSE;
  if (sOpt.Contains("Rje")) if (AnalysisRje()) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
void AnalysisTaskUser::SlaveTerminate()
{
// The SlaveTerminate() function is called after all entries or objects
// have been processed. When running with PROOF SlaveTerminate() is called
// on each slave server.

  return;
}

//_____________________________________________________________________________
void AnalysisTaskUser::Terminate()
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
Bool_t AnalysisTaskUser::AnalysisDsj()
{
//
//  AnalysisTaskUser::AnalysisDsj
//

  TH1D *hJet = dynamic_cast<TH1D*>(fOutput->FindObject("hJet")); if (!hJet) return kTRUE;

  TH2D *hLjeIrj = dynamic_cast<TH2D*>(fOutput->FindObject("hLjeIrj")); if (!hLjeIrj) return kTRUE;
  TH2D *hLjeIrf = dynamic_cast<TH2D*>(fOutput->FindObject("hLjeIrf")); if (!hLjeIrf) return kTRUE;

  TH2D *hLjeLrj = dynamic_cast<TH2D*>(fOutput->FindObject("hLjeLrj")); if (!hLjeLrj) return kTRUE;
  TH2D *hLjeLrf = dynamic_cast<TH2D*>(fOutput->FindObject("hLjeLrf")); if (!hLjeLrf) return kTRUE;

  TH2D *hLtkIrj = dynamic_cast<TH2D*>(fOutput->FindObject("hLtkIrj")); if (!hLtkIrj) return kTRUE;
  TH2D *hLtkIrf = dynamic_cast<TH2D*>(fOutput->FindObject("hLtkIrf")); if (!hLtkIrf) return kTRUE;

  TH2D *hLtkLrj = dynamic_cast<TH2D*>(fOutput->FindObject("hLtkLrj")); if (!hLtkLrj) return kTRUE;
  TH2D *hLtkLrf = dynamic_cast<TH2D*>(fOutput->FindObject("hLtkLrf")); if (!hLtkLrf) return kTRUE;


  TH2D *hJet1sj = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1sj")); if (!hJet1sj) return kTRUE;
  TH2D *hJet1sz = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1sz")); if (!hJet1sz) return kTRUE;

  TH2D *hJet2sj = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2sj")); if (!hJet2sj) return kTRUE;
  TH2D *hJet2sz = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2sz")); if (!hJet2sz) return kTRUE;

  TH2D *hJetDsj = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDsj")); if (!hJetDsj) return kTRUE;
  TH2D *hJetDsz = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDsz")); if (!hJetDsz) return kTRUE;
//=============================================================================

  if (fJet<0.) return kTRUE;
  const Double_t dWgt = fWgt / fNorm; if (dWgt<0.) return kTRUE;
//=============================================================================

  hJet->Fill(fJet, dWgt);
//=============================================================================

  if (fLje>0.) {
    if (fLjr>0) { hLjeIrj->Fill(fLje, fJet, dWgt); hLjeIrf->Fill(fLje, fJet/fLje, dWgt); }
    if (fLjr>1) { hLjeLrj->Fill(fLje, fJet, dWgt); hLjeLrf->Fill(fLje, fJet/fLje, dWgt); }
  }

  if (fLtk>0.) {
    if (fLtr>0) { hLtkIrj->Fill(fLtk, fJet, dWgt); hLtkIrf->Fill(fLtk, fJet/fLtk, dWgt); }
    if (fLtr>1) { hLtkLrj->Fill(fLtk, fJet, dWgt); hLtkLrf->Fill(fLtk, fJet/fLtk, dWgt); }
  }
//=============================================================================

  Double_t d1sj = (f1sj>0. ? f1sj : 0.);
  Double_t d2sj = (f2sj>0. ? f2sj : 0.);
  Double_t dDsj = d1sj - d2sj;

  hJet1sj->Fill(fJet, d1sj, dWgt); hJet1sz->Fill(fJet, d1sj/fJet, dWgt);
  hJet2sj->Fill(fJet, d2sj, dWgt); hJet2sz->Fill(fJet, d2sj/fJet, dWgt);
  hJetDsj->Fill(fJet, dDsj, dWgt); hJetDsz->Fill(fJet, dDsj/fJet, dWgt);
//=============================================================================

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AnalysisTaskUser::AnalysisDsm()
{
//
//  AnalysisTaskUser::AnalysisDsm
//

  TH2D *hJetRef = dynamic_cast<TH2D*>(fOutput->FindObject("hJetRef")); if (!hJetRef) return kTRUE;

  TH2D *hJet1sr = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1sr")); if (!hJet1sr) return kTRUE;
  TH2D *hJet2sr = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2sr")); if (!hJet2sr) return kTRUE;
  TH2D *hJetDsr = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDsr")); if (!hJetDsr) return kTRUE;

  TH2D *hJet1fr = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1fr")); if (!hJet1fr) return kTRUE;
  TH2D *hJet2fr = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2fr")); if (!hJet2fr) return kTRUE;
  TH2D *hJetDfr = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDfr")); if (!hJetDfr) return kTRUE;


  TH2D *hJetMas = dynamic_cast<TH2D*>(fOutput->FindObject("hJetMas")); if (!hJetMas) return kTRUE;

  TH2D *hJet1sm = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1sm")); if (!hJet1sm) return kTRUE;
  TH2D *hJet2sm = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2sm")); if (!hJet2sm) return kTRUE;
  TH2D *hJetDsm = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDsm")); if (!hJetDsm) return kTRUE;

  TH2D *hJet1dm = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1dm")); if (!hJet1dm) return kTRUE;
  TH2D *hJet2dm = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2dm")); if (!hJet2dm) return kTRUE;
  TH2D *hJetDdm = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDdm")); if (!hJetDdm) return kTRUE;

  TH2D *hJet1fm = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1fm")); if (!hJet1fm) return kTRUE;
  TH2D *hJet2fm = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2fm")); if (!hJet2fm) return kTRUE;
  TH2D *hJetDfm = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDfm")); if (!hJetDfm) return kTRUE;

  TH2D *hDsrDsm050 = dynamic_cast<TH2D*>(fOutput->FindObject("hDsrDsm050")); if (!hDsrDsm050) return kTRUE;
  TH2D *hDsrDsm100 = dynamic_cast<TH2D*>(fOutput->FindObject("hDsrDsm100")); if (!hDsrDsm100) return kTRUE;
  TH2D *hDsrDsm150 = dynamic_cast<TH2D*>(fOutput->FindObject("hDsrDsm150")); if (!hDsrDsm150) return kTRUE;

  TH2D *hDfrDsm050 = dynamic_cast<TH2D*>(fOutput->FindObject("hDfrDsm050")); if (!hDfrDsm050) return kTRUE;
  TH2D *hDfrDsm100 = dynamic_cast<TH2D*>(fOutput->FindObject("hDfrDsm100")); if (!hDfrDsm100) return kTRUE;
  TH2D *hDfrDsm150 = dynamic_cast<TH2D*>(fOutput->FindObject("hDfrDsm150")); if (!hDfrDsm150) return kTRUE;

  TH2D *hDfrDdm050 = dynamic_cast<TH2D*>(fOutput->FindObject("hDfrDdm050")); if (!hDfrDdm050) return kTRUE;
  TH2D *hDfrDdm100 = dynamic_cast<TH2D*>(fOutput->FindObject("hDfrDdm100")); if (!hDfrDdm100) return kTRUE;
  TH2D *hDfrDdm150 = dynamic_cast<TH2D*>(fOutput->FindObject("hDfrDdm150")); if (!hDfrDdm150) return kTRUE;

  TH2D *hDfrDfm050 = dynamic_cast<TH2D*>(fOutput->FindObject("hDfrDfm050")); if (!hDfrDfm050) return kTRUE;
  TH2D *hDfrDfm100 = dynamic_cast<TH2D*>(fOutput->FindObject("hDfrDfm100")); if (!hDfrDfm100) return kTRUE;
  TH2D *hDfrDfm150 = dynamic_cast<TH2D*>(fOutput->FindObject("hDfrDfm150")); if (!hDfrDfm150) return kTRUE;
//=============================================================================

  if (fJet<0.) return kTRUE;
  const Double_t dRef = TMath::Sqrt(fAje/TMath::Pi());
  const Double_t dWgt = fWgt / fNorm; if (dWgt<0.) return kTRUE;
//=============================================================================

  hJetRef->Fill(fJet, dRef, dWgt);
  hJetMas->Fill(fJet, fMje, dWgt);
//=============================================================================

  if (f1sj>0.) {
    hJet1sr->Fill(fJet, f1sr, dWgt);
    hJet1fr->Fill(fJet, f1sr/dRef, dWgt);

    hJet1sm->Fill(fJet, f1sm, dWgt);
    hJet1dm->Fill(fJet, fMje-f1sm, dWgt);
    hJet1fm->Fill(fJet, f1sm/fMje, dWgt);
  }

  if (f2sj>0.) {
    hJet2sr->Fill(fJet, f2sr, dWgt);
    hJet2fr->Fill(fJet, f2sr/dRef, dWgt);

    hJet2sm->Fill(fJet, f2sm, dWgt);
    hJet2dm->Fill(fJet, fMje-f2sm, dWgt);
    hJet2fm->Fill(fJet, f2sm/fMje, dWgt);
  }
//=============================================================================

  if ((f1sj>0.) && (f2sj>0.)) {
    hJetDsr->Fill(fJet, fDsr, dWgt);
    hJetDfr->Fill(fJet, fDsr/2./dRef, dWgt);

    hJetDsm->Fill(fJet, fDsm, dWgt);
    hJetDdm->Fill(fJet, fMje-fDsm, dWgt);
    hJetDfm->Fill(fJet, fDsm/fMje, dWgt);

    if ((fJet>=45.) && (fJet<55.)) {
      hDsrDsm050->Fill(fDsr, fDsm, dWgt);
      hDfrDsm050->Fill(fDsr/2./dRef, fDsm, dWgt);
      hDfrDdm050->Fill(fDsr/2./dRef, fMje-fDsm, dWgt);
      hDfrDfm050->Fill(fDsr/2./dRef, fDsm/fMje, dWgt);
    }

    if ((fJet>=90.) && (fJet<110.)) {
      hDsrDsm100->Fill(fDsr, fDsm, dWgt);
      hDfrDsm100->Fill(fDsr/2./dRef, fDsm, dWgt);
      hDfrDdm100->Fill(fDsr/2./dRef, fMje-fDsm, dWgt);
      hDfrDfm100->Fill(fDsr/2./dRef, fDsm/fMje, dWgt);
    }

    if ((fJet>=140.) && (fJet<160.)) {
      hDsrDsm150->Fill(fDsr, fDsm, dWgt);
      hDfrDsm150->Fill(fDsr/2./dRef, fDsm, dWgt);
      hDfrDdm150->Fill(fDsr/2./dRef, fMje-fDsm, dWgt);
      hDfrDfm150->Fill(fDsr/2./dRef, fDsm/fMje, dWgt);
    }
  }
//=============================================================================

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AnalysisTaskUser::AnalysisRje()
{
//
//  AnalysisTaskUser::AnalysisRje
//

  TH2D *hJet1szj120 = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1szj120")); if (!hJet1szj120) return kTRUE;
  TH2D *hJet2szj120 = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2szj120")); if (!hJet2szj120) return kTRUE;
  TH2D *hJetDszj120 = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDszj120")); if (!hJetDszj120) return kTRUE;
  TH2D *hLjeDszj120 = dynamic_cast<TH2D*>(fOutput->FindObject("hLjeDszj120")); if (!hLjeDszj120) return kTRUE;

  TH2D *hJet1szj150 = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1szj150")); if (!hJet1szj150) return kTRUE;
  TH2D *hJet2szj150 = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2szj150")); if (!hJet2szj150) return kTRUE;
  TH2D *hJetDszj150 = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDszj150")); if (!hJetDszj150) return kTRUE;
  TH2D *hLjeDszj150 = dynamic_cast<TH2D*>(fOutput->FindObject("hLjeDszj150")); if (!hLjeDszj150) return kTRUE;


  TH2D *hJet1szt010 = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1szt010")); if (!hJet1szt010) return kTRUE;
  TH2D *hJet2szt010 = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2szt010")); if (!hJet2szt010) return kTRUE;
  TH2D *hJetDszt010 = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDszt010")); if (!hJetDszt010) return kTRUE;
  TH2D *hLjeDszt010 = dynamic_cast<TH2D*>(fOutput->FindObject("hLjeDszt010")); if (!hLjeDszt010) return kTRUE;

  TH2D *hJet1szt020 = dynamic_cast<TH2D*>(fOutput->FindObject("hJet1szt020")); if (!hJet1szt020) return kTRUE;
  TH2D *hJet2szt020 = dynamic_cast<TH2D*>(fOutput->FindObject("hJet2szt020")); if (!hJet2szt020) return kTRUE;
  TH2D *hJetDszt020 = dynamic_cast<TH2D*>(fOutput->FindObject("hJetDszt020")); if (!hJetDszt020) return kTRUE;
  TH2D *hLjeDszt020 = dynamic_cast<TH2D*>(fOutput->FindObject("hLjeDszt020")); if (!hLjeDszt020) return kTRUE;


  TH2D *hAJ0120INFN = dynamic_cast<TH2D*>(fOutput->FindObject("hAJ0120INFN")); if (!hAJ0120INFN) return kTRUE;
  TH2D *hAJ0100INFN = dynamic_cast<TH2D*>(fOutput->FindObject("hAJ0100INFN")); if (!hAJ0100INFN) return kTRUE;

  TH2D *hAJ01500180 = dynamic_cast<TH2D*>(fOutput->FindObject("hAJ01500180")); if (!hAJ01500180) return kTRUE;
  TH2D *hAJ01800220 = dynamic_cast<TH2D*>(fOutput->FindObject("hAJ01800220")); if (!hAJ01800220) return kTRUE;
  TH2D *hAJ02200260 = dynamic_cast<TH2D*>(fOutput->FindObject("hAJ02200260")); if (!hAJ02200260) return kTRUE;
  TH2D *hAJ02600300 = dynamic_cast<TH2D*>(fOutput->FindObject("hAJ02600300")); if (!hAJ02600300) return kTRUE;
//=============================================================================

  if (fJet<0.) return kTRUE;
  const Double_t dWgt = fWgt / fNorm; if (dWgt<0.) return kTRUE;
//=============================================================================
  Double_t d1sz = (f1sj>0. ? f1sj : 0.) / fJet;
  Double_t d2sz = (f2sj>0. ? f2sj : 0.) / fJet;
  Double_t dDsz = d1sz - d2sz;
//=============================================================================

  if ((fLje>120.) && (fLjr>0.)) {
    hJet1szj120->Fill(fJet, d1sz, dWgt);
    hJet2szj120->Fill(fJet, d2sz, dWgt);
    hJetDszj120->Fill(fJet, dDsz, dWgt);
    if (fLjr>1) hLjeDszj120->Fill(fJet, dDsz, dWgt);
  }
//=============================================================================

  if ((fLje>150.) && (fLjr>0.)) {
    hJet1szj150->Fill(fJet, d1sz, dWgt);
    hJet2szj150->Fill(fJet, d2sz, dWgt);
    hJetDszj150->Fill(fJet, dDsz, dWgt);
    if (fLjr>1) hLjeDszj150->Fill(fJet, dDsz, dWgt);
  }
//=============================================================================

  if ((fLtk>10.) && (fLtr>0.)) {
    hJet1szt010->Fill(fJet, d1sz, dWgt);
    hJet2szt010->Fill(fJet, d2sz, dWgt);
    hJetDszt010->Fill(fJet, dDsz, dWgt);
    if (fLtr>1) hLjeDszt010->Fill(fJet, dDsz, dWgt);
  }
//=============================================================================

  if ((fLtk>20.) && (fLtr>0.)) {
    hJet1szt020->Fill(fJet, d1sz, dWgt);
    hJet2szt020->Fill(fJet, d2sz, dWgt);
    hJetDszt020->Fill(fJet, dDsz, dWgt);
    if (fLtr>1) hLjeDszt020->Fill(fJet, dDsz, dWgt);
  }
//=============================================================================

  Double_t d1sj = (f1sj>0. ? f1sj : 0.);
  Double_t d2sj = (f2sj>0. ? f2sj : 0.);
  Double_t dZsj = (d1sj-d2sj)/fJet;

  if ((fLje>=120.) && (fLjr>1) && (fJet>=50.)) hAJ0120INFN->Fill((fLje-fJet)/(fLje+fJet), dZsj, dWgt);
  if ((fLje>=100.) && (fLjr>1) && (fJet>=25.)) hAJ0100INFN->Fill((fLje-fJet)/(fLje+fJet), dZsj, dWgt);

  if (((fLje>=150.) && (fLje<180.)) && (fLjr>1) && (fJet>=30.)) hAJ01500180->Fill((fLje-fJet)/(fLje+fJet), dZsj, dWgt);
  if (((fLje>=180.) && (fLje<220.)) && (fLjr>1) && (fJet>=30.)) hAJ01800220->Fill((fLje-fJet)/(fLje+fJet), dZsj, dWgt);
  if (((fLje>=220.) && (fLje<260.)) && (fLjr>1) && (fJet>=30.)) hAJ02200260->Fill((fLje-fJet)/(fLje+fJet), dZsj, dWgt);
  if (((fLje>=260.) && (fLje<300.)) && (fLjr>1) && (fJet>=30.)) hAJ02600300->Fill((fLje-fJet)/(fLje+fJet), dZsj, dWgt);
//=============================================================================

  return kFALSE;
}

//_____________________________________________________________________________
void AnalysisTaskUser::MakeOutputDsj()
{
//
//  AnalysisTaskUser::MakeOutputDsj
//

  if (!fOutput) return;
//=============================================================================

  TH1D *hJet = new TH1D("hJet", "", 1000, 0., 1000.); hJet->Sumw2(); fOutput->Add(hJet);

  TH2D *hLjeIrj = new TH2D("hLjeIrj", "", 1000, 0., 1000., 1000, 0., 1000.); hLjeIrj->Sumw2(); fOutput->Add(hLjeIrj);
  TH2D *hLtkIrj = new TH2D("hLtkIrj", "", 1000, 0., 1000., 1000, 0., 1000.); hLtkIrj->Sumw2(); fOutput->Add(hLtkIrj);

  TH2D *hLjeLrj = new TH2D("hLjeLrj", "", 1000, 0., 1000., 1000, 0., 1000.); hLjeLrj->Sumw2(); fOutput->Add(hLjeLrj);
  TH2D *hLtkLrj = new TH2D("hLtkLrj", "", 1000, 0., 1000., 1000, 0., 1000.); hLtkLrj->Sumw2(); fOutput->Add(hLtkLrj);

  TH2D *hLjeIrf = new TH2D("hLjeIrf", "", 1000, 0., 1000., 1000, 0., 10.); hLjeIrf->Sumw2(); fOutput->Add(hLjeIrf);
  TH2D *hLtkIrf = new TH2D("hLtkIrf", "", 1000, 0., 1000., 1000, 0., 10.); hLtkIrf->Sumw2(); fOutput->Add(hLtkIrf);

  TH2D *hLjeLrf = new TH2D("hLjeLrf", "", 1000, 0., 1000., 1000, 0., 10.); hLjeLrf->Sumw2(); fOutput->Add(hLjeLrf);
  TH2D *hLtkLrf = new TH2D("hLtkLrf", "", 1000, 0., 1000., 1000, 0., 10.); hLtkLrf->Sumw2(); fOutput->Add(hLtkLrf);


  TH2D *hJet1sj = new TH2D("hJet1sj", "", 1000, 0., 1000., 1000, 0., 1000.); hJet1sj->Sumw2(); fOutput->Add(hJet1sj);
  TH2D *hJet2sj = new TH2D("hJet2sj", "", 1000, 0., 1000., 1000, 0., 1000.); hJet2sj->Sumw2(); fOutput->Add(hJet2sj);
  TH2D *hJetDsj = new TH2D("hJetDsj", "", 1000, 0., 1000., 1000, 0., 1000.); hJetDsj->Sumw2(); fOutput->Add(hJetDsj);

  TH2D *hJet1sz = new TH2D("hJet1sz", "", 1000, 0., 1000., 100, 0., 1.); hJet1sz->Sumw2(); fOutput->Add(hJet1sz);
  TH2D *hJet2sz = new TH2D("hJet2sz", "", 1000, 0., 1000., 100, 0., 1.); hJet2sz->Sumw2(); fOutput->Add(hJet2sz);
  TH2D *hJetDsz = new TH2D("hJetDsz", "", 1000, 0., 1000., 100, 0., 1.); hJetDsz->Sumw2(); fOutput->Add(hJetDsz);

  return;
}

//_____________________________________________________________________________
void AnalysisTaskUser::MakeOutputDsm()
{
//
//  AnalysisTaskUser::MakeOutputDsm
//

  if (!fOutput) return;
//=============================================================================

  TH2D *hJetRef = new TH2D("hJetRef", "", 1000, 0., 1000., 100, 0., 1.0); hJetRef->Sumw2(); fOutput->Add(hJetRef);

  TH2D *hJet1sr = new TH2D("hJet1sr", "", 1000, 0., 1000., 200, 0., 2.0); hJet1sr->Sumw2(); fOutput->Add(hJet1sr);
  TH2D *hJet2sr = new TH2D("hJet2sr", "", 1000, 0., 1000., 200, 0., 2.0); hJet2sr->Sumw2(); fOutput->Add(hJet2sr);
  TH2D *hJetDsr = new TH2D("hJetDsr", "", 1000, 0., 1000., 200, 0., 2.0); hJetDsr->Sumw2(); fOutput->Add(hJetDsr);

  TH2D *hJet1fr = new TH2D("hJet1fr", "", 1000, 0., 1000., 200, 0., 2.0); hJet1fr->Sumw2(); fOutput->Add(hJet1fr);
  TH2D *hJet2fr = new TH2D("hJet2fr", "", 1000, 0., 1000., 200, 0., 2.0); hJet2fr->Sumw2(); fOutput->Add(hJet2fr);
  TH2D *hJetDfr = new TH2D("hJetDfr", "", 1000, 0., 1000., 200, 0., 2.0); hJetDfr->Sumw2(); fOutput->Add(hJetDfr);


  TH2D *hJetMas = new TH2D("hJetMas", "", 1000, 0., 1000., 500, 0., 50.); hJetMas->Sumw2(); fOutput->Add(hJetMas);

  TH2D *hJet1sm = new TH2D("hJet1sm", "", 1000, 0., 1000., 500, 0., 50.); hJet1sm->Sumw2(); fOutput->Add(hJet1sm);
  TH2D *hJet2sm = new TH2D("hJet2sm", "", 1000, 0., 1000., 500, 0., 50.); hJet2sm->Sumw2(); fOutput->Add(hJet2sm);
  TH2D *hJetDsm = new TH2D("hJetDsm", "", 1000, 0., 1000., 500, 0., 50.); hJetDsm->Sumw2(); fOutput->Add(hJetDsm);

  TH2D *hJet1dm = new TH2D("hJet1dm", "", 1000, 0., 1000., 500, 0., 50.); hJet1dm->Sumw2(); fOutput->Add(hJet1dm);
  TH2D *hJet2dm = new TH2D("hJet2dm", "", 1000, 0., 1000., 500, 0., 50.); hJet2dm->Sumw2(); fOutput->Add(hJet2dm);
  TH2D *hJetDdm = new TH2D("hJetDdm", "", 1000, 0., 1000., 500, 0., 50.); hJetDdm->Sumw2(); fOutput->Add(hJetDdm);

  TH2D *hJet1fm = new TH2D("hJet1fm", "", 1000, 0., 1000., 500, 0., 5.0); hJet1fm->Sumw2(); fOutput->Add(hJet1fm);
  TH2D *hJet2fm = new TH2D("hJet2fm", "", 1000, 0., 1000., 500, 0., 5.0); hJet2fm->Sumw2(); fOutput->Add(hJet2fm);
  TH2D *hJetDfm = new TH2D("hJetDfm", "", 1000, 0., 1000., 500, 0., 5.0); hJetDfm->Sumw2(); fOutput->Add(hJetDfm);


  TH2D *hDsrDsm050 = new TH2D("hDsrDsm050", "", 200, 0., 2.0, 500, 0., 50.); hDsrDsm050->Sumw2(); fOutput->Add(hDsrDsm050);
  TH2D *hDsrDsm100 = new TH2D("hDsrDsm100", "", 200, 0., 2.0, 500, 0., 50.); hDsrDsm100->Sumw2(); fOutput->Add(hDsrDsm100);
  TH2D *hDsrDsm150 = new TH2D("hDsrDsm150", "", 200, 0., 2.0, 500, 0., 50.); hDsrDsm150->Sumw2(); fOutput->Add(hDsrDsm150);

  TH2D *hDfrDsm050 = new TH2D("hDfrDsm050", "", 200, 0., 2.0, 500, 0., 50.); hDfrDsm050->Sumw2(); fOutput->Add(hDfrDsm050);
  TH2D *hDfrDsm100 = new TH2D("hDfrDsm100", "", 200, 0., 2.0, 500, 0., 50.); hDfrDsm100->Sumw2(); fOutput->Add(hDfrDsm100);
  TH2D *hDfrDsm150 = new TH2D("hDfrDsm150", "", 200, 0., 2.0, 500, 0., 50.); hDfrDsm150->Sumw2(); fOutput->Add(hDfrDsm150);

  TH2D *hDfrDdm050 = new TH2D("hDfrDdm050", "", 200, 0., 2.0, 500, 0., 50.); hDfrDdm050->Sumw2(); fOutput->Add(hDfrDdm050);
  TH2D *hDfrDdm100 = new TH2D("hDfrDdm100", "", 200, 0., 2.0, 500, 0., 50.); hDfrDdm100->Sumw2(); fOutput->Add(hDfrDdm100);
  TH2D *hDfrDdm150 = new TH2D("hDfrDdm150", "", 200, 0., 2.0, 500, 0., 50.); hDfrDdm150->Sumw2(); fOutput->Add(hDfrDdm150);

  TH2D *hDfrDfm050 = new TH2D("hDfrDfm050", "", 200, 0., 2.0, 500, 0., 5.0); hDfrDfm050->Sumw2(); fOutput->Add(hDfrDfm050);
  TH2D *hDfrDfm100 = new TH2D("hDfrDfm100", "", 200, 0., 2.0, 500, 0., 5.0); hDfrDfm100->Sumw2(); fOutput->Add(hDfrDfm100);
  TH2D *hDfrDfm150 = new TH2D("hDfrDfm150", "", 200, 0., 2.0, 500, 0., 5.0); hDfrDfm150->Sumw2(); fOutput->Add(hDfrDfm150);

  return;
}

//_____________________________________________________________________________
void AnalysisTaskUser::MakeOutputRje()
{
//
//  AnalysisTaskUser::MakeOutputRje
//

  if (!fOutput) return;
//=============================================================================

  TH2D *hJet1szj120 = new TH2D("hJet1szj120", "", 1000, 0., 1000., 100, 0., 1.); hJet1szj120->Sumw2(); fOutput->Add(hJet1szj120);
  TH2D *hJet2szj120 = new TH2D("hJet2szj120", "", 1000, 0., 1000., 100, 0., 1.); hJet2szj120->Sumw2(); fOutput->Add(hJet2szj120);
  TH2D *hJetDszj120 = new TH2D("hJetDszj120", "", 1000, 0., 1000., 100, 0., 1.); hJetDszj120->Sumw2(); fOutput->Add(hJetDszj120);
  TH2D *hLjeDszj120 = new TH2D("hLjeDszj120", "", 1000, 0., 1000., 100, 0., 1.); hLjeDszj120->Sumw2(); fOutput->Add(hLjeDszj120);

  TH2D *hJet1szj150 = new TH2D("hJet1szj150", "", 1000, 0., 1000., 100, 0., 1.); hJet1szj150->Sumw2(); fOutput->Add(hJet1szj150);
  TH2D *hJet2szj150 = new TH2D("hJet2szj150", "", 1000, 0., 1000., 100, 0., 1.); hJet2szj150->Sumw2(); fOutput->Add(hJet2szj150);
  TH2D *hJetDszj150 = new TH2D("hJetDszj150", "", 1000, 0., 1000., 100, 0., 1.); hJetDszj150->Sumw2(); fOutput->Add(hJetDszj150);
  TH2D *hLjeDszj150 = new TH2D("hLjeDszj150", "", 1000, 0., 1000., 100, 0., 1.); hLjeDszj150->Sumw2(); fOutput->Add(hLjeDszj150);


  TH2D *hJet1szt010 = new TH2D("hJet1szt010", "", 1000, 0., 1000., 100, 0., 1.); hJet1szt010->Sumw2(); fOutput->Add(hJet1szt010);
  TH2D *hJet2szt010 = new TH2D("hJet2szt010", "", 1000, 0., 1000., 100, 0., 1.); hJet2szt010->Sumw2(); fOutput->Add(hJet2szt010);
  TH2D *hJetDszt010 = new TH2D("hJetDszt010", "", 1000, 0., 1000., 100, 0., 1.); hJetDszt010->Sumw2(); fOutput->Add(hJetDszt010);
  TH2D *hLjeDszt010 = new TH2D("hLjeDszt010", "", 1000, 0., 1000., 100, 0., 1.); hLjeDszt010->Sumw2(); fOutput->Add(hLjeDszt010);

  TH2D *hJet1szt020 = new TH2D("hJet1szt020", "", 1000, 0., 1000., 100, 0., 1.); hJet1szt020->Sumw2(); fOutput->Add(hJet1szt020);
  TH2D *hJet2szt020 = new TH2D("hJet2szt020", "", 1000, 0., 1000., 100, 0., 1.); hJet2szt020->Sumw2(); fOutput->Add(hJet2szt020);
  TH2D *hJetDszt020 = new TH2D("hJetDszt020", "", 1000, 0., 1000., 100, 0., 1.); hJetDszt020->Sumw2(); fOutput->Add(hJetDszt020);
  TH2D *hLjeDszt020 = new TH2D("hLjeDszt020", "", 1000, 0., 1000., 100, 0., 1.); hLjeDszt020->Sumw2(); fOutput->Add(hLjeDszt020);

  TH2D *hAJ0120INFN = new TH2D("hAJ0120INFN", "", 20, 0., 1.2, 100, 0., 1.); hAJ0120INFN->Sumw2(); fOutput->Add(hAJ0120INFN);
  TH2D *hAJ0100INFN = new TH2D("hAJ0100INFN", "", 20, 0., 1.2, 100, 0., 1.); hAJ0100INFN->Sumw2(); fOutput->Add(hAJ0100INFN);

  TH2D *hAJ01500180 = new TH2D("hAJ01500180", "", 20, 0., 1.2, 100, 0., 1.); hAJ01500180->Sumw2(); fOutput->Add(hAJ01500180);
  TH2D *hAJ01800220 = new TH2D("hAJ01800220", "", 20, 0., 1.2, 100, 0., 1.); hAJ01800220->Sumw2(); fOutput->Add(hAJ01800220);
  TH2D *hAJ02200260 = new TH2D("hAJ02200260", "", 20, 0., 1.2, 100, 0., 1.); hAJ02200260->Sumw2(); fOutput->Add(hAJ02200260);
  TH2D *hAJ02600300 = new TH2D("hAJ02600300", "", 20, 0., 1.2, 100, 0., 1.); hAJ02600300->Sumw2(); fOutput->Add(hAJ02600300);

  return;
}
