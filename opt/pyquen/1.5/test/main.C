#include <iostream>
#include <cstring>
#include <cmath>

#include "pycall.h"

using namespace std;

int main()
{
// set initial beam parameters
  int nEvents = 100;

  double dEnergy = 5500.; // c.m.s energy per nucleon pair
  double dA      = 207.;  // atomic weigth

//int iFB      = 0;  // flag for fixed impact parameter
  int iFB      = 1;  // flag for minimum bias choice
  double dBFIX = 0.; // impact parameter in [fm]
//=============================================================================

// set of input PYQUEN parameters:
  pyqpar.fIENGLU = 0; // set type of partonic energy loss
                      // = 0: radiative and collisional loss
                      // = 1: only radiative loss
                      // = 2: only collisional loss

  pyqpar.fIANGLU = 0; // set angular spectrum of gluon radiation
                      // = 0: small-angular radiation
                      // = 1: wide angular radiation
                      // = 2: collinear radiation

  pyqpar.fT0   = 1.;  // initial QGP temperature
  pyqpar.fTAU0 = 0.1; // proper time of QGP formation
  pyqpar.fNF   = 0;   //  number of active quark flavours in QGP
//=============================================================================

// set of input PYTHIA parameters
  pysubs.fMSEL      = 1;   // QCD-dijet production
  pysubs.fCKIN[3-1] = 50.; // minimum pt in initial hard sub-process

  pydat1.fPARU[14-1] = 1.; // tolerance parameter to adjust fragmentation
  pydat1.fMSTU[21-1] = 1;  // avoid stopping run

  pypars.fMSTP[51-1]  = 7; // CTEQ5M pdf
  pypars.fMSTP[81-1]  = 0; // pp multiple scattering off
  pypars.fMSTP[111-1] = 0; // hadronization off
//=============================================================================

  char *sFrame  = (char*)"CMS";
  char *sBeam   = (char*)"p";
  char *sTarget = (char*)"p";

  long int lFrame  = strlen(sFrame);
  long int lBeam   = strlen(sBeam);
  long int lTarget = strlen(sTarget);

  pyinit(sFrame, sBeam, sTarget, &dEnergy, lFrame, lBeam, lTarget);
//=============================================================================

// set original test values for mean pT and event multiplicity
  double dPtA0 = 0.77;
  double dNA0  = 207.;

// set initial test values and its RMS
  double dPtAM  = 0.;
  double dPtRMS = 0.;

  double dNAM  = 0.;
  double dNRMS = 0.;
//=============================================================================

  int kPyEditFlag = 2;
  for (int iEvent=0; iEvent<nEvents; iEvent++) {
//  pydat1.fMSTJ[41-1] = 0  // vacuum showering off

    pyevnt();                  //  generate single partonic jet event
    pyquen(&dA, &iFB, &dBFIX); // set parton rescattering and energy loss

    pyexec();             // hadronization done
    pyedit(&kPyEditFlag); // remove unstable particles and partons

//  int kPyListFlag = 1;
//  pylist(&kPyListFlag);
//=============================================================================

    int kPypFlag = 10;
    for (int i=0, k=1; i<pyjets.fN; i++, k++) {
      double dPt = pyp(&k, &kPypFlag);

      dPtAM  += dPt;
      dPtRMS += ((dPt-dPtA0) * (dPt-dPtA0));
    }

    dNAM  += (double)pyjets.fN;
    dNRMS += ((pyjets.fN - dNA0) * (pyjets.fN - dNA0));
//  cout << "Event #" << iEvent << ", Impact parameter = " << plfpar.fBGEN << " fm" << endl;
  }
//=============================================================================

  dPtAM  /= dNAM;
  dPtRMS  = sqrt(dPtRMS) / dNAM;

  dNAM  /= nEvents;
  dNRMS  = sqrt(dNRMS) / nEvents;

  cout << "True mean multiplicity = "      << dNA0 << endl;
  cout << "Generated mean multiplicity = " << dNAM << " +- " << dNRMS << endl;

  cout << "True mean transverse momentum = "      << dPtA0 << endl;
  cout << "Generated mean transverse momentum = " << dPtAM << " +- " << dPtRMS << endl;

  return 0;
}
