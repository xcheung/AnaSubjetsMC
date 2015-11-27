void PlotJetPt()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnalysisResults_vac_JetR05_skTR01.root", "READ");
  TH2D *hJetPtEtaVac = (TH2D*)file->Get("hJetPtEta"); hJetPtEtaVac->SetName("hJetPtEtaVac"); hJetPtEtaVac->SetDirectory(0);
  TH2D *hLjePtEtaVac = (TH2D*)file->Get("hLjePtEta"); hLjePtEtaVac->SetName("hLjePtEtaVac"); hLjePtEtaVac->SetDirectory(0);
  TH2D *hNjePtEtaVac = (TH2D*)file->Get("hNjePtEta"); hNjePtEtaVac->SetName("hNjePtEtaVac"); hNjePtEtaVac->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/AnalysisResults_med_JetR05_skTR01.root", "READ");
  TH2D *hJetPtEtaMed = (TH2D*)file->Get("hJetPtEta"); hJetPtEtaMed->SetName("hJetPtEtaMed"); hJetPtEtaMed->SetDirectory(0);
  TH2D *hLjePtEtaMed = (TH2D*)file->Get("hLjePtEta"); hLjePtEtaMed->SetName("hLjePtEtaMed"); hLjePtEtaMed->SetDirectory(0);
  TH2D *hNjePtEtaMed = (TH2D*)file->Get("hNjePtEta"); hNjePtEtaMed->SetName("hNjePtEtaMed"); hNjePtEtaMed->SetDirectory(0);
  file->Close();
//=============================================================================

  TH1D *hJetPtVac = hJetPtEtaVac->ProjectionX("hJetPtVac");
  TH1D *hJetPtMed = hJetPtEtaMed->ProjectionX("hJetPtMed");

  TH1D *hLjePtVac = hLjePtEtaVac->ProjectionX("hLjePtVac");
  TH1D *hLjePtMed = hLjePtEtaMed->ProjectionX("hLjePtMed");

  TH1D *hNjePtVac = hNjePtEtaVac->ProjectionX("hNjePtVac");
  TH1D *hNjePtMed = hNjePtEtaMed->ProjectionX("hNjePtMed");

  hJetPtVac->Rebin(10); hJetPtVac->Scale(1./5.);
  hJetPtMed->Rebin(10); hJetPtMed->Scale(1./5.);

  hLjePtVac->Rebin(10); hLjePtVac->Scale(1./5.);
  hLjePtMed->Rebin(10); hLjePtMed->Scale(1./5.);

  hNjePtVac->Rebin(10); hNjePtVac->Scale(1./5.);
  hNjePtMed->Rebin(10); hNjePtMed->Scale(1./5.);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 10., dfux = 500.;
  const Float_t dfly = 8e-13, dfuy = 8.;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T,jet} (GeV/#it{c})";
  const TString stny = "d#sigma/d#it{p}_{T} (mb/GeV/#it{c})";

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

  can = MakeCanvas("JetPtVac"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hJetPtVac, wcl[0], wmk[0], "SAME");
  DrawHisto(hLjePtVac, wcl[1], wmk[0], "SAME");
  DrawHisto(hNjePtVac, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hJetPtVac, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hLjePtVac, "Leading", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hNjePtVac, "Sub-leading", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, vacuum, 2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<2");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("JetPtMed"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hJetPtMed, wcl[0], wmk[0], "SAME");
  DrawHisto(hLjePtMed, wcl[1], wmk[0], "SAME");
  DrawHisto(hNjePtMed, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hJetPtMed, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hLjePtMed, "Leading", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hNjePtMed, "Sub-leading", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, medium, 2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<2");
  CanvasEnd(can);
//=============================================================================

  const Double_t dBins[] = { 5., 10., 20., 30., 50., 80., 120., 160., 200., 250., 300., 400., 500. };
  const Int_t nBins = sizeof(dBins) / sizeof(Double_t) - 1;

  TH1D *hJetPtVacRB = hJetPtVac->Rebin(nBins, "hJetPtVacRB", dBins);
  TH1D *hJetPtMedRB = hJetPtMed->Rebin(nBins, "hJetPtMedRB", dBins); hJetPtMedRB->Divide(hJetPtVacRB);

  TH1D *hLjePtVacRB = hLjePtVac->Rebin(nBins, "hLjePtVacRB", dBins);
  TH1D *hLjePtMedRB = hLjePtMed->Rebin(nBins, "hLjePtMedRB", dBins); hLjePtMedRB->Divide(hLjePtVacRB);

  TH1D *hNjePtVacRB = hNjePtVac->Rebin(nBins, "hNjePtVacRB", dBins);
  TH1D *hNjePtMedRB = hNjePtMed->Rebin(nBins, "hNjePtMedRB", dBins); hNjePtMedRB->Divide(hNjePtVacRB);

  can = MakeCanvas("JetPtRAA"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx, 0., dfux, 1.); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, "#it{R}_{AA}");
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hJetPtMedRB, wcl[0], wmk[0], "SAME");
  DrawHisto(hLjePtMedRB, wcl[1], wmk[0], "SAME");
  DrawHisto(hNjePtMedRB, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hJetPtMedRB, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hLjePtMedRB, "Leading", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hNjePtMedRB, "Sub-leading", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, 2.76 TeV, |#eta|<2.6");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<2");
  CanvasEnd(can);
//=============================================================================

  return;
}
