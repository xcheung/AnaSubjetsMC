void PlotDrmCorr()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();

 const TString sJetTag = "120<#it{p}_{T,jet}<150 GeV/#it{c}";
//=============================================================================

  TFile *file = TFile::Open("data/mass/AnalysisOutputs_Dsm_py8_JetR05_SjeR01.root", "READ");
  TH2D *h5py8 = (TH2D*)file->Get("hDfrDdm120"); h5py8->SetName("h5py8"); h5py8->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_qpy_JetR05_SjeR01.root", "READ");
  TH2D *h5qpy = (TH2D*)file->Get("hDfrDdm120"); h5qpy->SetName("h5qpy"); h5qpy->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_med_JetR05_SjeR01.root", "READ");
  TH2D *h5med = (TH2D*)file->Get("hDfrDdm120"); h5med->SetName("h5med"); h5med->SetDirectory(0);
  file->Close();


  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_py8_JetR04_SjeR01.root", "READ");
  TH2D *h4py8 = (TH2D*)file->Get("hDfrDdm120"); h4py8->SetName("h4py8"); h4py8->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_qpy_JetR04_SjeR01.root", "READ");
  TH2D *h4qpy = (TH2D*)file->Get("hDfrDdm120"); h4qpy->SetName("h4qpy"); h4qpy->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_Dsm_med_JetR04_SjeR01.root", "READ");
  TH2D *h4med = (TH2D*)file->Get("hDfrDdm120"); h4med->SetName("h4med"); h4med->SetDirectory(0);
  file->Close();
//=============================================================================

  const Double_t dBin[] = { 0., 0.1, 0.3, 0.5, 0.8, 1.2 };
  const Int_t nBin = sizeof(dBin) / sizeof(Double_t) -1;

  h5py8->RebinX(50); h4py8->RebinX(50);
  h5qpy->RebinX(50); h4qpy->RebinX(50);
  h5med->RebinX(50); h4med->RebinX(50);

  TH1D *h5py8M = SetRMS(h5py8,"h5py8M"); TH1D *h4py8M = SetRMS(h4py8,"h4py8M");
  TH1D *h5qpyM = SetRMS(h5qpy,"h5qpyM"); TH1D *h4qpyM = SetRMS(h4qpy,"h4qpyM");
  TH1D *h5medM = SetRMS(h5med,"h5medM"); TH1D *h4medM = SetRMS(h4med,"h4medM");

  TGraph *g5py8 = new TGraph(h5py8M); TGraph *g4py8 = new TGraph(h4py8M);
  TGraph *g5qpy = new TGraph(h5qpyM); TGraph *g4qpy = new TGraph(h4qpyM);
  TGraph *g5med = new TGraph(h5medM); TGraph *g4med = new TGraph(h4medM);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 0.2, dfux = 1.;
  const Float_t dfly = 2., dfuy = 15.;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{R}(sj^{1st},sj^{2nd})";
  const TString stny = "#sigma(m_{jet}-m_{sj}) (GeV/#it{c}^{2})";

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

  can = MakeCanvas("Jet5py8DrmRMS"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawGraph(g5py8, wcl[3], "C");
  DrawGraph(g5qpy, wcl[1], "C");
  DrawGraph(g5med, wcl[5], "C");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(g5py8, "PYTHIA 8", "L")->SetTextSizePixels(24);
  leg->AddEntry(g5qpy, "Q-PYTHIA", "L")->SetTextSizePixels(24);
  leg->AddEntry(g5med, "JEWEL+PYTHIA", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet #it{R}=0.5, anti-#it{k}_{T}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.84, sJetTag.Data());
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet4py8DrmRMS"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawGraph(g4py8, wcl[3], "C");
  DrawGraph(g4qpy, wcl[1], "C");
  DrawGraph(g4med, wcl[5], "C");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(g4py8, "PYTHIA 8", "L")->SetTextSizePixels(24);
  leg->AddEntry(g4qpy, "Q-PYTHIA", "L")->SetTextSizePixels(24);
  leg->AddEntry(g4med, "JEWEL+PYTHIA", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet #it{R}=0.4, anti-#it{k}_{T}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.84, sJetTag.Data());
  CanvasEnd(can);
//=============================================================================



  return;
}

//_____________________________________________________________________________
TH1D *SetRMS(TH2D *h2, const TString s)
{
  TH1D *h = h2->ProjectionX(s.Data()); h->Reset();
  for (Int_t kx=1; kx<=h2->GetNbinsX(); kx++) {
    TH1D *hTmp = h2->ProjectionY(Form("hTmp_%d",kx), kx, kx);

    if (hTmp->Integral()<=0.)
      h->SetBinContent(kx, 0.);
    else
      h->SetBinContent(kx, hTmp->GetRMS());

      cout << h->GetBinContent(kx) << endl;
    delete hTmp; hTmp = 0;
  }

  return h;
}
