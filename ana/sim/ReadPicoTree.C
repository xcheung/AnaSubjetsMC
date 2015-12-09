void ReadPicoTree()
{
  const TString sHere = gSystem->pwd();
  const TString sTopD = gSystem->DirName(sHere.Data());

  gSystem->AddIncludePath("-Wno-deprecated");
  gSystem->AddIncludePath(Form("-I%s/pico",sTopD.Data()));
  gSystem->Load(Form("%s/lib/libPico",sTopD.Data()));

  TChain *chain = new TChain("treePico"); chain->Add("out.root");
//chain->MakeSelector("AnaTest");
//chain->StartViewer();

/*TPicoEvent *pEvent = new TPicoEvent(); pEvent->ReadFromTree(chain);
  for (Int_t i=0; i<chain->GetEntries(); i++) if (chain->GetEntry(i)) {
    cout << pEvent->Header()->Leading()->Pt() << endl;
  }*/

  return;
}
