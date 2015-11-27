#define pydiff pydiff_
#define pyevnt pyevnt_
#define pyinit pyinit_
#define pychge pychge_
#define pycomp pycomp_
#define pyedit pyedit_
#define pyexec pyexec_
#define pyhepc pyhepc_
#define pygive pygive_
#define pylist pylist_
#define pymass pymass_
#define pyname pyname_
#define pyrget pyrget_
#define pyrset pyrset_
#define pystat pystat_
#define pytest pytest_
#define pytune pytune_
#define pyupda pyupda_
#define py1ent py1ent_
#define pyquen pyquen_

#define pyjets pyjets_
#define pydat1 pydat1_
#define pydatr pydatr_
#define pysubs pysubs_
#define pypars pypars_
#define pyqpar pyqpar_
#define plfpar plfpar_

#define pyr pyr_
#define pyp pyp_
#define pyk pyk_

#define tpythia6_open_fortran_file tpythia6_open_fortran_file_
#define tpythia6_close_fortran_file tpythia6_close_fortran_file_
#define pythia6_common_address pythia6_common_address

#define pythia6_common_address pythia6_common_address
#define tpythia6_open_fortran_file tpythia6_open_fortran_file_
#define tpythia6_close_fortran_file tpythia6_close_fortran_file_

extern "C" {
  extern struct {
    int    fN;
    int    fNPAD;
    int    fK[5][4000];
    double fP[5][4000];
    double fV[5][4000];
  } pyjets;

  extern struct {
    int    fMSTU[200];
    double fPARU[200];
    int    fMSTJ[200];
    double fPARJ[200];
  } pydat1;

  extern struct {
    int    fMRPY[6];
    double fRRPY[100];
  } pydatr;

  extern struct {
    int    fMSEL;
    int    fMSELPD;
    int    fMSUB[500];
    int    fKFIN[81][2];
    double fCKIN[200];
  } pysubs;

  extern struct {
    int    fMSTP[200];
    double fPARP[200];
    int    fMSTI[200];
    double fPARI[200];
  } pypars;

  extern struct {
    double fT0;
    double fTAU0;
    int    fNF;
    int    fIENGLU;
    int    fIANGLU;
  } pyqpar;

  extern struct {
    double fBGEN;
  } plfpar;

  void pyinit(char *frame, char *beam, char *target, double *win,
              long int l_frame, long int l_beam, long int l_target);

  void pyevnt();
  void pystat(int *key);
  void pylist(int *key);
  void pyedit(int *medit);
  void pydiff();
  void pyexec();
  void pygive(const char *param, long int lparam);
  void pyhepc(int *mconv);
  void pylist(int *flag);
  void py1ent(int&, int&, double&, double&, double&);
  void pyname(int *kf, char *name, long int l_name);

  int pychge(int *kf);
  int pycomp(int *kf);
  int pyr(int *dummy);
  int pyrget(int *lun, int *move);
  int pyrset(int *lun, int *move);
  int pytest(int *flag);
  int pytune(int *itune);
  int pyupda(int *mupda, int *lun);

  double pymass(int *kf);

  int    pyk(int *i, int *j);
  double pyp(int *i, int *j);

  double pyquen(double *dA, int *iFB, double *dBFIX);
}
