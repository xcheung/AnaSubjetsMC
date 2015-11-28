#include <iostream>

#include "HepMC/IO_GenEvent.h"
#include "HepMC/GenEvent.h"

#include "TApplication.h"
#include "TString.h"
#include "TMath.h"
#include "TVector3.h"
#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

#include "TPicoVector.h"
#include "TPicoParticle.h"
#include "TPicoJet.h"
#include "TPicoHeader.h"
#include "TPicoSimEvent.h"
//=============================================================================

using namespace std;

const TString srcName = "AnaCovHepMC2Pico";
//=============================================================================

int main(int argc, char* argv[])
{
  TApplication theApp(srcName.Data(), &argc, argv);
  for (int i=0; i<argc; i++) cout << "arg[" << i << "] = " << argv[i] << endl;
//=============================================================================

  if (argc<4) return -1;
  TString sPath = argv[1]; if (sPath.IsNull()) return -1;
  TString sFile = argv[2]; if (sFile.IsNull()) return -1;
  TString sWevt = argv[3]; if (sWevt.IsNull()) return -1;
//=============================================================================

  sPath.ReplaceAll("#", "/");
  bool bWev = false; if (sWevt=="true") bWev = true;
//=============================================================================

  TH1D *hWeightSum = 0;
  if (bWev) hWeightSum = new TH1D("hWeightSum", "", 1, 0., 1.);

  TFile *file = TFile::Open(Form("%s.root",sFile.Data()), "NEW");
  TTree *tree = new TTree("treePicoSim", "Pico Sim Event Tree");

  TPicoSimEvent *pEvent = new TPicoSimEvent(); pEvent->Write2Tree(tree);
//=============================================================================

  HepMC::IO_GenEvent ascii_in(Form("%s/%s.hepmc",sPath.Data(),sFile.Data()), std::ios::in);
  HepMC::GenEvent *evt = ascii_in.read_next_event();

  while (evt) {
    pEvent->Reset();

    double dXsect  = 1.;
    double dWeight = 1.;
    if (bWev) {
      dXsect  = evt->cross_section()->cross_section() / 1e9;
      dWeight = evt->weights().back();
      hWeightSum->Fill(0.5, dWeight);
    }
//=============================================================================

    double dLtk = -1.;
    TVector3 vTrk, vLtk;
    for (HepMC::GenEvent::particle_const_iterator p=evt->particles_begin(); p!=evt->particles_end(); ++p) if ((*p)->status()==1) {
      double dTrkEta = (*p)->momentum().eta(); if (TMath::Abs(dTrkEta)>3.) continue;
      double dTrkPt  = (*p)->momentum().perp();
      double dTrkPhi = (*p)->momentum().phi();

      pEvent->AddParticle(TPicoParticle(dTrkPt,dTrkEta,dTrkPhi,(*p)->pdg_id()));
      if (dLtk<dTrkPt) { dLtk = dTrkPt; vLtk.SetPtEtaPhi(dTrkPt,dTrkEta,dTrkPhi); }
    }

    pEvent->Header()->Set(TPicoVector(vLtk.Pt(),vLtk.Eta(),vLtk.Phi()),-1.,dWeight,dXsect);
//=============================================================================

    tree->Fill();
    delete evt; ascii_in >> evt;
  }
//=============================================================================

  file->cd(); tree->Write(); file->Close();
//=============================================================================


  if (bWev) {
    TString sWgt = sFile; sWgt.ReplaceAll("out_", "wgt_");
    file = TFile::Open(Form("%s.root",sWgt.Data()), "NEW");
    hWeightSum->Write();
    file->Close();
  }
//=============================================================================

  cout << "DONE" << endl;
//=============================================================================

  return 0;
}
