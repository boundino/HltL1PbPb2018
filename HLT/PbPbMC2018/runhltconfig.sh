#!/bin/bash

# MENU="/users/wangj/PbPb2018/HLTPbPb2018Import/V20"
# CONFIG=expHLT_102X_ImportV20_cfg
MENU="/users/davidlw/HLT_PbPb2018_FullTrackv2/V50"
CONFIG=expHLT_102X_TrkV50_cfg
FILE=file:/afs/cern.ch/work/w/wangj/public/PbPb2018MCDs/raw/step1_DIGI_L1_DIGI2RAW_HLT_PU_184.root # Ds pthat100

# emulL1="--l1-emulator FullMC --l1Xml=/afs/cern.ch/user/i/icali/public/L1Menu_CollisionsHeavyIons2018_v1.xml"
emulL1=""

hltGetConfiguration $MENU \
   --globaltag auto:phase1_2018_realistic \
   --input $FILE \
   --customise HLTrigger/Configuration/customizeHLTforCMSSW.customiseFor2017DtUnpacking \
   --setup /dev/CMSSW_10_1_0/GRun \
   --process MYHLT --full --offline --mc --unprescale --max-events 10 $emulL1 > ${CONFIG}.py

sed -i 's/L1_ZeroBias/L1GlobalDecision/g' ${CONFIG}.py
# sed -i 's/ptMin = cms\.double( 0\.. )/ptMin = cms.double( 5.0 )/g' ${CONFIG}.py
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

echo '
process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
    ignoreTotal = cms.untracked.int32(2),
    oncePerEventMode = cms.untracked.bool(True),
    monitorPssAndPrivate = cms.untracked.bool(True),
    moduleMemorySummary = cms.untracked.bool(True)
)
process.Timing = cms.Service("Timing",
  summaryOnly = cms.untracked.bool(False),
  useJobReport = cms.untracked.bool(True)
)' >> ${CONFIG}.py

set -x
edmConfigDump ${CONFIG}.py >& ${CONFIG}_DUMP.py
set +x

sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_DUMP.py
[[ "x$emulL1" != "x" ]] && { sed -i '1s/^/# /' ${CONFIG}_DUMP.py ; sed -i '/hgcal/s/^/# /' ${CONFIG}_DUMP.py; }