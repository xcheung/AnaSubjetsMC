void PlotDszRAA()
{
  gROOT->LoadMacro("$LOCAL/include/TUntilsOpHisto.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsAliFigs.h");
  gROOT->LoadMacro("$LOCAL/include/TUntilsPlotStd.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/incl/AnalysisOutputs_jet_py6_JetR05_SjeR01.root", "READ");
  TH1D *h1py6 = (TH1D*)file->Get("hJet");    h1py6->SetName("h1py6"); h1py6->SetDirectory(0);
  TH2D *h5py6 = (TH2D*)file->Get("hJetDsz"); h5py6->SetName("h5py6"); h5py6->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_qpy_JetR05_SjeR01.root", "READ");
  TH1D *h1qpy = (TH1D*)file->Get("hJet");    h1qpy->SetName("h1qpy"); h1qpy->SetDirectory(0);
  TH2D *h5qpy = (TH2D*)file->Get("hJetDsz"); h5qpy->SetName("h5qpy"); h5qpy->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_vac_JetR05_SjeR01.root", "READ");
  TH1D *h1vac = (TH1D*)file->Get("hJet");    h1vac->SetName("h1vac"); h1vac->SetDirectory(0);
  TH2D *h5vac = (TH2D*)file->Get("hJetDsz"); h5vac->SetName("h5vac"); h5vac->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_med_JetR05_SjeR01.root", "READ");
  TH1D *h1med = (TH1D*)file->Get("hJet");    h1med->SetName("h1med"); h1med->SetDirectory(0);
  TH2D *h5med = (TH2D*)file->Get("hJetDsz"); h5med->SetName("h5med"); h5med->SetDirectory(0);
  file->Close();


  file = TFile::Open("data/incl/AnalysisOutputs_jet_py6_JetR04_SjeR01.root", "READ");
  TH1D *h2py6 = (TH1D*)file->Get("hJet");    h2py6->SetName("h2py6"); h2py6->SetDirectory(0);
  TH2D *h4py6 = (TH2D*)file->Get("hJetDsz"); h4py6->SetName("h4py6"); h4py6->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_qpy_JetR04_SjeR01.root", "READ");
  TH1D *h2qpy = (TH1D*)file->Get("hJet");    h2qpy->SetName("h2qpy"); h2qpy->SetDirectory(0);
  TH2D *h4qpy = (TH2D*)file->Get("hJetDsz"); h4qpy->SetName("h4qpy"); h4qpy->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_vac_JetR04_SjeR01.root", "READ");
  TH1D *h2vac = (TH1D*)file->Get("hJet");    h2vac->SetName("h2vac"); h2vac->SetDirectory(0);
  TH2D *h4vac = (TH2D*)file->Get("hJetDsz"); h4vac->SetName("h4vac"); h4vac->SetDirectory(0);
  file->Close();

  file = TFile::Open("data/incl/AnalysisOutputs_jet_med_JetR04_SjeR01.root", "READ");
  TH1D *h2med = (TH1D*)file->Get("hJet");    h2med->SetName("h2med"); h2med->SetDirectory(0);
  TH2D *h4med = (TH2D*)file->Get("hJetDsz"); h4med->SetName("h4med"); h4med->SetDirectory(0);
  file->Close();
//=============================================================================

  const Double_t dBin[] = { 0., 10., 20., 30., 40., 50., 60., 80., 100., 120., 150., 200., 250., 300., 350., 400., 500. };
  const Int_t nBin = sizeof(dBin) / sizeof(Double_t) -1;

  TH1D *h5py6X = h5py6->ProjectionX("h5py6X", h5py6->GetYaxis()->FindBin(0.8+1e-6), h5py6->GetNbinsY());
  TH1D *h5qpyX = h5qpy->ProjectionX("h5qpyX", h5qpy->GetYaxis()->FindBin(0.8+1e-6), h5qpy->GetNbinsY());

  TH1D *h5vacX = h5vac->ProjectionX("h5vacX", h5vac->GetYaxis()->FindBin(0.8+1e-6), h5vac->GetNbinsY());
  TH1D *h5medX = h5med->ProjectionX("h5medX", h5med->GetYaxis()->FindBin(0.8+1e-6), h5med->GetNbinsY());


  TH1D *h4py6X = h4py6->ProjectionX("h4py6X", h4py6->GetYaxis()->FindBin(0.8+1e-6), h4py6->GetNbinsY());
  TH1D *h4qpyX = h4qpy->ProjectionX("h4qpyX", h4qpy->GetYaxis()->FindBin(0.8+1e-6), h4qpy->GetNbinsY());

  TH1D *h4vacX = h4vac->ProjectionX("h4vacX", h4vac->GetYaxis()->FindBin(0.8+1e-6), h4vac->GetNbinsY());
  TH1D *h4medX = h4med->ProjectionX("h4medX", h4med->GetYaxis()->FindBin(0.8+1e-6), h4med->GetNbinsY());


  TH1D *h5py6rb = h5py6X->Rebin(nBin, "h5py6rb", dBin); TH1D *h4py6rb = h4py6X->Rebin(nBin, "h4py6rb", dBin);
  TH1D *h5qpyrb = h5qpyX->Rebin(nBin, "h5qpyrb", dBin); TH1D *h4qpyrb = h4qpyX->Rebin(nBin, "h4qpyrb", dBin);

  TH1D *h5vacrb = h5vacX->Rebin(nBin, "h5vacrb", dBin); TH1D *h4vacrb = h4vacX->Rebin(nBin, "h4vacrb", dBin);
  TH1D *h5medrb = h5medX->Rebin(nBin, "h5medrb", dBin); TH1D *h4medrb = h4medX->Rebin(nBin, "h4medrb", dBin);


  h5qpyrb->Divide(h5py6rb); TGraph *g5qpy = new TGraph(h5qpyrb);
  h5medrb->Divide(h5vacrb); TGraph *g5med = new TGraph(h5medrb);

  h4qpyrb->Divide(h4py6rb); TGraph *g4qpy = new TGraph(h4qpyrb);
  h4medrb->Divide(h4vacrb); TGraph *g4med = new TGraph(h4medrb);
//=============================================================================

  TH1D *h1py6rb = h1py6->Rebin(nBin, "h1py6rb", dBin); TH1D *h2py6rb = h2py6->Rebin(nBin, "h2py6rb", dBin);
  TH1D *h1qpyrb = h1qpy->Rebin(nBin, "h1qpyrb", dBin); TH1D *h2qpyrb = h2qpy->Rebin(nBin, "h2qpyrb", dBin);
  TH1D *h1vacrb = h1vac->Rebin(nBin, "h1vacrb", dBin); TH1D *h2vacrb = h2vac->Rebin(nBin, "h2vacrb", dBin);
  TH1D *h1medrb = h1med->Rebin(nBin, "h1medrb", dBin); TH1D *h2medrb = h2med->Rebin(nBin, "h2medrb", dBin);

  TH1D *h1qpyRAA = (TH1D*)h1qpyrb->Clone("h1qpyRAA"); h1qpyRAA->Divide(h1py6rb);
  TH1D *h1medRAA = (TH1D*)h1medrb->Clone("h1medRAA"); h1medRAA->Divide(h1vacrb);

  TH1D *h2qpyRAA = (TH1D*)h2qpyrb->Clone("h2qpyRAA"); h2qpyRAA->Divide(h2py6rb);
  TH1D *h2medRAA = (TH1D*)h2medrb->Clone("h2medRAA"); h2medRAA->Divide(h2vacrb);

  TGraph *g1qpy = new TGraph(h1qpyRAA); TGraph *g2qpy = new TGraph(h2qpyRAA);
  TGraph *g1med = new TGraph(h1medRAA); TGraph *g2med = new TGraph(h2medRAA);
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

  const TString stnx = "#it{p}_{T,jet} (GeV/#it{c})";
  const TString stny = "#it{R}_{AA}";
//=============================================================================

  can = MakeCanvas("Jet5DszRAA"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0., 400., 1.2); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawGraph(g5qpy, wcl[1], "C");
  DrawGraph(g5med, wcl[5], "C");

  g1qpy->SetLineStyle(7); DrawGraph(g1qpy, wcl[1], "C");
  g1med->SetLineStyle(7); DrawGraph(g1med, wcl[5], "C");

  leg = new TLegend(0.42, 0.56, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(g5qpy, "Q-PYTHIA, #Delta#it{z}_{sj}>0.8", "L")->SetTextSizePixels(24);
  leg->AddEntry(g1qpy, "Q-PYTHIA, inclusive", "L")->SetTextSizePixels(24);
  leg->AddEntry(g5med, "JEWEL+PYTHIA, #Delta#it{z}_{sj}>0.8", "L")->SetTextSizePixels(24);
  leg->AddEntry(g1med, "JEWEL+PYTHIA, inclusive", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet #it{R}=0.5, anti-#it{k}_{T}, |#eta_{jet}|<1");
  CanvasEnd(can);
//=============================================================================

  can = MakeCanvas("Jet4DszRAA"); can->SetGridx(); can->SetGridy();
  hfm = can->DrawFrame(0., 0., 400., 1.2); SetupFrame(hfm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawGraph(g4qpy, wcl[1], "C");
  DrawGraph(g4med, wcl[5], "C");

  g2qpy->SetLineStyle(7); DrawGraph(g2qpy, wcl[1], "C");
  g2med->SetLineStyle(7); DrawGraph(g2med, wcl[5], "C");

  leg = new TLegend(0.42, 0.56, 0.98, 0.88); SetupLegend(leg);
  leg->AddEntry(g4qpy, "Q-PYTHIA, #Delta#it{z}_{sj}>0.8", "L")->SetTextSizePixels(24);
  leg->AddEntry(g2qpy, "Q-PYTHIA, inclusive", "L")->SetTextSizePixels(24);
  leg->AddEntry(g4med, "JEWEL+PYTHIA, #Delta#it{z}_{sj}>0.8", "L")->SetTextSizePixels(24);
  leg->AddEntry(g2med, "JEWEL+PYTHIA, inclusive", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "2.76 TeV, Jet #it{R}=0.4, anti-#it{k}_{T}, |#eta_{jet}|<1, #Delta#it{z}_{sj}>0.8");
  CanvasEnd(can);
//=============================================================================

  return;
}
