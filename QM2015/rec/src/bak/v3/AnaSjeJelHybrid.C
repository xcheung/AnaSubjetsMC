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

#include "util.h"
//=============================================================================

using namespace std;

const TString srcName = "AnaSjeJelHybrid";
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

  const int multiLHC = 3000;
  const double dJetsPtMin  = 0.001;
  const double dCutEtaMax  = 1.6;
  const double dJetEtaMax  = 1.;
  const double dJetAreaRef = TMath::Pi() * dJetR * dJetR;

  fastjet::GhostedAreaSpec areaSpc(dCutEtaMax);
  fastjet::JetDefinition   jetsDef(fastjet::antikt_algorithm, dJetR, fastjet::BIpt_scheme, fastjet::Best);

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

  std::vector<fastjet::PseudoJet> fjInputHard;
  std::vector<fastjet::PseudoJet> fjInputHybd;

  TRandom3 *r3 = new TRandom3(0);
  TF1 *fBkg = BackgroundSpec();
//=============================================================================

  TList *list = new TList();
  TH1D *hWeightSum = new TH1D("hWeightSum", "", 1, 0., 1.); list->Add(hWeightSum);

  TH1D *hJet = new TH1D("hJet", "", 1500, -500., 1000.); hJet->Sumw2(); list->Add(hJet);

  TH2D *hJetNsj = new TH2D("hJetNsj", "", 1500, -500., 1000., 101, -0.5, 100.5); hJetNsj->Sumw2(); list->Add(hJetNsj);

  TH2D *hJetIsj = new TH2D("hJetIsj", "", 1500, -500., 1000., 1000, 0., 1000.); hJetIsj->Sumw2(); list->Add(hJetIsj);
  TH2D *hJet1sj = new TH2D("hJet1sj", "", 1500, -500., 1000., 1000, 0., 1000.); hJet1sj->Sumw2(); list->Add(hJet1sj);
  TH2D *hJet2sj = new TH2D("hJet2sj", "", 1500, -500., 1000., 1000, 0., 1000.); hJet2sj->Sumw2(); list->Add(hJet2sj);
  TH2D *hJetDsj = new TH2D("hJetDsj", "", 1500, -500., 1000., 1000, 0., 1000.); hJetDsj->Sumw2(); list->Add(hJetDsj);

  TH2D *hJetIsz = new TH2D("hJetIsz", "", 1500, -500., 1000., 500, 0., 5.); hJetIsz->Sumw2(); list->Add(hJetIsz);
  TH2D *hJet1sz = new TH2D("hJet1sz", "", 1500, -500., 1000., 500, 0., 5.); hJet1sz->Sumw2(); list->Add(hJet1sz);
  TH2D *hJet2sz = new TH2D("hJet2sz", "", 1500, -500., 1000., 500, 0., 5.); hJet2sz->Sumw2(); list->Add(hJet2sz);
  TH2D *hJetDsz = new TH2D("hJetDsz", "", 1500, -500., 1000., 500, 0., 5.); hJetDsz->Sumw2(); list->Add(hJetDsz);


  TH1D *hBkg = new TH1D("hBkg", "", 1500, -500., 1000.); hBkg->Sumw2(); list->Add(hBkg);
  TH2D *hBkgNsj = new TH2D("hBkgNsj", "", 1500, -500., 1000., 101, -0.5, 100.5); hBkgNsj->Sumw2(); list->Add(hBkgNsj);
  TH2D *hBkgDsj = new TH2D("hBkgDsj", "", 1500, -500., 1000., 1000, 0., 1000.);  hBkgDsj->Sumw2(); list->Add(hBkgDsj);

  TH2D *hBkgDsb = new TH2D("hBkgDsb", "", 1500, -500., 1000., 500, 0., 5.); hBkgDsb->Sumw2(); list->Add(hBkgDsb);
  TH2D *hBkgDsa = new TH2D("hBkgDsa", "", 1500, -500., 1000., 500, 0., 5.); hBkgDsa->Sumw2(); list->Add(hBkgDsa);
  TH2D *hBkgDss = new TH2D("hBkgDss", "", 1500, -500., 1000., 500, 0., 5.); hBkgDss->Sumw2(); list->Add(hBkgDss);


  TH1D *hMix = new TH1D("hMix", "", 1500, -500., 1000.); hMix->Sumw2(); list->Add(hMix);
  TH2D *hMixNsj = new TH2D("hMixNsj", "", 1500, -500., 1000., 101, -0.5, 100.5); hMixNsj->Sumw2(); list->Add(hMixNsj);
  TH2D *hMixDsj = new TH2D("hMixDsj", "", 1500, -500., 1000., 1000, 0., 1000.);  hMixDsj->Sumw2(); list->Add(hMixDsj);

  TH2D *hMixDsb = new TH2D("hMixDsb", "", 1500, -500., 1000., 500, 0., 5.); hMixDsb->Sumw2(); list->Add(hMixDsb);
  TH2D *hMixDsa = new TH2D("hMixDsa", "", 1500, -500., 1000., 500, 0., 5.); hMixDsa->Sumw2(); list->Add(hMixDsa);
  TH2D *hMixDss = new TH2D("hMixDss", "", 1500, -500., 1000., 500, 0., 5.); hMixDss->Sumw2(); list->Add(hMixDss);


  TH1D *hMat = new TH1D("hMat", "", 1500, -500., 1000.); hMat->Sumw2(); list->Add(hMat);
  TH2D *hMatNsj = new TH2D("hMatNsj", "", 1500, -500., 1000., 101, -0.5, 100.5); hMatNsj->Sumw2(); list->Add(hMatNsj);
  TH2D *hMatDsj = new TH2D("hMatDsj", "", 1500, -500., 1000., 1000, 0., 1000.);  hMatDsj->Sumw2(); list->Add(hMatDsj);

  TH2D *hMatDsb = new TH2D("hMatDsb", "", 1500, -500., 1000., 500, 0., 5.); hMatDsb->Sumw2(); list->Add(hMatDsb);
  TH2D *hMatDsa = new TH2D("hMatDsa", "", 1500, -500., 1000., 500, 0., 5.); hMatDsa->Sumw2(); list->Add(hMatDsa);
  TH2D *hMatDss = new TH2D("hMatDss", "", 1500, -500., 1000., 500, 0., 5.); hMatDss->Sumw2(); list->Add(hMatDss);


  TH1D *hPhy = new TH1D("hPhy", "", 1500, -500., 1000.); hPhy->Sumw2(); list->Add(hPhy);
  TH2D *hPhyNsj = new TH2D("hPhyNsj", "", 1500, -500., 1000., 101, -0.5, 100.5); hPhyNsj->Sumw2(); list->Add(hPhyNsj);
  TH2D *hPhyDsj = new TH2D("hPhyDsj", "", 1500, -500., 1000., 1000, 0., 1000.);  hPhyDsj->Sumw2(); list->Add(hPhyDsj);

  TH2D *hPhyDsb = new TH2D("hPhyDsb", "", 1500, -500., 1000., 500, 0., 5.); hPhyDsb->Sumw2(); list->Add(hPhyDsb);
  TH2D *hPhyDsa = new TH2D("hPhyDsa", "", 1500, -500., 1000., 500, 0., 5.); hPhyDsa->Sumw2(); list->Add(hPhyDsa);
  TH2D *hPhyDss = new TH2D("hPhyDss", "", 1500, -500., 1000., 500, 0., 5.); hPhyDss->Sumw2(); list->Add(hPhyDss);
  TH2D *hPhyDsz = new TH2D("hPhyDsz", "", 1500, -500., 1000., 500, 0., 5.); hPhyDsz->Sumw2(); list->Add(hPhyDsz);
