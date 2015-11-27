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

const TString srcName = "AnaSjeQpyIncl_sAntikT";
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
  fastjet::JetDefinition subjDef(fastjet::antikt_algorithm, dSjeR, fastjet::BIpt_scheme, fastjet::Best);
//=============================================================================

  std::vector<fastjet::PseudoJet> fjInput;
  const Double_t dCut = TMath::TwoPi() / 3.;
//=============================================================================

  TH1D *hPtHat = new TH1D("hPtHat", "", 1000, 0., 1000.);
  enum { kWgt, kLje, kLjr, kLtk, kLtr, kJet, kAje, kMje, k1sz, k1sA, k1sm, k1sr, k2sz, k2sA, k2sm, k2sr, kDsm, kDsr, kVar };

  TFile *file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  TNtuple *nt = new TNtuple("nt", "", "fWgt:fLje:fLjr:fLtk:fLtr:fJet:fAje:fMje:f1sj:f1sA:f1sm:f1sr:f2sj:f2sA:f2sm:f2sr:fDsm:fDsr");
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

    double dLtk = -1.;
    TVector3 vPar, vLtk;
    for (Int_t i=0; i<pStack->GetNtrack(); i++) if (pStack->IsPhysicalPrimary(i)) {
      TParticle *pTrk = pStack->Particle(i); if (!pTrk) continue;
      double dEta = pTrk->Eta(); if (TMath::Abs(dEta)>dCutEtaMax) { pTrk = 0; continue; }

      double dTrk = pTrk->Pt();
      double dPhi = pTrk->Phi();
      vPar.SetPtEtaPhi(dTrk, dEta, dPhi);
      fjInput.push_back(fastjet::PseudoJet(vPar.Px(), vPar.Py(), vPar.Pz(), vPar.Mag()));
      if (dTrk>dLtk) { dLtk = dTrk; vLtk.SetPtEtaPhi(dTrk, dEta, dPhi); }

      pTrk = 0;
    }
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInput, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJets = clustSeq.inclusive_jets(dJetsPtMin);
    std::vector<fastjet::PseudoJet> selectJets = selectJet(includJets);
//=============================================================================

    if (selectJets.size()>0) {
      std::vector<fastjet::PseudoJet> sortedJets = fastjet::sorted_by_pt(selectJets);
      TVector3 vLje; vLje.SetPtEtaPhi(sortedJets[0].pt(), sortedJets[0].eta(), sortedJets[0].phi());

      TVector3 vJet;
      int kJrl = -1; double dJrl = -1.;
      int kTrl = -1; double dTrl = -1.;
      for (int j=0; j<sortedJets.size(); j++) {
        double dJet = sortedJets[j].pt();
        sortedJets[j].set_user_index(-1);
        vJet.SetPtEtaPhi(dJet, sortedJets[j].eta(), sortedJets[j].phi());
        if (TMath::Abs(vJet.DeltaPhi(vLje))>dCut) { sortedJets[j].set_user_index(1); if (dJet>dJrl) { dJrl = dJet; kJrl = j; } }
        if (TMath::Abs(vJet.DeltaPhi(vLtk))>dCut) { sortedJets[j].set_user_index(2); if (dJet>dTrl) { dTrl = dJet; kTrl = j; } }
      }
//=============================================================================

      TVector3 v1sj, v2sj;
      for (int j=0; j<sortedJets.size(); j++) {
        Float_t dVar[kVar]; for (Int_t i=0; i<kVar; i++) dVar[i] = -1.; dVar[kWgt] = 1.;
        vJet.SetPtEtaPhi(sortedJets[j].pt(), sortedJets[j].eta(), sortedJets[j].phi());
//=============================================================================

        dVar[kLje] = vLje.Pt(); if (sortedJets[j].user_index()==1) { dVar[kLjr] = ((kJrl==j) ? 1.5 : 0.5); }
        dVar[kLtk] = vLtk.Pt(); if (sortedJets[j].user_index()==2) { dVar[kLtr] = ((kTrl==j) ? 1.5 : 0.5); }
//=============================================================================

        dVar[kJet] = sortedJets[j].pt();
        dVar[kAje] = sortedJets[j].area();
        dVar[kMje] = sortedJets[j].m();
//=============================================================================

        fastjet::Filter trimmer(subjDef, fastjet::SelectorPtFractionMin(0.));
        fastjet::PseudoJet trimmdJet = trimmer(sortedJets[j]);
        std::vector<fastjet::PseudoJet> trimmdSj = trimmdJet.pieces();

        double d1sj = -1.; int k1sj = -1;
        double d2sj = -1.; int k2sj = -1;
        for (int i=0; i<trimmdSj.size(); i++) {
          double dIsj = trimmdSj[i].pt(); if (dIsj<0.001) continue;

          if (dIsj>d1sj) {
            d2sj = d1sj; k2sj = k1sj;
            d1sj = dIsj; k1sj = i;
          } else if (dIsj>d2sj) {
            d2sj = dIsj; k2sj = i;
          }
        }
//=============================================================================

        if (d1sj>0.) {
          v1sj.SetPtEtaPhi(d1sj, trimmdSj[k1sj].eta(), trimmdSj[k1sj].phi());
          dVar[k1sz] = d1sj;
          dVar[k1sA] = trimmdSj[k1sj].area();
          dVar[k1sm] = trimmdSj[k1sj].m();
          dVar[k1sr] = v1sj.DeltaR(vJet);
        }

        if (d2sj>0.) {
          v2sj.SetPtEtaPhi(d2sj, trimmdSj[k2sj].eta(), trimmdSj[k2sj].phi());
          dVar[k2sz] = d2sj;
          dVar[k2sA] = trimmdSj[k2sj].area();
          dVar[k2sm] = trimmdSj[k2sj].m();
          dVar[k2sr] = v2sj.DeltaR(vJet);
        }

        if ((d1sj>0.) && (d2sj>0.)) dVar[kDsr] = v2sj.DeltaR(v1sj);

        nt->Fill(dVar);
      }
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
