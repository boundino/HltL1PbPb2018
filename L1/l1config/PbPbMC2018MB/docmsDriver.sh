#!/bin/bash

GLOBTAG="100X_upgrade2018_realistic_v10"
SAMPLE="file:/afs/cern.ch/work/w/wangj/public/PbPb2018MCMB/RAW/B62D715A-EF26-E811-9EEA-A4BF01158D78.root"
NEVENT=10

cmsDriver.py l1Ntuple_MC -s RAW2DIGI --era=Run2_2018  \
--customise=L1Trigger/Configuration/customiseReEmul.L1TReEmulMCFromRAW \
--customise=L1Trigger/L1TNtuples/customiseL1Ntuple.L1NtupleEMU \
--customise=L1Trigger/L1TNtuples/customiseL1Ntuple.L1NtupleGEN \
--customise=L1Trigger/Configuration/customiseUtils.L1TTurnOffUnpackStage2GtGmtAndCalo \
--customise_commands="process.simTwinMuxDigis.DTDigi_Source = cms.InputTag('bmtfDigis')\n process.simTwinMuxDigis.DTThetaDigi_Source = cms.InputTag('bmtfDigis')\n process.simTwinMuxDigis.RPC_Source = cms.InputTag('muonRPCDigis')\n" \
--conditions=$GLOBTAG -n $NEVENT --mc --no_exec --no_output \
--filein=$SAMPLE

edmConfigDump l1Ntuple_MC_RAW2DIGI.py >& l1Ntuple_MC_RAW2DIGI_DUMP.py
