void RunAnalysisAJ(const TString sList="med_JetR05_SjeR01", const TString sPtHard, const TString sPath="data/dataLists/inclAJ")
{
//TChain *chain = CreateChain(Form("%s/%s.txt",sPath.Data(),sList.Data())); if (!chain) return;
//chain->Process("AnalysisTaskUserAJ.C+", Form("%s:DAJ",sList.Data()));
//=============================================================================

  TChain *chain = new TChain("nt"); chain->Add(Form("data/inclAJ/med_JetR05_SjeR01/out_%s.root",sPtHard.Data()));
  chain->Process("AnalysisTaskUserAJ.C+", Form("%s:DAJ",sList.Data()));
//=============================================================================

  return;
}

//_____________________________________________________________________________
TChain *CreateChain(TString sData)
{
  TChain *chain = new TChain("nt");
//=============================================================================

  if (gSystem->AccessPathName(sData.Data())) {
    ::Error("RunAnalysis.C::CreateChain","Dataset %s does not exist!",sData.Data());
    return NULL;
  }
//=============================================================================

  TString sFile;
  ifstream dataList(sData.Data(), ios::in);
  while (!dataList.eof()) {
    sFile.ReadLine(dataList,kFALSE);
    if (!sFile.EndsWith(".root")) continue;
    if (!gSystem->AccessPathName(sFile.Data())) chain->Add(sFile.Data());
  } dataList.close();
//=============================================================================

  return chain;
}
