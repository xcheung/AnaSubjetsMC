void PlotJe2Eta()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnalysisResults_vac_JetR05_skTR01.root", "READ");
  TH2D *hJetPtEtaVac = (TH2D*)file->Get("hJe2PtEta"); hJetPtEtaVac->SetName("hJetPtEtaVac"); hJetPtEtaVac->SetDirectory(0);
  TH2D *hLjePtEtaVac = (TH2D*)file->Get("hLj2PtEta"); hLjePtEtaVac->SetName("hLjePtEtaVac"); hLjePtEtaVac->SetDirectory(0);
  TH2D *hNjePtEtaVac = (TH2D*)file->Get("hNj2PtEta"); hNjePtEtaVac->SetName("hNjePtEtaVac"); hNjePtEtaVac->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/AnalysisResults_med_JetR05_skTR01.root", "READ");
  TH2D *hJetPtEtaMed = (TH2D*)file->Get("hJe2PtEta"); hJetPtEtaMed->SetName("hJetPtEtaMed"); hJetPtEtaMed->SetDirectory(0);
  TH2D *hLjePtEtaMed = (TH2D*)file->Get("hLj2PtEta"); hLjePtEtaMed->SetName("hLjePtEtaMed"); hLjePtEtaMed->SetDirectory(0);
  TH2D *hNjePtEtaMed = (TH2D*)file->Get("hNj2PtEta"); hNjePtEtaMed->SetName("hNjePtEtaMed"); hNjePtEtaMed->SetDirectory(0);
  file->Close();
