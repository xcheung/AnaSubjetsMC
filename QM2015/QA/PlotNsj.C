void PlotNsj()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnalysisResults_vac_JetR05_skTR01.root", "READ");
  TH2D *hJetPtNsjVac = (TH2D*)file->Get("hJetPtNsj"); hJetPtNsjVac->SetName("hJetPtNsjVac"); hJetPtNsjVac->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/AnalysisResults_med_JetR05_skTR01.root", "READ");
  TH2D *hJetPtNsjMed = (TH2D*)file->Get("hJetPtNsj"); hJetPtNsjMed->SetName("hJetPtNsjMed"); hJetPtNsjMed->SetDirectory(0);
  file->Close();
//=============================================================================

  TProfile *hJetNsjVac = hJetPtNsjVac->ProfileX("hJetNsjVac"); hJetNsjVac->Rebin(10);
  TProfile *hJetNsjMed = hJetPtNsjMed->ProfileX("hJetNsjMed"); hJetNsjMed->Rebin(10);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 10., dfux = 500.;
  const Float_t dfly = 0., dfuy = 12.;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T,jet} (GeV/#it{c})";
  const TString stny = "<#it{N}_{sj}>";

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

  can = MakeCanvas("JetNsj"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hJetNsjVac, wcl[3], wmk[0], "SAME");
  DrawHisto(hJetNsjMed, wcl[1], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.72, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hJetNsjVac, "Vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hJetNsjMed, "Medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, vacuum, 2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<2, sub-jet: #it{k}_{T}, #it{R}=0.1");
  CanvasEnd(can);
//=============================================================================

  return;
}
