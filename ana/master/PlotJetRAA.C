void PlotJetRAA()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/incl/AnalysisOutputs_jet_py8_JetR05_SjeR01.root", "READ");
  TH1D *h5py8 = (TH1D*)file->Get("hJet"); h5py8->SetName("h5py8"); h5py8->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_py6_JetR05_SjeR01.root", "READ");
  TH1D *h5py6 = (TH1D*)file->Get("hJet"); h5py6->SetName("h5py6"); h5py6->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_qpy_JetR05_SjeR01.root", "READ");
  TH1D *h5qpy = (TH1D*)file->Get("hJet"); h5qpy->SetName("h5qpy"); h5qpy->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_vac_JetR05_SjeR01.root", "READ");
  TH1D *h5vac = (TH1D*)file->Get("hJet"); h5vac->SetName("h5vac"); h5vac->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_med_JetR05_SjeR01.root", "READ");
  TH1D *h5med = (TH1D*)file->Get("hJet"); h5med->SetName("h5med"); h5med->SetDirectory(0);
  file->Close();


  file = TFile::Open("data/incl/AnalysisOutputs_jet_py8_JetR04_SjeR01.root", "READ");
  TH1D *h4py8 = (TH1D*)file->Get("hJet"); h4py8->SetName("h4py8"); h4py8->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_py6_JetR04_SjeR01.root", "READ");
  TH1D *h4py6 = (TH1D*)file->Get("hJet"); h4py6->SetName("h4py6"); h4py6->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_qpy_JetR04_SjeR01.root", "READ");
  TH1D *h4qpy = (TH1D*)file->Get("hJet"); h4qpy->SetName("h4qpy"); h4qpy->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_vac_JetR04_SjeR01.root", "READ");
  TH1D *h4vac = (TH1D*)file->Get("hJet"); h4vac->SetName("h4vac"); h4vac->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_med_JetR04_SjeR01.root", "READ");
  TH1D *h4med = (TH1D*)file->Get("hJet"); h4med->SetName("h4med"); h4med->SetDirectory(0);
  file->Close();
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

  const TString stnx = "#it{p}_{T,jet}^{ch} (GeV/#it{c})";
  const TString stny = "d#sigma/d#it{p}_{T} (mb/GetV/#it{c})";

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

  can = MakeCanvas("Jet5"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(0., 8e-13, 500., 8e3); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy,
                                                        "#it{p}_{T,jet} (GeV/#it{c})",
                                                        "d#sigma/d#it{p}_{T} (mb/GeV/#it{c})");
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h5py8, wcl[3], wmk[0], "SAME");
  DrawHisto(h5qpy, wcl[1], wmk[0], "SAME");
  DrawHisto(h5med, wcl[5], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(h5py8, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h5qpy, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h5med, "JEWEL+PYTHIA", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, jet anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet4"); can->SetGridx(); can->SetGridy(); can->SetLogy();
  hfm = can->DrawFrame(0., 8e-13, 500., 8e3); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy,
                                                        "#it{p}_{T,jet} (GeV/#it{c})",
                                                        "d#sigma/d#it{p}_{T} (mb/GeV/#it{c})");
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h4py8, wcl[3], wmk[0], "SAME");
  DrawHisto(h4qpy, wcl[1], wmk[0], "SAME");
  DrawHisto(h4med, wcl[5], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(h4py8, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h4qpy, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h4med, "JEWEL+PYTHIA", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, jet anti-#it{k}_{T}, #it{R}=0.4, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  const Double_t dBin[] = { 0., 10., 20., 30., 40., 50., 60., 80., 100., 120., 150., 200., 250., 300., 350., 400., 500. };
  const Int_t nBin = sizeof(dBin) / sizeof(Double_t) -1;

  TH1D *h5py8rb = h5py8->Rebin(nBin, "h5py8rb", dBin); TH1D *h4py8rb = h4py8->Rebin(nBin, "h4py8rb", dBin);
  TH1D *h5py6rb = h5py6->Rebin(nBin, "h5py6rb", dBin); TH1D *h4py6rb = h4py6->Rebin(nBin, "h4py6rb", dBin);
  TH1D *h5qpyrb = h5qpy->Rebin(nBin, "h5qpyrb", dBin); TH1D *h4qpyrb = h4qpy->Rebin(nBin, "h4qpyrb", dBin);
  TH1D *h5vacrb = h5vac->Rebin(nBin, "h5vacrb", dBin); TH1D *h4vacrb = h4vac->Rebin(nBin, "h4vacrb", dBin);
  TH1D *h5medrb = h5med->Rebin(nBin, "h5medrb", dBin); TH1D *h4medrb = h4med->Rebin(nBin, "h4medrb", dBin);
//=============================================================================

  TH1D *hRpy8 = (TH1D*)h4py8rb->Clone("hRpy8"); hRpy8->Divide(h5py8rb);
  TH1D *hRqpy = (TH1D*)h4qpyrb->Clone("hRqpy"); hRqpy->Divide(h5qpyrb);
  TH1D *hRmed = (TH1D*)h4medrb->Clone("hRmed"); hRmed->Divide(h5medrb);
//=============================================================================

  can = MakeCanvas("JetR"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0.4, 500., 1.5); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy,
                                                      "#it{p}_{T,jet} (GeV/#it{c})",
                                                      "Ratio: #it{R}=0.4 / #it{R}=0.5");
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(hRpy8, wcl[3], wmk[0], "SAME");
  DrawHisto(hRqpy, wcl[1], wmk[0], "SAME");
  DrawHisto(hRmed, wcl[5], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(hRpy8, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hRqpy, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hRmed, "JEWEL+PYTHIA", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jets anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  TH1D *h5qpyRAA = (TH1D*)h5qpyrb->Clone("h5qpyRAA"); h5qpyRAA->Divide(h5py6rb);
  TH1D *h5medRAA = (TH1D*)h5medrb->Clone("h5medRAA"); h5medRAA->Divide(h5vacrb);

  TH1D *h4qpyRAA = (TH1D*)h4qpyrb->Clone("h4qpyRAA"); h4qpyRAA->Divide(h4py6rb);
  TH1D *h4medRAA = (TH1D*)h4medrb->Clone("h4medRAA"); h4medRAA->Divide(h4vacrb);

  can = MakeCanvas("JetRAA"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0., 500., 1.2); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy,
                                                        "#it{p}_{T,jet} (GeV/#it{c})",
                                                        "#it{R}_{AA}");
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h5qpyRAA, wcl[1], wmk[0], "SAME");
  DrawHisto(h5medRAA, wcl[5], wmk[0], "SAME");

  DrawHisto(h4qpyRAA, wcl[1], wmk[2], "SAME");
  DrawHisto(h4medRAA, wcl[5], wmk[2], "SAME");

  leg = new TLegend(0.48, 0.56, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(h5qpyRAA, "#it{R}=0.5, Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h4qpyRAA, "#it{R}=0.4, Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h5medRAA, "#it{R}=0.5, JEWEL+PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h4medRAA, "#it{R}=0.4, JEWEL+PYTHIA", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  return;
}
