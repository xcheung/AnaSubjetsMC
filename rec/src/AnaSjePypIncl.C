#include <iostream>
#include <cfortran.h>

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
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TNtuple.h"

#include "TParticle.h"
#include "TParticlePDG.h"

#include "AliStack.h"
#include "AliHeader.h"
#include "AliRunLoader.h"

#include "AliGenPythiaEventHeader.h"

#include "util.h"
//=============================================================================

using namespace std;

const TString srcName = "AnaSjePypIncl";
//=============================================================================

int main(int argc, char* argv[])
{
  TApplication theApp(srcName.Data(), &argc, argv);
//=============================================================================

  for (int i=0; i<argc; i++) cout << i << ", " << argv[i] << endl;
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

  const int    multiLHC    = 2000;
  const double dJetsPtMin  = 20.00;
  const double dCutEtaMax  = 1.;
  const double dJetEtaMax  = 0.4;
  const double dJetAreaRef = TMath::Pi() * dJetR * dJetR;

  fastjet::GhostedAreaSpec areaSpc(dCutEtaMax);
  fastjet::JetDefinition   jetsDef(fastjet::antikt_algorithm, dJetR, fastjet::BIpt_scheme, fastjet::Best);
  fastjet::AreaDefinition  areaDef(fastjet::active_area_explicit_ghosts, areaSpc);

  fastjet::JetDefinition   bkgsDef(fastjet::kt_algorithm, 0.2, fastjet::BIpt_scheme, fastjet::Best);
  fastjet::AreaDefinition  aBkgDef(fastjet::active_area_explicit_ghosts, areaSpc);

  fastjet::Selector selectJet = fastjet::SelectorAbsEtaMax(dJetEtaMax);
  fastjet::Selector selectRho = fastjet::SelectorAbsEtaMax(dCutEtaMax-0.2);
  fastjet::Selector selecHard = fastjet::SelectorNHardest(2);
  fastjet::Selector selectBkg = selectRho * (!(selecHard));
  fastjet::JetMedianBackgroundEstimator bkgsEstimator(selectBkg, bkgsDef, aBkgDef);

  fastjet::JetDefinition subjDef(fastjet::kt_algorithm, dSjeR, fastjet::BIpt_scheme, fastjet::Best);
//=============================================================================

  TRandom3 *r3 = new TRandom3(0);
  TF1 *fBkg = BackgroundSpec();

  std::vector<fastjet::PseudoJet> fjInputVac;
  std::vector<fastjet::PseudoJet> fjInputMed;
//=============================================================================

  TFile *file = TFile::Open(Form("%s.root",sFile.Data()), "NEW"); TList *list = new TList();
  TH1D *hJetVac = new TH1D("hJetVac", "", 1000, 0., 1000.); hJetVac->Sumw2(); list->Add(hJetVac);
  TH2D *hJetNsjVac = new TH2D("hJetNsjVac", "", 1000, 0., 1000., 101, -0.5, 100.5); hJetNsjVac->Sumw2(); list->Add(hJetNsjVac);

  TH2D *hJetIsjVac = new TH2D("hJetIsjVac", "", 1000, 0., 1000., 1000, 0., 1000.); hJetIsjVac->Sumw2(); list->Add(hJetIsjVac);
  TH2D *hJet1sjVac = new TH2D("hJet1sjVac", "", 1000, 0., 1000., 1000, 0., 1000.); hJet1sjVac->Sumw2(); list->Add(hJet1sjVac);
  TH2D *hJet2sjVac = new TH2D("hJet2sjVac", "", 1000, 0., 1000., 1000, 0., 1000.); hJet2sjVac->Sumw2(); list->Add(hJet2sjVac);
  TH2D *hJetDsjVac = new TH2D("hJetDsjVac", "", 1000, 0., 1000., 1000, 0., 1000.); hJetDsjVac->Sumw2(); list->Add(hJetDsjVac);

  TH2D *hJetIszVac = new TH2D("hJetIszVac", "", 1000, 0., 1000.,  200, 0., 2.000); hJetIszVac->Sumw2(); list->Add(hJetIszVac);
  TH2D *hJet1szVac = new TH2D("hJet1szVac", "", 1000, 0., 1000.,  200, 0., 2.000); hJet1szVac->Sumw2(); list->Add(hJet1szVac);
  TH2D *hJet2szVac = new TH2D("hJet2szVac", "", 1000, 0., 1000.,  200, 0., 2.000); hJet2szVac->Sumw2(); list->Add(hJet2szVac);
  TH2D *hJetDszVac = new TH2D("hJetDszVac", "", 1000, 0., 1000.,  200, 0., 2.000); hJetDszVac->Sumw2(); list->Add(hJetDszVac);

  TH2D *hJetDsjBkg = new TH2D("hJetDsjBkg", "", 1000, 0., 1000., 1000, 0., 1000.); hJetDsjBkg->Sumw2(); list->Add(hJetDsjBkg);
  TH2D *hJetDsjSub = new TH2D("hJetDsjSub", "", 1000, 0., 1000., 1000, 0., 1000.); hJetDsjSub->Sumw2(); list->Add(hJetDsjSub);

  TH2D *hJetDszBkg = new TH2D("hJetDszBkg", "", 1000, 0., 1000.,  200, 0., 2.000); hJetDszBkg->Sumw2(); list->Add(hJetDszBkg);
  TH2D *hJetDszSub = new TH2D("hJetDszSub", "", 1000, 0., 1000.,  200, 0., 2.000); hJetDszSub->Sumw2(); list->Add(hJetDszSub);

  TH2D *hJetDsjBdf = new TH2D("hJetDsjBdf", "", 1000, 0., 1000.,  400, -20., 20.); hJetDsjBdf->Sumw2(); list->Add(hJetDsjBdf);
  TH2D *hJetDsjSdf = new TH2D("hJetDsjSdf", "", 1000, 0., 1000.,  400, -20., 20.); hJetDsjSdf->Sumw2(); list->Add(hJetDsjSdf);

  TH2D *hJetDszBdf = new TH2D("hJetDszBdf", "", 1000, 0., 1000.,  400, -2.0, 2.0); hJetDszBdf->Sumw2(); list->Add(hJetDszBdf);
  TH2D *hJetDszSdf = new TH2D("hJetDszSdf", "", 1000, 0., 1000.,  400, -2.0, 2.0); hJetDszSdf->Sumw2(); list->Add(hJetDszSdf);
//=============================================================================

  AliRunLoader *rl = AliRunLoader::Open(Form("%s/galice.root",sPath.Data())); if (!rl) return -1;

  if (rl->LoadHeader()) return -1;
  if (rl->LoadKinematics("READ")) return -1;
//=============================================================================

  for (Int_t iEvent=0; iEvent<rl->GetNumberOfEvents(); iEvent++) {
    fjInputVac.resize(0);
    fjInputMed.resize(0);
    if (rl->GetEvent(iEvent)) continue;
//=============================================================================

    AliStack  *pStack  = rl->Stack();     if (!pStack)  continue;
    AliHeader *pHeader = rl->GetHeader(); if (!pHeader) continue;
//=============================================================================

    AliGenPythiaEventHeader *pHeadPy = (AliGenPythiaEventHeader*)pHeader->GenEventHeader();

    if (!pHeadPy) continue;
//=============================================================================

    TVector3 vPar;
    for (Int_t i=0; i<pStack->GetNtrack(); i++) if (pStack->IsPhysicalPrimary(i)) {
      TParticle *pTrk = pStack->Particle(i); if (!pTrk) continue;
      double dEta = pTrk->Eta(); if (TMath::Abs(dEta)>dCutEtaMax) { pTrk = 0; continue; }

      double dTrk = pTrk->Pt();
      double dPhi = pTrk->Phi();
      vPar.SetPtEtaPhi(dTrk, dEta, dPhi);
      fjInputVac.push_back(fastjet::PseudoJet(vPar.Px(), vPar.Py(), vPar.Pz(), vPar.Mag()));
      fjInputVac.back().set_user_info(new UserInfoTrk(false));
      fjInputVac.back().set_user_index(i);

      pTrk = 0;
    }
//=============================================================================

    for (int i=0; i<=multiLHC; i++) {
      double dPt = fBkg->GetRandom(fgkPtBkgMin, fgkPtBkgMax); if (dPt<0.001) continue;

      vPar.SetPtEtaPhi(dPt, r3->Uniform(-1.*dCutEtaMax,dCutEtaMax), r3->Uniform(0.,TMath::TwoPi()));
      fjInputMed.push_back(fastjet::PseudoJet(vPar.Px(), vPar.Py(), vPar.Pz(), vPar.Mag()));
      fjInputMed.back().set_user_info(new UserInfoTrk(true));
      fjInputMed.back().set_user_index(-10);
    }

    fjInputMed.insert(fjInputMed.end(), fjInputVac.begin(),fjInputVac.end());
//=============================================================================

    fastjet::ClusterSequenceArea clustSeqVac(fjInputVac, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJetVac = clustSeqVac.inclusive_jets(dJetsPtMin);
    std::vector<fastjet::PseudoJet> selectJetVac = selectJet(includJetVac);
//=============================================================================

    for (int j=0; j<selectJetVac.size(); j++) {
      SetJetUserInfo(selectJetVac[j]);
      selectJetVac[j].set_user_index(j);
      double dJet = selectJetVac[j].pt(); hJetVac->Fill(dJet);

      fastjet::Filter trimmer(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet = trimmer(selectJetVac[j]);
      std::vector<fastjet::PseudoJet> trimmdSj = trimmdJet.pieces();

      int nIsj = 0;
      double d1sj = -1.; int k1sj = -1;
      double d2sj = -1.; int k2sj = -1;
      for (int i=0; i<trimmdSj.size(); i++) {
        double dIsj = trimmdSj[i].pt(); if (dIsj<0.001) continue;
        hJetIsjVac->Fill(dJet,dIsj); hJetIszVac->Fill(dJet,dIsj/dJet); nIsj += 1;
        if (dIsj>d1sj) { d2sj = d1sj; k2sj = k1sj; d1sj = dIsj; k1sj = i; } else if (dIsj>d2sj) { d2sj = dIsj; k2sj = i; }
      }

      double d1uj = 0., d2uj = 0.;
      hJetNsjVac->Fill(dJet, nIsj);
      if (d1sj>0.) { hJet1sjVac->Fill(dJet, d1sj); hJet1szVac->Fill(dJet, d1sj/dJet); d1uj = d1sj; }
      if (d2sj>0.) { hJet2sjVac->Fill(dJet, d2sj); hJet2szVac->Fill(dJet, d2sj/dJet); d2uj = d2sj; }

      hJetDsjVac->Fill(dJet,  d1uj-d2uj);
      hJetDszVac->Fill(dJet, (d1uj-d2uj)/dJet);
    }
//=============================================================================

    bkgsEstimator.set_particles(fjInputMed);
    double dBkgRho = bkgsEstimator.rho();
    double dBkgRms = bkgsEstimator.sigma();

    fastjet::ClusterSequenceArea clustSeqMed(fjInputMed, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJetMed = clustSeqMed.inclusive_jets(dJetsPtMin);
    std::vector<fastjet::PseudoJet> selectJetMed = selectJet(includJetMed);

    for (int j=0; j<selectJetMed.size(); j++) {
      SetJetUserInfo(selectJetMed[j]);
      selectJetMed[j].set_user_index(j);
      if (selectJetMed[j].user_info<UserInfoJet>().IsBkg()) continue;

      for (int i=0; i<selectJetVac.size(); i++) {
        if (CalcDeltaR(selectJetMed[j],selectJetVac[i])>0.8) continue;
        DoTrkMatch(selectJetMed[j], selectJetVac[i]);
      }
    }
//=============================================================================

    for (int j=0; j<selectJetMed.size(); j++) {
      if (selectJetMed[j].user_info<UserInfoJet>().IsBkg()) continue;
      bool bMatched = IsJetTrkMatched(selectJetMed[j],selectJetVac);

      int kVac = -1;
      if (bMatched) {
        kVac = selectJetMed[j].user_info<UserInfoJet>().GetTrkMatchedJetID();

        if (kVac<0) {
          bMatched = false;
        } else if (selectJetVac[kVac].user_info<UserInfoJet>().GetTrkMatchedJetFr()<0.5) {
          bMatched = false;
        }
      }

      if (!bMatched) continue;
//=============================================================================

      double dJet = selectJetVac[kVac].pt();
      fastjet::Filter trimmerMed(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJetMed = trimmerMed(selectJetMed[j]);
      std::vector<fastjet::PseudoJet> trimmdSjMed = trimmdJetMed.pieces();

      double d1jb = -9999.; int k1jb = -1;
      double d2jb = -9999.; int k2jb = -1;
      double d1ja = -9999.; int k1ja = -1;
      double d2ja = -9999.; int k2ja = -1;
      for (int i=0; i<trimmdSjMed.size(); i++) {
        double dIjb = trimmdSjMed[i].pt(); if (dIjb<0.001) continue;
        double dIja = dIjb - (dBkgRho * trimmdSjMed[i].area());
        if (dIjb>d1jb) { d2jb = d1jb; k2jb = k1jb; d1jb = dIjb; k1jb = i; } else if (dIjb>d2jb) { d2jb = dIjb; k2jb = i; }
        if (dIja>d1ja) { d2ja = d1ja; k2ja = k1ja; d1ja = dIja; k1ja = i; } else if (dIja>d2ja) { d2ja = dIja; k2ja = i; }
      }

      double d1uj = (k1jb>=0 ? d1jb : 0.);
      double d2uj = (k2jb>=0 ? d2jb : 0.);
      double dbjj = d1uj - d2uj; hJetDsjBkg->Fill(dJet, dbjj);
      double dbjz = dbjj / dJet; hJetDszBkg->Fill(dJet, dbjz);

      d1uj = (k1ja>=0 ? d1ja : 0.);
      d2uj = (k2ja>=0 ? d2ja : 0.);
      double dajj = d1uj - d2uj; hJetDsjSub->Fill(dJet, dajj);
      double dajz = dajj / dJet; hJetDszSub->Fill(dJet, dajz);
//=============================================================================

      fastjet::Filter trimmerVac(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJetVac = trimmerVac(selectJetVac[kVac]);
      std::vector<fastjet::PseudoJet> trimmdSjVac = trimmdJetVac.pieces();

      double d1sj = -1.; int k1sj = -1;
      double d2sj = -1.; int k2sj = -1;
      for (int i=0; i<trimmdSjVac.size(); i++) {
        double dIsj = trimmdSjVac[i].pt(); if (dIsj<0.001) continue;
        if (dIsj>d1sj) { d2sj = d1sj; k2sj = k1sj; d1sj = dIsj; k1sj = i; } else if (dIsj>d2sj) { d2sj = dIsj; k2sj = i; }
      }

      d1uj = (k1sj>=0 ? d1sj : 0.);
      d2uj = (k2sj>=0 ? d2sj : 0.);
      double dvsj = d1uj - d2uj;
      double dvsz = dvsj / dJet;

      hJetDsjBdf->Fill(dJet, dbjj-dvsj); hJetDszBdf->Fill(dJet, dbjz-dvsz);
      hJetDsjSdf->Fill(dJet, dajj-dvsj); hJetDszSdf->Fill(dJet, dajz-dvsz);
    }
//=============================================================================

    pStack  = 0;
    pHeadPy = 0;
    pHeader = 0;
  }
//=============================================================================

  rl->UnloadgAlice();
  rl->UnloadHeader();
  rl->UnloadKinematics();
  rl->RemoveEventFolder();
//=============================================================================

  file->cd(); list->Write(); file->Close();
//=============================================================================

  cout << "DONE" << endl;
//=============================================================================

  return 0;
}
