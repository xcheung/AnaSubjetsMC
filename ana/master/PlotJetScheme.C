void PlotJetScheme()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/incl/AnalysisOutputs_jet_py8_JetR05_SjeR01.root", "READ");
  TH1D *h5py8I = (TH1D*)file->Get("hJet"); h5py8I->SetName("h5py8I"); h5py8I->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_py6_JetR05_SjeR01.root", "READ");
  TH1D *h5py6I = (TH1D*)file->Get("hJet"); h5py6I->SetName("h5py6I"); h5py6I->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_qpy_JetR05_SjeR01.root", "READ");
  TH1D *h5qpyI = (TH1D*)file->Get("hJet"); h5qpyI->SetName("h5qpyI"); h5qpyI->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_vac_JetR05_SjeR01.root", "READ");
  TH1D *h5vacI = (TH1D*)file->Get("hJet"); h5vacI->SetName("h5vacI"); h5vacI->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_med_JetR05_SjeR01.root", "READ");
  TH1D *h5medI = (TH1D*)file->Get("hJet"); h5medI->SetName("h5medI"); h5medI->SetDirectory(0);
  file->Close();


  file = TFile::Open("data/incl/AnalysisOutputs_jet_py8_JetR04_SjeR01.root", "READ");
  TH1D *h4py8I = (TH1D*)file->Get("hJet"); h4py8I->SetName("h4py8I"); h4py8I->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_py6_JetR04_SjeR01.root", "READ");
  TH1D *h4py6I = (TH1D*)file->Get("hJet"); h4py6I->SetName("h4py6I"); h4py6I->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_qpy_JetR04_SjeR01.root", "READ");
  TH1D *h4qpyI = (TH1D*)file->Get("hJet"); h4qpyI->SetName("h4qpyI"); h4qpyI->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_vac_JetR04_SjeR01.root", "READ");
  TH1D *h4vacI = (TH1D*)file->Get("hJet"); h4vacI->SetName("h4vacI"); h4vacI->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_med_JetR04_SjeR01.root", "READ");
  TH1D *h4medI = (TH1D*)file->Get("hJet"); h4medI->SetName("h4medI"); h4medI->SetDirectory(0);
  file->Close();


  file = TFile::Open("data/mass/AnalysisOutputs_jet_py8_JetR05_SjeR01.root", "READ");
  TH1D *h5py8M = (TH1D*)file->Get("hJet"); h5py8M->SetName("h5py8M"); h5py8M->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_jet_py6_JetR05_SjeR01.root", "READ");
  TH1D *h5py6M = (TH1D*)file->Get("hJet"); h5py6M->SetName("h5py6M"); h5py6M->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_jet_qpy_JetR05_SjeR01.root", "READ");
  TH1D *h5qpyM = (TH1D*)file->Get("hJet"); h5qpyM->SetName("h5qpyM"); h5qpyM->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_jet_vac_JetR05_SjeR01.root", "READ");
  TH1D *h5vacM = (TH1D*)file->Get("hJet"); h5vacM->SetName("h5vacM"); h5vacM->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_jet_med_JetR05_SjeR01.root", "READ");
  TH1D *h5medM = (TH1D*)file->Get("hJet"); h5medM->SetName("h5medM"); h5medM->SetDirectory(0);
  file->Close();


  file = TFile::Open("data/mass/AnalysisOutputs_jet_py8_JetR04_SjeR01.root", "READ");
  TH1D *h4py8M = (TH1D*)file->Get("hJet"); h4py8M->SetName("h4py8M"); h4py8M->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_jet_py6_JetR04_SjeR01.root", "READ");
  TH1D *h4py6M = (TH1D*)file->Get("hJet"); h4py6M->SetName("h4py6M"); h4py6M->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_jet_qpy_JetR04_SjeR01.root", "READ");
  TH1D *h4qpyM = (TH1D*)file->Get("hJet"); h4qpyM->SetName("h4qpyM"); h4qpyM->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_jet_vac_JetR04_SjeR01.root", "READ");
  TH1D *h4vacM = (TH1D*)file->Get("hJet"); h4vacM->SetName("h4vacM"); h4vacM->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/mass/AnalysisOutputs_jet_med_JetR04_SjeR01.root", "READ");
  TH1D *h4medM = (TH1D*)file->Get("hJet"); h4medM->SetName("h4medM"); h4medM->SetDirectory(0);
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

  const Double_t dBin[] = { 0., 10., 20., 30., 40., 50., 60., 80., 100., 120., 150., 200., 250., 300., 350., 400., 500. };
  const Int_t nBin = sizeof(dBin) / sizeof(Double_t) -1;

  TH1D *h5py8Irb = h5py8I->Rebin(nBin, "h5py8Irb", dBin); TH1D *h4py8Irb = h4py8I->Rebin(nBin, "h4py8Irb", dBin);
  TH1D *h5py6Irb = h5py6I->Rebin(nBin, "h5py6Irb", dBin); TH1D *h4py6Irb = h4py6I->Rebin(nBin, "h4py6Irb", dBin);
  TH1D *h5qpyIrb = h5qpyI->Rebin(nBin, "h5qpyIrb", dBin); TH1D *h4qpyIrb = h4qpyI->Rebin(nBin, "h4qpyIrb", dBin);
  TH1D *h5vacIrb = h5vacI->Rebin(nBin, "h5vacIrb", dBin); TH1D *h4vacIrb = h4vacI->Rebin(nBin, "h4vacIrb", dBin);
  TH1D *h5medIrb = h5medI->Rebin(nBin, "h5medIrb", dBin); TH1D *h4medIrb = h4medI->Rebin(nBin, "h4medIrb", dBin);

  TH1D *h5py8Mrb = h5py8M->Rebin(nBin, "h5py8Mrb", dBin); TH1D *h4py8Mrb = h4py8M->Rebin(nBin, "h4py8Mrb", dBin);
  TH1D *h5py6Mrb = h5py6M->Rebin(nBin, "h5py6Mrb", dBin); TH1D *h4py6Mrb = h4py6M->Rebin(nBin, "h4py6Mrb", dBin);
  TH1D *h5qpyMrb = h5qpyM->Rebin(nBin, "h5qpyMrb", dBin); TH1D *h4qpyMrb = h4qpyM->Rebin(nBin, "h4qpyMrb", dBin);
  TH1D *h5vacMrb = h5vacM->Rebin(nBin, "h5vacMrb", dBin); TH1D *h4vacMrb = h4vacM->Rebin(nBin, "h4vacMrb", dBin);
  TH1D *h5medMrb = h5medM->Rebin(nBin, "h5medMrb", dBin); TH1D *h4medMrb = h4medM->Rebin(nBin, "h4medMrb", dBin);
