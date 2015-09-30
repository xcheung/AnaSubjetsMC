void ConvertList(const TString sFile)
{
  if (!sFile.EndsWith(".txt")) return;

  TString dataFile;
  ifstream dataList(sFile.Data(), ios::in);

  while (!dataList.eof()) {
    dataFile.ReadLine(dataList,kFALSE);
    if (!dataFile.EndsWith("root")) continue;
    if (gSystem->AccessPathName(dataFile.Data())) continue;

    dataFile.ReplaceAll("/","#");
    cout << dataFile.Data() << endl;
  } dataList.close();

  return;
}
