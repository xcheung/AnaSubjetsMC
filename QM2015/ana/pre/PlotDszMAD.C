void PlotDszMAD()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnalysisOutputs_Dsz.root", "READ");
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

  TH1D *hPy8R4S1 = (TH1D*)listPy8R4S1->FindObject("hJetDsz_MAD"); hPy8R4S1->SetName("hPy8R4S1");
  TH1D *hPy8R4S2 = (TH1D*)listPy8R4S2->FindObject("hJetDsz_MAD"); hPy8R4S2->SetName("hPy8R4S2");
  TH1D *hPy8R4S3 = (TH1D*)listPy8R4S3->FindObject("hJetDsz_MAD"); hPy8R4S3->SetName("hPy8R4S3");
  TH1D *hPy8R5S1 = (TH1D*)listPy8R5S1->FindObject("hJetDsz_MAD"); hPy8R5S1->SetName("hPy8R5S1");
  TH1D *hPy8R5S2 = (TH1D*)listPy8R5S2->FindObject("hJetDsz_MAD"); hPy8R5S2->SetName("hPy8R5S2");
  TH1D *hPy8R5S3 = (TH1D*)listPy8R5S3->FindObject("hJetDsz_MAD"); hPy8R5S3->SetName("hPy8R5S3");
  TH1D *hPy8R5S4 = (TH1D*)listPy8R5S4->FindObject("hJetDsz_MAD"); hPy8R5S4->SetName("hPy8R5S4");

  TH1D *hVacR4S1 = (TH1D*)listVacR4S1->FindObject("hJetDsz_MAD"); hVacR4S1->SetName("hVacR4S1");
  TH1D *hVacR4S2 = (TH1D*)listVacR4S2->FindObject("hJetDsz_MAD"); hVacR4S2->SetName("hVacR4S2");
  TH1D *hVacR4S3 = (TH1D*)listVacR4S3->FindObject("hJetDsz_MAD"); hVacR4S3->SetName("hVacR4S3");
  TH1D *hVacR5S1 = (TH1D*)listVacR5S1->FindObject("hJetDsz_MAD"); hVacR5S1->SetName("hVacR5S1");
  TH1D *hVacR5S2 = (TH1D*)listVacR5S2->FindObject("hJetDsz_MAD"); hVacR5S2->SetName("hVacR5S2");
  TH1D *hVacR5S3 = (TH1D*)listVacR5S3->FindObject("hJetDsz_MAD"); hVacR5S3->SetName("hVacR5S3");
  TH1D *hVacR5S4 = (TH1D*)listVacR5S4->FindObject("hJetDsz_MAD"); hVacR5S4->SetName("hVacR5S4");

  TH1D *hMedR4S1 = (TH1D*)listMedR4S1->FindObject("hJetDsz_MAD"); hMedR4S1->SetName("hMedR4S1");
  TH1D *hMedR4S2 = (TH1D*)listMedR4S2->FindObject("hJetDsz_MAD"); hMedR4S2->SetName("hMedR4S2");
  TH1D *hMedR4S3 = (TH1D*)listMedR4S3->FindObject("hJetDsz_MAD"); hMedR4S3->SetName("hMedR4S3");
  TH1D *hMedR5S1 = (TH1D*)listMedR5S1->FindObject("hJetDsz_MAD"); hMedR5S1->SetName("hMedR5S1");
  TH1D *hMedR5S2 = (TH1D*)listMedR5S2->FindObject("hJetDsz_MAD"); hMedR5S2->SetName("hMedR5S2");
  TH1D *hMedR5S3 = (TH1D*)listMedR5S3->FindObject("hJetDsz_MAD"); hMedR5S3->SetName("hMedR5S3");
  TH1D *hMedR5S4 = (TH1D*)listMedR5S4->FindObject("hJetDsz_MAD"); hMedR5S4->SetName("hMedR5S4");
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 0., dfux = 500.;
  const Float_t dfly = 2e-3, dfuy = 2.;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T,jet} (GeV/#it{c})";
  const TString stny = "#Delta#it{z}_{sj}^{MAD}";

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

  can = MakeCanvas("DszPy8R04_MAD"); can->SetGridx(); can->SetGridy(); can->SetLogy();
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

  can = MakeCanvas("DszPy8R05_MAD"); can->SetGridx(); can->SetGridy(); can->SetLogy();
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

  can = MakeCanvas("DszVacR04_MAD"); can->SetGridx(); can->SetGridy(); can->SetLogy();
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

  can = MakeCanvas("DszVacR05_MAD"); can->SetGridx(); can->SetGridy(); can->SetLogy();
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

  can = MakeCanvas("DszMedR04_MAD"); can->SetGridx(); can->SetGridy(); can->SetLogy();
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

  can = MakeCanvas("DszMedR05_MAD"); can->SetGridx(); can->SetGridy(); can->SetLogy();
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
