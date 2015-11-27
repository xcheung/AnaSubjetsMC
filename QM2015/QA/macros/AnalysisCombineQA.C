void AnalysisCombineQA()
{
  gROOT->LoadMacro("include/utils.h");
//=============================================================================

  const Int_t nHist = 15;
  const TString sHist[] = {
    "hTrkPtEta", "hTrkPtPhi", "hJetPtNsj",
    "hJetPtEta", "hJetPtPhi", "hLjePtEta", "hLjePtPhi", "hNjePtEta", "hNjePtPhi",
    "hJe2PtEta", "hJe2PtPhi", "hLj2PtEta", "hLj2PtPhi", "hNj2PtEta", "hNj2PtPhi" };

  const TString sPath = "/Local/xzhang/subjetsTH/data/QA/med_JetR05_skTR01";
//=============================================================================

  TH2D *hist2 = 0;
  TList *list = new TList();
  for (Int_t i=0; i<nHist; i++) {
    hist2 = GetHist2JEL(sHist[i], sPath);
    hist2->SetName(sHist[i].Data());
    list->Add(hist2);
  }
//=============================================================================

/*TFile *file = TFile::Open("AnalysisResults.root", "NEW");
  list->Print();
  list->Write();
  file->Close();*/
//=============================================================================

  return;
}
