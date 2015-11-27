void PlotDsz()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnalysisOutputs_Dsz.root", "READ");
  TList *listPy8R4S1 = (TList*)file->Get("list_py8_JetR04_SjeR01");
  TList *listPy8R5S1 = (TList*)file->Get("list_py8_JetR05_SjeR01");

  TList *listQpyR4S1 = (TList*)file->Get("list_qpy_JetR04_SjeR01");
  TList *listQpyR5S1 = (TList*)file->Get("list_qpy_JetR05_SjeR01");

  TList *listVacR4S1 = (TList*)file->Get("list_vac_JetR04_SjeR01");
  TList *listVacR5S1 = (TList*)file->Get("list_vac_JetR05_SjeR01");

  TList *listMedR4S1 = (TList*)file->Get("list_med_JetR04_SjeR01");
  TList *listMedR5S1 = (TList*)file->Get("list_med_JetR05_SjeR01");
  file->Close();


  TH2D *hPy8R4S1 = (TH2D*)listPy8R4S1->FindObject("hJetDsz"); hPy8R4S1->SetName("hPy8R4S1");
  TH2D *hPy8R5S1 = (TH2D*)listPy8R5S1->FindObject("hJetDsz"); hPy8R5S1->SetName("hPy8R5S1");

  TH2D *hQpyR4S1 = (TH2D*)listQpyR4S1->FindObject("hJetDsz"); hQpyR4S1->SetName("hQpyR4S1");
  TH2D *hQpyR5S1 = (TH2D*)listQpyR5S1->FindObject("hJetDsz"); hQpyR5S1->SetName("hQpyR5S1");

  TH2D *hVacR4S1 = (TH2D*)listVacR4S1->FindObject("hJetDsz"); hVacR4S1->SetName("hVacR4S1");
  TH2D *hVacR5S1 = (TH2D*)listVacR5S1->FindObject("hJetDsz"); hVacR5S1->SetName("hVacR5S1");

  TH2D *hMedR4S1 = (TH2D*)listMedR4S1->FindObject("hJetDsz"); hMedR4S1->SetName("hMedR4S1");
  TH2D *hMedR5S1 = (TH2D*)listMedR5S1->FindObject("hJetDsz"); hMedR5S1->SetName("hMedR5S1");


  TH1D *hPy8R4S1Y020 = hPy8R4S1->ProjectionY("hPy8R4S1Y020", hPy8R4S1->GetXaxis()->FindBin( 20.+1e-6), hPy8R4S1->GetNbinsX());
  TH1D *hPy8R4S1Y060 = hPy8R4S1->ProjectionY("hPy8R4S1Y060", hPy8R4S1->GetXaxis()->FindBin( 60.+1e-6), hPy8R4S1->GetNbinsX());
  TH1D *hPy8R4S1Y120 = hPy8R4S1->ProjectionY("hPy8R4S1Y120", hPy8R4S1->GetXaxis()->FindBin(120.+1e-6), hPy8R4S1->GetNbinsX());

  TH1D *hPy8R5S1Y020 = hPy8R5S1->ProjectionY("hPy8R5S1Y020", hPy8R5S1->GetXaxis()->FindBin( 20.+1e-6), hPy8R5S1->GetNbinsX());
  TH1D *hPy8R5S1Y060 = hPy8R5S1->ProjectionY("hPy8R5S1Y060", hPy8R5S1->GetXaxis()->FindBin( 60.+1e-6), hPy8R5S1->GetNbinsX());
  TH1D *hPy8R5S1Y120 = hPy8R5S1->ProjectionY("hPy8R5S1Y120", hPy8R5S1->GetXaxis()->FindBin(120.+1e-6), hPy8R5S1->GetNbinsX());



  TH1D *hQpyR4S1Y020 = hQpyR4S1->ProjectionY("hQpyR4S1Y020", hQpyR4S1->GetXaxis()->FindBin( 20.+1e-6), hQpyR4S1->GetNbinsX());
  TH1D *hQpyR4S1Y060 = hQpyR4S1->ProjectionY("hQpyR4S1Y060", hQpyR4S1->GetXaxis()->FindBin( 60.+1e-6), hQpyR4S1->GetNbinsX());
  TH1D *hQpyR4S1Y120 = hQpyR4S1->ProjectionY("hQpyR4S1Y120", hQpyR4S1->GetXaxis()->FindBin(120.+1e-6), hQpyR4S1->GetNbinsX());

  TH1D *hQpyR5S1Y020 = hQpyR5S1->ProjectionY("hQpyR5S1Y020", hQpyR5S1->GetXaxis()->FindBin( 20.+1e-6), hQpyR5S1->GetNbinsX());
  TH1D *hQpyR5S1Y060 = hQpyR5S1->ProjectionY("hQpyR5S1Y060", hQpyR5S1->GetXaxis()->FindBin( 60.+1e-6), hQpyR5S1->GetNbinsX());
  TH1D *hQpyR5S1Y120 = hQpyR5S1->ProjectionY("hQpyR5S1Y120", hQpyR5S1->GetXaxis()->FindBin(120.+1e-6), hQpyR5S1->GetNbinsX());


  TH1D *hVacR4S1Y020 = hVacR4S1->ProjectionY("hVacR4S1Y020", hVacR4S1->GetXaxis()->FindBin( 20.+1e-6), hVacR4S1->GetNbinsX());
  TH1D *hVacR4S1Y060 = hVacR4S1->ProjectionY("hVacR4S1Y060", hVacR4S1->GetXaxis()->FindBin( 60.+1e-6), hVacR4S1->GetNbinsX());
  TH1D *hVacR4S1Y120 = hVacR4S1->ProjectionY("hVacR4S1Y120", hVacR4S1->GetXaxis()->FindBin(120.+1e-6), hVacR4S1->GetNbinsX());

  TH1D *hVacR5S1Y020 = hVacR5S1->ProjectionY("hVacR5S1Y020", hVacR5S1->GetXaxis()->FindBin( 20.+1e-6), hVacR5S1->GetNbinsX());
  TH1D *hVacR5S1Y060 = hVacR5S1->ProjectionY("hVacR5S1Y060", hVacR5S1->GetXaxis()->FindBin( 60.+1e-6), hVacR5S1->GetNbinsX());
  TH1D *hVacR5S1Y120 = hVacR5S1->ProjectionY("hVacR5S1Y120", hVacR5S1->GetXaxis()->FindBin(120.+1e-6), hVacR5S1->GetNbinsX());


  TH1D *hMedR4S1Y020 = hMedR4S1->ProjectionY("hMedR4S1Y020", hMedR4S1->GetXaxis()->FindBin( 20.+1e-6), hMedR4S1->GetNbinsX());
  TH1D *hMedR4S1Y060 = hMedR4S1->ProjectionY("hMedR4S1Y060", hMedR4S1->GetXaxis()->FindBin( 60.+1e-6), hMedR4S1->GetNbinsX());
  TH1D *hMedR4S1Y120 = hMedR4S1->ProjectionY("hMedR4S1Y120", hMedR4S1->GetXaxis()->FindBin(120.+1e-6), hMedR4S1->GetNbinsX());

  TH1D *hMedR5S1Y020 = hMedR5S1->ProjectionY("hMedR5S1Y020", hMedR5S1->GetXaxis()->FindBin( 20.+1e-6), hMedR5S1->GetNbinsX());
  TH1D *hMedR5S1Y060 = hMedR5S1->ProjectionY("hMedR5S1Y060", hMedR5S1->GetXaxis()->FindBin( 60.+1e-6), hMedR5S1->GetNbinsX());
  TH1D *hMedR5S1Y120 = hMedR5S1->ProjectionY("hMedR5S1Y120", hMedR5S1->GetXaxis()->FindBin(120.+1e-6), hMedR5S1->GetNbinsX());


  hPy8R4S1Y020->Rebin(5); hPy8R4S1Y020->Scale(1./hPy8R4S1Y020->Integral()); NormBinningHistogram(hPy8R4S1Y020);
  hPy8R4S1Y060->Rebin(5); hPy8R4S1Y060->Scale(1./hPy8R4S1Y060->Integral()); NormBinningHistogram(hPy8R4S1Y060);
  hPy8R4S1Y120->Rebin(5); hPy8R4S1Y120->Scale(1./hPy8R4S1Y120->Integral()); NormBinningHistogram(hPy8R4S1Y120);

  hPy8R5S1Y020->Rebin(5); hPy8R5S1Y020->Scale(1./hPy8R5S1Y020->Integral()); NormBinningHistogram(hPy8R5S1Y020);
  hPy8R5S1Y060->Rebin(5); hPy8R5S1Y060->Scale(1./hPy8R5S1Y060->Integral()); NormBinningHistogram(hPy8R5S1Y060);
  hPy8R5S1Y120->Rebin(5); hPy8R5S1Y120->Scale(1./hPy8R5S1Y120->Integral()); NormBinningHistogram(hPy8R5S1Y120);


  hQpyR4S1Y020->Rebin(5); hQpyR4S1Y020->Scale(1./hQpyR4S1Y020->Integral()); NormBinningHistogram(hQpyR4S1Y020);
  hQpyR4S1Y060->Rebin(5); hQpyR4S1Y060->Scale(1./hQpyR4S1Y060->Integral()); NormBinningHistogram(hQpyR4S1Y060);
  hQpyR4S1Y120->Rebin(5); hQpyR4S1Y120->Scale(1./hQpyR4S1Y120->Integral()); NormBinningHistogram(hQpyR4S1Y120);

  hQpyR5S1Y020->Rebin(5); hQpyR5S1Y020->Scale(1./hQpyR5S1Y020->Integral()); NormBinningHistogram(hQpyR5S1Y020);
  hQpyR5S1Y060->Rebin(5); hQpyR5S1Y060->Scale(1./hQpyR5S1Y060->Integral()); NormBinningHistogram(hQpyR5S1Y060);
  hQpyR5S1Y120->Rebin(5); hQpyR5S1Y120->Scale(1./hQpyR5S1Y120->Integral()); NormBinningHistogram(hQpyR5S1Y120);


  hVacR4S1Y020->Rebin(5); hVacR4S1Y020->Scale(1./hVacR4S1Y020->Integral()); NormBinningHistogram(hVacR4S1Y020);
  hVacR4S1Y060->Rebin(5); hVacR4S1Y060->Scale(1./hVacR4S1Y060->Integral()); NormBinningHistogram(hVacR4S1Y060);
  hVacR4S1Y120->Rebin(5); hVacR4S1Y120->Scale(1./hVacR4S1Y120->Integral()); NormBinningHistogram(hVacR4S1Y120);

  hVacR5S1Y020->Rebin(5); hVacR5S1Y020->Scale(1./hVacR5S1Y020->Integral()); NormBinningHistogram(hVacR5S1Y020);
  hVacR5S1Y060->Rebin(5); hVacR5S1Y060->Scale(1./hVacR5S1Y060->Integral()); NormBinningHistogram(hVacR5S1Y060);
  hVacR5S1Y120->Rebin(5); hVacR5S1Y120->Scale(1./hVacR5S1Y120->Integral()); NormBinningHistogram(hVacR5S1Y120);


  hMedR4S1Y020->Rebin(5); hMedR4S1Y020->Scale(1./hMedR4S1Y020->Integral()); NormBinningHistogram(hMedR4S1Y020);
  hMedR4S1Y060->Rebin(5); hMedR4S1Y060->Scale(1./hMedR4S1Y060->Integral()); NormBinningHistogram(hMedR4S1Y060);
  hMedR4S1Y120->Rebin(5); hMedR4S1Y120->Scale(1./hMedR4S1Y120->Integral()); NormBinningHistogram(hMedR4S1Y120);

  hMedR5S1Y020->Rebin(5); hMedR5S1Y020->Scale(1./hMedR5S1Y020->Integral()); NormBinningHistogram(hMedR5S1Y020);
  hMedR5S1Y060->Rebin(5); hMedR5S1Y060->Scale(1./hMedR5S1Y060->Integral()); NormBinningHistogram(hMedR5S1Y060);
  hMedR5S1Y120->Rebin(5); hMedR5S1Y120->Scale(1./hMedR5S1Y120->Integral()); NormBinningHistogram(hMedR5S1Y120);
