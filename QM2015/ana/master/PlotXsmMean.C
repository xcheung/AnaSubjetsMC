void PlotXsmMean()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/mass/AnalysisOutputs_Dsm_py8_JetR05_SjeR01.root", "READ");
  TH2D *h5py81 = (TH2D*)file->Get("hJet1sm"); h5py81->SetName("h5py81"); h5py81->SetDirectory(0);
  TH2D *h5py82 = (TH2D*)file->Get("hJet2sm"); h5py82->SetName("h5py82"); h5py82->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_qpy_JetR05_SjeR01.root", "READ");
  TH2D *h5qpy1 = (TH2D*)file->Get("hJet1sm"); h5qpy1->SetName("h5qpy1"); h5qpy1->SetDirectory(0);
  TH2D *h5qpy2 = (TH2D*)file->Get("hJet2sm"); h5qpy2->SetName("h5qpy2"); h5qpy2->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_med_JetR05_SjeR01.root", "READ");
  TH2D *h5med1 = (TH2D*)file->Get("hJet1sm"); h5med1->SetName("h5med1"); h5med1->SetDirectory(0);
  TH2D *h5med2 = (TH2D*)file->Get("hJet2sm"); h5med2->SetName("h5med2"); h5med2->SetDirectory(0);
  file->Close();


  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_py8_JetR04_SjeR01.root", "READ");
  TH2D *h4py81 = (TH2D*)file->Get("hJet1sm"); h4py81->SetName("h4py81"); h4py81->SetDirectory(0);
  TH2D *h4py82 = (TH2D*)file->Get("hJet2sm"); h4py82->SetName("h4py82"); h4py82->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_qpy_JetR04_SjeR01.root", "READ");
  TH2D *h4qpy1 = (TH2D*)file->Get("hJet1sm"); h4qpy1->SetName("h4qpy1"); h4qpy1->SetDirectory(0);
  TH2D *h4qpy2 = (TH2D*)file->Get("hJet2sm"); h4qpy2->SetName("h4qpy2"); h4qpy2->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_med_JetR04_SjeR01.root", "READ");
  TH2D *h4med1 = (TH2D*)file->Get("hJet1sm"); h4med1->SetName("h4med1"); h4med1->SetDirectory(0);
  TH2D *h4med2 = (TH2D*)file->Get("hJet2sm"); h4med2->SetName("h4med2"); h4med2->SetDirectory(0);
  file->Close();
