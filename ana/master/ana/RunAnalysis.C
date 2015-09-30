void RunAnalysis(const TString sList, const TString sPath="data/dataLists/incl")
{
//TChain *chain = CreateChain(Form("%s/%s.txt",sPath.Data(),sList.Data())); if (!chain) return;
///hain->Process("AnalysisTaskUser.C+", Form("%s:Rje",sList.Data()));
//=============================================================================

  TChain *chain = new TChain("nt"); chain->Add("data/mass/qpy_JetR04_SjeR01/out_dPtHard_00084_00117.root");
  chain->Process("AnalysisTaskUser.C+", Form("%s:Rje",sList.Data()));
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
