//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep 25 23:04:54 2015 by ROOT version 5.34/32
// from TTree nt/
// found on file: out_dPtHat_1005_1011.root
//////////////////////////////////////////////////////////

#ifndef AnalysisTaskUserAJ_h
#define AnalysisTaskUserAJ_h

#include <TROOT.h>
#include <TString.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TProfile.h>

#include <TSelector.h>
//=============================================================================

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class AnalysisTaskUserAJ : public TSelector {

 public :

  AnalysisTaskUserAJ(TTree * /*tree*/ =0) : fChain(0) { }
  virtual ~AnalysisTaskUserAJ() { }

  virtual Int_t  Version() const { return 2; }
  virtual void   Begin(TTree *tree);
  virtual void   SlaveBegin(TTree *tree);

  virtual void   Init(TTree *tree);
  virtual Bool_t Notify();

  virtual Bool_t Process(Long64_t entry);
  virtual Int_t  GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }

  virtual void   SetOption(const char *option) { fOption = option; }
  virtual void   SetObject(TObject *obj) { fObject = obj; }

  virtual void   SetInputList(TList *input) { fInput = input; }
  virtual TList *GetOutputList() const { return fOutput; }

  virtual void   SlaveTerminate();
  virtual void   Terminate();
//=============================================================================

 private :

  Bool_t AnalysisDAJ();
  void MakeOutputDAJ();
//=============================================================================

  TFile *fFile;

  Double_t fNorm;
//=============================================================================

  TTree *fChain;

  Float_t fWgt;  // event weight
  Float_t fXsc;  // event weight
  Float_t f1je;  // leading jet pT
  Float_t f1jA;  // leading jet area
  Float_t f2je;  // sub-leading jet pT
  Float_t f2jA;  // sub-leading jet area
  Float_t fDje;  // DeltaPhi between two leading jets
  Float_t f11j;  // 1st sj pT   in leading jet
  Float_t f11A;  // 1st sj area in leading jet
  Float_t f11r;  // 1st sj dr   in leading jet
  Float_t f12j;  // 2nd sj pT   in leading jet
  Float_t f12A;  // 2nd sj area in leading jet
  Float_t f12r;  // 2nd sj dr   in leading jet
  Float_t f1dr;  // distance between two hardest sj in leading jet
  Float_t f21j;  // 1st sj pT   in sub-leading jet
  Float_t f21A;  // 1st sj area in sub-leading jet
  Float_t f21r;  // 1st sj dr   in sub-leading jet
  Float_t f22j;  // 2nd sj pT   in sub-leading jet
  Float_t f22A;  // 2nd sj area in sub-leading jet
  Float_t f22r;  // 2nd sj dr   in sub-leading jet
  Float_t f2dr;  // distance between two hardest sj in leading jet

  TBranch *b_fWgt;  //!
  TBranch *b_fXsc;  //!
  TBranch *b_f1je;  //!
  TBranch *b_f1jA;  //!
  TBranch *b_f2je;  //!
  TBranch *b_f2jA;  //!
  TBranch *b_fDje;  //!
  TBranch *b_f11j;  //!
  TBranch *b_f11A;  //!
  TBranch *b_f11r;  //!
  TBranch *b_f12j;  //!
  TBranch *b_f12A;  //!
  TBranch *b_f12r;  //!
  TBranch *b_f1dr;  //!
  TBranch *b_f21j;  //!
  TBranch *b_f21A;  //!
  TBranch *b_f21r;  //!
  TBranch *b_f22j;  //!
  TBranch *b_f22A;  //!
  TBranch *b_f22r;  //!
  TBranch *b_f2dr;  //!
//=============================================================================

  ClassDef(AnalysisTaskUserAJ,0);
};

#endif
//=============================================================================

#ifdef AnalysisTaskUserAJ_cxx

//_____________________________________________________________________________
void AnalysisTaskUserAJ::Init(TTree *tree)
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
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("fWgt", &fWgt, &b_fWgt);
  fChain->SetBranchAddress("fXsc", &fXsc, &b_fXsc);
  fChain->SetBranchAddress("f1je", &f1je, &b_f1je);
  fChain->SetBranchAddress("f1jA", &f1jA, &b_f1jA);
  fChain->SetBranchAddress("f2je", &f2je, &b_f2je);
  fChain->SetBranchAddress("f2jA", &f2jA, &b_f2jA);
  fChain->SetBranchAddress("fDje", &fDje, &b_fDje);
  fChain->SetBranchAddress("f11j", &f11j, &b_f11j);
  fChain->SetBranchAddress("f11A", &f11A, &b_f11A);
  fChain->SetBranchAddress("f11r", &f11r, &b_f11r);
  fChain->SetBranchAddress("f12j", &f12j, &b_f12j);
  fChain->SetBranchAddress("f12A", &f12A, &b_f12A);
  fChain->SetBranchAddress("f12r", &f12r, &b_f12r);
  fChain->SetBranchAddress("f1dr", &f1dr, &b_f1dr);
  fChain->SetBranchAddress("f21j", &f21j, &b_f21j);
  fChain->SetBranchAddress("f21A", &f21A, &b_f21A);
  fChain->SetBranchAddress("f21r", &f21r, &b_f21r);
  fChain->SetBranchAddress("f22j", &f22j, &b_f22j);
  fChain->SetBranchAddress("f22A", &f22A, &b_f22A);
  fChain->SetBranchAddress("f22r", &f22r, &b_f22r);
  fChain->SetBranchAddress("f2dr", &f2dr, &b_f2dr);

  return;
}

//_____________________________________________________________________________
Bool_t AnalysisTaskUserAJ::Notify()
{
// The Notify() function is called when a new file is opened. This
// can be either for a new TTree in a TChain or when when a new TTree
// is started when using PROOF. It is normally not necessary to make changes
// to the generated code, but the routine can be extended by the
// user if needed. The return value is currently not used.

  TString sOut = fChain->GetCurrentFile()->GetName();
  TString sWgt = sOut; sWgt.ReplaceAll("out_", "wgt_");

  cout << sOut.Data() << endl;
  cout << sWgt.Data() << endl;
//=============================================================================

  fNorm = -1.;
  TString sOpt = GetOption();
  TFile *file = TFile::Open(sWgt.Data(), "READ");
  if (sOpt.Contains("py8") || sOpt.Contains("py6") || sOpt.Contains("qpy") || sOpt.Contains("qp6") || sOpt.Contains("qp4")) {
    Double_t dSumw = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
    Double_t dXsec = ((TProfile*)file->Get("hSigmaGen"))->GetBinContent(1);
    fNorm = dSumw / dXsec;
  }

  if (sOpt.Contains("vac") || sOpt.Contains("med")) {
    fNorm = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
  } file->Close();

  cout << "Normalization factor = " << fNorm << endl;

  if (fNorm<0.) return kFALSE;
//============================================================================

   return kTRUE;
}

#endif // #ifdef AnalysisTaskUserAJ_cxx
