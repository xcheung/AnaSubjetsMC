{
  Bool_t bt = kFALSE;
  const Int_t nHardI = 6;
  const Int_t nHardF = 10;
  const TString sPath = "data/inclAJ/outputs/qp6_JetR05_SjeR01/120050";

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
  TH2D *hMyAJ = 0;
  Bool_t bNew = kTRUE;
  for (Int_t i=nHardI; i<nHardF; i++) {
    file = TFile::Open(Form("%s/AnalysisOutputs_%s.root",sPath.Data(),sHard[i].Data()), "READ");
    TH1D *hSum = (TH1D*)file->Get("hSum");
    Int_t kEntries = hSum->GetEntries();
    Double_t dSum  = hSum->GetBinContent(1);
    cout << "Sum = " << dSum << ", Entries = " << kEntries << endl;
    if (dSum==0.) continue;

    TH2D *hAJ = (TH2D*)file->Get("hAJ");
    hAJ->SetDirectory(0);
    hAJ->SetName(Form("hAJ_%d",i));
    hAJ->Scale(1./dSum);
    file->Close();

    if (bNew) {
      hMyAJ = (TH2D*)hAJ->Clone("hMyAJ");
      hMyAJ->Reset();
      bNew = kFALSE;
    }

    hMyAJ->Add(hAJ);
  }

  if (bt) return;
  file = TFile::Open("AnalysisOutputs.root", "NEW");
  hMyAJ->Write();
  file->Close();
}