//=============================================================================

  const Double_t dBin[] = { 0., 10., 20., 30., 40., 50., 60., 80., 100., 120., 150., 200., 250., 300., 350., 400., 500. };
  const Int_t nBin = sizeof(dBin) / sizeof(Double_t) -1;

  TProfile *h5py81M = h5py81->ProfileX("h5py81M"); TProfile *h4py81M = h4py81->ProfileX("h4py81M");
  TProfile *h5qpy1M = h5qpy1->ProfileX("h5qpy1M"); TProfile *h4qpy1M = h4qpy1->ProfileX("h4qpy1M");
  TProfile *h5med1M = h5med1->ProfileX("h5med1M"); TProfile *h4med1M = h4med1->ProfileX("h4med1M");

  TProfile *h5py82M = h5py82->ProfileX("h5py82M"); TProfile *h4py82M = h4py82->ProfileX("h4py82M");
  TProfile *h5qpy2M = h5qpy2->ProfileX("h5qpy2M"); TProfile *h4qpy2M = h4qpy2->ProfileX("h4qpy2M");
  TProfile *h5med2M = h5med2->ProfileX("h5med2M"); TProfile *h4med2M = h4med2->ProfileX("h4med2M");


  TH1D *h5py81Mr = h5py81M->Rebin(nBin, "h5py81Mr", dBin); TH1D *h4py81Mr = h4py81M->Rebin(nBin, "h4py81Mr", dBin);
  TH1D *h5qpy1Mr = h5qpy1M->Rebin(nBin, "h5qpy1Mr", dBin); TH1D *h4qpy1Mr = h4qpy1M->Rebin(nBin, "h4qpy1Mr", dBin);
  TH1D *h5med1Mr = h5med1M->Rebin(nBin, "h5med1Mr", dBin); TH1D *h4med1Mr = h4med1M->Rebin(nBin, "h4med1Mr", dBin);

  TH1D *h5py82Mr = h5py82M->Rebin(nBin, "h5py82Mr", dBin); TH1D *h4py82Mr = h4py82M->Rebin(nBin, "h4py82Mr", dBin);
  TH1D *h5qpy2Mr = h5qpy2M->Rebin(nBin, "h5qpy2Mr", dBin); TH1D *h4qpy2Mr = h4qpy2M->Rebin(nBin, "h4qpy2Mr", dBin);
  TH1D *h5med2Mr = h5med2M->Rebin(nBin, "h5med2Mr", dBin); TH1D *h4med2Mr = h4med2M->Rebin(nBin, "h4med2Mr", dBin);


  TGraph *g5py81 = new TGraph(h5py81Mr); TGraph *g4py81 = new TGraph(h4py81Mr);
  TGraph *g5qpy1 = new TGraph(h5qpy1Mr); TGraph *g4qpy1 = new TGraph(h4qpy1Mr);
  TGraph *g5med1 = new TGraph(h5med1Mr); TGraph *g4med1 = new TGraph(h4med1Mr);

  TGraph *g5py82 = new TGraph(h5py82Mr); TGraph *g4py82 = new TGraph(h4py82Mr);
  TGraph *g5qpy2 = new TGraph(h5qpy2Mr); TGraph *g4qpy2 = new TGraph(h4qpy2Mr);
  TGraph *g5med2 = new TGraph(h5med2Mr); TGraph *g4med2 = new TGraph(h4med2Mr);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 0., dfux = 400.;
  const Float_t dfly = 0., dfuy = 15.;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T,jet} (GeV/#it{c})";
  const TString stny = "<#it{m}_{sj}> (GeV/#it{c}^{2})";

  TH1D *hSE = new TH1D("hSE", "", 10., 0., 10.);
  hSE->SetLineWidth(2);
  hSE->SetLineColor(wcl[0]);
  hSE->SetLineStyle(1);

  TH1D *hME = new TH1D("hME", "", 10., 0., 10.);
  hME->SetLineWidth(2);
  hME->SetLineColor(wcl[0]);
  hME->SetLineStyle(7);
//=============================================================================

  can = MakeCanvas("Jet5XsmMean"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawGraph(g5py81, wcl[3], "C");
  DrawGraph(g5qpy1, wcl[1], "C");
  DrawGraph(g5med1, wcl[5], "C");

  g5py82->SetLineStyle(7); DrawGraph(g5py82, wcl[3], "C");
  g5qpy2->SetLineStyle(7); DrawGraph(g5qpy2, wcl[1], "C");
  g5med2->SetLineStyle(7); DrawGraph(g5med2, wcl[5], "C");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(g5py81, "PYTHIA 8", "L")->SetTextSizePixels(24);
  leg->AddEntry(g5qpy1, "Q-PYTHIA", "L")->SetTextSizePixels(24);
  leg->AddEntry(g5med1, "JEWEL+PYTHIA", "L")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.62, 0.72, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hSE, "1st leading", "L")->SetTextSizePixels(24);
  leg->AddEntry(hME, "2nd leading", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet #it{R}=0.5, anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet4XsmMean"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawGraph(g4py81, wcl[3], "C");
  DrawGraph(g4qpy1, wcl[1], "C");
  DrawGraph(g4med1, wcl[5], "C");

  g4py82->SetLineStyle(7); DrawGraph(g4py82, wcl[3], "C");
  g4qpy2->SetLineStyle(7); DrawGraph(g4qpy2, wcl[1], "C");
  g4med2->SetLineStyle(7); DrawGraph(g4med2, wcl[5], "C");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(g4py81, "PYTHIA 8", "L")->SetTextSizePixels(24);
  leg->AddEntry(g4qpy1, "Q-PYTHIA", "L")->SetTextSizePixels(24);
  leg->AddEntry(g4med1, "JEWEL+PYTHIA", "L")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.62, 0.72, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hSE, "1st leading", "L")->SetTextSizePixels(24);
  leg->AddEntry(hME, "2nd leading", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet #it{R}=0.4, anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  return;
}
