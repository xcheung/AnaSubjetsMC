void PlotDsr()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnalysisOutputs_Dsr.root", "READ");
  TList *listPy8R5S1 = (TList*)file->Get("list_py8_JetR05_SjeR01");
  TList *listQpyR5S1 = (TList*)file->Get("list_qpy_JetR05_SjeR01");
  TList *listVacR5S1 = (TList*)file->Get("list_vac_JetR05_SjeR01");
  TList *listMedR5S1 = (TList*)file->Get("list_med_JetR05_SjeR01");
  file->Close();


  TH3D *hPy8R5S1 = (TH3D*)listPy8R5S1->FindObject("hJetDsr"); hPy8R5S1->SetName("hPy8R5S1"); hPy8R5S1->RebinY(10);
  TH3D *hQpyR5S1 = (TH3D*)listQpyR5S1->FindObject("hJetDsr"); hQpyR5S1->SetName("hQpyR5S1"); hQpyR5S1->RebinY(10);
  TH3D *hVacR5S1 = (TH3D*)listVacR5S1->FindObject("hJetDsr"); hVacR5S1->SetName("hVacR5S1"); hVacR5S1->RebinY(10);
  TH3D *hMedR5S1 = (TH3D*)listMedR5S1->FindObject("hJetDsr"); hMedR5S1->SetName("hMedR5S1"); hMedR5S1->RebinY(10);


  hPy8R5S1->GetXaxis()->SetRange(hPy8R5S1->GetXaxis()->FindBin(20.+1e-6), hPy8R5S1->GetNbinsX());
  TH2D *hPy8R5S1YZ020 = hPy8R5S1->Project3D("hPy8R5S1020_yz");

  hQpyR5S1->GetXaxis()->SetRange(hQpyR5S1->GetXaxis()->FindBin(20.+1e-6), hQpyR5S1->GetNbinsX());
  TH2D *hQpyR5S1YZ020 = hQpyR5S1->Project3D("hQpyR5S1020_yz");

  hVacR5S1->GetXaxis()->SetRange(hVacR5S1->GetXaxis()->FindBin(20.+1e-6), hVacR5S1->GetNbinsX());
  TH2D *hVacR5S1YZ020 = hVacR5S1->Project3D("hVacR5S1020_yz");

  hMedR5S1->GetXaxis()->SetRange(hMedR5S1->GetXaxis()->FindBin(20.+1e-6), hMedR5S1->GetNbinsX());
  TH2D *hMedR5S1YZ020 = hMedR5S1->Project3D("hSimR5S1020_yz");


  hPy8R5S1->GetXaxis()->SetRange(hPy8R5S1->GetXaxis()->FindBin(60.+1e-6), hPy8R5S1->GetNbinsX());
  TH2D *hPy8R5S1YZ060 = hPy8R5S1->Project3D("hPy8R5S1060_yz");

  hQpyR5S1->GetXaxis()->SetRange(hQpyR5S1->GetXaxis()->FindBin(60.+1e-6), hQpyR5S1->GetNbinsX());
  TH2D *hQpyR5S1YZ060 = hQpyR5S1->Project3D("hQpyR5S1060_yz");

  hVacR5S1->GetXaxis()->SetRange(hVacR5S1->GetXaxis()->FindBin(60.+1e-6), hVacR5S1->GetNbinsX());
  TH2D *hVacR5S1YZ060 = hVacR5S1->Project3D("hVacR5S1060_yz");

  hMedR5S1->GetXaxis()->SetRange(hMedR5S1->GetXaxis()->FindBin(60.+1e-6), hMedR5S1->GetNbinsX());
  TH2D *hMedR5S1YZ060 = hMedR5S1->Project3D("hSimR5S1060_yz");


  hPy8R5S1->GetXaxis()->SetRange(hPy8R5S1->GetXaxis()->FindBin(120.+1e-6), hPy8R5S1->GetNbinsX());
  TH2D *hPy8R5S1YZ120 = hPy8R5S1->Project3D("hPy8R5S1120_yz");

  hQpyR5S1->GetXaxis()->SetRange(hQpyR5S1->GetXaxis()->FindBin(120.+1e-6), hQpyR5S1->GetNbinsX());
  TH2D *hQpyR5S1YZ120 = hQpyR5S1->Project3D("hQpyR5S1120_yz");

  hVacR5S1->GetXaxis()->SetRange(hVacR5S1->GetXaxis()->FindBin(120.+1e-6), hVacR5S1->GetNbinsX());
  TH2D *hVacR5S1YZ120 = hVacR5S1->Project3D("hVacR5S1120_yz");

  hMedR5S1->GetXaxis()->SetRange(hMedR5S1->GetXaxis()->FindBin(120.+1e-6), hMedR5S1->GetNbinsX());
  TH2D *hMedR5S1YZ120 = hMedR5S1->Project3D("hSimR5S1120_yz");
