#include <iostream>

#include "HepMC/IO_GenEvent.h"
#include "HepMC/GenEvent.h"

#ifdef HEPMC_HAS_UNITS
#include "HepMC/Units.h"
#endif

#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/AreaDefinition.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/tools/Filter.hh"

#include "TRandom3.h"
#include "TString.h"
#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"

#include "TPicoVector.h"
#include "TPicoPiece.h"
#include "TPicoJet.h"
#include "TPicoHeader.h"
#include "TPicoEvent.h"
//=============================================================================

using namespace std;

const TString srcName = "AnaRecoPicoEvents";
//=============================================================================

int Run(const char *aPath,
        const char *aFile,
        const char *aJetR,
        const char *aSjeR)
{
  TString sPath = aPath; if (sPath.IsNull()) return -1;
  TString sFile = aFile; if (sFile.IsNull()) return -1;
  TString sJetR = aJetR; if (sJetR.IsNull()) return -1;
  TString sSjeR = aSjeR; if (sSjeR.IsNull()) return -1;
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
//=============================================================================

  std::vector<fastjet::PseudoJet> fjInput;
//=============================================================================

  TH1D *hWeightSum = new TH1D("hWeightSum", "", 1, 0., 1.);

  TFile *file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  TTree *tree = new TTree("treePico", "Pico Event Tree");

  TPicoEvent *pEvent = new TPicoEvent(); pEvent->Write2Tree(tree);
//=============================================================================

  HepMC::IO_GenEvent ascii_in(Form("%s/%s.hepmc",sPath.Data(),sFile.Data()), std::ios::in);
  HepMC::GenEvent *evt = ascii_in.read_next_event();

  while (evt) {
    pEvent->Reset();
    fjInput.resize(0);
    double dWeight = evt->weights().back();
    double dXsect  = evt->cross_section()->cross_section() / 1e9;
    hWeightSum->Fill(0.5, dWeight);
//=============================================================================

    double dLtk = -1.;
    TVector3 vTrk, vLtk;
    for (HepMC::GenEvent::particle_const_iterator p=evt->particles_begin(); p!=evt->particles_end(); ++p) if ((*p)->status()==1) {
      double dTrkPt  = (*p)->momentum().perp(); if (dTrkPt<0.5) continue;
      double dTrkEta = (*p)->momentum().eta();  if (TMath::Abs(dTrkEta)>dCutEtaMax) continue;
      double dTrkPhi = (*p)->momentum().phi();  vTrk.SetPtEtaPhi(dTrkPt, dTrkEta, dTrkPhi);

      fjInput.push_back(fastjet::PseudoJet(vTrk.Px(), vTrk.Py(), vTrk.Pz(), vTrk.Mag()));
      if (dTrkPt>dLtk) { dLtk = dTrkPt; vLtk.SetPtEtaPhi(dTrkPt, dTrkEta, dTrkPhi); }
    }
//=============================================================================

    pEvent->Header()->Set(dXsect, dWeight, TPicoVector(vLtk.Pt(),vLtk.Eta(),vLtk.Phi()));
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInput, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJets = clustSeq.inclusive_jets(dJetsPtMin);
    std::vector<fastjet::PseudoJet> selectJets = selectJet(includJets);
    std::vector<fastjet::PseudoJet> sortedJets = fastjet::sorted_by_pt(selectJets);
//=============================================================================

    for (unsigned int j=0; j<sortedJets.size(); j++) {
      TPicoJet *pJet = new TPicoJet(j, -1., sortedJets[j].area(),
                                            sortedJets[j].pt(),
                                            sortedJets[j].eta(),
                                            sortedJets[j].phi());
//=============================================================================

      fastjet::Filter trimmer(subjDef, fastjet::SelectorPtFractionMin(0.));
      fastjet::PseudoJet trimmdJet = trimmer(sortedJets[j]);
      std::vector<fastjet::PseudoJet> trimmdSj = trimmdJet.pieces();
      std::vector<fastjet::PseudoJet> sortedSj = fastjet::sorted_by_pt(trimmdSj);

      for (unsigned int i=0; i<trimmdSj.size(); i++) if (trimmdSj[i].pt()>0.1) {
        pJet->AddPiece(TPicoPiece(i, sortedSj[i].area(),
                                     sortedSj[i].pt(),
                                     sortedSj[i].eta(),
                                     sortedSj[i].phi()));
      }
//=============================================================================

      pEvent->AddJet(pJet);
      delete pJet; pJet = 0;
    }
//=============================================================================

    tree->Fill();
//=============================================================================

    delete evt; ascii_in >> evt;
  }
//=============================================================================

  file->cd(); tree->Write(); file->Close();
//=============================================================================

  sFile.ReplaceAll("out", "wgt");
  file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  hWeightSum->Write();
  file->Close();
//=============================================================================

  cout << "DONE" << endl;
//=============================================================================

  return 0;
}

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(AnaRecoPicoEvents)
{
  def("Run", Run);
}
