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

const TString srcName = "AnaSjeQpyIncl";
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
//=============================================================================

  TH1D *hPtHat = new TH1D("hPtHat", "", 1000, 0., 1000.);
  enum { kWgt, kJet, kAje, k1sz, k1sA, k1sr, k2sz, k2sA, k2sr, kDsr, kVar };

  TFile *file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  TNtuple *nt = new TNtuple("nt", "", "fWgt:fJet:fAje:f1sj:f1sA:f1sr:f2sj:f2sA:f2sr:fDsr");
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

    for (Int_t i=0; i<pStack->GetNtrack(); i++) if (pStack->IsPhysicalPrimary(i)) {
      TParticle *pTrk = pStack->Particle(i); if (!pTrk) continue;
      if (TMath::Abs(pTrk->Eta())>dCutEtaMax) { pTrk = 0; continue; }

      fjInput.push_back(fastjet::PseudoJet(pTrk->Px(), pTrk->Py(), pTrk->Pz(), pTrk->P()));

      pTrk = 0;
    }
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInput, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJets = clustSeq.inclusive_jets(dJetsPtMin);
    std::vector<fastjet::PseudoJet> selectJets = selectJet(includJets);

    TVector3 vJet, v1sj, v2sj;
    for (int j=0; j<selectJets.size(); j++) {
      double dJet = selectJets[j].pt();
      vJet.SetPtEtaPhi(dJet, selectJets[j].eta(), selectJets[j].phi());

      fastjet::Filter trimmer(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet = trimmer(selectJets[j]);
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

      Float_t dVar[] = { 1., dJet, selectJets[j].area(), d1sj, -1., -1., d2sj, -1., -1., -1. };

      if (d1sj>0.) {
        v1sj.SetPtEtaPhi(d1sj, trimmdSj[k1sj].eta(), trimmdSj[k1sj].phi());
        dVar[k1sr] = v1sj.DeltaR(vJet);
        dVar[k1sA] = trimmdSj[k1sj].area();
      }

      if (d2sj>0.) {
        v2sj.SetPtEtaPhi(d2sj, trimmdSj[k2sj].eta(), trimmdSj[k2sj].phi());
        dVar[k2sr] = v2sj.DeltaR(vJet);
        dVar[k2sA] = trimmdSj[k2sj].area();
      }

      if ((d1sj>0.) && (d2sj>0.)) dVar[kDsr] = v2sj.DeltaR(v1sj);
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
