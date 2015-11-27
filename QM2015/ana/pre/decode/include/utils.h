const Int_t nJEL = 8;
const TString sJEL[] = {
  "dPtJet_1005_1011", "dPtJet_1011_1021", "dPtJet_1021_1036", "dPtJet_1036_1057",
  "dPtJet_1057_1084", "dPtJet_1084_1117", "dPtJet_1117_1152", "dPtJet_1152_INFN" };

const Int_t nPy8 = 8;
const TString sPy8[] = {
  "dPtHat_1005_1011", "dPtHat_1011_1021", "dPtHat_1021_1036", "dPtHat_1036_1057",
  "dPtHat_1057_1084", "dPtHat_1084_1117", "dPtHat_1117_1152", "dPtHat_1152_INFN" };

const Int_t nQpy = 10;
const TString sQpy[] = {
  "dPtHard_00005_00011", "dPtHard_00011_00021", "dPtHard_00021_00036", "dPtHard_00036_00057", "dPtHard_00057_00084",
  "dPtHard_00084_00117", "dPtHard_00117_00152", "dPtHard_00152_00191", "dPtHard_00191_00234", "dPtHard_00234_INFTY" };
//=============================================================================

TH1D *GetHistoJEL(const TString sHist, const TString sPath)
{
  TH1D *histo = 0;
  TFile *file = 0;
  for (Int_t i=0; i<nJEL; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sJEL[i].Data()), "READ");
    Double_t dWgt = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);

    TH1D *hTemp = (TH1D*)file->Get(sHist.Data());
    hTemp->SetName(Form("%s_%s",sHist.Data(),sJEL[i].Data()));
    hTemp->SetDirectory(0);
    file->Close();

    if (i==0) { histo = (TH1D*)hTemp->Clone(Form("%s_Merge",sHist.Data())); histo->Reset(); }
    histo->Add(hTemp, 1./dWgt);
  }

  return histo;
}

//_____________________________________________________________________________
TH2D *GetHist2JEL(const TString sHist, const TString sPath)
{
  TH2D *hist2 = 0;
  TFile *file = 0;
  for (Int_t i=0; i<nJEL; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sJEL[i].Data()), "READ");
    Double_t dWgt = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
    TH2D *hTemp = (TH2D*)file->Get(sHist.Data());
    hTemp->SetName(Form("%s_%s",sHist.Data(),sJEL[i].Data()));
    hTemp->SetDirectory(0);
    file->Close();

    if (i==0) { hist2 = (TH2D*)hTemp->Clone(Form("%s_Merge",sHist.Data())); hist2->Reset(); }
    hist2->Add(hTemp, 1./dWgt);
  }

  return hist2;
}

//_____________________________________________________________________________
TH3D *GetHist3JEL(const TString sHist, const TString sPath)
{
  TH3D *hist3 = 0;
  TFile *file = 0;
  for (Int_t i=0; i<nJEL; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sJEL[i].Data()), "READ");
    Double_t dWgt = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
    TH3D *hTemp = (TH3D*)file->Get(sHist.Data());
    hTemp->SetName(Form("%s_%s",sHist.Data(),sJEL[i].Data()));
    hTemp->SetDirectory(0);
    file->Close();

    if (i==0) { hist3 = (TH3D*)hTemp->Clone(Form("%s_Merge",sHist.Data())); hist3->Reset(); }
    hist3->Add(hTemp, 1./dWgt);
  }

  return hist3;
}
//=============================================================================
//=============================================================================

TH1D *GetHistoPy8(const TString sHist, const TString sPath)
{
  TH1D *histo = 0;
  TFile *file = 0;
  for (Int_t i=0; i<nPy8; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sPy8[i].Data()), "READ");
    Double_t dX = ((TProfile*)file->Get("hSigmaGen"))->GetBinContent(1);
    Double_t dW = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
    Double_t dWgt = dX / dW;

    TH1D *hTemp = (TH1D*)file->Get(sHist.Data());
    hTemp->SetName(Form("%s_%s",sHist.Data(),sPy8[i].Data()));
    hTemp->SetDirectory(0);
    file->Close();

    if (i==0) { histo = (TH1D*)hTemp->Clone(Form("%s_Merge",sHist.Data())); histo->Reset(); }
    histo->Add(hTemp, dWgt);
  }

  return histo;
}

//_____________________________________________________________________________
TH2D *GetHist2Py8(const TString sHist, const TString sPath)
{
  TH2D *hist2 = 0;
  TFile *file = 0;
  for (Int_t i=0; i<nPy8; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sPy8[i].Data()), "READ");
    Double_t dX = ((TProfile*)file->Get("hSigmaGen"))->GetBinContent(1);
    Double_t dW = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
    Double_t dWgt = dX / dW;

    TH2D *hTemp = (TH2D*)file->Get(sHist.Data());
    hTemp->SetName(Form("%s_%s",sHist.Data(),sPy8[i].Data()));
    hTemp->SetDirectory(0);
    file->Close();

    if (i==0) { hist2 = (TH2D*)hTemp->Clone(Form("%s_Merge",sHist.Data())); hist2->Reset(); }
    hist2->Add(hTemp, dWgt);
  }

  return hist2;
}

