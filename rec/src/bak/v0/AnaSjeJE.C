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
#include "TList.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "THnSparse.h"
#include "TF1.h"
//=============================================================================

using namespace std;

const TString srcName = "AnaSjeJE";
//=============================================================================

int main(int argc, char* argv[])
{
  TApplication theApp(srcName.Data(), &argc, argv);
//=============================================================================

  if (argc<3) return -1;
  TString sPath = argv[1]; if (sPath.IsNull()) return -1;
  TString sFile = argv[2]; if (sFile.IsNull()) return -1;

  sPath.ReplaceAll("#", "/");
//=============================================================================

  const double dJetsRange  = 0.4;
  const double dJetsPtMin  = 0.10;
  const double dPseuPtMin  = 0.15;
  const double dCutEtaMax  = 0.9;
  const double dJetEtaMax  = 0.45;
  const double dJetAreaRef = TMath::Pi() * dJetsRange * dJetsRange;

  fastjet::GhostedAreaSpec areaSpc(dCutEtaMax);
  fastjet::JetDefinition   jetsDef(fastjet::antikt_algorithm, dJetsRange, fastjet::BIpt_scheme, fastjet::Best);

//fastjet::AreaDefinition  areaDef(fastjet::active_area,areaSpc);
  fastjet::AreaDefinition  areaDef(fastjet::active_area_explicit_ghosts,areaSpc);

//fastjet::JetDefinition   bkgsDef(fastjet::kt_algorithm, 0.2, fastjet::BIpt_scheme, fastjet::Best);
//fastjet::AreaDefinition  aBkgDef(fastjet::active_area_explicit_ghosts, areaSpc);

  fastjet::Selector selectJet = fastjet::SelectorAbsEtaMax(dJetEtaMax);
//fastjet::Selector selectRho = fastjet::SelectorAbsEtaMax(dCutEtaMax-0.2);
//fastjet::Selector selecHard = fastjet::SelectorNHardest(2);
//fastjet::Selector selectBkg = selectRho * (!(selecHard));
//fastjet::JetMedianBackgroundEstimator bkgsEstimator(selectBkg, bkgsDef, aBkgDef);
//fastjet::Subtractor                   bkgSubtractor(&bkgsEstimator);

  fastjet::JetDefinition subjDef01(fastjet::kt_algorithm, 0.1, fastjet::BIpt_scheme, fastjet::Best);
  fastjet::JetDefinition subjDef02(fastjet::kt_algorithm, 0.2, fastjet::BIpt_scheme, fastjet::Best);
//=============================================================================

  std::vector<fastjet::PseudoJet> fjInput;
//=============================================================================

  TList *list = new TList();
  TH1D *hWeightSum = new TH1D("hWeightSum", "", 1, 0., 1.); list->Add(hWeightSum);
  TH2D *hJetPtEta = new TH2D("hJetPtEta", "", 2000, 0., 1000., 200, -10., 10.); hJetPtEta->Sumw2(); list->Add(hJetPtEta);


  TH2D *hJetPtNtrk = new TH2D("hJetPtNtrk", "", 2000, 0., 1000., 101, -0.5, 100.5); hJetPtNtrk->Sumw2(); list->Add(hJetPtNtrk);

  TH2D *hJetTrkPt = new TH2D("hJetTrkPt", "", 2000, 0., 1000., 2000, 0., 1000.); hJetTrkPt->Sumw2(); list->Add(hJetTrkPt);
  TH2D *hJet1tkPt = new TH2D("hJet1tkPt", "", 2000, 0., 1000., 2000, 0., 1000.); hJet1tkPt->Sumw2(); list->Add(hJet1tkPt);
  TH2D *hJet2tkPt = new TH2D("hJet2tkPt", "", 2000, 0., 1000., 2000, 0., 1000.); hJet2tkPt->Sumw2(); list->Add(hJet2tkPt);

  TH2D *hJetPtDtk = new TH2D("hJetPtDtk", "", 2000, 0., 1000., 200, 0., 100.); hJetPtDtk->Sumw2(); list->Add(hJetPtDtk);
  TH2D *hJetPtZtk = new TH2D("hJetPtZtk", "", 2000, 0., 1000., 200, 0.,   2.); hJetPtZtk->Sumw2(); list->Add(hJetPtZtk);


  TH2D *hJetPtNsj01 = new TH2D("hJetPtNsj01", "", 2000, 0., 1000., 101, -0.5, 100.5); hJetPtNsj01->Sumw2(); list->Add(hJetPtNsj01);
  TH2D *hJetPtNsj02 = new TH2D("hJetPtNsj02", "", 2000, 0., 1000., 101, -0.5, 100.5); hJetPtNsj02->Sumw2(); list->Add(hJetPtNsj02);

  TH2D *hJetIsj01Pt = new TH2D("hJetIsj01Pt", "", 2000, 0., 1000., 2000, 0., 1000.); hJetIsj01Pt->Sumw2(); list->Add(hJetIsj01Pt);
  TH2D *hJetIsj02Pt = new TH2D("hJetIsj02Pt", "", 2000, 0., 1000., 2000, 0., 1000.); hJetIsj02Pt->Sumw2(); list->Add(hJetIsj02Pt);

  TH2D *hJet1sj01Pt = new TH2D("hJet1sj01Pt", "", 2000, 0., 1000., 2000, 0., 1000.); hJet1sj01Pt->Sumw2(); list->Add(hJet1sj01Pt);
  TH2D *hJet1sj02Pt = new TH2D("hJet1sj02Pt", "", 2000, 0., 1000., 2000, 0., 1000.); hJet1sj02Pt->Sumw2(); list->Add(hJet1sj02Pt);

  TH2D *hJet2sj01Pt = new TH2D("hJet2sj01Pt", "", 2000, 0., 1000., 2000, 0., 1000.); hJet2sj01Pt->Sumw2(); list->Add(hJet2sj01Pt);
  TH2D *hJet2sj02Pt = new TH2D("hJet2sj02Pt", "", 2000, 0., 1000., 2000, 0., 1000.); hJet2sj02Pt->Sumw2(); list->Add(hJet2sj02Pt);

  TH2D *hJetPtDsj01 = new TH2D("hJetPtDsj01", "", 2000, 0., 1000., 200, 0., 100.); hJetPtDsj01->Sumw2(); list->Add(hJetPtDsj01);
  TH2D *hJetPtDsj02 = new TH2D("hJetPtDsj02", "", 2000, 0., 1000., 200, 0., 100.); hJetPtDsj02->Sumw2(); list->Add(hJetPtDsj02);

  TH2D *hJetPtZsj01 = new TH2D("hJetPtZsj01", "", 2000, 0., 1000., 200, 0., 2.); hJetPtZsj01->Sumw2(); list->Add(hJetPtZsj01);
  TH2D *hJetPtZsj02 = new TH2D("hJetPtZsj02", "", 2000, 0., 1000., 200, 0., 2.); hJetPtZsj02->Sumw2(); list->Add(hJetPtZsj02);
//=============================================================================

  HepMC::IO_GenEvent ascii_in(Form("%s/%s.hepmc",sPath.Data(),sFile.Data()), std::ios::in);
  HepMC::GenEvent *evt = ascii_in.read_next_event();

  while (evt) {
    fjInput.resize(0);
    double dXsect  = evt->cross_section()->cross_section() / 1e9;
    double dWeight = evt->weights().back();
    double dNorm = dWeight * dXsect;
    hWeightSum->Fill(0.5, dWeight);

    TVector3 vPar;
    for (HepMC::GenEvent::particle_const_iterator p=evt->particles_begin(); p!=evt->particles_end(); ++p) if ((*p)->status()==1) {
      vPar.SetXYZ((*p)->momentum().px(), (*p)->momentum().py(), (*p)->momentum().pz());

      if ((TMath::Abs(vPar.Eta())<dCutEtaMax)) {
        fjInput.push_back(fastjet::PseudoJet(vPar.Px(), vPar.Py(), vPar.Pz(), vPar.Mag()));
      }
    }
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInput, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJets = clustSeq.inclusive_jets(dJetsPtMin);
//  std::vector<fastjet::PseudoJet> subtedJets = bkgSubtractor(includJets);
    std::vector<fastjet::PseudoJet> selectJets = selectJet(includJets);
//  std::vector<fastjet::PseudoJet> sortedJets = fastjet::sorted_by_pt(selectJets);

    for (int j=0; j<selectJets.size(); j++) {
      double dJetPt  = selectJets[j].pt(); if (dJetPt<1e-10) continue;
      double dJetEta = selectJets[j].eta();

      hJetPtEta->Fill(dJetPt, dJetEta, dNorm);
      if (TMath::Abs(dJetEta)>0.45) continue;
//=============================================================================

      std::vector<fastjet::PseudoJet> consti = selectJets[j].constituents();

      double nTrk = 0.;
      double d1tk = -1., d2tk = -1.;
      for (int i=0; i<consti.size(); i++) {
        double dTrk = consti[i].pt(); if (dTrk<1e-10) continue;

        hJetTrkPt->Fill(dJetPt, dTrk, dNorm); nTrk += 1.;
        if (dTrk>d1tk) { d2tk = d1tk; d1tk = dTrk; } else if (dTrk>d2tk) { d2tk = dTrk; }
      }

      hJetPtNtrk->Fill(dJetPt, nTrk, dNorm);
      if (d1tk>0.) hJet1tkPt->Fill(dJetPt, d1tk, dNorm);
      if (d2tk>0.) hJet2tkPt->Fill(dJetPt, d2tk, dNorm);

      if ((d1tk>0.) && (d2tk>0.)) {
        double dtk = d1tk - d2tk;
        hJetPtDtk->Fill(dJetPt, dtk, dNorm);
        hJetPtZtk->Fill(dJetPt, dtk/dJetPt, dNorm);
      }
//=============================================================================

      fastjet::Filter trimmer01(subjDef01, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet01 = trimmer01(selectJets[j]);
      std::vector<fastjet::PseudoJet> trimmdSj01 = trimmdJet01.pieces();

      double nIsj = 0.;
      double d1sj = -1., d2sj = -1.;
      for (int i=0; i<trimmdSj01.size(); i++) {
        double dIsj = trimmdSj01[i].pt(); if (dIsj<1e-10) continue;

        hJetIsj01Pt->Fill(dJetPt, dIsj, dNorm); nIsj += 1.;
        if (dIsj>d1sj) { d2sj = d1sj; d1sj = dIsj; } else if (dIsj>d2sj) { d2sj = dIsj; }
      }

      hJetPtNsj01->Fill(dJetPt, nIsj, dNorm);
      if (d1sj>0.) hJet1sj01Pt->Fill(dJetPt, d1sj, dNorm);
      if (d2sj>0.) hJet2sj01Pt->Fill(dJetPt, d2sj, dNorm);

      if ((d1sj>0.) && (d2sj>0.)) {
        double dsj = d1sj - d2sj;
        hJetPtDsj01->Fill(dJetPt, dsj, dNorm);
        hJetPtZsj01->Fill(dJetPt, dsj/dJetPt, dNorm);
      }
//=============================================================================

      fastjet::Filter trimmer02(subjDef02, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet02 = trimmer02(selectJets[j]);
      std::vector<fastjet::PseudoJet> trimmdSj02 = trimmdJet02.pieces();

      nIsj = 0.; d1sj = -1.; d2sj = -1.;
      for (int i=0; i<trimmdSj02.size(); i++) {
        double dIsj = trimmdSj02[i].pt(); if (dIsj<1e-10) continue;

        hJetIsj02Pt->Fill(dJetPt, dIsj, dNorm); nIsj += 1.;
        if (dIsj>d1sj) { d2sj = d1sj; d1sj = dIsj; } else if (dIsj>d2sj) { d2sj = dIsj; }
      }

      hJetPtNsj02->Fill(dJetPt, nIsj, dNorm);
      if (d1sj>0.) hJet1sj02Pt->Fill(dJetPt, d1sj, dNorm);
      if (d2sj>0.) hJet2sj02Pt->Fill(dJetPt, d2sj, dNorm);

      if ((d1sj>0.) && (d2sj>0.)) {
        double dsj = d1sj - d2sj;
        hJetPtDsj02->Fill(dJetPt, dsj, dNorm);
        hJetPtZsj02->Fill(dJetPt, dsj/dJetPt, dNorm);
      }
    }
//=============================================================================

    delete evt;
    ascii_in >> evt;
  }
//=============================================================================

  TFile *file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  list->Write();
  file->Close();
//=============================================================================

  cout << "DONE" << endl;
  return 0;
}