//=============================================================================

  TH1D *h5py8R = (TH1D*)h5py8Irb->Clone("h5py8R"); h5py8R->Divide(h5py8Mrb);
  TH1D *h5qpyR = (TH1D*)h5qpyIrb->Clone("h5qpyR"); h5qpyR->Divide(h5qpyMrb);
  TH1D *h5medR = (TH1D*)h5medIrb->Clone("h5medR"); h5medR->Divide(h5medMrb);

  TH1D *h4py8R = (TH1D*)h4py8Irb->Clone("h4py8R"); h4py8R->Divide(h4py8Mrb);
  TH1D *h4qpyR = (TH1D*)h4qpyIrb->Clone("h4qpyR"); h4qpyR->Divide(h4qpyMrb);
  TH1D *h4medR = (TH1D*)h4medIrb->Clone("h4medR"); h4medR->Divide(h4medMrb);
//=============================================================================

  can = MakeCanvas("Jet5R"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0.95, 500., 1.2); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy,
                                                      "#it{p}_{T,jet} (GeV/#it{c})",
                                                      "Ratio: BIpt scheme / E scheme");
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h5py8R, wcl[3], wmk[0], "SAME");
  DrawHisto(h5qpyR, wcl[1], wmk[0], "SAME");
  DrawHisto(h5medR, wcl[5], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(h5py8R, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h5qpyR, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h5medR, "JEWEL+PYTHIA", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jets anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet4R"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0.95, 500., 1.2); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy,
                                                      "#it{p}_{T,jet} (GeV/#it{c})",
                                                      "Ratio: BIpt scheme / E scheme");
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h4py8R, wcl[3], wmk[0], "SAME");
  DrawHisto(h4qpyR, wcl[1], wmk[0], "SAME");
  DrawHisto(h4medR, wcl[5], wmk[0], "SAME");

  leg = new TLegend(0.62, 0.64, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(h4py8R, "PYTHIA 8", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h4qpyR, "Q-PYTHIA", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h4medR, "JEWEL+PYTHIA", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jets anti-#it{k}_{T}, #it{R}=0.4, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  TH1D *h5qpyIAA = (TH1D*)h5qpyIrb->Clone("h5qpyIAA"); h5qpyIAA->Divide(h5py6Irb);
  TH1D *h5medIAA = (TH1D*)h5medIrb->Clone("h5medIAA"); h5medIAA->Divide(h5vacIrb);

  TH1D *h4qpyIAA = (TH1D*)h4qpyIrb->Clone("h4qpyIAA"); h4qpyIAA->Divide(h4py6Irb);
  TH1D *h4medIAA = (TH1D*)h4medIrb->Clone("h4medIAA"); h4medIAA->Divide(h4vacIrb);

  TH1D *h5qpyMAA = (TH1D*)h5qpyMrb->Clone("h5qpyMAA"); h5qpyMAA->Divide(h5py6Mrb);
  TH1D *h5medMAA = (TH1D*)h5medMrb->Clone("h5medMAA"); h5medMAA->Divide(h5vacMrb);

  TH1D *h4qpyMAA = (TH1D*)h4qpyMrb->Clone("h4qpyMAA"); h4qpyMAA->Divide(h4py6Mrb);
  TH1D *h4medMAA = (TH1D*)h4medMrb->Clone("h4medMAA"); h4medMAA->Divide(h4vacMrb);
//=============================================================================

  can = MakeCanvas("Jet5RAA"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0., 500., 1.2); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy,
                                                        "#it{p}_{T,jet} (GeV/#it{c})",
                                                        "#it{R}_{AA}");
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h5qpyIAA, wcl[1], wmk[0], "SAME");
  DrawHisto(h5medIAA, wcl[5], wmk[0], "SAME");

  DrawHisto(h5qpyMAA, wcl[1], wmk[2], "SAME");
  DrawHisto(h5medMAA, wcl[5], wmk[2], "SAME");

  leg = new TLegend(0.42, 0.56, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(h5qpyIAA, "Q-PYTHIA, BIpt scheme", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h5qpyMAA, "Q-PYTHIA, BIpt scheme", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h5medIAA, "JEWEL+PYTHIA, E scheme", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h5medMAA, "JEWEL+PYTHIA, E scheme", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet anti-#it{k}_{T}, #it{R}=0.5, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet4RAA"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0., 500., 1.2); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy,
                                                        "#it{p}_{T,jet} (GeV/#it{c})",
                                                        "#it{R}_{AA}");
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h4qpyIAA, wcl[1], wmk[0], "SAME");
  DrawHisto(h4medIAA, wcl[5], wmk[0], "SAME");

  DrawHisto(h4qpyMAA, wcl[1], wmk[2], "SAME");
  DrawHisto(h4medMAA, wcl[5], wmk[2], "SAME");

  leg = new TLegend(0.42, 0.56, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(h4qpyIAA, "Q-PYTHIA, BIpt scheme", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h4qpyMAA, "Q-PYTHIA, BIpt scheme", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h4medIAA, "JEWEL+PYTHIA, E scheme", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h4medMAA, "JEWEL+PYTHIA, E scheme", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet anti-#it{k}_{T}, #it{R}=0.4, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  return;
}
