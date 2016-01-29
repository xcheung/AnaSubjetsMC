void RunAnalysis()
{
  gSystem->AddIncludePath("-Wno-deprecated");
  gSystem->AddIncludePath("-I${PICOPKG}/inc");
  gSystem->Load("${PICOPKG}/lib/libPico");
//=============================================================================

  gROOT->LoadMacro("AnalysisSelectorPicoJetEvent.cxx+"); return;
//=============================================================================

  const TString sECMS = "2760GeV";
  const TString sReco = "AkT05_kT01";

  const TString sType = "pyquen";
  const TString sMode = "IANGLU0";

  const TString sPath = "/data1/xzhang/mc/subjetsTH";
  const TString sList = Form("%s/%s/%s/%s/dataLists/%s.txt",sPath.Data(),sType.Data(),sECMS.Data(),sMode.Data(),sReco.Data());

  TChain *chain = CreateChain(sList); if (!chain) return;
//=============================================================================

  chain->Process("AnalysisSelectorPicoJetEvent.cxx+", "all");
//=============================================================================

  return;
}

//_____________________________________________________________________________
TChain *CreateChain(TString dataset)
{
  if (gSystem->AccessPathName(dataset.Data())) {
    ::Error("RunAnalysis.C::CreateChain","Dataset %s does not exist!",dataset.Data());
    return NULL;
  }
//=============================================================================

  TChain *chain = new TChain("treePicoJet");

  TString dataFile;
  ifstream dataList(dataset.Data(), ios::in);
  while (!dataList.eof()) {
    dataFile.ReadLine(dataList,kFALSE);
    if (!dataFile.EndsWith(".root")) continue;
    if (!gSystem->AccessPathName(dataFile.Data())) chain->Add(dataFile.Data());
  } dataList.close();

  return chain;
}
