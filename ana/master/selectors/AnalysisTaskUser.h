//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Sep 20 19:38:37 2015 by ROOT version 5.34/32
// from TTree nt/
// found on file: out_dPtHard_00005_00011.root
//////////////////////////////////////////////////////////

#ifndef AnalysisTaskUser_h
#define AnalysisTaskUser_h

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

class AnalysisTaskUser : public TSelector {
 public :

  AnalysisTaskUser(TTree * /*tree*/ =0) : fChain(0) { }
  virtual ~AnalysisTaskUser() { }

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

  Bool_t AnalysisDsj();
  void MakeOutputDsj();

  Bool_t AnalysisDsm();
  void MakeOutputDsm();

  Bool_t AnalysisRje();
  void MakeOutputRje();
//=============================================================================

  TFile *fFile;

  Double_t fNorm;
//=============================================================================

  TTree *fChain;

  Float_t fWgt;  // event weight, used for JEWEL
  Float_t fLje;  // leading jet pT
  Float_t fLjr;  // leading jet recoil: <0, false; >0, true; >1, leading
  Float_t fLtk;  // leading particle pT
  Float_t fLtr;  // leading particle recoil: <0, false; >0, true; >1, leading
  Float_t fJet;  // jet pT
  Float_t fAje;  // jet area
  Float_t fMje;  // jet mass
  Float_t f1sj;  // 1st leading sub-jet pT
  Float_t f1sA;  // 1st leading sub-jet area
  Float_t f1sm;  // 1st leading sub-jet mass
  Float_t f1sr;  // 1st leading sub-jet, DeltaR to jet
  Float_t f2sj;  // 2nd leading sub-jet pT
  Float_t f2sA;  // 2nd leading sub-jet area
  Float_t f2sm;  // 2nd leading sub-jet mass
  Float_t f2sr;  // 2nd leading sub-jet, DeltaR to jet
  Float_t fDsm;  // 1st and 2nd sub-jets, InvM
  Float_t fDsr;  // 1st and 2nd sub-jets, DeltaR

  TBranch *b_fWgt;  //!
  TBranch *b_fLje;  //!
  TBranch *b_fLjr;  //!
  TBranch *b_fLtk;  //!
  TBranch *b_fLtr;  //!
  TBranch *b_fJet;  //!
  TBranch *b_fAje;  //!
  TBranch *b_fMje;  //!
  TBranch *b_f1sj;  //!
  TBranch *b_f1sA;  //!
  TBranch *b_f1sm;  //!
  TBranch *b_f1sr;  //!
  TBranch *b_f2sj;  //!
  TBranch *b_f2sA;  //!
  TBranch *b_f2sm;  //!
  TBranch *b_f2sr;  //!
  TBranch *b_fDsm;  //!
  TBranch *b_fDsr;  //!
//=============================================================================

   ClassDef(AnalysisTaskUser,0);
};

#endif
//=============================================================================

#ifdef AnalysisTaskUser_cxx

//_____________________________________________________________________________
void AnalysisTaskUser::Init(TTree *tree)
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
  fChain->SetBranchAddress("fLje", &fLje, &b_fLje);
  fChain->SetBranchAddress("fLjr", &fLjr, &b_fLjr);
  fChain->SetBranchAddress("fLtk", &fLtk, &b_fLtk);
  fChain->SetBranchAddress("fLtr", &fLtr, &b_fLtr);
  fChain->SetBranchAddress("fJet", &fJet, &b_fJet);
  fChain->SetBranchAddress("fAje", &fAje, &b_fAje);
  fChain->SetBranchAddress("fMje", &fMje, &b_fMje);
  fChain->SetBranchAddress("f1sj", &f1sj, &b_f1sj);
  fChain->SetBranchAddress("f1sA", &f1sA, &b_f1sA);
  fChain->SetBranchAddress("f1sm", &f1sm, &b_f1sm);
  fChain->SetBranchAddress("f1sr", &f1sr, &b_f1sr);
  fChain->SetBranchAddress("f2sj", &f2sj, &b_f2sj);
  fChain->SetBranchAddress("f2sA", &f2sA, &b_f2sA);
  fChain->SetBranchAddress("f2sm", &f2sm, &b_f2sm);
  fChain->SetBranchAddress("f2sr", &f2sr, &b_f2sr);
  fChain->SetBranchAddress("fDsm", &fDsm, &b_fDsm);
  fChain->SetBranchAddress("fDsr", &fDsr, &b_fDsr);

  return;
}

//_____________________________________________________________________________
Bool_t AnalysisTaskUser::Notify()
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
//=============================================================================

  return kTRUE;
}

#endif // #ifdef AnalysisTaskUser_cxx
