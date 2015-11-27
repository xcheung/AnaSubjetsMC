void Plot2smCorr()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/mass/AnalysisOutputs_Dsm_py8_JetR05_SjeR01.root", "READ");
  TH2D *h5py8 = (TH2D*)file->Get("hJet2sm"); h5py8->SetName("h5py8"); h5py8->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_qpy_JetR05_SjeR01.root", "READ");
  TH2D *h5qpy = (TH2D*)file->Get("hJet2sm"); h5qpy->SetName("h5qpy"); h5qpy->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_med_JetR05_SjeR01.root", "READ");
  TH2D *h5med = (TH2D*)file->Get("hJet2sm"); h5med->SetName("h5med"); h5med->SetDirectory(0);
  file->Close();


  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_py8_JetR04_SjeR01.root", "READ");
  TH2D *h4py8 = (TH2D*)file->Get("hJet2sm"); h4py8->SetName("h4py8"); h4py8->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_qpy_JetR04_SjeR01.root", "READ");
  TH2D *h4qpy = (TH2D*)file->Get("hJet2sm"); h4qpy->SetName("h4qpy"); h4qpy->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_med_JetR04_SjeR01.root", "READ");
  TH2D *h4med = (TH2D*)file->Get("hJet2sm"); h4med->SetName("h4med"); h4med->SetDirectory(0);
  file->Close();
//=============================================================================

  const Double_t dBin[] = { 0., 10., 20., 30., 40., 50., 60., 80., 100., 120., 150., 200., 250., 300., 350., 400., 500. };
  const Int_t nBin = sizeof(dBin) / sizeof(Double_t) -1;

  TH2DnormY(h5py8); TH2DnormY(h4py8);
  TH2DnormY(h5qpy); TH2DnormY(h4qpy);
  TH2DnormY(h5med); TH2DnormY(h4med);

  TProfile *h5py8M = h5py8->ProfileX("h5py8M"); TProfile *h4py8M = h4py8->ProfileX("h4py8M");
  TProfile *h5qpyM = h5qpy->ProfileX("h5qpyM"); TProfile *h4qpyM = h4qpy->ProfileX("h4qpyM");
  TProfile *h5medM = h5med->ProfileX("h5medM"); TProfile *h4medM = h4med->ProfileX("h4medM");

  TH1D *h5py8Mr = h5py8M->Rebin(nBin, "h5py8Mr", dBin); TH1D *h4py8Mr = h4py8M->Rebin(nBin, "h4py8Mr", dBin);
  TH1D *h5qpyMr = h5qpyM->Rebin(nBin, "h5qpyMr", dBin); TH1D *h4qpyMr = h4qpyM->Rebin(nBin, "h4qpyMr", dBin);
  TH1D *h5medMr = h5medM->Rebin(nBin, "h5medMr", dBin); TH1D *h4medMr = h4medM->Rebin(nBin, "h4medMr", dBin);

  TGraph *g5py8 = new TGraph(h5py8Mr); TGraph *g4py8 = new TGraph(h4py8Mr);
  TGraph *g5qpy = new TGraph(h5qpyMr); TGraph *g4qpy = new TGraph(h4qpyMr);
  TGraph *g5med = new TGraph(h5medMr); TGraph *g4med = new TGraph(h4medMr);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 0., dfux = 400.;
  const Float_t dfly = 0., dfuy = 12.;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T,jet} (GeV/#it{c})";
  const TString stny = "#it{m}_{sj^{2nd}} (GeV/#it{c}^{2})";

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

  can = MakeCanvas("Jet5py82smCorr"); can->SetGridx(); can->SetGridy(); can->SetLogz();
  can->SetTopMargin(0.1); can->SetRightMargin(0.1);
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  h5py8->Draw("COLZ SAME");
  DrawGraph(g5py8, wcl[0], "C");

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.06, 0.94, "PYTHIA 8 at 2.76 TeV, Jet #it{R}=0.5, anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet5qpy2smCorr"); can->SetGridx(); can->SetGridy(); can->SetLogz();
  can->SetTopMargin(0.1); can->SetRightMargin(0.1);
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  h5qpy->Draw("COLZ SAME");
  DrawGraph(g5qpy, wcl[0], "C");

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.06, 0.94, "Q-PYTHIA at 2.76 TeV, Jet #it{R}=0.5, anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet5med2smCorr"); can->SetGridx(); can->SetGridy(); can->SetLogz();
  can->SetTopMargin(0.1); can->SetRightMargin(0.1);
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  h5med->Draw("COLZ SAME");
  DrawGraph(g5med, wcl[0], "C");

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.06, 0.94, "JEWEL+PYTHIA at 2.76 TeV, Jet #it{R}=0.5, anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet4py82smCorr"); can->SetGridx(); can->SetGridy(); can->SetLogz();
  can->SetTopMargin(0.1); can->SetRightMargin(0.1);
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  h4py8->Draw("COLZ SAME");
  DrawGraph(g4py8, wcl[0], "C");

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.06, 0.94, "PYTHIA 8 at 2.76 TeV, Jet #it{R}=0.4, anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet4qpy2smCorr"); can->SetGridx(); can->SetGridy(); can->SetLogz();
  can->SetTopMargin(0.1); can->SetRightMargin(0.1);
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  h4qpy->Draw("COLZ SAME");
  DrawGraph(g4qpy, wcl[0], "C");

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.06, 0.94, "Q-PYTHIA at 2.76 TeV, Jet #it{R}=0.4, anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet4med2smCorr"); can->SetGridx(); can->SetGridy(); can->SetLogz();
  can->SetTopMargin(0.1); can->SetRightMargin(0.1);
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  h4med->Draw("COLZ SAME");
  DrawGraph(g4med, wcl[0], "C");

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.06, 0.94, "JEWEL+PYTHIA at 2.76 TeV, Jet #it{R}=0.4, anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  return;
}

//_____________________________________________________________________________
void TH2DnormY(TH2D *hOrg2)
{
  for (Int_t kx=1; kx<=hOrg2->GetNbinsX(); kx++) {
    Double_t dInt = hOrg2->Integral(kx, kx, 1, hOrg2->GetNbinsY());
    if (dInt==0.) continue;

    for (Int_t ky=1; ky<=hOrg2->GetNbinsY(); ky++) {
      Double_t dBW = hOrg2->GetYaxis()->GetBinWidth(ky);
      hOrg2->SetBinContent(kx, ky, hOrg2->GetBinContent(kx,ky)/dInt/dBW);
      hOrg2->SetBinError(kx, ky, hOrg2->GetBinError(kx,ky)/dInt/dBW);
    }
  }

  return;
}
