void AnaMakeDsrJEL(const TString sPref,
                   const TString sPath,
                   const TString sHist="hJetDsr")
{
  gROOT->LoadMacro("include/utils.h");
//=============================================================================

  TList *list = new TList();

  TH3D *hist3 = GetHist3JEL(sHist, Form("%s/%s",sPath.Data(),sPref.Data()));
  hist3->SetName(sHist.Data());
  hist3->RebinX(10);
  list->Add(hist3);
//=============================================================================

  list->Print();
  TFile *file = TFile::Open("AnalysisOutputs_Dsr.root", "UPDATE");
  list->Write(Form("list_%s",sPref.Data()), TObject::kSingleKey);
  file->Close();
//=============================================================================

  cout << "DONE" << endl;
//=============================================================================

  return;
}
