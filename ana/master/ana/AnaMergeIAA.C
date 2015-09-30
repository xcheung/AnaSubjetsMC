{
  const Bool_t bt = kFALSE;
  const Int_t nHardI = 4;
  const Int_t nHardF = 8;
  const TString sPath = "data/inclIAA/outputs/qp6_JetR05_SjeR01";
  const TString sTrig = "40";

/*const TString sHard[] = {
    "dPtJet_1005_1011", "dPtJet_1011_1021", "dPtJet_1021_1036", "dPtJet_1036_1057",
    "dPtJet_1057_1084", "dPtJet_1084_1117", "dPtJet_1117_1152", "dPtJet_1152_INFN" };*/

/*const TString sHard[] = {
    "dPtHat_1005_1011", "dPtHat_1011_1021", "dPtHat_1021_1036", "dPtHat_1036_1057",
    "dPtHat_1057_1084", "dPtHat_1084_1117", "dPtHat_1117_1152", "dPtHat_1152_INFN" };*/

  const TString sHard[] = {
    "dPtHard_00005_00011", "dPtHard_00011_00021", "dPtHard_00021_00036", "dPtHard_00036_00057", "dPtHard_00057_00084",
    "dPtHard_00084_00117", "dPtHard_00117_00152", "dPtHard_00152_00191", "dPtHard_00191_00234", "dPtHard_00234_INFTY" };

  TFile *file = 0;
  TH2D *hMyJet = 0;
  TH2D *hMyTrg = 0;
  Bool_t bNew = kTRUE;
  for (Int_t i=nHardI; i<nHardF; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sHard[i].Data()), "READ");
    TH1D *hSum = (TH1D*)file->Get(Form("hSum%s",sTrig.Data()));
    Int_t kEntries = hSum->GetEntries();
    Double_t dSum  = hSum->GetBinContent(1);
    cout << "Sum = " << dSum << ", Entries = " << kEntries << endl;
    if (dSum==0.) continue;

    TH2D *hJet = (TH2D*)file->Get(Form("hJet%s",sTrig.Data()));
    hJet->SetDirectory(0);
    hJet->SetName(Form("hJet_%d",i));
    hJet->Scale(1./dSum);

    TH2D *hTrg = (TH2D*)file->Get(Form("hTrg%s",sTrig.Data()));
    hTrg->SetDirectory(0);
    hTrg->SetName(Form("hJet_%d",i));
    hTrg->Scale(1./dSum);
    file->Close();

    if (bNew) {
      hMyJet = (TH2D*)hJet->Clone("hMyJet"); hMyJet->Reset();
      hMyTrg = (TH2D*)hTrg->Clone("hMyTrg"); hMyTrg->Reset();
      bNew = kFALSE;
    }

    hMyJet->Add(hJet);
    hMyTrg->Add(hTrg);
  }

  if (bt) return;
  file = TFile::Open("AnalysisOutputs.root", "NEW");
  hMyJet->Write();
  hMyTrg->Write();
  file->Close();
}
