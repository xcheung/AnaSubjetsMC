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

const TString srcName = "AnaSjePy";
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
//=============================================================================

  double dSjeR = -1.;
  if (sSjeR=="SjeR01") dSjeR = 0.1;
  if (sSjeR=="SjeR02") dSjeR = 0.2;
  if (sSjeR=="SjeR03") dSjeR = 0.3;
  if (dSjeR<0.) return -1;
//=============================================================================

  const double dJetsRange  = dJetR;
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

  fastjet::JetDefinition subjDef(fastjet::kt_algorithm, dSjeR, fastjet::BIpt_scheme, fastjet::Best);
//=============================================================================

  std::vector<fastjet::PseudoJet> fjInput;
//=============================================================================

  TList *list = new TList();
  TH1D *hJet = new TH1D("hJet", "", 1000, 0., 1000.); hJet->Sumw2(); list->Add(hJet);
  TH1D *hL1j = new TH1D("hL1j", "", 1000, 0., 1000.); hL1j->Sumw2(); list->Add(hL1j);
  TH1D *hL2j = new TH1D("hL2j", "", 1000, 0., 1000.); hL2j->Sumw2(); list->Add(hL2j);

  TH2D *hL1jNsj = new TH2D("hL1jNsj", "", 1000, 0., 1000., 101, -0.5, 100.5); hL1jNsj->Sumw2(); list->Add(hL1jNsj);
  TH2D *hL2jNsj = new TH2D("hL2jNsj", "", 1000, 0., 1000., 101, -0.5, 100.5); hL2jNsj->Sumw2(); list->Add(hL2jNsj);

  TH2D *hL1jIsj = new TH2D("hL1jIsj", "", 1000, 0., 1000., 1000, 0., 1000.); hL1jIsj->Sumw2(); list->Add(hL1jIsj);
  TH2D *hL1j1sj = new TH2D("hL1j1sj", "", 1000, 0., 1000., 1000, 0., 1000.); hL1j1sj->Sumw2(); list->Add(hL1j1sj);
  TH2D *hL1j2sj = new TH2D("hL1j2sj", "", 1000, 0., 1000., 1000, 0., 1000.); hL1j2sj->Sumw2(); list->Add(hL1j2sj);
  TH2D *hL1jDsj = new TH2D("hL1jDsj", "", 1000, 0., 1000., 1000, 0., 1000.); hL1jDsj->Sumw2(); list->Add(hL1jDsj);

  TH2D *hL2jIsj = new TH2D("hL2jIsj", "", 1000, 0., 1000., 1000, 0., 1000.); hL2jIsj->Sumw2(); list->Add(hL2jIsj);
  TH2D *hL2j1sj = new TH2D("hL2j1sj", "", 1000, 0., 1000., 1000, 0., 1000.); hL2j1sj->Sumw2(); list->Add(hL2j1sj);
  TH2D *hL2j2sj = new TH2D("hL2j2sj", "", 1000, 0., 1000., 1000, 0., 1000.); hL2j2sj->Sumw2(); list->Add(hL2j2sj);
  TH2D *hL2jDsj = new TH2D("hL2jDsj", "", 1000, 0., 1000., 1000, 0., 1000.); hL2jDsj->Sumw2(); list->Add(hL2jDsj);

  TH2D *hL1jIsz = new TH2D("hL1jIsz", "", 2000, 0., 1000., 120, 0., 1.2); hL1jIsz->Sumw2(); list->Add(hL1jIsz);
  TH2D *hL1j1sz = new TH2D("hL1j1sz", "", 2000, 0., 1000., 120, 0., 1.2); hL1j1sz->Sumw2(); list->Add(hL1j1sz);
  TH2D *hL1j2sz = new TH2D("hL1j2sz", "", 2000, 0., 1000., 120, 0., 1.2); hL1j2sz->Sumw2(); list->Add(hL1j2sz);
  TH2D *hL1jDsz = new TH2D("hL1jDsz", "", 2000, 0., 1000., 120, 0., 1.2); hL1jDsz->Sumw2(); list->Add(hL1jDsz);

  TH2D *hL2jIsz = new TH2D("hL2jIsz", "", 2000, 0., 1000., 120, 0., 1.2); hL2jIsz->Sumw2(); list->Add(hL2jIsz);
  TH2D *hL2j1sz = new TH2D("hL2j1sz", "", 2000, 0., 1000., 120, 0., 1.2); hL2j1sz->Sumw2(); list->Add(hL2j1sz);
  TH2D *hL2j2sz = new TH2D("hL2j2sz", "", 2000, 0., 1000., 120, 0., 1.2); hL2j2sz->Sumw2(); list->Add(hL2j2sz);
  TH2D *hL2jDsz = new TH2D("hL2jDsz", "", 2000, 0., 1000., 120, 0., 1.2); hL2jDsz->Sumw2(); list->Add(hL2jDsz);
