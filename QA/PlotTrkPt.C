void PlotTrkPt()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnalysisResults_vac_JetR05_skTR01.root", "READ");
  TH2D *hTrkPtEtaVac = (TH2D*)file->Get("hTrkPtEta"); hTrkPtEtaVac->SetName("hTrkPtEtaVac"); hTrkPtEtaVac->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/AnalysisResults_med_JetR05_skTR01.root", "READ");
  TH2D *hTrkPtEtaMed = (TH2D*)file->Get("hTrkPtEta"); hTrkPtEtaMed->SetName("hTrkPtEtaMed"); hTrkPtEtaMed->SetDirectory(0);
  file->Close();
//=============================================================================

  TH1D *hTrkPtVac = hTrkPtEtaVac->ProjectionX("hTrkPtVac");
  TH1D *hTrkPtMed = hTrkPtEtaMed->ProjectionX("hTrkPtMed");

  hTrkPtVac->Rebin(10); hTrkPtVac->Scale(1./5.);
  hTrkPtMed->Rebin(10); hTrkPtMed->Scale(1./5.);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 0., dfux = 300.;
  const Float_t dfly = 8e-13, dfuy = 8e2;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
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

  can = MakeCanvas("TrkPt"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hTrkPtVac, wcl[3], wmk[0], "SAME");
  DrawHisto(hTrkPtMed, wcl[1], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.72, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hTrkPtVac, "Vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hTrkPtMed, "Medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, 2.76 TeV, |#eta|<2.6");
  CanvasEnd(can);
//=============================================================================

  const Double_t dBins[] = { 0., 5., 10., 20., 30., 50., 80., 120., 160., 200., 250., 300., 400., 500. };
  const Int_t nBins = sizeof(dBins) / sizeof(Double_t) - 1;

  TH1D *hTrkPtVacRB = hTrkPtVac->Rebin(nBins, "hTrkPtVacRB", dBins);
  TH1D *hTrkPtMedRB = hTrkPtMed->Rebin(nBins, "hTrkPtMedRB", dBins); hTrkPtMedRB->Divide(hTrkPtVacRB);

  can = MakeCanvas("TrkPtRAA"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx, 0., dfux, 2.); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, "#it{R}_{AA}");
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hTrkPtMedRB, wcl[0], wmk[0], "SAME");

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, 2.76 TeV, |#eta|<2.6");
  CanvasEnd(can);
//=============================================================================

  return;
}
