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
#include "TH1D.h"
#include "TProfile.h"
#include "TNtuple.h"

#include "TParticle.h"
#include "TParticlePDG.h"

#include "AliStack.h"
#include "AliHeader.h"
#include "AliRunLoader.h"

#include "AliGenPythiaEventHeader.h"
//=============================================================================

using namespace std;

const TString srcName = "AnaSjeQpyInclAJ";
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

  const double dJetsPtMin  = 0.001;
  const double dCutEtaMax  = 1.6;
  const double dJetEtaMax  = 1.;
  const double dJetAreaRef = TMath::Pi() * dJetR * dJetR;

  fastjet::GhostedAreaSpec areaSpc(dCutEtaMax);
  fastjet::JetDefinition   jetsDef(fastjet::antikt_algorithm, dJetR, fastjet::BIpt_scheme, fastjet::Best);
  fastjet::AreaDefinition  areaDef(fastjet::active_area_explicit_ghosts,areaSpc);

  fastjet::Selector selectJet = fastjet::SelectorAbsEtaMax(dJetEtaMax);
  fastjet::JetDefinition subjDef(fastjet::kt_algorithm, dSjeR, fastjet::BIpt_scheme, fastjet::Best);
//=============================================================================

  std::vector<fastjet::PseudoJet> fjInput;
  const Double_t dCut = TMath::TwoPi() / 3.;
//=============================================================================

  TH1D *hPtHat = new TH1D("hPtHat", "", 1000, 0., 1000.);
  enum { kWgt, kXsc, k1je, k1jA, k2je, k2jA, kDje, k11j, k11A, k11r, k12j, k12A, k12r, k1dr, k21j, k21A, k21r, k22j, k22A, k22r, k2dr, kVar };

  TFile *file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  TNtuple *nt = new TNtuple("nt", "", "fWgt:fXsc:f1je:f1jA:f2je:f2jA:fDje:f11j:f11A:f11r:f12j:f12A:f12r:f1dr:f21j:f21A:f21r:f22j:f22A:f22r:f2dr");
//=============================================================================

  AliRunLoader *rl = AliRunLoader::Open(Form("%s/galice.root",sPath.Data())); if (!rl) return -1;

  if (rl->LoadHeader()) return -1;
  if (rl->LoadKinematics("READ")) return -1;
