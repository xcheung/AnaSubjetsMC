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

  fastjet::JetDefinition   bkgsDef(fastjet::kt_algorithm, 0.2, fastjet::BIpt_scheme, fastjet::Best);
  fastjet::AreaDefinition  aBkgDef(fastjet::active_area_explicit_ghosts, areaSpc);

  fastjet::Selector selectJet = fastjet::SelectorAbsEtaMax(dJetEtaMax);
  fastjet::Selector selectRho = fastjet::SelectorAbsEtaMax(dCutEtaMax-0.2);
  fastjet::Selector selecHard = fastjet::SelectorNHardest(2);
  fastjet::Selector selectBkg = selectRho * (!(selecHard));
  fastjet::JetMedianBackgroundEstimator bkgsEstimator(selectBkg, bkgsDef, aBkgDef);
//fastjet::Subtractor                   bkgSubtractor(&bkgsEstimator);

  fastjet::JetDefinition subjDef(fastjet::kt_algorithm, dSjeR, fastjet::BIpt_scheme, fastjet::Best);
//=============================================================================

  TRandom3 *r3 = new TRandom3(0);
  TF1 *fBkg = BackgroundSpec();
//=============================================================================

  std::vector<fastjet::PseudoJet> fjInputVac;
  std::vector<fastjet::PseudoJet> fjInputHyd;
//=============================================================================

  TList *list = new TList();
  TH1D *hWeightSum = new TH1D("hWeightSum", "", 1, 0., 1.); list->Add(hWeightSum);


//=============================================================================

  HepMC::IO_GenEvent ascii_in(Form("%s/%s.hepmc",sPath.Data(),sFile.Data()), std::ios::in);
  HepMC::GenEvent *evt = ascii_in.read_next_event();

  while (evt) {
    fjInputVac.resize(0);
    fjInputHyd.resize(0);

    double dXsect  = evt->cross_section()->cross_section() / 1e9;
    double dWeight = evt->weights().back();
    double dNorm = dWeight * dXsect;
    hWeightSum->Fill(0.5, dWeight);

    int iCount = 0;
    TLorentzVector vPseudo;
    for (HepMC::GenEvent::particle_const_iterator p=evt->particles_begin(); p!=evt->particles_end(); ++p) if ((*p)->status()==1) {
      vPseudo.SetPtEtaPhiM((*p)->momentum().perp(), (*p)->momentum().eta(), (*p)->momentum().phi(), 0.);

      if ((TMath::Abs(vPar.Eta())<dCutEtaMax)) {
        fjInputVac.push_back(fastjet::PseudoJet(vPseudo.Px(), vPseudo.Py(), vPseudo.Pz(), vPseudo.E()));
        fjInputVac.back().set_user_info(new UserInfoTrk(false));
        fjInputVac.back().set_user_index(iCount); iCount+=1;
      }
    }
//=============================================================================

    for (int i=0; i<=multiLHC; i++) {
      double dPt = fBkg->GetRandom(fgkPtBkgMin, fgkPtBkgMax); if (dPt<0.001) continue;

      vPseudo.SetPtEtaPhiM(dPt, r3->Uniform(-1.*dCutEtaMax,dCutEtaMax), r3->Uniform(0.,TMath::TwoPi()), 0.);
      fjInputHyd.push_back(fastjet::PseudoJet(vPseudo.Px(), vPseudo.Py(), vPseudo.Pz(), vPseudo.E()));
      fjInputHyd.back().set_user_info(new UserInfoTrk(true));
      fjInputHyd.back().set_user_index(-10);
    }

    fjInputHyd.insert(fjInputHyd.end(), fjInputVac.begin(),fjInputVac.end());
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInputVac, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJetsPy = clustSeq.inclusive_jets(dJetsPtMin);
//  std::vector<fastjet::PseudoJet> subtedJetsPy = bkgSubtractor(includJetsPy);
    std::vector<fastjet::PseudoJet> selectJetsPy = selectJet(includJetsPy);
//  std::vector<fastjet::PseudoJet> sortedJetsPy = fastjet::sorted_by_pt(selectJetsPy);

    for (int j=0; j<selectJetsPy.size(); j++) {
      SetJetUserInfo(selectJetsPy[j]);
      selectJetsPy[j].set_user_index(j);
    }
//=============================================================================

    bkgsEstimator.set_particles(fjInputHyd);
    double dBkgRhoHd = bkgsEstimator.rho();
    double dBkgRmsHd = bkgsEstimator.sigma();

    fastjet::ClusterSequenceArea clustSeqHd(fjInputHyd, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJetsHd = clustSeqHd.inclusive_jets(dJetsPtMin);
    std::vector<fastjet::PseudoJet> selectJetsHd = selectJet(includJetsHd);

    for (int j=0; j<selectJetsHd.size(); j++) {
      SetJetUserInfo(selectJetsHd[j]);
      selectJetsHd[j].set_user_index(j);
      if (selectJetsHd[j].user_info<UserInfoJet>().IsBkg()) continue;

      for (int i=0; i<selectJetsPy.size(); i++) {
        if (CalcDeltaR(selectJetsHd[j],selectJetsPy[i])>0.8) continue;
        DoTrkMatch(selectJetsHd[j], selectJetsPy[i]);
      }
    }
//=============================================================================

  








    for (int j=0; j<sortedJets.size(); j++) {
      double dJet = sortedJets[j].pt();

      hJet->Fill(dJet, dNorm);
//=============================================================================

      fastjet::Filter trimmer(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet = trimmer(sortedJets[j]);
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
        TVector3 v1sj; v1sj.SetPtEtaPhi(d1sj, trimmdSj[k1sj].eta(), trimmdSj[k1sj].phi());
        TVector3 v2sj; v2sj.SetPtEtaPhi(d2sj, trimmdSj[k2sj].eta(), trimmdSj[k2sj].phi());

        double dsj = d1sj - d2sj;
        double dsz = dsj / dJet;
        double dsr = v1sj.DeltaR(v2sj) / 2. / dJetR;

        hJetDsj->Fill(dJet, dsj, dNorm);
        hJetDsz->Fill(dJet, dsz, dNorm);
        hJetDsr->Fill(dJet, dsz, dsr, dNorm);
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
