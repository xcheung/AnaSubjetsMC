void PlotDszRAA()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnalysisOutputs_Dsz.root", "READ");
  TList *listPy8R4S1 = (TList*)file->Get("list_py8_JetR04_SjeR01");
  TList *listQpyR4S1 = (TList*)file->Get("list_qpy_JetR04_SjeR01");
  TList *listVacR4S1 = (TList*)file->Get("list_vac_JetR04_SjeR01");
  TList *listMedR4S1 = (TList*)file->Get("list_med_JetR04_SjeR01");

  TList *listPy8R5S1 = (TList*)file->Get("list_py8_JetR05_SjeR01");
  TList *listQpyR5S1 = (TList*)file->Get("list_qpy_JetR05_SjeR01");
  TList *listVacR5S1 = (TList*)file->Get("list_vac_JetR05_SjeR01");
  TList *listMedR5S1 = (TList*)file->Get("list_med_JetR05_SjeR01");
  file->Close();


  TH2D *hPy8R4S1 = (TH2D*)listPy8R4S1->FindObject("hJetDsz"); hPy8R4S1->SetName("hPy8R4S1");
  TH2D *hQpyR4S1 = (TH2D*)listQpyR4S1->FindObject("hJetDsz"); hQpyR4S1->SetName("hQpyR4S1");
  TH2D *hVacR4S1 = (TH2D*)listVacR4S1->FindObject("hJetDsz"); hVacR4S1->SetName("hVacR4S1");
  TH2D *hMedR4S1 = (TH2D*)listMedR4S1->FindObject("hJetDsz"); hMedR4S1->SetName("hMedR4S1");

  TH2D *hPy8R5S1 = (TH2D*)listPy8R5S1->FindObject("hJetDsz"); hPy8R5S1->SetName("hPy8R5S1");
  TH2D *hQpyR5S1 = (TH2D*)listQpyR5S1->FindObject("hJetDsz"); hQpyR5S1->SetName("hQpyR5S1");
  TH2D *hVacR5S1 = (TH2D*)listVacR5S1->FindObject("hJetDsz"); hVacR5S1->SetName("hVacR5S1");
  TH2D *hMedR5S1 = (TH2D*)listMedR5S1->FindObject("hJetDsz"); hMedR5S1->SetName("hMedR5S1");


  TH1D *hPy8R4S1XA = hPy8R4S1->ProjectionX("hPy8R4S1XA");
  TH1D *hPy8R4S1XL = hPy8R4S1->ProjectionX("hPy8R4S1XL", hPy8R4S1->GetYaxis()->FindBin(0.0+1e-6), hPy8R4S1->GetYaxis()->FindBin(0.8-1e-6));
  TH1D *hPy8R4S1XH = hPy8R4S1->ProjectionX("hPy8R4S1XH", hPy8R4S1->GetYaxis()->FindBin(0.8+1e-6), hPy8R4S1->GetYaxis()->FindBin(1.0-1e-6));

  TH1D *hQpyR4S1XA = hQpyR4S1->ProjectionX("hQpyR4S1XA");
  TH1D *hQpyR4S1XL = hQpyR4S1->ProjectionX("hQpyR4S1XL", hQpyR4S1->GetYaxis()->FindBin(0.0+1e-6), hQpyR4S1->GetYaxis()->FindBin(0.8-1e-6));
  TH1D *hQpyR4S1XH = hQpyR4S1->ProjectionX("hQpyR4S1XH", hQpyR4S1->GetYaxis()->FindBin(0.8+1e-6), hQpyR4S1->GetYaxis()->FindBin(1.0-1e-6));

  TH1D *hVacR4S1XA = hVacR4S1->ProjectionX("hVacR4S1XA");
  TH1D *hVacR4S1XL = hVacR4S1->ProjectionX("hVacR4S1XL", hVacR4S1->GetYaxis()->FindBin(0.0+1e-6), hVacR4S1->GetYaxis()->FindBin(0.8-1e-6));
  TH1D *hVacR4S1XH = hVacR4S1->ProjectionX("hVacR4S1XH", hVacR4S1->GetYaxis()->FindBin(0.8+1e-6), hVacR4S1->GetYaxis()->FindBin(1.0-1e-6));

  TH1D *hMedR4S1XA = hMedR4S1->ProjectionX("hMedR4S1XA");
  TH1D *hMedR4S1XL = hMedR4S1->ProjectionX("hMedR4S1XL", hMedR4S1->GetYaxis()->FindBin(0.0+1e-6), hMedR4S1->GetYaxis()->FindBin(0.8-1e-6));
  TH1D *hMedR4S1XH = hMedR4S1->ProjectionX("hMedR4S1XH", hMedR4S1->GetYaxis()->FindBin(0.8+1e-6), hMedR4S1->GetYaxis()->FindBin(1.0-1e-6));


  TH1D *hPy8R5S1XA = hPy8R5S1->ProjectionX("hPy8R5S1XA");
  TH1D *hPy8R5S1XL = hPy8R5S1->ProjectionX("hPy8R5S1XL", hPy8R5S1->GetYaxis()->FindBin(0.0+1e-6), hPy8R5S1->GetYaxis()->FindBin(0.8-1e-6));
  TH1D *hPy8R5S1XH = hPy8R5S1->ProjectionX("hPy8R5S1XH", hPy8R5S1->GetYaxis()->FindBin(0.8+1e-6), hPy8R5S1->GetYaxis()->FindBin(1.0-1e-6));

  TH1D *hQpyR5S1XA = hQpyR5S1->ProjectionX("hQpyR5S1XA");
  TH1D *hQpyR5S1XL = hQpyR5S1->ProjectionX("hQpyR5S1XL", hQpyR5S1->GetYaxis()->FindBin(0.0+1e-6), hQpyR5S1->GetYaxis()->FindBin(0.8-1e-6));
  TH1D *hQpyR5S1XH = hQpyR5S1->ProjectionX("hQpyR5S1XH", hQpyR5S1->GetYaxis()->FindBin(0.8+1e-6), hQpyR5S1->GetYaxis()->FindBin(1.0-1e-6));

  TH1D *hVacR5S1XA = hVacR5S1->ProjectionX("hVacR5S1XA");
  TH1D *hVacR5S1XL = hVacR5S1->ProjectionX("hVacR5S1XL", hVacR5S1->GetYaxis()->FindBin(0.0+1e-6), hVacR5S1->GetYaxis()->FindBin(0.8-1e-6));
  TH1D *hVacR5S1XH = hVacR5S1->ProjectionX("hVacR5S1XH", hVacR5S1->GetYaxis()->FindBin(0.8+1e-6), hVacR5S1->GetYaxis()->FindBin(1.0-1e-6));

  TH1D *hMedR5S1XA = hMedR5S1->ProjectionX("hMedR5S1XA");
  TH1D *hMedR5S1XL = hMedR5S1->ProjectionX("hMedR5S1XL", hMedR5S1->GetYaxis()->FindBin(0.0+1e-6), hMedR5S1->GetYaxis()->FindBin(0.8-1e-6));
  TH1D *hMedR5S1XH = hMedR5S1->ProjectionX("hMedR5S1XH", hMedR5S1->GetYaxis()->FindBin(0.8+1e-6), hMedR5S1->GetYaxis()->FindBin(1.0-1e-6));



  TH1D *hQpyR4S1RA = (TH1D*)hQpyR4S1XA->Clone("hQpyR4S1RA"); hQpyR4S1RA->Divide(hPy8R4S1XA);
  TH1D *hQpyR4S1RL = (TH1D*)hQpyR4S1XL->Clone("hQpyR4S1RL"); hQpyR4S1RL->Divide(hPy8R4S1XL);
  TH1D *hQpyR4S1RH = (TH1D*)hQpyR4S1XH->Clone("hQpyR4S1RH"); hQpyR4S1RH->Divide(hPy8R4S1XH);

  TH1D *hJelR4S1RA = (TH1D*)hMedR4S1XA->Clone("hJelR4S1RA"); hJelR4S1RA->Divide(hVacR4S1XA);
  TH1D *hJelR4S1RL = (TH1D*)hMedR4S1XL->Clone("hJelR4S1RL"); hJelR4S1RL->Divide(hVacR4S1XL);
  TH1D *hJelR4S1RH = (TH1D*)hMedR4S1XH->Clone("hJelR4S1RH"); hJelR4S1RH->Divide(hVacR4S1XH);


  TH1D *hQpyR5S1RA = (TH1D*)hQpyR5S1XA->Clone("hQpyR5S1RA"); hQpyR5S1RA->Divide(hPy8R5S1XA);
  TH1D *hQpyR5S1RL = (TH1D*)hQpyR5S1XL->Clone("hQpyR5S1RL"); hQpyR5S1RL->Divide(hPy8R5S1XL);
  TH1D *hQpyR5S1RH = (TH1D*)hQpyR5S1XH->Clone("hQpyR5S1RH"); hQpyR5S1RH->Divide(hPy8R5S1XH);

  TH1D *hJelR5S1RA = (TH1D*)hMedR5S1XA->Clone("hJelR5S1RA"); hJelR5S1RA->Divide(hVacR5S1XA);
  TH1D *hJelR5S1RL = (TH1D*)hMedR5S1XL->Clone("hJelR5S1RL"); hJelR5S1RL->Divide(hVacR5S1XL);
  TH1D *hJelR5S1RH = (TH1D*)hMedR5S1XH->Clone("hJelR5S1RH"); hJelR5S1RH->Divide(hVacR5S1XH);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 0., dfux = 500.;
  const Float_t dfly = 0., dfuy = 1.5;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T,jet} (GeV/#it{c})";
  const TString stny = "#it{R}_{AA}";

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

  can = MakeCanvas("DszR04S1RAA"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hQpyR4S1RA, wcl[0], wmk[0], "SAME");
  DrawHisto(hJelR4S1RA, wcl[0], wmk[2], "SAME");

  DrawHisto(hQpyR4S1RL, wcl[1], wmk[0], "SAME");
  DrawHisto(hJelR4S1RL, wcl[1], wmk[2], "SAME");

  DrawHisto(hQpyR4S1RH, wcl[4], wmk[0], "SAME");
  DrawHisto(hJelR4S1RH, wcl[4], wmk[2], "SAME");

  leg = new TLegend(0.62, 0.56, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hQpyR4S1RA, "Inclusive", "L")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR4S1RL, "#Delta#it{z}_{sj}<0.8", "L")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR4S1RH, "#Delta#it{z}_{sj}>0.8", "L")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.62, 0.40, 0.98, 0.56); SetupLegend(leg);
  leg->AddEntry(hSE, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hME, "JEWEL", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DszR05S1RAA"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hQpyR5S1RA, wcl[0], wmk[0], "SAME");
  DrawHisto(hJelR5S1RA, wcl[0], wmk[2], "SAME");

  DrawHisto(hQpyR5S1RL, wcl[1], wmk[0], "SAME");
  DrawHisto(hJelR5S1RL, wcl[1], wmk[2], "SAME");

  DrawHisto(hQpyR5S1RH, wcl[4], wmk[0], "SAME");
  DrawHisto(hJelR5S1RH, wcl[4], wmk[2], "SAME");

  leg = new TLegend(0.62, 0.56, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hQpyR5S1RA, "Inclusive", "L")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1RL, "#Delta#it{z}_{sj}<0.8", "L")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1RH, "#Delta#it{z}_{sj}>0.8", "L")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.62, 0.40, 0.98, 0.56); SetupLegend(leg);
  leg->AddEntry(hSE, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hME, "JEWEL", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  return;
}
