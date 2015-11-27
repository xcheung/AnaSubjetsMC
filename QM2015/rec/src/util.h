static const double fgkPtBkgMean=0.7, fgkPtBkgMin=0., fgkPtBkgMax=200.;
//=============================================================================

double Boltzmann(Double_t *x, Double_t *par)
{
  double  dKernel = 2. * x[0] / par[0];
  return (dKernel * TMath::Exp(-1.*dKernel));
}

//_____________________________________________________________________________
TF1 *BackgroundSpec()
{
  TF1 *fBkg = new TF1("fBkg", Boltzmann, fgkPtBkgMin, fgkPtBkgMax, 1);
  fBkg->SetParameter(0, fgkPtBkgMean);
  fBkg->SetNpx(2000); 
  return fBkg;
}
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
class UserInfoTrk : public fastjet::PseudoJet::UserInfoBase {

 public :

  UserInfoTrk(bool b) : fIsBkg(b) {}

  bool IsBkg() const { return   fIsBkg;  }
  bool IsPhy() const { return (!fIsBkg); }
//=============================================================================

 private :

  bool  fIsBkg;
};

//_____________________________________________________________________________
class UserInfoJet : public fastjet::PseudoJet::UserInfoBase {

 public :

  UserInfoJet(double dPhyPt,
              double dLtkPt, int idLtk) : fThisPhysPt(dPhyPt),
                                          fThisLtrkPt(dLtkPt), fThisLtrkID(idLtk),
                                          fTrkMatchFr(0.),     fTrkMatchID(-1),
                                          fGeoMatchDs(99999.), fGeoMatchID(-1) {}

  double GetPhyPt() const { return  fThisPhysPt; }
  bool   IsPhy()    const { return (fThisPhysPt>0.1); }
  bool   IsBkg()    const { return (fThisPhysPt<0.1); }

  int    GetLeadingTrkID() const { return fThisLtrkID; }
  double GetLeadingTrkPt() const { return fThisLtrkPt; }

  int    GetTrkMatchedJetID() const { return fTrkMatchID; }
  double GetTrkMatchedJetFr() const { return fTrkMatchFr; }

  int    GetGeoMatchedJetID() const { return fGeoMatchID; }
  double GetGeoMatchedJetDs() const { return fGeoMatchDs; }

  void SetTrkMatchedJet(const double d, const int id) { fTrkMatchFr = d; fTrkMatchID = id; }
  void SetGeoMatchedJet(const double d, const int id) { fGeoMatchDs = d; fGeoMatchID = id; }
//=============================================================================

 private :

  double fThisPhysPt;

  double fThisLtrkPt;
  int    fThisLtrkID;

  double fTrkMatchFr;
  int    fTrkMatchID;

  double fGeoMatchDs;
  int    fGeoMatchID;
};
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
double CalcDeltaR(fastjet::PseudoJet &pJetHd, fastjet::PseudoJet &pJetPy)
{
  if  (pJetHd.user_info<UserInfoJet>().IsBkg()) return 999999.;
  if ((pJetHd.user_index()<0) || (pJetPy.user_index()<0)) return 999999.;
//=============================================================================

  TVector3 vJetHd; vJetHd.SetPtEtaPhi(pJetHd.pt(), pJetHd.eta(), pJetHd.phi());
  TVector3 vJetPy; vJetPy.SetPtEtaPhi(pJetPy.pt(), pJetPy.eta(), pJetPy.phi());
//=============================================================================

  return vJetPy.DeltaR(vJetHd);
}

