void RunAnalysisSim()
{
  gSystem->AddIncludePath("-Wno-deprecated");
  gSystem->AddIncludePath("-I${PICOPKG}/inc");
  gSystem->Load("${PICOPKG}/lib/libPico");
//=============================================================================

//gROOT->LoadMacro("AnalysisSelectorPicoSimEvent.cxx+"); return;
//=============================================================================

  TChain *chain = new TChain("treePicoSim"); chain->Add("data/out.root");
//=============================================================================

  chain->Process("AnalysisSelectorPicoSimEvent.cxx+");
//=============================================================================

  return;
}