//=============================================================================

  TH1F    *hfm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx = 0.,   dfux = 1.;
  const Float_t dfly = 8e-3, dfuy = 6.;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#Delta#it{z}_{sj}";
  const TString stny = "1/#it{N}_{jet} d#it{N}/d#Delta#it{z}_{sj}";

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

  can = MakeCanvas("DszR04S1Y020"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R4S1Y020, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR4S1Y020, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR4S1Y020, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR4S1Y020, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R4S1Y020, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR4S1Y020, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR4S1Y020, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR4S1Y020, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}>20 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DszR05S1Y020"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1Y020, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1Y020, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1Y020, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1Y020, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1Y020, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1Y020, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1Y020, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1Y020, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>20 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DszR04S1Y060"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R4S1Y060, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR4S1Y060, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR4S1Y060, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR4S1Y060, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R4S1Y060, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR4S1Y060, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR4S1Y060, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR4S1Y060, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}>60 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DszR05S1Y060"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1Y060, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1Y060, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1Y060, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1Y060, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1Y060, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1Y060, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1Y060, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1Y060, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>60 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DszR04S1Y120"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R4S1Y120, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR4S1Y120, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR4S1Y120, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR4S1Y120, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.56, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R4S1Y120, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR4S1Y120, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR4S1Y120, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR4S1Y120, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}>120 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("DszR05S1Y120"); can->SetGridx(); can->SetGridy(); //can->SetLogy();
  hfm = can->DrawFrame(dflx,dfly,dfux,dfuy); SetupFrame(hfm,dlsx,dlsy,dtsx,dtsy,dtox,dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hPy8R5S1Y120, wcl[3], wmk[0], "SAME");
  DrawHisto(hQpyR5S1Y120, wcl[2], wmk[0], "SAME");
  DrawHisto(hVacR5S1Y120, wcl[1], wmk[0], "SAME");
  DrawHisto(hMedR5S1Y120, wcl[4], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.48, 0.98, 0.80); SetupLegend(leg);
  leg->AddEntry(hPy8R5S1Y120, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hQpyR5S1Y120, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hVacR5S1Y120, "JEWEL vacuum", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hMedR5S1Y120, "JEWEL medium", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "PYTHIA+JEWEL, #sqrt{#it{s}_{NN}}=2.76 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.5, #it{p}_{T,jet}>120 GeV/#it{c}, |#eta_{jet}|<1");
  tex->DrawLatex(0.16, 0.76, "Sub-jet: #it{k}_{T}, #it{R}_{sub}=0.1");
  CanvasEnd(can);
//=============================================================================

  return;
}