//=============================================================================

  TH1D *hJetEtaVacI = hJetPtEtaVac->ProjectionY("hJetEtaVacI");
  TH1D *hJetEtaMedI = hJetPtEtaMed->ProjectionY("hJetEtaMedI");

  TH1D *hLjeEtaVacI = hLjePtEtaVac->ProjectionY("hLjeEtaVacI");
  TH1D *hLjeEtaMedI = hLjePtEtaMed->ProjectionY("hLjeEtaMedI");

  TH1D *hNjeEtaVacI = hNjePtEtaVac->ProjectionY("hNjeEtaVacI");
  TH1D *hNjeEtaMedI = hNjePtEtaMed->ProjectionY("hNjeEtaMedI");


  TH1D *hJetEtaVacL = hJetPtEtaVac->ProjectionY("hJetEtaVacL", hJetPtEtaVac->GetXaxis()->FindBin(15.+1e-6), hJetPtEtaVac->GetXaxis()->FindBin(25.-1e-6));
  TH1D *hJetEtaMedL = hJetPtEtaMed->ProjectionY("hJetEtaMedL", hJetPtEtaMed->GetXaxis()->FindBin(15.+1e-6), hJetPtEtaMed->GetXaxis()->FindBin(25.-1e-6));

  TH1D *hLjeEtaVacL = hLjePtEtaVac->ProjectionY("hLjeEtaVacL", hLjePtEtaVac->GetXaxis()->FindBin(15.+1e-6), hLjePtEtaVac->GetXaxis()->FindBin(25.-1e-6));
  TH1D *hLjeEtaMedL = hLjePtEtaMed->ProjectionY("hLjeEtaMedL", hLjePtEtaMed->GetXaxis()->FindBin(15.+1e-6), hLjePtEtaMed->GetXaxis()->FindBin(25.-1e-6));

  TH1D *hNjeEtaVacL = hNjePtEtaVac->ProjectionY("hNjeEtaVacL", hNjePtEtaVac->GetXaxis()->FindBin(15.+1e-6), hNjePtEtaVac->GetXaxis()->FindBin(25.-1e-6));
  TH1D *hNjeEtaMedL = hNjePtEtaMed->ProjectionY("hNjeEtaMedL", hNjePtEtaMed->GetXaxis()->FindBin(15.+1e-6), hNjePtEtaMed->GetXaxis()->FindBin(25.-1e-6));


  TH1D *hJetEtaVacM = hJetPtEtaVac->ProjectionY("hJetEtaVacM", hJetPtEtaVac->GetXaxis()->FindBin(45.+1e-6), hJetPtEtaVac->GetXaxis()->FindBin(55.-1e-6));
  TH1D *hJetEtaMedM = hJetPtEtaMed->ProjectionY("hJetEtaMedM", hJetPtEtaMed->GetXaxis()->FindBin(45.+1e-6), hJetPtEtaMed->GetXaxis()->FindBin(55.-1e-6));

  TH1D *hLjeEtaVacM = hLjePtEtaVac->ProjectionY("hLjeEtaVacM", hLjePtEtaVac->GetXaxis()->FindBin(45.+1e-6), hLjePtEtaVac->GetXaxis()->FindBin(55.-1e-6));
  TH1D *hLjeEtaMedM = hLjePtEtaMed->ProjectionY("hLjeEtaMedM", hLjePtEtaMed->GetXaxis()->FindBin(45.+1e-6), hLjePtEtaMed->GetXaxis()->FindBin(55.-1e-6));

  TH1D *hNjeEtaVacM = hNjePtEtaVac->ProjectionY("hNjeEtaVacM", hNjePtEtaVac->GetXaxis()->FindBin(45.+1e-6), hNjePtEtaVac->GetXaxis()->FindBin(55.-1e-6));
  TH1D *hNjeEtaMedM = hNjePtEtaMed->ProjectionY("hNjeEtaMedM", hNjePtEtaMed->GetXaxis()->FindBin(45.+1e-6), hNjePtEtaMed->GetXaxis()->FindBin(55.-1e-6));


  TH1D *hJetEtaVacH = hJetPtEtaVac->ProjectionY("hJetEtaVacH", hJetPtEtaVac->GetXaxis()->FindBin(90.+1e-6), hJetPtEtaVac->GetXaxis()->FindBin(110.-1e-6));
  TH1D *hJetEtaMedH = hJetPtEtaMed->ProjectionY("hJetEtaMedH", hJetPtEtaMed->GetXaxis()->FindBin(90.+1e-6), hJetPtEtaMed->GetXaxis()->FindBin(110.-1e-6));

  TH1D *hLjeEtaVacH = hLjePtEtaVac->ProjectionY("hLjeEtaVacH", hLjePtEtaVac->GetXaxis()->FindBin(90.+1e-6), hLjePtEtaVac->GetXaxis()->FindBin(110.-1e-6));
  TH1D *hLjeEtaMedH = hLjePtEtaMed->ProjectionY("hLjeEtaMedH", hLjePtEtaMed->GetXaxis()->FindBin(90.+1e-6), hLjePtEtaMed->GetXaxis()->FindBin(110.-1e-6));

  TH1D *hNjeEtaVacH = hNjePtEtaVac->ProjectionY("hNjeEtaVacH", hNjePtEtaVac->GetXaxis()->FindBin(90.+1e-6), hNjePtEtaVac->GetXaxis()->FindBin(110.-1e-6));
  TH1D *hNjeEtaMedH = hNjePtEtaMed->ProjectionY("hNjeEtaMedH", hNjePtEtaMed->GetXaxis()->FindBin(90.+1e-6), hNjePtEtaMed->GetXaxis()->FindBin(110.-1e-6));


  hJetEtaVacI->Scale(1./hJetEtaVacI->Integral()); NormBinningHistogram(hJetEtaVacI);
  hLjeEtaVacI->Scale(1./hLjeEtaVacI->Integral()); NormBinningHistogram(hLjeEtaVacI);
  hNjeEtaVacI->Scale(1./hNjeEtaVacI->Integral()); NormBinningHistogram(hNjeEtaVacI);

  hJetEtaMedI->Scale(1./hJetEtaMedI->Integral()); NormBinningHistogram(hJetEtaMedI);
  hLjeEtaMedI->Scale(1./hLjeEtaMedI->Integral()); NormBinningHistogram(hLjeEtaMedI);
  hNjeEtaMedI->Scale(1./hNjeEtaMedI->Integral()); NormBinningHistogram(hNjeEtaMedI);


  hJetEtaVacL->Scale(2./hJetEtaVacL->Integral()); NormBinningHistogram(hJetEtaVacL);
  hLjeEtaVacL->Scale(2./hLjeEtaVacL->Integral()); NormBinningHistogram(hLjeEtaVacL);
  hNjeEtaVacL->Scale(2./hNjeEtaVacL->Integral()); NormBinningHistogram(hNjeEtaVacL);

  hJetEtaMedL->Scale(2./hJetEtaMedL->Integral()); NormBinningHistogram(hJetEtaMedL);
  hLjeEtaMedL->Scale(2./hLjeEtaMedL->Integral()); NormBinningHistogram(hLjeEtaMedL);
  hNjeEtaMedL->Scale(2./hNjeEtaMedL->Integral()); NormBinningHistogram(hNjeEtaMedL);


  hJetEtaVacM->Scale(4./hJetEtaVacM->Integral()); NormBinningHistogram(hJetEtaVacM);
  hLjeEtaVacM->Scale(4./hLjeEtaVacM->Integral()); NormBinningHistogram(hLjeEtaVacM);
  hNjeEtaVacM->Scale(4./hNjeEtaVacM->Integral()); NormBinningHistogram(hNjeEtaVacM);

  hJetEtaMedM->Scale(4./hJetEtaMedM->Integral()); NormBinningHistogram(hJetEtaMedM);
  hLjeEtaMedM->Scale(4./hLjeEtaMedM->Integral()); NormBinningHistogram(hLjeEtaMedM);
  hNjeEtaMedM->Scale(4./hNjeEtaMedM->Integral()); NormBinningHistogram(hNjeEtaMedM);


  hJetEtaVacH->Scale(8./hJetEtaVacH->Integral()); NormBinningHistogram(hJetEtaVacH);
  hLjeEtaVacH->Scale(8./hLjeEtaVacH->Integral()); NormBinningHistogram(hLjeEtaVacH);
  hNjeEtaVacH->Scale(8./hNjeEtaVacH->Integral()); NormBinningHistogram(hNjeEtaVacH);

  hJetEtaMedH->Scale(8./hJetEtaMedH->Integral()); NormBinningHistogram(hJetEtaMedH);
  hLjeEtaMedH->Scale(8./hLjeEtaMedH->Integral()); NormBinningHistogram(hLjeEtaMedH);
  hNjeEtaMedH->Scale(8./hNjeEtaMedH->Integral()); NormBinningHistogram(hNjeEtaMedH);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = -2., dfux = 2.;
  const Float_t dfly = 0., dfuy = 8.;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#eta_{jet}";
  const TString stny = "Probobility density";

  TH1D *hI = new TH1D("hI", "", 10., 0., 10.);
  hI->SetLineWidth(2);
  hI->SetLineColor(wcl[0]);
  hI->SetMarkerStyle(wmk[0]);
  hI->SetMarkerColor(wcl[0]);

  TH1D *hL = new TH1D("hL", "", 10., 0., 10.);
  hL->SetLineWidth(2);
  hL->SetLineColor(wcl[0]);
  hL->SetMarkerStyle(wmk[1]);
  hL->SetMarkerColor(wcl[0]);

  TH1D *hM = new TH1D("hM", "", 10., 0., 10.);
  hM->SetLineWidth(2);
  hM->SetLineColor(wcl[0]);
  hM->SetMarkerStyle(wmk[2]);
  hM->SetMarkerColor(wcl[0]);

  TH1D *hH = new TH1D("hH", "", 10., 0., 10.);
  hH->SetLineWidth(2);
  hH->SetLineColor(wcl[0]);
  hH->SetMarkerStyle(wmk[3]);
  hH->SetMarkerColor(wcl[0]);
