#!/bin/bash

MENU="/users/wangj/PbPb2018/HLTPbPb2018Import/V11"
FILE=file:/afs/cern.ch/work/w/wangj/public/PbPb2018MCDs/raw/step1_DIGI_L1_DIGI2RAW_HLT_PU_184.root # Ds pthat100
# FILE=file:/afs/cern.ch/work/w/wangj/public/PbPb2018MCDs/aod/step2_RAW2DIGI_L1Reco_RECO_94.root
# PARENT=file:/afs/cern.ch/work/w/wangj/public/PbPb2018MCDs/raw/step1_DIGI_L1_DIGI2RAW_HLT_PU_184.root

CONFIG=expHLT_102X_cfg

hltGetConfiguration $MENU \
   --globaltag auto:phase1_2018_realistic \
   --input $FILE \
   --customise HLTrigger/Configuration/customizeHLTforCMSSW.customiseFor2017DtUnpacking,FWCore/ParameterSet/MassReplace.massReplaceInputTag \
   --setup /dev/CMSSW_10_1_0/GRun \
   --process MYHLT --full --offline --data --unprescale --max-events 10 > ${CONFIG}.py

sed -i 's/L1_ZeroBias/L1GlobalDecision/g' ${CONFIG}.py
# sed -i 's/numberOfThreads = cms.untracked\.uint32( 4 )/numberOfThreads = cms.untracked.uint32( 1 )/g' ${CONFIG}.py
# sed -i 's/process\.DQMStore\.enableMultiThread = True/process.DQMStore.enableMultiThread = False/g' ${CONFIG}.py

echo '
# hltbitanalysis
process.load("HLTrigger.HLTanalyzers.HLTBitAnalyser_cfi")
process.hltbitanalysis.HLTProcessName = cms.string("MYHLT")
process.hltbitanalysis.hltresults = cms.InputTag( "TriggerResults","","MYHLT" )
process.hltbitanalysis.UseTFileService = cms.untracked.bool(True)
process.hltbitanalysis.RunParameters = cms.PSet(
    isData = cms.untracked.bool(True))
process.hltBitAnalysis = cms.EndPath(process.hltbitanalysis)
process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string("openHLT.root"))' >> ${CONFIG}.py

set -x
edmConfigDump ${CONFIG}.py >& ${CONFIG}_DUMP.py
set +x

sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_DUMP.py
sed 's/minPt = cms\.double(0\.\([0-9]\)),/minPt = cms.double(5.0), # minPt = cms.double(0.\1)/g' ${CONFIG}_DUMP.py > ${CONFIG}_DUMP_chpt.py