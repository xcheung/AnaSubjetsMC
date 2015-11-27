void AnaMakeIsjJEL(const TString sPref,
                   const TString sPath,
                   const TString sHist="hJetIsj")
{
  gROOT->LoadMacro("include/utils.h");
//=============================================================================

  TList *list = new TList();

  TH2D *hist2 = GetHist2JEL(sHist, Form("%s/%s",sPath.Data(),sPref.Data()));
  hist2->SetName(sHist.Data());
  hist2->RebinX(10);
  list->Add(hist2);
//=============================================================================

  TProfile *hMean = hist2->ProfileX(Form("%s_mean",sHist.Data())); list->Add(hMean);
  TH1D *hRMS = hist2->ProjectionX(Form("%s_RMS",sHist.Data())); hRMS->Reset(); list->Add(hRMS);

  TH1D *hMed = hist2->ProjectionX(Form("%s_Median",sHist.Data())); hMed->Reset(); list->Add(hMed);
  TH1D *hMAD = hist2->ProjectionX(Form("%s_MAD",   sHist.Data())); hMAD->Reset(); list->Add(hMAD);

  for (Int_t k=1; k<=hist2->GetNbinsX(); k++) {
    hRMS->SetBinContent(k, hMean->GetBinError(k));
    TH1D *hTemp = hist2->ProjectionY(Form("%s_TempY_%d",sHist.Data(),k), k, k);

    Double_t dM = CalcMedian(hTemp);

    hMed->SetBinContent(k, dM);
    hMAD->SetBinContent(k, CalcMAD(hTemp,dM));

    delete hTemp; hTemp = 0;
  }
//=============================================================================

  list->Print();
  TFile *file = TFile::Open("AnalysisOutputs_Isj.root", "UPDATE");
  list->Write(Form("list_%s",sPref.Data()), TObject::kSingleKey);
  file->Close();
//=============================================================================

  cout << "DONE" << endl;
//=============================================================================

  return;
}