//_____________________________________________________________________________
double CalcSharedPt(fastjet::PseudoJet &pJetHd, fastjet::PseudoJet &pJetPy)
{
  if  (pJetHd.user_info<UserInfoJet>().IsBkg()) return -1.;
  if ((pJetHd.user_index()<0) || (pJetPy.user_index()<0)) return -1.;
//=============================================================================

  std::vector<fastjet::PseudoJet> aTrksHd = pJetHd.constituents();
  std::vector<fastjet::PseudoJet> aTrksPy = pJetPy.constituents();
//=============================================================================

  double dSharedPt = 0.;
  for (int i=0; i<aTrksHd.size(); i++) {
    double dPtTrk = aTrksHd[i].pt(); if (dPtTrk<0.1) continue;
    if (aTrksHd[i].user_info<UserInfoTrk>().IsBkg()) continue;

    int idTrk = aTrksHd[i].user_index();
    for (int j=0; j<aTrksPy.size(); j++) if (aTrksPy[j].pt()>0.1) {
      if (aTrksPy[j].user_index()==idTrk) {
        dSharedPt += dPtTrk;
        break;
      }
    }
  }
//=============================================================================

  return dSharedPt;
}
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
void SetJetUserInfo(fastjet::PseudoJet &pJet)
{
  std::vector<fastjet::PseudoJet> aTrk = pJet.constituents();
//=============================================================================

  int    idLk = -1;
  double dLtk = -1.;
  double dPhy =  0.;
  for (int i=0; i<aTrk.size(); i++) {
    double dTmp = aTrk[i].pt(); if (dTmp<0.1) continue;

    if (aTrk[i].user_info<UserInfoTrk>().IsPhy()) dPhy += dTmp;
    if (dTmp>dLtk) { idLk = aTrk[i].user_index(); dLtk  = dTmp; }
  }

  pJet.set_user_info(new UserInfoJet(dPhy, dLtk, idLk));
//=============================================================================

  return;
}
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
void DoGeoMatch(fastjet::PseudoJet &pJetHd, fastjet::PseudoJet &pJetPy)
{
  if (pJetHd.user_info<UserInfoJet>().IsBkg()) return;
  const int idJetHd = pJetHd.user_index(); if (idJetHd<0) return;
  const int idJetPy = pJetPy.user_index(); if (idJetPy<0) return;
//=============================================================================

  const double deltaR = CalcDeltaR(pJetHd, pJetPy);
//=============================================================================

  if (deltaR<pJetHd.user_info<UserInfoJet>().GetGeoMatchedJetDs()) {
    UserInfoJet *pUserInfoJetHd = new UserInfoJet(pJetHd.user_info<UserInfoJet>().GetPhyPt(),
                                                  pJetHd.user_info<UserInfoJet>().GetLeadingTrkPt(),
                                                  pJetHd.user_info<UserInfoJet>().GetLeadingTrkID());

    pUserInfoJetHd->SetGeoMatchedJet(deltaR, idJetPy);
    pUserInfoJetHd->SetTrkMatchedJet(pJetHd.user_info<UserInfoJet>().GetTrkMatchedJetFr(),
                                     pJetHd.user_info<UserInfoJet>().GetTrkMatchedJetID());

    pJetHd.set_user_info(pUserInfoJetHd); pUserInfoJetHd = 0;
  }
//=============================================================================

  if (deltaR<pJetPy.user_info<UserInfoJet>().GetGeoMatchedJetDs()) {
    UserInfoJet *pUserInfoJetPy = new UserInfoJet(pJetPy.user_info<UserInfoJet>().GetPhyPt(),
                                                  pJetPy.user_info<UserInfoJet>().GetLeadingTrkPt(),
                                                  pJetPy.user_info<UserInfoJet>().GetLeadingTrkID());

    pUserInfoJetPy->SetGeoMatchedJet(deltaR, idJetHd);
    pUserInfoJetPy->SetTrkMatchedJet(pJetPy.user_info<UserInfoJet>().GetTrkMatchedJetFr(),
                                     pJetPy.user_info<UserInfoJet>().GetTrkMatchedJetID());


    pJetPy.set_user_info(pUserInfoJetPy); pUserInfoJetPy = 0;
  }
//=============================================================================

  return;
}