//=============================================================================

  can = MakeCanvas("Je2EtaVac"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hJetEtaVacI, wcl[0], wmk[0], "SAME");
  DrawHisto(hLjeEtaVacI, wcl[1], wmk[0], "SAME");
  DrawHisto(hNjeEtaVacI, wcl[2], wmk[0], "SAME");

  DrawHisto(hJetEtaVacL, wcl[0], wmk[1], "SAME");
  DrawHisto(hLjeEtaVacL, wcl[1], wmk[1], "SAME");
  DrawHisto(hNjeEtaVacL, wcl[2], wmk[1], "SAME");

  DrawHisto(hJetEtaVacM, wcl[0], wmk[2], "SAME");
  DrawHisto(hLjeEtaVacM, wcl[1], wmk[2], "SAME");
  DrawHisto(hNjeEtaVacM, wcl[2], wmk[2], "SAME");

  DrawHisto(hJetEtaVacH, wcl[0], wmk[3], "SAME");
  DrawHisto(hLjeEtaVacH, wcl[1], wmk[3], "SAME");
  DrawHisto(hNjeEtaVacH, wcl[2], wmk[3], "SAME");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hJetEtaVacI, "Inclusive", "L")->SetTextSizePixels(24);
  leg->AddEntry(hLjeEtaVacI, "Leading", "L")->SetTextSizePixels(24);
  leg->AddEntry(hNjeEtaVacI, "Sub-leading", "L")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.62, 0.56, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hI, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hL, "15<#it{p}_{T,jet}<25 GeV/#it{c} #times2", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hM, "55<#it{p}_{T,jet}<55 GeV/#it{c} #times4", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hH, "90<#it{p}_{T,jet}<110 GeV/#it{c} #times8", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, vacuum, 2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{N}_{sj}#geq2");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Je2EtaMed"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hJetEtaMedI, wcl[0], wmk[0], "SAME");
  DrawHisto(hLjeEtaMedI, wcl[1], wmk[0], "SAME");
  DrawHisto(hNjeEtaMedI, wcl[2], wmk[0], "SAME");

  DrawHisto(hJetEtaMedL, wcl[0], wmk[1], "SAME");
  DrawHisto(hLjeEtaMedL, wcl[1], wmk[1], "SAME");
  DrawHisto(hNjeEtaMedL, wcl[2], wmk[1], "SAME");

  DrawHisto(hJetEtaMedM, wcl[0], wmk[2], "SAME");
  DrawHisto(hLjeEtaMedM, wcl[1], wmk[2], "SAME");
  DrawHisto(hNjeEtaMedM, wcl[2], wmk[2], "SAME");

  DrawHisto(hJetEtaMedH, wcl[0], wmk[3], "SAME");
  DrawHisto(hLjeEtaMedH, wcl[1], wmk[3], "SAME");
  DrawHisto(hNjeEtaMedH, wcl[2], wmk[3], "SAME");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hJetEtaMedI, "Inclusive", "L")->SetTextSizePixels(24);
  leg->AddEntry(hLjeEtaMedI, "Leading", "L")->SetTextSizePixels(24);
  leg->AddEntry(hNjeEtaMedI, "Sub-leading", "L")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.62, 0.56, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hI, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hL, "15<#it{p}_{T,jet}<25 GeV/#it{c} #times2", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hM, "55<#it{p}_{T,jet}<55 GeV/#it{c} #times4", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hH, "90<#it{p}_{T,jet}<110 GeV/#it{c} #times8", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, medium, 2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{N}_{sj}#geq2");
  CanvasEnd(can);
//=============================================================================


  return;
}