//=============================================================================

  for (Int_t iEvent=0; iEvent<rl->GetNumberOfEvents(); iEvent++) {
    fjInput.resize(0);
    if (rl->GetEvent(iEvent)) continue;
//=============================================================================

    AliStack  *pStack  = rl->Stack();     if (!pStack)  continue;
    AliHeader *pHeader = rl->GetHeader(); if (!pHeader) continue;
//=============================================================================

    AliGenPythiaEventHeader *pHeadPy = (AliGenPythiaEventHeader*)pHeader->GenEventHeader();

    if (!pHeadPy) continue;
    hPtHat->Fill(pHeadPy->GetPtHard());
//=============================================================================

    TVector3 vPar;
    for (Int_t i=0; i<pStack->GetNtrack(); i++) if (pStack->IsPhysicalPrimary(i)) {
      TParticle *pTrk = pStack->Particle(i); if (!pTrk) continue;
      double dEta = pTrk->Eta(); if (TMath::Abs(dEta)>dCutEtaMax) { pTrk = 0; continue; }

      double dTrk = pTrk->Pt();
      double dPhi = pTrk->Phi();
      vPar.SetPtEtaPhi(dTrk, dEta, dPhi);
      fjInput.push_back(fastjet::PseudoJet(vPar.Px(), vPar.Py(), vPar.Pz(), vPar.Mag()));

      pTrk = 0;
    }
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInput, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJets = clustSeq.inclusive_jets(dJetsPtMin);
    std::vector<fastjet::PseudoJet> selectJets = selectJet(includJets);
    std::vector<fastjet::PseudoJet> sortedJets = fastjet::sorted_by_pt(selectJets);
//=============================================================================

    Float_t dVar[kVar];
    if (sortedJets.size()>1) {
      TVector3 v1je, v2je, v1sj, v2sj;
      dVar[kWgt] = 1.; dVar[kXsc] = 1.;

      dVar[k11j] = -1.; dVar[k11A] = -1.; dVar[k11r] = -1.;
      dVar[k12j] = -1.; dVar[k12A] = -1.; dVar[k12r] = -1.; dVar[k1dr] = -1.;

      dVar[k21j] = -1.; dVar[k21A] = -1.; dVar[k21r] = -1.;
      dVar[k22j] = -1.; dVar[k22A] = -1.; dVar[k22r] = -1.; dVar[k2dr] = -1.;
//=============================================================================

      dVar[k1je] = sortedJets[0].pt();
      dVar[k1jA] = sortedJets[0].area();
      v1je.SetPtEtaPhi(dVar[k1je], sortedJets[0].eta(), sortedJets[0].phi());

      fastjet::Filter trimmer1(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet1 = trimmer1(sortedJets[0]);
      std::vector<fastjet::PseudoJet> trimmdSj1 = trimmdJet1.pieces();

      double d1sj = -1.; int k1sj = -1;
      double d2sj = -1.; int k2sj = -1;
      for (int i=0; i<trimmdSj1.size(); i++) {
        double dIsj = trimmdSj1[i].pt(); if (dIsj<0.001) continue;

        if (dIsj>d1sj) {
          d2sj = d1sj; k2sj = k1sj;
          d1sj = dIsj; k1sj = i;
        } else if (dIsj>d2sj) {
          d2sj = dIsj; k2sj = i;
        }
      }

      if (d1sj>0.) {
        v1sj.SetPtEtaPhi(d1sj, trimmdSj1[k1sj].eta(), trimmdSj1[k1sj].phi());
        dVar[k11j] = d1sj;
        dVar[k11A] = trimmdSj1[k1sj].area();
        dVar[k11r] = v1sj.DeltaR(v1je);
      }

      if (d2sj>0.) {
        v2sj.SetPtEtaPhi(d2sj, trimmdSj1[k2sj].eta(), trimmdSj1[k2sj].phi());
        dVar[k12j] = d2sj;
        dVar[k12A] = trimmdSj1[k2sj].area();
        dVar[k12r] = v2sj.DeltaR(v1je);
      }

      if ((d1sj>0.) && (d2sj>0.)) dVar[k1dr] = v2sj.DeltaR(v1sj);
//=============================================================================

      dVar[k2je] = sortedJets[1].pt();
      dVar[k2jA] = sortedJets[1].area();
      v2je.SetPtEtaPhi(dVar[k2je], sortedJets[1].eta(), sortedJets[1].phi());

      fastjet::Filter trimmer2(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet2 = trimmer2(sortedJets[1]);
      std::vector<fastjet::PseudoJet> trimmdSj2 = trimmdJet2.pieces();

      d1sj = -1.; k1sj = -1;
      d2sj = -1.; k2sj = -1;
      for (int i=0; i<trimmdSj2.size(); i++) {
        double dIsj = trimmdSj2[i].pt(); if (dIsj<0.001) continue;

        if (dIsj>d1sj) {
          d2sj = d1sj; k2sj = k1sj;
          d1sj = dIsj; k1sj = i;
        } else if (dIsj>d2sj) {
          d2sj = dIsj; k2sj = i;
        }
      }

      if (d1sj>0.) {
        v1sj.SetPtEtaPhi(d1sj, trimmdSj2[k1sj].eta(), trimmdSj2[k1sj].phi());
        dVar[k21j] = d1sj;
        dVar[k21A] = trimmdSj2[k1sj].area();
        dVar[k21r] = v1sj.DeltaR(v2je);
      }

      if (d2sj>0.) {
        v2sj.SetPtEtaPhi(d2sj, trimmdSj2[k2sj].eta(), trimmdSj2[k2sj].phi());
        dVar[k22j] = d2sj;
        dVar[k22A] = trimmdSj2[k2sj].area();
        dVar[k22r] = v2sj.DeltaR(v2je);
      }

      if ((d1sj>0.) && (d2sj>0.)) dVar[k2dr] = v2sj.DeltaR(v1sj);
//=============================================================================

      dVar[kDje] = v1je.DeltaPhi(v2je);
//=============================================================================

      nt->Fill(dVar);
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

  file->cd(); nt->Write(); file->Close();
//=============================================================================

  file = TFile::Open(Form("%s/pyxsec_hists.root",sPath.Data()), "READ");
  TList *lXsc = (TList*)file->Get("cFilterList");
  file->Close();

  TH1D     *hWeightSum = (TH1D*)lXsc->FindObject("h1Trials");   hWeightSum->SetName("hWeightSum");
  TProfile *hSigmaGen  = (TProfile*)lXsc->FindObject("h1Xsec"); hSigmaGen->SetName("hSigmaGen");
//=============================================================================

  sFile.ReplaceAll("out", "wgt");
  file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  hPtHat->Write();
  hWeightSum->Write();
  hSigmaGen->Write();
  file->Close();
//=============================================================================

  cout << "DONE" << endl;
//=============================================================================

  return 0;
}
