const Int_t cycleL = 50;
//=============================================================================

void AnaMergeFilesLocal(TString ifList="dataset.txt", TString ofName="AnalysisResults")
{
//if (LoadLibraries()) return;
  if (ofName.EndsWith(".root")) ofName.ReplaceAll(".root","");

  TString ifName;
  TFileMerger merger;
  TSystemFile *systFile=0;
  Int_t count=0, cycleN=0;
  ifstream dataList(ifList.Data(), ios::in);
  while (!dataList.eof()) {  // loop with the cycle length
    ifName.ReadLine(dataList,kFALSE);
    if (!ifName.EndsWith(".root")) continue;
    if (gSystem->AccessPathName(ifName.Data())) continue;
    if (merger.AddFile(ifName.Data(),kFALSE)) count++;
    if ((count%cycleL)==0) {  // merge in cycle
      cycleN = count/cycleL;  cout << "cycleN===" << cycleN << endl;
      TString previous = Form("%s_%d.root",ofName.Data(),cycleN-1);
      if (!gSystem->AccessPathName(previous.Data())) {
        merger.AddFile(previous.Data(),kFALSE);
        systFile = new TSystemFile(previous.Data(),"."); systFile->Delete(); delete systFile; systFile=0;
      } merger.OutputFile(Form("%s_%d.root",ofName.Data(),cycleN)); merger.Merge(); merger.Reset();
    }  // end merge in cycle
  }    // end loop with the cycle length
  if (count==0) { cout << "No input file!!!" << endl; return; }

  if (count<cycleL) { // the end of the day
    cout << "cycleN===" << 0 << endl;
    merger.OutputFile(Form("%s.root",ofName.Data())); merger.Merge();
  } else if ((count%cycleL)==0) {
    TString lastFileName = Form("%s_%d.root",ofName.Data(),cycleN);
    if (gSystem->AccessPathName(lastFileName.Data())) { cout << "Merging failed miserably!!!" << endl; return; }
    gSystem->Rename(lastFileName.Data(), Form("%s.root",ofName.Data()));
  } else {
    TString lastFileName = Form("%s_%d.root",ofName.Data(),cycleN);
    if (gSystem->AccessPathName(lastFileName.Data())) { cout << "Merging failed miserably!!!" << endl; return; }
    cout << "cycleN===" << cycleN+1 << endl;
    merger.AddFile(lastFileName.Data(),kFALSE); merger.OutputFile(Form("%s.root",ofName.Data())); merger.Merge();
    systFile = new TSystemFile(lastFileName.Data(),"."); systFile->Delete(); delete systFile; systFile=0;
  } return;
}

//=============================================================================
Bool_t LoadLibraries()
{
  if (gSystem->Load("libTree")       <0) return kTRUE;
  if (gSystem->Load("libGeom")       <0) return kTRUE;
  if (gSystem->Load("libPhysics")    <0) return kTRUE;
  if (gSystem->Load("libVMC")        <0) return kTRUE;
  if (gSystem->Load("libMinuit")     <0) return kTRUE;
  if (gSystem->Load("libMinuit2")    <0) return kTRUE;

  if (gSystem->Load("libCore")       <0) return kTRUE;
  if (gSystem->Load("libXMLIO")      <0) return kTRUE;
  if (gSystem->Load("libXMLParser")  <0) return kTRUE;
  if (gSystem->Load("libProof")      <0) return kTRUE;
  if (gSystem->Load("libProofPlayer")<0) return kTRUE;
  if (gSystem->Load("libGui")        <0) return kTRUE;
//=============================================================================

  gSystem->AddIncludePath("-Wno-deprecated");
  gSystem->AddIncludePath("-I$ALICE_ROOT/include");
  gSystem->AddIncludePath("-I$ALICE_ROOT/PWGHF/vertexingHF");
  gSystem->AddIncludePath("-I$ALICE_ROOT/EMCAL");
  gSystem->AddIncludePath("-I$ALICE_ROOT/JETAN");
  gSystem->AddIncludePath("-I$ALICE_ROOT/JETAN/fastjet");

  if (gSystem->Load("libSTEERBase")         <0) return kTRUE;
  if (gSystem->Load("libESD")               <0) return kTRUE;
  if (gSystem->Load("libAOD")               <0) return kTRUE;
  if (gSystem->Load("libANALYSIS")          <0) return kTRUE;
  if (gSystem->Load("libOADB")              <0) return kTRUE;
  if (gSystem->Load("libANALYSISalice")     <0) return kTRUE;
  if (gSystem->Load("libCORRFW")            <0) return kTRUE;

  if (gSystem->Load("libPWGTools")          <0) return kTRUE;
  if (gSystem->Load("libPWGflowBase")       <0) return kTRUE;
  if (gSystem->Load("libPWGflowTasks")      <0) return kTRUE;
  if (gSystem->Load("libPWGHFbase")         <0) return kTRUE;
  if (gSystem->Load("libPWGHFvertexingHF")  <0) return kTRUE;

  if (gSystem->Load("libSTAT")              <0) return kTRUE;
  if (gSystem->Load("libEMCALUtils")        <0) return kTRUE;
//if (gSystem->Load("libPHOSUtils")         <0) return kTRUE;

  if (gSystem->Load("libCDB")               <0) return kTRUE;
  if (gSystem->Load("libRAWDatabase")       <0) return kTRUE;
  if (gSystem->Load("libRAWDatarec")        <0) return kTRUE;
  if (gSystem->Load("libSTEER")             <0) return kTRUE;
  if (gSystem->Load("libITSbase")           <0) return kTRUE;
  if (gSystem->Load("libITSrec")            <0) return kTRUE;
  if (gSystem->Load("libTPCbase")           <0) return kTRUE;
  if (gSystem->Load("libTPCrec")            <0) return kTRUE;
  if (gSystem->Load("libTRDbase")           <0) return kTRUE;
  if (gSystem->Load("libTRDrec")            <0) return kTRUE;
  if (gSystem->Load("libTOFbase")           <0) return kTRUE;
//if (gSystem->Load("libTOFrec")            <0) return kTRUE;
  if (gSystem->Load("libHMPIDbase")         <0) return kTRUE;
  if (gSystem->Load("libEMCALraw")          <0) return kTRUE;
  if (gSystem->Load("libEMCALbase")         <0) return kTRUE;
  if (gSystem->Load("libEMCALrec")          <0) return kTRUE;
  if (gSystem->Load("libVZERObase")         <0) return kTRUE;
  if (gSystem->Load("libVZEROrec")          <0) return kTRUE;
  if (gSystem->Load("libTENDER")            <0) return kTRUE;
  if (gSystem->Load("libTENDERSupplies")    <0) return kTRUE;

  if (gSystem->Load("libCGAL")              <0) return kTRUE;
  if (gSystem->Load("libfastjet")           <0) return kTRUE;
  if (gSystem->Load("libsiscone")           <0) return kTRUE;
  if (gSystem->Load("libSISConePlugin")     <0) return kTRUE;
  
  if (gSystem->Load("libJETAN")             <0) return kTRUE;
  if (gSystem->Load("libFASTJETAN")         <0) return kTRUE;
  if (gSystem->Load("libPWGEMCAL")          <0) return kTRUE;
  if (gSystem->Load("libPWGGAEMCALTasks")   <0) return kTRUE;
  if (gSystem->Load("libPWGJEEMCALJetTasks")<0) return kTRUE;

  return kFALSE;
}
