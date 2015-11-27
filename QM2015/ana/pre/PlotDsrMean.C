void PlotDsrMean()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnalysisOutputs_Dsr.root", "READ");
  TList *listPy8R5S1 = (TList*)file->Get("list_py8_JetR05_SjeR01");
  TList *listQpyR5S1 = (TList*)file->Get("list_qpy_JetR05_SjeR01");
  TList *listVacR5S1 = (TList*)file->Get("list_vac_JetR05_SjeR01");
  TList *listMedR5S1 = (TList*)file->Get("list_med_JetR05_SjeR01");
  file->Close();


  TH3D *hPy8R5S1 = (TH3D*)listPy8R5S1->FindObject("hJetDsr"); hPy8R5S1->SetName("hPy8R5S1"); hPy8R5S1->RebinY(10);
  TH3D *hQpyR5S1 = (TH3D*)listQpyR5S1->FindObject("hJetDsr"); hQpyR5S1->SetName("hQpyR5S1"); hQpyR5S1->RebinY(10);
  TH3D *hVacR5S1 = (TH3D*)listVacR5S1->FindObject("hJetDsr"); hVacR5S1->SetName("hVacR5S1"); hVacR5S1->RebinY(10);
  TH3D *hMedR5S1 = (TH3D*)listMedR5S1->FindObject("hJetDsr"); hMedR5S1->SetName("hMedR5S1"); hMedR5S1->RebinY(10);


  hPy8R5S1->GetXaxis()->SetRange(hPy8R5S1->GetXaxis()->FindBin(20.+1e-6), hPy8R5S1->GetNbinsX());
  TH2D *hPy8R5S1YZ020 = hPy8R5S1->Project3D("hPy8R5S1020_yz");

  hQpyR5S1->GetXaxis()->SetRange(hQpyR5S1->GetXaxis()->FindBin(20.+1e-6), hQpyR5S1->GetNbinsX());
  TH2D *hQpyR5S1YZ020 = hQpyR5S1->Project3D("hQpyR5S1020_yz");

  hVacR5S1->GetXaxis()->SetRange(hVacR5S1->GetXaxis()->FindBin(20.+1e-6), hVacR5S1->GetNbinsX());
  TH2D *hVacR5S1YZ020 = hVacR5S1->Project3D("hVacR5S1020_yz");

  hMedR5S1->GetXaxis()->SetRange(hMedR5S1->GetXaxis()->FindBin(20.+1e-6), hMedR5S1->GetNbinsX());
  TH2D *hMedR5S1YZ020 = hMedR5S1->Project3D("hSimR5S1020_yz");


  hPy8R5S1->GetXaxis()->SetRange(hPy8R5S1->GetXaxis()->FindBin(60.+1e-6), hPy8R5S1->GetNbinsX());
  TH2D *hPy8R5S1YZ060 = hPy8R5S1->Project3D("hPy8R5S1060_yz");

  hQpyR5S1->GetXaxis()->SetRange(hQpyR5S1->GetXaxis()->FindBin(60.+1e-6), hQpyR5S1->GetNbinsX());
  TH2D *hQpyR5S1YZ060 = hQpyR5S1->Project3D("hQpyR5S1060_yz");

  hVacR5S1->GetXaxis()->SetRange(hVacR5S1->GetXaxis()->FindBin(60.+1e-6), hVacR5S1->GetNbinsX());
  TH2D *hVacR5S1YZ060 = hVacR5S1->Project3D("hVacR5S1060_yz");

  hMedR5S1->GetXaxis()->SetRange(hMedR5S1->GetXaxis()->FindBin(60.+1e-6), hMedR5S1->GetNbinsX());
  TH2D *hMedR5S1YZ060 = hMedR5S1->Project3D("hSimR5S1060_yz");


  hPy8R5S1->GetXaxis()->SetRange(hPy8R5S1->GetXaxis()->FindBin(120.+1e-6), hPy8R5S1->GetNbinsX());
  TH2D *hPy8R5S1YZ120 = hPy8R5S1->Project3D("hPy8R5S1120_yz");

  hQpyR5S1->GetXaxis()->SetRange(hQpyR5S1->GetXaxis()->FindBin(120.+1e-6), hQpyR5S1->GetNbinsX());
  TH2D *hQpyR5S1YZ120 = hQpyR5S1->Project3D("hQpyR5S1120_yz");

  hVacR5S1->GetXaxis()->SetRange(hVacR5S1->GetXaxis()->FindBin(120.+1e-6), hVacR5S1->GetNbinsX());
  TH2D *hVacR5S1YZ120 = hVacR5S1->Project3D("hVacR5S1120_yz");

  hMedR5S1->GetXaxis()->SetRange(hMedR5S1->GetXaxis()->FindBin(120.+1e-6), hMedR5S1->GetNbinsX());
  TH2D *hMedR5S1YZ120 = hMedR5S1->Project3D("hSimR5S1120_yz");
