void CompileAliRootMacros(const TString sMacros="AliGenPythiaPair.cxx")
{
  if (LoadLibraries()) return;

  gROOT->LoadMacro(Form("%s+",sMacros.Data()));
  return;
}

Bool_t LoadLibraries()
{

  gSystem->AddIncludePath("-Wno-deprecated");
  gSystem->AddIncludePath("-I$ALICE_ROOT/include");
//gSystem->AddIncludePath("-I$ALICE_ROOT/FASTSIM");
//gSystem->AddIncludePath("-I$ALICE_ROOT/STEER/STEER");
//gSystem->AddIncludePath("-I$ALICE_ROOT/EVGEN");
//gSystem->AddIncludePath("-I$ALICE_ROOT/PYTHIA6");

  if (gSystem->Load("libFASTSIM")     <0) return kTRUE;
  if (gSystem->Load("libEVGEN")       <0) return kTRUE;
  if (gSystem->Load("liblhapdf")      <0) return kTRUE;
  if (gSystem->Load("libEGPythia6")   <0) return kTRUE;
//if (gSystem->Load("libpythia6.4.21")<0) return kTRUE;
  if (gSystem->Load("libqpythia")     <0) return kTRUE;
  if (gSystem->Load("libAliPythia6")  <0) return kTRUE;
  return kFALSE;
}