//=============================================================================

  HepMC::IO_GenEvent ascii_in(Form("%s/%s.hepmc",sPath.Data(),sFile.Data()), std::ios::in);
  HepMC::GenEvent *evt = ascii_in.read_next_event();

  while (evt) {
    fjInputHard.resize(0);
    fjInputHybd.resize(0);

    double dXsect  = evt->cross_section()->cross_section() / 1e9;
    double dWeight = evt->weights().back();
    double dNorm = dWeight * dXsect;
    hWeightSum->Fill(0.5, dWeight);

    TVector3 vPar;
    for (HepMC::GenEvent::particle_const_iterator p=evt->particles_begin(); p!=evt->particles_end(); ++p) if ((*p)->status()==1) {
      vPar.SetXYZ((*p)->momentum().px(), (*p)->momentum().py(), (*p)->momentum().pz());

      if ((TMath::Abs(vPar.Eta())<dCutEtaMax)) {
        fjInputHard.push_back(fastjet::PseudoJet(vPar.Px(), vPar.Py(), vPar.Pz(), vPar.Mag()));
        
      }
    }
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInput, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJets = clustSeq.inclusive_jets(dJetsPtMin);
//  std::vector<fastjet::PseudoJet> subtedJets = bkgSubtractor(includJets);
    std::vector<fastjet::PseudoJet> selectJets = selectJet(includJets);
//  std::vector<fastjet::PseudoJet> sortedJets = fastjet::sorted_by_pt(selectJets);

    for (int j=0; j<selectJets.size(); j++) {
      double dJet = selectJets[j].pt();

      hJet->Fill(dJet, dNorm);
//=============================================================================

      fastjet::Filter trimmer(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet = trimmer(selectJets[j]);
      std::vector<fastjet::PseudoJet> trimmdSj = trimmdJet.pieces();

      double nIsj = 0.;
      double d1sj = -1.; int k1sj = -1;
      double d2sj = -1.; int k2sj = -1;
      for (int i=0; i<trimmdSj.size(); i++) {
        double dIsj = trimmdSj[i].pt(); if (dIsj<0.001) continue;

        hJetIsj->Fill(dJet, dIsj, dNorm);
        hJetIsz->Fill(dJet, dIsj/dJet, dNorm);

        if (dIsj>d1sj) {
          d2sj = d1sj; k2sj = k1sj;
          d1sj = dIsj; k1sj = i;
        } else if (dIsj>d2sj) {
          d2sj = dIsj; k2sj = i;
        } nIsj += 1.;
      }

      hJetNsj->Fill(dJet, nIsj, dNorm);
      if (d1sj>0.) { hJet1sj->Fill(dJet, d1sj, dNorm); hJet1sz->Fill(dJet, d1sj/dJet, dNorm); }
      if (d2sj>0.) { hJet2sj->Fill(dJet, d2sj, dNorm); hJet2sz->Fill(dJet, d2sj/dJet, dNorm); }

      if ((d1sj>0.) && (d2sj>0.)) {
        double dsj = d1sj - d2sj;
        double dsz = dsj / dJet;

        hJetDsj->Fill(dJet, dsj, dNorm);
        hJetDsz->Fill(dJet, dsz, dNorm);
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
