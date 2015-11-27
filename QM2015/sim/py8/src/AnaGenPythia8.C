#include <iostream>

#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"
//nclude "Pythia8Plugins/FastJet3.h"

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
#include "TF1.h"
//=============================================================================

using namespace std;
using namespace Pythia8;

const TString srcName = "AnaGenPythia8";
//=============================================================================

int main(int argc, char* argv[])
{
  TApplication theApp(srcName.Data(), &argc, argv);
//=============================================================================

  if (argc<1) return -1;
  TString sSGE = argv[1]; if (sSGE.IsNull()) return -1;
//=============================================================================

  Pythia8::Pythia pythia;
  Pythia8::Event& event = pythia.event;
  Pythia8::Info&  info  = pythia.info;

  pythia.readString("Main:numberOfEvents = 50001");

//pythia.readString("SoftQCD:minBias = off");
  pythia.readString("HardQCD:all = on");
  pythia.readFile((srcName+".cmnd").Data());

  pythia.readString("Next:numberShowInfo = 0");
  pythia.readString("Next:numberShowProcess = 0");
  pythia.readString("Next:numberShowEvent = 0");

  pythia.readString("Random:setSeed = on");
  pythia.readString(Form("Random:seed = %s",sSGE.Data()));

  pythia.readString("Tune:pp = 5");
  pythia.readString("Beams:eCM = 2760.");

//pythia.readString("ColourReconnection:reconnect = on");
//pythia.readString("ColourReconnection:reconnect = off");

  pythia.init();
//=============================================================================

  HepMC::Pythia8ToHepMC ToHepMC;
  HepMC::IO_GenEvent ascii_io(Form("out_%s.hepmc",sSGE.Data()), std::ios::out);
//=============================================================================

  TList *list = new TList();

  TH1D     *hPtHat = new TH1D("hPtHat", "", 1000, 0., 1000.);      list->Add(hPtHat);
  TH1D     *hWeightSum = new TH1D("hWeightSum", "", 1, 0., 1.);    list->Add(hWeightSum);
  TProfile *hSigmaGen  = new TProfile("hSigmaGen", "", 1, 0., 1.); list->Add(hSigmaGen);
//=============================================================================

  for (int iEvent=0; iEvent<pythia.mode("Main:numberOfEvents"); iEvent++) if (pythia.next()) {

    HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
    ToHepMC.fill_next_event(pythia, hepmcevt);

    ascii_io << hepmcevt;
    delete hepmcevt;

    hPtHat->Fill(info.pTHat());
  }
//=============================================================================

  hSigmaGen->Fill(0.5, info.sigmaGen());
  hWeightSum->Fill(0.5, info.weightSum());
//=============================================================================

  TFile *file = TFile::Open(Form("xsecs_%s.root",sSGE.Data()), "NEW");
  list->Write();
  file->Close();
//=============================================================================

  cout << "DONE" << endl;
//=============================================================================

  return 0;
}
