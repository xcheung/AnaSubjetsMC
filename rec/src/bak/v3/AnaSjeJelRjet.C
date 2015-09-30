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
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TFile.h"
#include "TList.h"
#include "TH1D.h"
#include "TNtuple.h"
//=============================================================================

using namespace std;

const TString srcName = "AnaSjeJelRjet";
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

  const double dJetsPtMin  = 0.001;
  const double dCutEtaMax  = 1.6;
  const double dJetEtaMax  = 1.;
  const double dJetAreaRef = TMath::Pi() * dJetR * dJetR;

  fastjet::GhostedAreaSpec areaSpc(dCutEtaMax);
  fastjet::JetDefinition   jetsDef(fastjet::antikt_algorithm, dJetR, fastjet::E_scheme, fastjet::Best);
  fastjet::AreaDefinition  areaDef(fastjet::active_area_explicit_ghosts,areaSpc);

  fastjet::Selector selectJet = fastjet::SelectorAbsEtaMax(dJetEtaMax);
  fastjet::JetDefinition subjDef(fastjet::kt_algorithm, dSjeR, fastjet::E_scheme, fastjet::Best);
//=============================================================================

  const Double_t d2PI = TMath::TwoPi();
  const Double_t dCut = d2PI / 3.;
  const double dMass = TDatabasePDG::Instance()->GetParticle(211)->Mass();

  std::vector<fastjet::PseudoJet> fjInput;
//=============================================================================

  TH1D *hWeightSum = new TH1D("hWeightSum", "", 1, 0., 1.);
  enum { kWgt, kTrg, kIje, kAje, kMje, k1sz, k1sA, k1sr, k1sm, k2sz, k2sA, k2sr, k2sm, kDsr, kIsm, kVar };

  TFile *file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  TNtuple *nt = new TNtuple("nt", "", "fWgt:fTrg:fJet:fAje:fMje:f1sj:f1sA:f1sr:f1sm:f2sj:f2sA:f2sr:f2sm:fDsr:fIsm");
//=============================================================================

  HepMC::IO_GenEvent ascii_in(Form("%s/%s.hepmc",sPath.Data(),sFile.Data()), std::ios::in);
  HepMC::GenEvent *evt = ascii_in.read_next_event();

  while (evt) {
    fjInput.resize(0);
    double dXsect  = evt->cross_section()->cross_section() / 1e9;
    double dWeight = evt->weights().back();
    double dNorm = dWeight * dXsect;
    hWeightSum->Fill(0.5, dWeight);

    TLorentzVector vPar;
    for (HepMC::GenEvent::particle_const_iterator p=evt->particles_begin(); p!=evt->particles_end(); ++p) if ((*p)->status()==1) {
      vPar.SetPtEtaPhiM((*p)->momentum().perp(), (*p)->momentum().eta(), (*p)->momentum().phi(), dMass);

      if ((TMath::Abs(vPar.Eta())<dCutEtaMax)) {
        fjInput.push_back(fastjet::PseudoJet(vPar.Px(), vPar.Py(), vPar.Pz(), vPar.E()));
      }
    }
//=============================================================================

    fastjet::ClusterSequenceArea clustSeq(fjInput, jetsDef, areaDef);
    std::vector<fastjet::PseudoJet> includJets = clustSeq.inclusive_jets(dJetsPtMin);
    std::vector<fastjet::PseudoJet> selectJets = selectJet(includJets);
    std::vector<fastjet::PseudoJet> sortedJets = fastjet::sorted_by_pt(selectJets);

    Float_t dVar[] = { dNorm, -1., -1., -1., -1., -1., -1., -1., -1., -1., -1., -1., -1., -1., -1. };
//=============================================================================

    if (sortedJets.size()>0) {
      dVar[kTrg] = sortedJets[0].pt();
      TLorentzVector vTrg; vTrg.SetPtEtaPhiM(sortedJets[0].pt(), sortedJets[0].eta(), sortedJets[0].phi(), sortedJets[0].m());
//=============================================================================

      double dJet = -1.; int kJet = -1;
      TLorentzVector vJet, v1sj, v2sj, vIsj;
      for (int j=1; j<sortedJets.size(); j++) {
        vJet.SetPtEtaPhiM(sortedJets[j].pt(), sortedJets[j].eta(), sortedJets[j].phi(), sortedJets[j].m());
        if (TMath::Abs(vJet.DeltaPhi(vTrg))<dCut) continue;
        if (vJet.Pt()>dJet) { dJet = vJet.Pt(), kJet = j; }
      }
//=============================================================================

      if (dJet>0.) {
        dVar[kIje] = dJet;
        dVar[kMje] = sortedJets[kJet].m();
        dVar[kAje] = sortedJets[kJet].area();
        vJet.SetPtEtaPhiM(dJet, sortedJets[kJet].eta(), sortedJets[kJet].phi(), sortedJets[kJet].m());
//=============================================================================

        fastjet::Filter trimmer(subjDef, fastjet::SelectorPtFractionMin(0.));
        fastjet::PseudoJet trimmdJet = trimmer(sortedJets[kJet]);
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
          v1sj.SetPtEtaPhiM(d1sj, trimmdSj[k1sj].eta(), trimmdSj[k1sj].phi(), trimmdSj[k1sj].m());
          dVar[k1sr] = v1sj.DeltaR(vJet);
          dVar[k1sm] = trimmdSj[k1sj].m();
          dVar[k1sA] = trimmdSj[k1sj].area();
          dVar[k1sz] = d1sj;
        }

        if (d2sj>0.) {
          v2sj.SetPtEtaPhiM(d2sj, trimmdSj[k2sj].eta(), trimmdSj[k2sj].phi(), trimmdSj[k2sj].m());
          dVar[k2sr] = v2sj.DeltaR(vJet);
          dVar[k2sm] = trimmdSj[k2sj].m();
          dVar[k2sA] = trimmdSj[k2sj].area();
          dVar[k2sz] = d2sj;
        }

        if ((d1sj>0.) && (d2sj>0.)) {
          vIsj = v1sj + v2sj;
          dVar[kIsm] = vIsj.M();
          dVar[kDsr] = v2sj.DeltaR(v1sj);
        }
      }
    }

    nt->Fill(dVar);
//=============================================================================

    delete evt;
    ascii_in >> evt;
  }
//=============================================================================

  file->cd(); nt->Write(); file->Close();
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