//=============================================================================

  HepMC::IO_GenEvent ascii_in(Form("%s/%s.hepmc",sPath.Data(),sFile.Data()), std::ios::in);
  HepMC::GenEvent *evt = ascii_in.read_next_event();

  while (evt) {
    fjInput.resize(0);

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
    std::vector<fastjet::PseudoJet> sortedJets = fastjet::sorted_by_pt(selectJets);

    for (int j=0; j<sortedJets.size(); j++) {
      double dJet = sortedJets[j].pt();

      hJet->Fill(dJet);
      if (j==0) hL1j->Fill(dJet);
      if (j==1) hL2j->Fill(dJet); if (j>1) continue;
//=============================================================================

      fastjet::Filter trimmer(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet = trimmer(sortedJets[j]);
      std::vector<fastjet::PseudoJet> trimmdSj = trimmdJet.pieces();

      double nIsj = 0.;
      double d1sj = -1., d2sj = -1.;
      for (int i=0; i<trimmdSj.size(); i++) {
        double dIsj = trimmdSj[i].pt(); if (dIsj<0.001) continue;

        if (j==0) { hL1jIsj->Fill(dJet, dIsj); hL1jIsz->Fill(dJet, dIsj/dJet); }
        if (j==1) { hL2jIsj->Fill(dJet, dIsj); hL2jIsz->Fill(dJet, dIsj/dJet); }
        if (dIsj>d1sj) { d2sj = d1sj; d1sj = dIsj; } else if (dIsj>d2sj) { d2sj = dIsj; }

        nIsj += 1.;
      }

      if (j==0) hL1jNsj->Fill(dJet, nIsj);
      if (j==1) hL2jNsj->Fill(dJet, nIsj);

      if (d1sj>0.) {
        if (j==0) { hL1j1sj->Fill(dJet, d1sj); hL1j1sz->Fill(dJet, d1sj/dJet); }
        if (j==1) { hL2j1sj->Fill(dJet, d1sj); hL2j1sz->Fill(dJet, d1sj/dJet); }
      }

      if (d2sj>0.) {
        if (j==0) { hL1j2sj->Fill(dJet, d2sj); hL1j2sz->Fill(dJet, d2sj/dJet); }
        if (j==1) { hL2j2sj->Fill(dJet, d2sj); hL2j2sz->Fill(dJet, d2sj/dJet); }
      }

      if ((d1sj>0.) && (d2sj>0.)) {
        double dsj = d1sj - d2sj;
        if (j==0) { hL1jDsj->Fill(dJet, dsj); hL1jDsz->Fill(dJet, dsj/dJet); }
        if (j==1) { hL2jDsj->Fill(dJet, dsj); hL2jDsz->Fill(dJet, dsj/dJet); }
      }
    }
//=============================================================================

    delete evt;
    ascii_in >> evt;
  }
//=============================================================================

  TString sXsec = sFile; sXsec.ReplaceAll("out", "xsecs");
  TFile *file = TFile::Open(Form("%s/xsecs/%s.root",sPath.Data(),sXsec.Data()), "READ");
  TH1D *hPtHat        = (TH1D*)file->Get("hPtHat");        hPtHat->SetDirectory(0);
  TH1D *hWeightSum    = (TH1D*)file->Get("hWeightSum");    hWeightSum->SetDirectory(0);
  TProfile *hSigmaGen = (TProfile*)file->Get("hSigmaGen"); hSigmaGen->SetDirectory(0);
  file->Close();
//=============================================================================

  file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  hPtHat->Write();
  hWeightSum->Write();
  hSigmaGen->Write();
  list->Write();
  file->Close();
//=============================================================================

  cout << "DONE" << endl;
  return 0;
}
