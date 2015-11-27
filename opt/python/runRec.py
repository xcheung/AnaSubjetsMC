#!/usr/bin/python

import sys, os
sys.path.append('lib')

sPath = "#Local#xzhang#subjetsTH#QA#rec#data"
sFile = "out"
sJetR = "JetR05"
sSjeR = "SjeR01"

import AnaRecoPicoEvents
AnaRecoPicoEvents.Run(sPath,sFile,sJetR,sSjeR)