//=============================================================================

  TH1D *hPy8R5S1YZ020Xl = hPy8R5S1YZ020->ProjectionX("hPy8R5S1YZ020Xl", hPy8R5S1YZ020->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hPy8R5S1YZ020->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hPy8R5S1YZ020Xh = hPy8R5S1YZ020->ProjectionX("hPy8R5S1YZ020Xh", hPy8R5S1YZ020->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hPy8R5S1YZ020->GetYaxis()->FindBin(1.0-1e-6) );

  TH1D *hPy8R5S1YZ060Xl = hPy8R5S1YZ060->ProjectionX("hPy8R5S1YZ060Xl", hPy8R5S1YZ060->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hPy8R5S1YZ060->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hPy8R5S1YZ060Xh = hPy8R5S1YZ060->ProjectionX("hPy8R5S1YZ060Xh", hPy8R5S1YZ060->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hPy8R5S1YZ060->GetYaxis()->FindBin(1.0-1e-6) );

  TH1D *hPy8R5S1YZ120Xl = hPy8R5S1YZ120->ProjectionX("hPy8R5S1YZ120Xl", hPy8R5S1YZ120->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hPy8R5S1YZ120->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hPy8R5S1YZ120Xh = hPy8R5S1YZ120->ProjectionX("hPy8R5S1YZ120Xh", hPy8R5S1YZ120->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hPy8R5S1YZ120->GetYaxis()->FindBin(1.0-1e-6) );


  TH1D *hQpyR5S1YZ020Xl = hQpyR5S1YZ020->ProjectionX("hQpyR5S1YZ020Xl", hQpyR5S1YZ020->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hQpyR5S1YZ020->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hQpyR5S1YZ020Xh = hQpyR5S1YZ020->ProjectionX("hQpyR5S1YZ020Xh", hQpyR5S1YZ020->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hQpyR5S1YZ020->GetYaxis()->FindBin(1.0-1e-6) );

  TH1D *hQpyR5S1YZ060Xl = hQpyR5S1YZ060->ProjectionX("hQpyR5S1YZ060Xl", hQpyR5S1YZ060->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hQpyR5S1YZ060->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hQpyR5S1YZ060Xh = hQpyR5S1YZ060->ProjectionX("hQpyR5S1YZ060Xh", hQpyR5S1YZ060->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hQpyR5S1YZ060->GetYaxis()->FindBin(1.0-1e-6) );

  TH1D *hQpyR5S1YZ120Xl = hQpyR5S1YZ120->ProjectionX("hQpyR5S1YZ120Xl", hQpyR5S1YZ120->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hQpyR5S1YZ120->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hQpyR5S1YZ120Xh = hQpyR5S1YZ120->ProjectionX("hQpyR5S1YZ120Xh", hQpyR5S1YZ120->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hQpyR5S1YZ120->GetYaxis()->FindBin(1.0-1e-6) );


  TH1D *hVacR5S1YZ020Xl = hVacR5S1YZ020->ProjectionX("hVacR5S1YZ020Xl", hVacR5S1YZ020->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hVacR5S1YZ020->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hVacR5S1YZ020Xh = hVacR5S1YZ020->ProjectionX("hVacR5S1YZ020Xh", hVacR5S1YZ020->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hVacR5S1YZ020->GetYaxis()->FindBin(1.0-1e-6) );

  TH1D *hVacR5S1YZ060Xl = hVacR5S1YZ060->ProjectionX("hVacR5S1YZ060Xl", hVacR5S1YZ060->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hVacR5S1YZ060->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hVacR5S1YZ060Xh = hVacR5S1YZ060->ProjectionX("hVacR5S1YZ060Xh", hVacR5S1YZ060->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hVacR5S1YZ060->GetYaxis()->FindBin(1.0-1e-6) );

  TH1D *hVacR5S1YZ120Xl = hVacR5S1YZ120->ProjectionX("hVacR5S1YZ120Xl", hVacR5S1YZ120->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hVacR5S1YZ120->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hVacR5S1YZ120Xh = hVacR5S1YZ120->ProjectionX("hVacR5S1YZ120Xh", hVacR5S1YZ120->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hVacR5S1YZ120->GetYaxis()->FindBin(1.0-1e-6) );


  TH1D *hMedR5S1YZ020Xl = hMedR5S1YZ020->ProjectionX("hMedR5S1YZ020Xl", hMedR5S1YZ020->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hMedR5S1YZ020->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hMedR5S1YZ020Xh = hMedR5S1YZ020->ProjectionX("hMedR5S1YZ020Xh", hMedR5S1YZ020->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hMedR5S1YZ020->GetYaxis()->FindBin(1.0-1e-6) );

  TH1D *hMedR5S1YZ060Xl = hMedR5S1YZ060->ProjectionX("hMedR5S1YZ060Xl", hMedR5S1YZ060->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hMedR5S1YZ060->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hMedR5S1YZ060Xh = hMedR5S1YZ060->ProjectionX("hMedR5S1YZ060Xh", hMedR5S1YZ060->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hMedR5S1YZ060->GetYaxis()->FindBin(1.0-1e-6) );

  TH1D *hMedR5S1YZ120Xl = hMedR5S1YZ120->ProjectionX("hMedR5S1YZ120Xl", hMedR5S1YZ120->GetYaxis()->FindBin(0.0+1e-6),
                                                                        hMedR5S1YZ120->GetYaxis()->FindBin(0.5-1e-6) );

  TH1D *hMedR5S1YZ120Xh = hMedR5S1YZ120->ProjectionX("hMedR5S1YZ120Xh", hMedR5S1YZ120->GetYaxis()->FindBin(0.5+1e-6),
                                                                        hMedR5S1YZ120->GetYaxis()->FindBin(1.0-1e-6) );


  hPy8R5S1YZ020Xl->Rebin(10); hPy8R5S1YZ060Xl->Rebin(10); hPy8R5S1YZ120Xl->Rebin(10);
  hPy8R5S1YZ020Xh->Rebin(10); hPy8R5S1YZ060Xh->Rebin(10); hPy8R5S1YZ120Xh->Rebin(10);

  hQpyR5S1YZ020Xl->Rebin(10); hQpyR5S1YZ060Xl->Rebin(10); hQpyR5S1YZ120Xl->Rebin(10);
  hQpyR5S1YZ020Xh->Rebin(10); hQpyR5S1YZ060Xh->Rebin(10); hQpyR5S1YZ120Xh->Rebin(10);

  hVacR5S1YZ020Xl->Rebin(10); hVacR5S1YZ060Xl->Rebin(10); hVacR5S1YZ120Xl->Rebin(10);
  hVacR5S1YZ020Xh->Rebin(10); hVacR5S1YZ060Xh->Rebin(10); hVacR5S1YZ120Xh->Rebin(10);

  hMedR5S1YZ020Xl->Rebin(10); hMedR5S1YZ060Xl->Rebin(10); hMedR5S1YZ120Xl->Rebin(10);
  hMedR5S1YZ020Xh->Rebin(10); hMedR5S1YZ060Xh->Rebin(10); hMedR5S1YZ120Xh->Rebin(10);


  hPy8R5S1YZ020Xl->Scale(1./hPy8R5S1YZ020Xl->Integral());
  hPy8R5S1YZ020Xh->Scale(1./hPy8R5S1YZ020Xh->Integral());

  hPy8R5S1YZ060Xl->Scale(1./hPy8R5S1YZ060Xl->Integral());
  hPy8R5S1YZ060Xh->Scale(1./hPy8R5S1YZ060Xh->Integral());

  hPy8R5S1YZ120Xl->Scale(1./hPy8R5S1YZ120Xl->Integral());
  hPy8R5S1YZ120Xh->Scale(1./hPy8R5S1YZ120Xh->Integral());


  hQpyR5S1YZ020Xl->Scale(1./hQpyR5S1YZ020Xl->Integral());
  hQpyR5S1YZ020Xh->Scale(1./hQpyR5S1YZ020Xh->Integral());

  hQpyR5S1YZ060Xl->Scale(1./hQpyR5S1YZ060Xl->Integral());
  hQpyR5S1YZ060Xh->Scale(1./hQpyR5S1YZ060Xh->Integral());

  hQpyR5S1YZ120Xl->Scale(1./hQpyR5S1YZ120Xl->Integral());
  hQpyR5S1YZ120Xh->Scale(1./hQpyR5S1YZ120Xh->Integral());


  hVacR5S1YZ020Xl->Scale(1./hVacR5S1YZ020Xl->Integral());
  hVacR5S1YZ020Xh->Scale(1./hVacR5S1YZ020Xh->Integral());

  hVacR5S1YZ060Xl->Scale(1./hVacR5S1YZ060Xl->Integral());
  hVacR5S1YZ060Xh->Scale(1./hVacR5S1YZ060Xh->Integral());

  hVacR5S1YZ120Xl->Scale(1./hVacR5S1YZ120Xl->Integral());
  hVacR5S1YZ120Xh->Scale(1./hVacR5S1YZ120Xh->Integral());


  hMedR5S1YZ020Xl->Scale(1./hMedR5S1YZ020Xl->Integral());
  hMedR5S1YZ020Xh->Scale(1./hMedR5S1YZ020Xh->Integral());

  hMedR5S1YZ060Xl->Scale(1./hMedR5S1YZ060Xl->Integral());
  hMedR5S1YZ060Xh->Scale(1./hMedR5S1YZ060Xh->Integral());

  hMedR5S1YZ120Xl->Scale(1./hMedR5S1YZ120Xl->Integral());
  hMedR5S1YZ120Xh->Scale(1./hMedR5S1YZ120Xh->Integral());


  NormBinningHistogram(hPy8R5S1YZ020Xl); NormBinningHistogram(hPy8R5S1YZ020Xh);
  NormBinningHistogram(hPy8R5S1YZ060Xl); NormBinningHistogram(hPy8R5S1YZ060Xh);
  NormBinningHistogram(hPy8R5S1YZ120Xl); NormBinningHistogram(hPy8R5S1YZ120Xh);

  NormBinningHistogram(hQpyR5S1YZ020Xl); NormBinningHistogram(hQpyR5S1YZ020Xh);
  NormBinningHistogram(hQpyR5S1YZ060Xl); NormBinningHistogram(hQpyR5S1YZ060Xh);
  NormBinningHistogram(hQpyR5S1YZ120Xl); NormBinningHistogram(hQpyR5S1YZ120Xh);

  NormBinningHistogram(hVacR5S1YZ020Xl); NormBinningHistogram(hVacR5S1YZ020Xh);
  NormBinningHistogram(hVacR5S1YZ060Xl); NormBinningHistogram(hVacR5S1YZ060Xh);
  NormBinningHistogram(hVacR5S1YZ120Xl); NormBinningHistogram(hVacR5S1YZ120Xh);

  NormBinningHistogram(hMedR5S1YZ020Xl); NormBinningHistogram(hMedR5S1YZ020Xh);
  NormBinningHistogram(hMedR5S1YZ060Xl); NormBinningHistogram(hMedR5S1YZ060Xh);
  NormBinningHistogram(hMedR5S1YZ120Xl); NormBinningHistogram(hMedR5S1YZ120Xh);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 0.,   dfux = 1.;
  const Float_t dfly = 8e-7, dfuy = 8e3;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#Delta#it{r}_{sj} = #Delta#it{R}_{sj} / 2#it{R}";
  const TString stny = "1/#it{N}_{jet} d#it{N}/d#Delta#it{r}_{sj}";

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

  can = MakeCanvas("DsrR05S1X020Xl"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1YZ020Xl, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1YZ020Xl, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1YZ020Xl, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1YZ020Xl, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1YZ020Xl, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1YZ020Xl, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1YZ020Xl, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1YZ020Xl, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>20 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1, #Delta#it{z}_{sj}<0.5");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DsrR05S1X020Xh"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1YZ020Xh, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1YZ020Xh, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1YZ020Xh, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1YZ020Xh, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1YZ020Xh, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1YZ020Xh, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1YZ020Xh, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1YZ020Xh, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>20 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1, #Delta#it{z}_{sj}>0.5");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DsrR05S1X060Xl"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1YZ060Xl, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1YZ060Xl, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1YZ060Xl, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1YZ060Xl, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1YZ060Xl, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1YZ060Xl, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1YZ060Xl, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1YZ060Xl, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>60 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1, #Delta#it{z}_{sj}<0.5");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DsrR05S1X060Xh"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1YZ060Xh, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1YZ060Xh, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1YZ060Xh, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1YZ060Xh, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1YZ060Xh, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1YZ060Xh, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1YZ060Xh, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1YZ060Xh, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>60 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1, #Delta#it{z}_{sj}>0.5");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DsrR05S1X120Xl"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1YZ120Xl, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1YZ120Xl, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1YZ120Xl, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1YZ120Xl, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1YZ120Xl, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1YZ120Xl, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1YZ120Xl, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1YZ120Xl, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>120 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1, #Delta#it{z}_{sj}<0.5");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DsrR05S1X120Xh"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1YZ120Xh, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1YZ120Xh, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1YZ120Xh, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1YZ120Xh, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1YZ120Xh, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1YZ120Xh, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1YZ120Xh, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1YZ120Xh, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>120 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1, #Delta#it{z}_{sj}>0.5");
  CanvasEnd(can);
//=============================================================================

  return;
}