//_____________________________________________________________________________
TH3D *GetHist3Py8(const TString sHist, const TString sPath)
{
  TH3D *hist3 = 0;
  TFile *file = 0;
  for (Int_t i=0; i<nPy8; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sPy8[i].Data()), "READ");
    Double_t dX = ((TProfile*)file->Get("hSigmaGen"))->GetBinContent(1);
    Double_t dW = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
    Double_t dWgt = dX / dW;

    TH3D *hTemp = (TH3D*)file->Get(sHist.Data());
    hTemp->SetName(Form("%s_%s",sHist.Data(),sPy8[i].Data()));
    hTemp->SetDirectory(0);
    file->Close();

    if (i==0) { hist3 = (TH3D*)hTemp->Clone(Form("%s_Merge",sHist.Data())); hist3->Reset(); }
    hist3->Add(hTemp, dWgt);
  }

  return hist3;
}
//=============================================================================
//=============================================================================

TH1D *GetHistoQpy(const TString sHist, const TString sPath)
{
  TH1D *histo = 0;
  TFile *file = 0;
  for (Int_t i=0; i<nQpy; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sQpy[i].Data()), "READ");
    Double_t dX = ((TProfile*)file->Get("hSigmaGen"))->GetBinContent(1);
    Double_t dW = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
    Double_t dWgt = dX / dW;

    TH1D *hTemp = (TH1D*)file->Get(sHist.Data());
    hTemp->SetName(Form("%s_%s",sHist.Data(),sQpy[i].Data()));
    hTemp->SetDirectory(0);
    file->Close();

    if (i==0) { histo = (TH1D*)hTemp->Clone(Form("%s_Merge",sHist.Data())); histo->Reset(); }
    histo->Add(hTemp, dWgt);
  }

  return histo;
}

//_____________________________________________________________________________
TH2D *GetHist2Qpy(const TString sHist, const TString sPath)
{
  TH2D *hist2 = 0;
  TFile *file = 0;
  for (Int_t i=0; i<nQpy; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sQpy[i].Data()), "READ");
    Double_t dX = ((TProfile*)file->Get("hSigmaGen"))->GetBinContent(1);
    Double_t dW = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
    Double_t dWgt = dX / dW;

    TH2D *hTemp = (TH2D*)file->Get(sHist.Data());
    hTemp->SetName(Form("%s_%s",sHist.Data(),sQpy[i].Data()));
    hTemp->SetDirectory(0);
    file->Close();

    if (i==0) { hist2 = (TH2D*)hTemp->Clone(Form("%s_Merge",sHist.Data())); hist2->Reset(); }
    hist2->Add(hTemp, dWgt);
  }

  return hist2;
}

//_____________________________________________________________________________
TH3D *GetHist3Qpy(const TString sHist, const TString sPath)
{
  TH3D *hist3 = 0;
  TFile *file = 0;
  for (Int_t i=0; i<nQpy; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sQpy[i].Data()), "READ");
    Double_t dX = ((TProfile*)file->Get("hSigmaGen"))->GetBinContent(1);
    Double_t dW = ((TH1D*)file->Get("hWeightSum"))->GetBinContent(1);
    Double_t dWgt = dX / dW;

    TH3D *hTemp = (TH3D*)file->Get(sHist.Data());
    hTemp->SetName(Form("%s_%s",sHist.Data(),sQpy[i].Data()));
    hTemp->SetDirectory(0);
    file->Close();

    if (i==0) { hist3 = (TH3D*)hTemp->Clone(Form("%s_Merge",sHist.Data())); hist3->Reset(); }
    hist3->Add(hTemp, dWgt);
  }

  return hist3;
}
//=============================================================================
//=============================================================================

Double_t CalcMedian(TH1D *h)
{
  Int_t kBin = -1;
  const Double_t dInt = h->Integral();
  for (Int_t k=1; k<=h->GetNbinsX(); k++) {
    if ((h->Integral(1,k)/dInt)>=0.5) { kBin = k; break; }
  }

  return (h->GetBinCenter(k));
}

//_____________________________________________________________________________
Double_t CalcMAD(TH1D *hOrg, const Double_t dM)
{
  TH1D *hMAD = (TH1D*)hOrg->Clone(Form("%s_Org_MAD",hOrg->GetName()));
  hMAD->Reset();

  for (Int_t k=1; k<=hOrg->GetNbinsX(); k++) {
    Double_t dBin = TMath::Abs(dM-hOrg->GetBinCenter(k)) + 1e-6;
    Int_t    kBin = hMAD->FindBin(dBin);

    hMAD->AddBinContent(kBin, hOrg->GetBinContent(k));
  }

  return CalcMedian(hMAD);
}
//=============================================================================
//=============================================================================
