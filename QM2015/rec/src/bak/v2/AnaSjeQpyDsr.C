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
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TFile.h"
#include "TList.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "THnSparse.h"
#include "TF1.h"

#include "TParticle.h"
#include "TParticlePDG.h"

#include "AliStack.h"
#include "AliHeader.h"
#include "AliRunLoader.h"

#include "AliGenPythiaEventHeader.h"
//=============================================================================

using namespace std;

const TString srcName = "AnaSjeQpyDsr";
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
  fastjet::JetDefinition   jetsDef(fastjet::antikt_algorithm, dJetR, fastjet::E_scheme, fastjet::Best);

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

  fastjet::JetDefinition subjDef(fastjet::kt_algorithm, dSjeR, fastjet::E_scheme, fastjet::Best);
//=============================================================================

  std::vector<fastjet::PseudoJet> fjInput;
  const double dMass = TDatabasePDG::Instance()->GetParticle(211)->Mass();
//=============================================================================

  TList *list = new TList();
  TH1D *hPtHat = new TH1D("hPtHat", "", 1000, 0., 1000.);

  TH1D *hJet = new TH1D("hJet", "", 1000, 0., 1000.); hJet->Sumw2(); list->Add(hJet);

  enum                    {  kJet,   kDsz,   k1sr,   k2sr,   kDsr, kVar };
  const TString sHist[] = { "aJet", "aDsz", "a1sr", "a2sr", "aDsr" };
  const Int_t      nv[] = {   1000,    120,    500,    500,    500 };
  const Double_t dMin[] = {     0.,     0.,     0.,     0.,     0. };
  const Double_t dMax[] = {  1000.,    1.2,     5.,     5.,     5. };

  THnSparseD *hs = new THnSparseD("hs", "", kVar, nv, dMin, dMax); hs->Sumw2();
  for (Int_t i=0; i<kVar; i++) hs->GetAxis(i)->SetName(sHist[i].Data()); list->Add(hs);
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

    TLorentzVector vPar;
    for (Int_t i=0; i<pStack->GetNtrack(); i++) if (pStack->IsPhysicalPrimary(i)) {
      TParticle *pTrk = pStack->Particle(i); if (!pTrk) continue;
      if (TMath::Abs(pTrk->Eta())>dCutEtaMax) { pTrk = 0; continue; }
//    TParticlePDG *pPDG = pTrk->GetPDG(); if (!pPDG) { pTrk = 0; continue; }

      vPar.SetPtEtaPhiM(pTrk->Pt(), pTrk->Eta(), pTrk->Phi(), dMass);
      fjInput.push_back(fastjet::PseudoJet(vPar.Px(), vPar.Py(), vPar.Pz(), vPar.E()));

//    pPDG = 0;
      pTrk = 0;
    }
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInput, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJets = clustSeq.inclusive_jets(dJetsPtMin);
//  std::vector<fastjet::PseudoJet> subtedJets = bkgSubtractor(includJets);
    std::vector<fastjet::PseudoJet> selectJets = selectJet(includJets);
//  std::vector<fastjet::PseudoJet> sortedJets = fastjet::sorted_by_pt(selectJets);

    for (int j=0; j<selectJets.size(); j++) {
      double dJet = selectJets[j].pt();

      hJet->Fill(dJet);
//=============================================================================

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

      if ((d1sj>0.) && (d2sj>0.)) {
        TVector3 vJet; vJet.SetPtEtaPhi(dJet,  selectJets[j].eta(),  selectJets[j].phi());
        TVector3 v1sj; v1sj.SetPtEtaPhi(d1sj, trimmdSj[k1sj].eta(), trimmdSj[k1sj].phi());
        TVector3 v2sj; v2sj.SetPtEtaPhi(d2sj, trimmdSj[k2sj].eta(), trimmdSj[k2sj].phi());

        Double_t dVar[] = { dJet, (d1sj-d2sj)/dJet, v1sj.DeltaR(vJet)/2./dJetR,
                                                    v2sj.DeltaR(vJet)/2./dJetR,
                                                    v2sj.DeltaR(v1sj)/2./dJetR };

        hs->Fill(dVar);
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

  TFile *file = TFile::Open(Form("%s/pyxsec_hists.root",sPath.Data()), "READ");
  TList *lXsc = (TList*)file->Get("cFilterList");
  file->Close();

  TH1D     *hWeightSum = (TH1D*)lXsc->FindObject("h1Trials");   hWeightSum->SetName("hWeightSum");
  TProfile *hSigmaGen  = (TProfile*)lXsc->FindObject("h1Xsec"); hSigmaGen->SetName("hSigmaGen");
//=============================================================================

  file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  hPtHat->Write();
  hWeightSum->Write();
  hSigmaGen->Write();
  list->Write();
  file->Close();
//=============================================================================

  cout << "DONE" << endl;
//=============================================================================

  return 0;
}
