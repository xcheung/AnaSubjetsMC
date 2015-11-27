void PlotDszR05()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/incl/AnalysisOutputs_jet_py8_JetR05_SjeR01.root", "READ");
  TH2D *hpy8 = (TH2D*)file->Get("hJetDsz"); hpy8->SetName("hpy8"); hpy8->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_qpy_JetR05_SjeR01.root", "READ");
  TH2D *hqpy = (TH2D*)file->Get("hJetDsz"); hqpy->SetName("hqpy"); hqpy->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_med_JetR05_SjeR01.root", "READ");
  TH2D *hmed = (TH2D*)file->Get("hJetDsz"); hmed->SetName("hmed"); hmed->SetDirectory(0);
  file->Close();
//=============================================================================

  TH1D *hpy8020 = hpy8->ProjectionY("hpy8020", hpy8->GetXaxis()->FindBin( 20.+1e-6), hpy8->GetXaxis()->FindBin( 30.-1e-6));
  TH1D *hpy8060 = hpy8->ProjectionY("hpy8060", hpy8->GetXaxis()->FindBin( 60.+1e-6), hpy8->GetXaxis()->FindBin( 80.-1e-6));
  TH1D *hpy8120 = hpy8->ProjectionY("hpy8120", hpy8->GetXaxis()->FindBin(120.+1e-6), hpy8->GetXaxis()->FindBin(150.-1e-6));

  TH1D *hqpy020 = hqpy->ProjectionY("hqpy020", hqpy->GetXaxis()->FindBin( 20.+1e-6), hqpy->GetXaxis()->FindBin( 30.-1e-6));
  TH1D *hqpy060 = hqpy->ProjectionY("hqpy060", hqpy->GetXaxis()->FindBin( 60.+1e-6), hqpy->GetXaxis()->FindBin( 80.-1e-6));
  TH1D *hqpy120 = hqpy->ProjectionY("hqpy120", hqpy->GetXaxis()->FindBin(120.+1e-6), hqpy->GetXaxis()->FindBin(150.-1e-6));

  TH1D *hmed020 = hmed->ProjectionY("hmed020", hmed->GetXaxis()->FindBin( 20.+1e-6), hmed->GetXaxis()->FindBin( 30.-1e-6));
  TH1D *hmed060 = hmed->ProjectionY("hmed060", hmed->GetXaxis()->FindBin( 60.+1e-6), hmed->GetXaxis()->FindBin( 80.-1e-6));
  TH1D *hmed120 = hmed->ProjectionY("hmed120", hmed->GetXaxis()->FindBin(120.+1e-6), hmed->GetXaxis()->FindBin(150.-1e-6));


  hpy8020->Rebin(10.); hpy8020->Scale(1./hpy8020->Integral()); NormBinningHistogram(hpy8020);
  hpy8060->Rebin(10.); hpy8060->Scale(1./hpy8060->Integral()); NormBinningHistogram(hpy8060);
  hpy8120->Rebin(10.); hpy8120->Scale(1./hpy8120->Integral()); NormBinningHistogram(hpy8120);

  hqpy020->Rebin(10.); hqpy020->Scale(1./hqpy020->Integral()); NormBinningHistogram(hqpy020);
  hqpy060->Rebin(10.); hqpy060->Scale(1./hqpy060->Integral()); NormBinningHistogram(hqpy060);
  hqpy120->Rebin(10.); hqpy120->Scale(1./hqpy120->Integral()); NormBinningHistogram(hqpy120);

  hmed020->Rebin(10.); hmed020->Scale(1./hmed020->Integral()); NormBinningHistogram(hmed020);
  hmed060->Rebin(10.); hmed060->Scale(1./hmed060->Integral()); NormBinningHistogram(hmed060);
  hmed120->Rebin(10.); hmed120->Scale(1./hmed120->Integral()); NormBinningHistogram(hmed120);


  TGraph *gpy8020 = new TGraph(hpy8020); TGraph *gpy8060 = new TGraph(hpy8060); TGraph *gpy8120 = new TGraph(hpy8120);
  TGraph *gqpy020 = new TGraph(hqpy020); TGraph *gqpy060 = new TGraph(hqpy060); TGraph *gqpy120 = new TGraph(hqpy120);
  TGraph *gmed020 = new TGraph(hmed020); TGraph *gmed060 = new TGraph(hmed060); TGraph *gmed120 = new TGraph(hmed120);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = -40., dfux = 200.;
  const Float_t dfly = 8e-10, dfuy = 8e3;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#Delta#it{z}_{sj}";
  const TString stny = "1/#it{N}_{jet} d#it{N}/d#Delta#it{z}_{sj}";
//=============================================================================

  can = MakeCanvas("Jet5Dsz020"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0., 1., 6.); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawGraph(gpy8020, wcl[3], "C");
  DrawGraph(gqpy020, wcl[1], "C");
  DrawGraph(gmed020, wcl[5], "C");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(gpy8020, "PYTHIA 8", "L")->SetTextSizePixels(24);
  leg->AddEntry(gqpy020, "Q-PYTHIA", "L")->SetTextSizePixels(24);
  leg->AddEntry(gmed020, "JEWEL+PYTHIA", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet #it{R}=0.5, anti-#it{k}_{T}, 20<#it{p}_{T,jet}<30 GeV/#it{c}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet5Dsz060"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0., 1., 5.); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawGraph(gpy8060, wcl[3], "C");
  DrawGraph(gqpy060, wcl[1], "C");
  DrawGraph(gmed060, wcl[5], "C");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(gpy8060, "PYTHIA 8", "L")->SetTextSizePixels(24);
  leg->AddEntry(gqpy060, "Q-PYTHIA", "L")->SetTextSizePixels(24);
  leg->AddEntry(gmed060, "JEWEL+PYTHIA", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet #it{R}=0.5, anti-#it{k}_{T}, 60<#it{p}_{T,jet}<80 GeV/#it{c}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet5Dsz120"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0., 1., 5.); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawGraph(gpy8120, wcl[3], "C");
  DrawGraph(gqpy120, wcl[1], "C");
  DrawGraph(gmed120, wcl[5], "C");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(gpy8120, "PYTHIA 8", "L")->SetTextSizePixels(24);
  leg->AddEntry(gqpy120, "Q-PYTHIA", "L")->SetTextSizePixels(24);
  leg->AddEntry(gmed120, "JEWEL+PYTHIA", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.14, 0.92, "2.76 TeV, Jet #it{R}=0.5, anti-#it{k}_{T}, 120<#it{p}_{T,jet}<150 GeV/#it{c}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  return;
}