//=============================================================================

  TProfile *hPy8R5S1YZ020ProfY = hPy8R5S1YZ020->ProfileY("hPy8R5S1YZ020ProfX");
  TProfile *hPy8R5S1YZ060ProfY = hPy8R5S1YZ060->ProfileY("hPy8R5S1YZ060ProfX");
  TProfile *hPy8R5S1YZ120ProfY = hPy8R5S1YZ120->ProfileY("hPy8R5S1YZ120ProfX");

  TProfile *hQpyR5S1YZ020ProfY = hQpyR5S1YZ020->ProfileY("hQpyR5S1YZ020ProfX");
  TProfile *hQpyR5S1YZ060ProfY = hQpyR5S1YZ060->ProfileY("hQpyR5S1YZ060ProfX");
  TProfile *hQpyR5S1YZ120ProfY = hQpyR5S1YZ120->ProfileY("hQpyR5S1YZ120ProfX");

  TProfile *hVacR5S1YZ020ProfY = hVacR5S1YZ020->ProfileY("hVacR5S1YZ020ProfX");
  TProfile *hVacR5S1YZ060ProfY = hVacR5S1YZ060->ProfileY("hVacR5S1YZ060ProfX");
  TProfile *hVacR5S1YZ120ProfY = hVacR5S1YZ120->ProfileY("hVacR5S1YZ120ProfX");

  TProfile *hMedR5S1YZ020ProfY = hMedR5S1YZ020->ProfileY("hMedR5S1YZ020ProfX");
  TProfile *hMedR5S1YZ060ProfY = hMedR5S1YZ060->ProfileY("hMedR5S1YZ060ProfX");
  TProfile *hMedR5S1YZ120ProfY = hMedR5S1YZ120->ProfileY("hMedR5S1YZ120ProfX");
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 0.,   dfux = 1.;
  const Float_t dfly = 0.15, dfuy = 0.4;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#Delta#it{z}_{sj}";
  const TString stny = "<#Delta#it{R}_{sj} / 2#it{R}>";

  TH1D *hSE = new TH1D("hSE", "", 10., 0., 10.);
  hSE->SetLineWidth(2);
  hSE->SetLineColor(wcl[0]);
  hSE->SetMarkerStyle(wmk[0]);
  hSE->SetMarkerColor(wcl[0]);

  TH1D *hME = new TH1D("hME", "", 10., 0., 10.);
  hME->SetLineWidth(2);
  hME->SetLineColor(wcl[0]);
  hME->SetMarkerStyle(wmk[2]);
  hME->SetMarkerColor(wcl[0]);
//=============================================================================

  can = MakeCanvas("DsrR05S1X020Mean"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1YZ020ProfY, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1YZ020ProfY, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1YZ020ProfY, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1YZ020ProfY, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1YZ020ProfY, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1YZ020ProfY, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1YZ020ProfY, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1YZ020ProfY, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>20 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DsrR05S1X060Mean"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1YZ060ProfY, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1YZ060ProfY, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1YZ060ProfY, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1YZ060ProfY, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1YZ060ProfY, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1YZ060ProfY, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1YZ060ProfY, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1YZ060ProfY, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>60 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DsrR05S1X120Mean"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1YZ120ProfY, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1YZ120ProfY, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1YZ120ProfY, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1YZ120ProfY, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1YZ120ProfY, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1YZ120ProfY, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1YZ120ProfY, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1YZ120ProfY, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>120 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  return;
}
