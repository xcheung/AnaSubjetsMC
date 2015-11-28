#include <iostream>

#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/AreaDefinition.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/tools/Filter.hh"

#include "TApplication.h"
#include "TString.h"
#include "TMath.h"
#include "TVector3.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

#include "TPicoVector.h"
#include "TPicoParticle.h"
#include "TPicoPiece.h"
#include "TPicoJet.h"
#include "TPicoHeader.h"
#include "TPicoSimEvent.h"
#include "TPicoJetEvent.h"
//=============================================================================

using namespace std;

const TString srcName = "AnaRecPicoJetEvent";
//=============================================================================

int main(int argc, char* argv[])
{
  TApplication theApp(srcName.Data(), &argc, argv);
  for (int i=0; i<argc; i++) cout << "arg[" << i << "] = " << argv[i] << endl;
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

  std::vector<fastjet::PseudoJet> fjInput;
//=============================================================================

  TChain *chain = new TChain("treePicoSim");
  chain->Add(Form("%s/%s.root",sPath.Data(),sFile.Data()));
  TPicoSimEvent *pEvent = new TPicoSimEvent(); pEvent->ReadFromTree(chain);
//=============================================================================

  TFile *file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  TTree *tree = new TTree("treePicoJet", "Pico Jet Event Tree");

  TPicoJetEvent *pJetEv = new TPicoJetEvent(); pJetEv->Write2Tree(tree);
//=============================================================================

  for (Int_t iEvent=0; iEvent<chain->GetEntries(); iEvent++) {
    pJetEv->Reset();
    fjInput.resize(0);
    chain->GetEntry(iEvent);
//=============================================================================

    TPicoHeader *pHeader = pEvent->Header();
    pJetEv->Header()->Set(*(pHeader->Leading()),
                            pHeader->PtHat(),
                            pHeader->Weight(),
                            pHeader->Xsect(),
                            pHeader->BkgRho());
    pHeader = 0;
//=============================================================================

    TVector3 vTrk;
    for (Int_t i=0; i<pEvent->GetNumberOfParticles(); i++) {
      TPicoParticle *p = pEvent->Particle(i); if (!p) continue;
      Double_t dTrkPt  = p->Pt();  if (dTrkPt<0.5) continue;
      Double_t dTrkEta = p->Eta(); if (TMath::Abs(dTrkEta)>dCutEtaMax) continue;
      vTrk.SetPtEtaPhi(dTrkPt, dTrkEta, p->Phi());

      fjInput.push_back(fastjet::PseudoJet(vTrk.Px(),vTrk.Py(),vTrk.Pz(),vTrk.Mag()));
      p = 0;
    }
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInput, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJets = clustSeq.inclusive_jets(dJetsPtMin);
    std::vector<fastjet::PseudoJet> selectJets = selectJet(includJets);
    std::vector<fastjet::PseudoJet> sortedJets = fastjet::sorted_by_pt(selectJets);
//=============================================================================

    for (unsigned int j=0; j<sortedJets.size(); j++) {
      TPicoJet *pJet = new TPicoJet(sortedJets[j].pt(),
                                    sortedJets[j].eta(),
                                    sortedJets[j].phi(),
                            j, -1., sortedJets[j].area());
//=============================================================================

      fastjet::Filter trimmer(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet = trimmer(sortedJets[j]);
      std::vector<fastjet::PseudoJet> trimmdSj = trimmdJet.pieces();
      std::vector<fastjet::PseudoJet> sortedSj = fastjet::sorted_by_pt(trimmdSj);

      for (unsigned int i=0; i<sortedSj.size(); i++) if (sortedSj[i].pt()>0.1) {
        pJet->AddPiece(TPicoPiece(sortedSj[i].pt(),
                                  sortedSj[i].eta(),
                                  sortedSj[i].phi(),
                               i, sortedSj[i].area()));
      }
//=============================================================================

      pJetEv->AddJet(pJet);
      delete pJet; pJet = 0;
    }
//=============================================================================

    tree->Fill();
  }
//=============================================================================

  file->cd(); tree->Write(); file->Close();
//=============================================================================

  cout << "DONE" << endl;
//=============================================================================

  return 0;
}
