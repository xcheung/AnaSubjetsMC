	PROGRAM MAIN
C
	IMPLICIT INTEGER(I-N)
	IMPLICIT DOUBLE PRECISION(A-H, O-Z)
C
	INTEGER PYK, PYCHGE, PYCOMP
C
	EXTERNAL PYDATA
	EXTERNAL PYP, PYR, PYK
C
	COMMON /PYJETS/ N, NPAD, K(4000,5), P(4000,5), V(4000,5)
	COMMON /PYDAT1/ MSTU(200), PARU(200), MSTJ(200), PARJ(200)
	COMMON /PYSUBS/ MSEL, MSELPD, MSUB(500), KFIN(2,-40:40), CKIN(200)
	COMMON /PYPARS/ MSTP(200), PARP(200), MSTI(200), PARI(200)
	COMMON /PYQPAR/ T0, TAU0, NF, IENGLU, IANGLU
	COMMON /PLFPAR/ BGEN
C==============================================================================
C
* set initial beam parameters
	ENERGY = 5500.d0  ! c.m.s energy per nucleon pair
	A      = 207.D0   ! atomic weigth
C	IFB    = 0        ! flag for fixed impact parameter
 	iFB    = 1        ! flag for minimum bias choice
	BFIX   = 0.d0     ! impact parameter in [fm]
C==============================================================================
C
* set of input PYQUEN parameters:
	IENGLU = 0  ! set type of partonic energy loss
                    ! = 0: radiative and collisional loss
                    ! = 1: only radiative loss
                    ! = 2: only collisional loss
C
	IANGLU = 0  ! set angular spectrum of gluon radiation
                    ! = 0: small-angular radiation
                    ! = 1: wide angular radiation
                    ! = 2: collinear radiation
C
	T0     = 1.d0   ! initial QGP temperature
	TAU0   = 0.1d0  ! proper time of QGP formation
	NF     = 0      ! number of active quark flavours in QGP
C==============================================================================
C
* set of input PYTHIA parameters
	MSEL = 1  ! QCD-dijet production
C
	PARU (14) = 1.d0   ! tolerance parameter to adjust fragmentation
	MSTU (21) = 1      ! avoid stopping run
	CKIN (3)  = 50.d0  ! minimum pt in initial hard sub-process
C
	MSTP (51)  = 7  ! CTEQ5M pdf
	MSTP (81)  = 0  ! pp multiple scattering off
	MSTP (111) = 0  ! hadronization off
C==============================================================================
C
* set original test values for mean pT and event multiplicity
	PTA0 = 0.77d0
	DNA0 = 207.d0
C
* set initial test values and its RMS
	PTAM  = 0.d0
	PTRMS = 0.d0
	DNAM  = 0.d0
	DNRMS = 0.d0
C==============================================================================
C
* initialization of pythia configuration
	CALL PYINIT('CMS','p','p',ENERGY)
C
* set number of generated events
	NTOT = 100
C	NTOT = 10000
C==============================================================================
C
	DO NE = 1, NTOT              ! cycle on events
C	  MSTJ(41) = 0               ! vacuum showering off
	  CALL PYEVNT                ! generate single partonic jet event
	  CALL PYQUEN(A, IFB, BFIX)  ! set parton rescattering and energy loss
C
C	  CALL PYLIST(1)
C
	  call PYEXEC     ! hadronization done
	  call PYEDIT(2)  ! remove unstable particles and partons
C
	  DO IP = 1, N  ! cycle on N particles
	    PT    = PYP(IP, 10) ! transverse momentum pT
	    PTAM  = PTAM  + PT  ! add current test value of pT and its RMS
	    PTRMS = PTRMS + (PT-PTA0)**2
	  END DO
C
* add current test value of event multiplicity and its RMS
	  DNAM  = DNAM  + N
	  DNRMS = DNRMS + (N-DNA0)**2
C	  WRITE(6,*) 'Event #', NE, ', Impact parameter =', BGEN, 'fm'
	END DO
C==============================================================================
C
* test calculating and printing of original "true" numbers
* and generated one's (with statistical errors)
	PTAM  = PTAM / DNAM
	PTRMS = DSQRT(PTRMS) / DNAM
C
	DNAM  = DNAM / NTOT
	DNRMS = dsqrt(DNRMS) / NTOT
C==============================================================================
C
1	FORMAT(2X,'True mean multiplicity =',d10.3)
2	FORMAT(2X,'Generated mean multiplicity =',d10.3,' +-',d9.2)
5	FORMAT(2X,'True mean transverse momentum =',d9.2)
6	FORMAT(2X,'Generated mean transverse momentum =',d9.2,' +-',d9.2)
C==============================================================================
C
	WRITE(6,1) DNA0
	WRITE(6,2) DNAM, DNRMS
	WRITE(6,5) PTA0
	WRITE(6,6) PTAM, PTRMS
C==============================================================================
C
	END