//_____________________________________________________________________________
void DoTrkMatch(fastjet::PseudoJet &pJetHd, fastjet::PseudoJet &pJetPy)
{
  if (pJetHd.user_info<UserInfoJet>().IsBkg()) return;
  const int idJetHd = pJetHd.user_index(); if (idJetHd<0) return;
  const int idJetPy = pJetPy.user_index(); if (idJetPy<0) return;
//=============================================================================

  const double dSharedPt = CalcSharedPt(pJetHd, pJetPy); if (dSharedPt<0.1) return;
//=============================================================================

  const double dFracHd = dSharedPt / pJetHd.user_info<UserInfoJet>().GetPhyPt();
  if (dFracHd>pJetHd.user_info<UserInfoJet>().GetTrkMatchedJetFr()) {
    UserInfoJet *pUserInfoJetHd = new UserInfoJet(pJetHd.user_info<UserInfoJet>().GetPhyPt(),
                                                  pJetHd.user_info<UserInfoJet>().GetLeadingTrkPt(),
                                                  pJetHd.user_info<UserInfoJet>().GetLeadingTrkID());

    pUserInfoJetHd->SetTrkMatchedJet(dFracHd, idJetPy);
    pUserInfoJetHd->SetGeoMatchedJet(pJetHd.user_info<UserInfoJet>().GetGeoMatchedJetDs(),
                                     pJetHd.user_info<UserInfoJet>().GetGeoMatchedJetID());

    pJetHd.set_user_info(pUserInfoJetHd); pUserInfoJetHd = 0;
  }
//=============================================================================

  const double dFracPy = dSharedPt / pJetPy.user_info<UserInfoJet>().GetPhyPt();
  if (dFracPy>pJetPy.user_info<UserInfoJet>().GetTrkMatchedJetFr()) {
    UserInfoJet *pUserInfoJetPy = new UserInfoJet(pJetPy.user_info<UserInfoJet>().GetPhyPt(),
                                                  pJetPy.user_info<UserInfoJet>().GetLeadingTrkPt(),
                                                  pJetPy.user_info<UserInfoJet>().GetLeadingTrkID());

    pUserInfoJetPy->SetTrkMatchedJet(dFracPy, idJetHd);
    pUserInfoJetPy->SetGeoMatchedJet(pJetPy.user_info<UserInfoJet>().GetGeoMatchedJetDs(),
                                     pJetPy.user_info<UserInfoJet>().GetGeoMatchedJetID());

    pJetPy.set_user_info(pUserInfoJetPy); pUserInfoJetPy = 0;
  }
//=============================================================================

  return;
}

//_____________________________________________________________________________
void DoJetMatch(fastjet::PseudoJet &pJetHd, fastjet::PseudoJet &pJetPy)
{
  if (pJetHd.user_info<UserInfoJet>().IsBkg()) return;
  const int idJetHd = pJetHd.user_index(); if (idJetHd<0) return;
  const int idJetPy = pJetPy.user_index(); if (idJetPy<0) return;
//=============================================================================

  DoGeoMatch(pJetHd, pJetPy);
  DoTrkMatch(pJetHd, pJetPy);
//=============================================================================

  return;
}
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
bool IsJetGeoMatched(fastjet::PseudoJet &pJetHd, std::vector<fastjet::PseudoJet> &aJetsPy)
{
  if (pJetHd.user_info<UserInfoJet>().IsBkg()) return false;
  const int idJetHd = pJetHd.user_index(); if (idJetHd<0) return false;
  const int idJetPy = pJetHd.user_info<UserInfoJet>().GetGeoMatchedJetID(); if (idJetPy<0) return false;
//=============================================================================

  if (aJetsPy[idJetPy].user_index()<0) return false;
  return (aJetsPy[idJetPy].user_info<UserInfoJet>().GetGeoMatchedJetID()==idJetHd);
}

//_____________________________________________________________________________
bool IsJetTrkMatched(fastjet::PseudoJet &pJetHd, std::vector<fastjet::PseudoJet> &aJetsPy)
{
  if (pJetHd.user_info<UserInfoJet>().IsBkg()) return false;
  const int idJetHd = pJetHd.user_index(); if (idJetHd<0) return false;
  const int idJetPy = pJetHd.user_info<UserInfoJet>().GetTrkMatchedJetID(); if (idJetPy<0) return false;
//=============================================================================

  if (aJetsPy[idJetPy].user_index()<0) return false;
  return (aJetsPy[idJetPy].user_info<UserInfoJet>().GetTrkMatchedJetID()==idJetHd);
}
