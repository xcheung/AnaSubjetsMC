void PlotNsjMean()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnalysisOutputs_Nsj.root", "READ");
  TList *listPy8R4S1 = (TList*)file->Get("list_py8_JetR04_SjeR01");
  TList *listPy8R4S2 = (TList*)file->Get("list_py8_JetR04_SjeR02");
  TList *listPy8R4S3 = (TList*)file->Get("list_py8_JetR04_SjeR03");
  TList *listPy8R5S1 = (TList*)file->Get("list_py8_JetR05_SjeR01");
  TList *listPy8R5S2 = (TList*)file->Get("list_py8_JetR05_SjeR02");
  TList *listPy8R5S3 = (TList*)file->Get("list_py8_JetR05_SjeR03");
  TList *listPy8R5S4 = (TList*)file->Get("list_py8_JetR05_SjeR04");

  TList *listVacR4S1 = (TList*)file->Get("list_vac_JetR04_SjeR01");
  TList *listVacR4S2 = (TList*)file->Get("list_vac_JetR04_SjeR02");
  TList *listVacR4S3 = (TList*)file->Get("list_vac_JetR04_SjeR03");
  TList *listVacR5S1 = (TList*)file->Get("list_vac_JetR05_SjeR01");
  TList *listVacR5S2 = (TList*)file->Get("list_vac_JetR05_SjeR02");
  TList *listVacR5S3 = (TList*)file->Get("list_vac_JetR05_SjeR03");
  TList *listVacR5S4 = (TList*)file->Get("list_vac_JetR05_SjeR04");

  TList *listMedR4S1 = (TList*)file->Get("list_med_JetR04_SjeR01");
  TList *listMedR4S2 = (TList*)file->Get("list_med_JetR04_SjeR02");
  TList *listMedR4S3 = (TList*)file->Get("list_med_JetR04_SjeR03");
  TList *listMedR5S1 = (TList*)file->Get("list_med_JetR05_SjeR01");
  TList *listMedR5S2 = (TList*)file->Get("list_med_JetR05_SjeR02");
  TList *listMedR5S3 = (TList*)file->Get("list_med_JetR05_SjeR03");
  TList *listMedR5S4 = (TList*)file->Get("list_med_JetR05_SjeR04");
  file->Close();

  TProfile *hPy8R4S1 = (TProfile*)listPy8R4S1->FindObject("hJetNsj_mean"); hPy8R4S1->SetName("hPy8R4S1");
  TProfile *hPy8R4S2 = (TProfile*)listPy8R4S2->FindObject("hJetNsj_mean"); hPy8R4S2->SetName("hPy8R4S2");
  TProfile *hPy8R4S3 = (TProfile*)listPy8R4S3->FindObject("hJetNsj_mean"); hPy8R4S3->SetName("hPy8R4S3");
  TProfile *hPy8R5S1 = (TProfile*)listPy8R5S1->FindObject("hJetNsj_mean"); hPy8R5S1->SetName("hPy8R5S1");
  TProfile *hPy8R5S2 = (TProfile*)listPy8R5S2->FindObject("hJetNsj_mean"); hPy8R5S2->SetName("hPy8R5S2");
  TProfile *hPy8R5S3 = (TProfile*)listPy8R5S3->FindObject("hJetNsj_mean"); hPy8R5S3->SetName("hPy8R5S3");
  TProfile *hPy8R5S4 = (TProfile*)listPy8R5S4->FindObject("hJetNsj_mean"); hPy8R5S4->SetName("hPy8R5S4");

  TProfile *hVacR4S1 = (TProfile*)listVacR4S1->FindObject("hJetNsj_mean"); hVacR4S1->SetName("hVacR4S1");
  TProfile *hVacR4S2 = (TProfile*)listVacR4S2->FindObject("hJetNsj_mean"); hVacR4S2->SetName("hVacR4S2");
  TProfile *hVacR4S3 = (TProfile*)listVacR4S3->FindObject("hJetNsj_mean"); hVacR4S3->SetName("hVacR4S3");
  TProfile *hVacR5S1 = (TProfile*)listVacR5S1->FindObject("hJetNsj_mean"); hVacR5S1->SetName("hVacR5S1");
  TProfile *hVacR5S2 = (TProfile*)listVacR5S2->FindObject("hJetNsj_mean"); hVacR5S2->SetName("hVacR5S2");
  TProfile *hVacR5S3 = (TProfile*)listVacR5S3->FindObject("hJetNsj_mean"); hVacR5S3->SetName("hVacR5S3");
  TProfile *hVacR5S4 = (TProfile*)listVacR5S4->FindObject("hJetNsj_mean"); hVacR5S4->SetName("hVacR5S4");

  TProfile *hMedR4S1 = (TProfile*)listMedR4S1->FindObject("hJetNsj_mean"); hMedR4S1->SetName("hMedR4S1");
  TProfile *hMedR4S2 = (TProfile*)listMedR4S2->FindObject("hJetNsj_mean"); hMedR4S2->SetName("hMedR4S2");
  TProfile *hMedR4S3 = (TProfile*)listMedR4S3->FindObject("hJetNsj_mean"); hMedR4S3->SetName("hMedR4S3");
  TProfile *hMedR5S1 = (TProfile*)listMedR5S1->FindObject("hJetNsj_mean"); hMedR5S1->SetName("hMedR5S1");
  TProfile *hMedR5S2 = (TProfile*)listMedR5S2->FindObject("hJetNsj_mean"); hMedR5S2->SetName("hMedR5S2");
  TProfile *hMedR5S3 = (TProfile*)listMedR5S3->FindObject("hJetNsj_mean"); hMedR5S3->SetName("hMedR5S3");
  TProfile *hMedR5S4 = (TProfile*)listMedR5S4->FindObject("hJetNsj_mean"); hMedR5S4->SetName("hMedR5S4");
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 0., dfux = 500.;
  const Float_t dfly = 0., dfuy = 15.;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T,jet} (GeV/#it{c})";
  const TString stny = "Number of sub-jets: mean";

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

  can = MakeCanvas("NsjPy8R04_mean"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R4S1, wcl[1], wmk[0], "SAME");
  DrawHisto(hPy8R4S2, wcl[3], wmk[0], "SAME");
  DrawHisto(hPy8R4S3, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.68, 0.66, 0.98, 0.90); SetupLegend(leg);
  leg->AddEntry(hPy8R4S1, "#it{R}_{sub}=0.1", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hPy8R4S2, "#it{R}_{sub}=0.2", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hPy8R4S3, "#it{R}_{sub}=0.3", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA 8, tune 4C, pp #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("NsjPy8R05_mean"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1, wcl[1], wmk[0], "SAME");
  DrawHisto(hPy8R5S2, wcl[3], wmk[0], "SAME");
  DrawHisto(hPy8R5S3, wcl[4], wmk[0], "SAME");
  DrawHisto(hPy8R5S4, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.58, 0.74, 0.98, 0.90); SetupLegend(leg);
  leg->SetNColumns(2);
  leg->AddEntry(hPy8R5S1, "#it{R}_{sub}=0.1", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hPy8R5S2, "#it{R}_{sub}=0.2", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hPy8R5S3, "#it{R}_{sub}=0.3", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hPy8R5S4, "#it{R}_{sub}=0.4", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA 8, tune 4C, pp #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("NsjVacR04_mean"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hVacR4S1, wcl[1], wmk[0], "SAME");
  DrawHisto(hVacR4S2, wcl[3], wmk[0], "SAME");
  DrawHisto(hVacR4S3, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.68, 0.66, 0.98, 0.90); SetupLegend(leg);
  leg->AddEntry(hVacR4S1, "#it{R}_{sub}=0.1", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR4S2, "#it{R}_{sub}=0.2", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR4S3, "#it{R}_{sub}=0.3", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, vacuum, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("NsjVacR05_mean"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy,  stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hVacR5S1, wcl[1], wmk[0], "SAME");
  DrawHisto(hVacR5S2, wcl[3], wmk[0], "SAME");
  DrawHisto(hVacR5S3, wcl[4], wmk[0], "SAME");
  DrawHisto(hVacR5S4, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.58, 0.74, 0.98, 0.90); SetupLegend(leg);
  leg->SetNColumns(2);
  leg->AddEntry(hVacR5S1, "#it{R}_{sub}=0.1", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S2, "#it{R}_{sub}=0.2", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S3, "#it{R}_{sub}=0.3", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S4, "#it{R}_{sub}=0.4", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, vacuum, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("NsjMedR04_mean"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy,  stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hMedR4S1, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR4S2, wcl[3], wmk[0], "SAME");
  DrawHisto(hMedR4S3, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.68, 0.66, 0.98, 0.90); SetupLegend(leg);
  leg->AddEntry(hMedR4S1, "#it{R}_{sub}=0.1", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR4S2, "#it{R}_{sub}=0.2", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR4S3, "#it{R}_{sub}=0.3", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, medium, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("NsjMedR05_mean"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy,  stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hMedR5S1, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S2, wcl[3], wmk[0], "SAME");
  DrawHisto(hMedR5S3, wcl[4], wmk[0], "SAME");
  DrawHisto(hMedR5S4, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.58, 0.74, 0.98, 0.90); SetupLegend(leg);
  leg->SetNColumns(2);
  leg->AddEntry(hMedR5S1, "#it{R}_{sub}=0.1", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S2, "#it{R}_{sub}=0.2", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S3, "#it{R}_{sub}=0.3", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S4, "#it{R}_{sub}=0.4", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, medium, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}");
  CanvasEnd(can);
//=============================================================================

  return;
}
