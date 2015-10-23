#include <iostream>

#include "HepMC/IO_GenEvent.h"
#include "HepMC/GenEvent.h"

#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/AreaDefinition.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/tools/Filter.hh"

#include "TApplication.h"
#include "TRandom3.h"
#include "TString.h"
#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TNtuple.h"
//=============================================================================

using namespace std;

const TString srcName = "AnalysisQA";
//=============================================================================

int main(int argc, char* argv[])
{
  TApplication theApp(srcName.Data(), &argc, argv);
//=============================================================================

  if (argc<5) return -1;
  TString sPath = argv[1]; if (sPath.IsNull()) return -1;
  TString sFile = argv[2]; if (sFile.IsNull()) return -1;
  TString sJetR = argv[3]; if (sJetR.IsNull()) return -1;
  TString sSjeR = argv[4]; if (sSjeR.IsNull()) return -1;
//=============================================================================

  sPath.ReplaceAll("#", "/");
//=============================================================================

  double dJetR = -1.;
  if (sJetR=="JetR02") dJetR = 0.2;
  if (sJetR=="JetR03") dJetR = 0.3;
  if (sJetR=="JetR04") dJetR = 0.4;
  if (sJetR=="JetR05") dJetR = 0.5;

  if (dJetR<0.) return -1;
  cout << "Jet R = " << dJetR << endl;
//=============================================================================

  double dSjeR = -1.;
  if (sSjeR=="SjeR01") dSjeR = 0.1;
  if (sSjeR=="SjeR02") dSjeR = 0.2;
  if (sSjeR=="SjeR03") dSjeR = 0.3;
  if (sSjeR=="SjeR04") dSjeR = 0.4;

  if (dSjeR<0.) return -1;
  cout << "Sub-jet R = " << dSjeR << endl;
//=============================================================================

  const double dJetsPtMin  = 0.1;
  const double dJetEtaMax  = 2.;
  const double dCutEtaMax  = 2.6;

  fastjet::GhostedAreaSpec areaSpc(dCutEtaMax);
  fastjet::JetDefinition   jetsDef(fastjet::antikt_algorithm, dJetR, fastjet::BIpt_scheme, fastjet::Best);
  fastjet::AreaDefinition  areaDef(fastjet::active_area_explicit_ghosts,areaSpc);

  fastjet::Selector selectJet = fastjet::SelectorAbsEtaMax(dJetEtaMax);
  fastjet::JetDefinition subjDef(fastjet::kt_algorithm, dSjeR, fastjet::BIpt_scheme, fastjet::Best);
//=============================================================================

  std::vector<fastjet::PseudoJet> fjInput;
//=============================================================================

  TFile *file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  TList *list = new TList();

  TH1D *hWeightSum = new TH1D("hWeightSum", "", 1, 0., 1.); list->Add(hWeightSum);

  TH2D *hTrkPtEta = new TH2D("hTrkPtEta", "", 1000, 0., 500., 60, -3., 3.); hTrkPtEta->Sumw2(); list->Add(hTrkPtEta);
  TH2D *hTrkPtPhi = new TH2D("hTrkPtPhi", "", 1000, 0., 500., 20, -1., 1.); hTrkPtPhi->Sumw2(); list->Add(hTrkPtPhi);

  TH2D *hJetPtNsj = new TH2D("hJetPtNsj", "", 1000, 0., 1000., 100, -0.5, 99.5); hJetPtNsj->Sumw2(); list->Add(hJetPtNsj);


  TH2D *hJetPtEta = new TH2D("hJetPtEta", "", 1000, 0., 1000., 60, -3., 3.); hJetPtEta->Sumw2(); list->Add(hJetPtEta);
  TH2D *hJetPtPhi = new TH2D("hJetPtPhi", "", 1000, 0., 1000., 20, -1., 1.); hJetPtPhi->Sumw2(); list->Add(hJetPtPhi);

  TH2D *hLjePtEta = new TH2D("hLjePtEta", "", 1000, 0., 1000., 60, -3., 3.); hLjePtEta->Sumw2(); list->Add(hLjePtEta);
  TH2D *hLjePtPhi = new TH2D("hLjePtPhi", "", 1000, 0., 1000., 20, -1., 1.); hLjePtPhi->Sumw2(); list->Add(hLjePtPhi);

  TH2D *hNjePtEta = new TH2D("hNjePtEta", "", 1000, 0., 1000., 60, -3., 3.); hNjePtEta->Sumw2(); list->Add(hNjePtEta);
  TH2D *hNjePtPhi = new TH2D("hNjePtPhi", "", 1000, 0., 1000., 20, -1., 1.); hNjePtPhi->Sumw2(); list->Add(hNjePtPhi);


  TH2D *hJe2PtEta = new TH2D("hJe2PtEta", "", 1000, 0., 1000., 60, -3., 3.); hJe2PtEta->Sumw2(); list->Add(hJe2PtEta);
  TH2D *hJe2PtPhi = new TH2D("hJe2PtPhi", "", 1000, 0., 1000., 20, -1., 1.); hJe2PtPhi->Sumw2(); list->Add(hJe2PtPhi);

  TH2D *hLj2PtEta = new TH2D("hLj2PtEta", "", 1000, 0., 1000., 60, -3., 3.); hLj2PtEta->Sumw2(); list->Add(hLj2PtEta);
  TH2D *hLj2PtPhi = new TH2D("hLj2PtPhi", "", 1000, 0., 1000., 20, -1., 1.); hLj2PtPhi->Sumw2(); list->Add(hLj2PtPhi);

  TH2D *hNj2PtEta = new TH2D("hNj2PtEta", "", 1000, 0., 1000., 60, -3., 3.); hNj2PtEta->Sumw2(); list->Add(hNj2PtEta);
  TH2D *hNj2PtPhi = new TH2D("hNj2PtPhi", "", 1000, 0., 1000., 20, -1., 1.); hNj2PtPhi->Sumw2(); list->Add(hNj2PtPhi);
//=============================================================================

  HepMC::IO_GenEvent ascii_in(Form("%s/%s.hepmc",sPath.Data(),sFile.Data()), std::ios::in);
  HepMC::GenEvent *evt = ascii_in.read_next_event();

  while (evt) {
    fjInput.resize(0);
    double dWeight = evt->weights().back();
    double dXsect  = evt->cross_section()->cross_section() / 1e9;
    double dNorm   = dWeight * dXsect;
    hWeightSum->Fill(0.5, dWeight);

    TVector3 vTrk;
    for (HepMC::GenEvent::particle_const_iterator p=evt->particles_begin(); p!=evt->particles_end(); ++p) if ((*p)->status()==1) {
      double dTrkPt  = (*p)->momentum().perp(); if (dTrkPt<0.5) continue;
      double dTrkEta = (*p)->momentum().eta();  if (TMath::Abs(dTrkEta)>dCutEtaMax) continue;
      double dTrkPhi = (*p)->momentum().phi();  vTrk.SetPtEtaPhi(dTrkPt, dTrkEta, dTrkPhi);
      double dTrkCos = TMath::Cos(dTrkPhi); if (dTrkCos==1.) dTrkCos = 1. - 1e-6;

      fjInput.push_back(fastjet::PseudoJet(vTrk.Px(), vTrk.Py(), vTrk.Pz(), vTrk.Mag()));

      hTrkPtEta->Fill(dTrkPt, dTrkEta, dNorm);
      hTrkPtPhi->Fill(dTrkPt, dTrkCos, dNorm);
    }
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInput, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJets = clustSeq.inclusive_jets(dJetsPtMin);
    std::vector<fastjet::PseudoJet> selectJets = selectJet(includJets);
    std::vector<fastjet::PseudoJet> sortedJets = fastjet::sorted_by_pt(selectJets);
//=============================================================================

    for (int j=0; j<sortedJets.size(); j++) {
      double dJetPt  = sortedJets[j].pt();
      double dJetEta = sortedJets[j].eta();
      double dJetPhi = sortedJets[j].phi();
      double dJetCos = TMath::Cos(dJetPhi);
      if (dJetCos==1.) dJetCos = 1. - 1e-6;

      fastjet::Filter trimmer(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet = trimmer(sortedJets[j]);
      std::vector<fastjet::PseudoJet> trimmdSj = trimmdJet.pieces();

      int nSje = 0;
      for (int i=0; i<trimmdSj.size(); i++) if (trimmdSj[i].pt()>0.1) { nSje += 1; }
      hJetPtNsj->Fill(dJetPt, nSje, dNorm);

      hJetPtEta->Fill(dJetPt, dJetEta, dNorm); hJetPtPhi->Fill(dJetPt, dJetCos, dNorm);
      if (j==0) { hLjePtEta->Fill(dJetPt, dJetEta, dNorm); hLjePtPhi->Fill(dJetPt, dJetCos, dNorm); }
      if (j==1) { hNjePtEta->Fill(dJetPt, dJetEta, dNorm); hNjePtPhi->Fill(dJetPt, dJetCos, dNorm); }

      if (nSje>=2) {
        hJe2PtEta->Fill(dJetPt, dJetEta, dNorm); hJe2PtPhi->Fill(dJetPt, dJetCos, dNorm);
        if (j==0) { hLj2PtEta->Fill(dJetPt, dJetEta, dNorm); hLj2PtPhi->Fill(dJetPt, dJetCos, dNorm); }
        if (j==1) { hNj2PtEta->Fill(dJetPt, dJetEta, dNorm); hNj2PtPhi->Fill(dJetPt, dJetCos, dNorm); }
      }
    }
//=============================================================================

    delete evt;
    ascii_in >> evt;
  }
//=============================================================================

  file->cd(); list->Write(); file->Close();
//=============================================================================

  cout << "DONE" << endl;
//=============================================================================

  return 0;
}
