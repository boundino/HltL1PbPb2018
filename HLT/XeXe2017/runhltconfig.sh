#!/bin/bash

# MENU="/users/davidlw/HLT_PbPb2018_FullTrackv2/V23"
MENU="/users/wangj/PbPb2018/HLTPbPb2018Import/V11"
FILE=file:/afs/cern.ch/work/w/wangj/public/XeXeMB8/raw/B662A9FF-90AF-E711-B5BA-02163E01375A.root
# FILE=root://cms-xrd-global.cern.ch//store/hidata/XeXeRun2017/HIMinimumBias8/AOD/13Dec2017-v1/10000/F2F884C7-76F9-E711-AE1F-0CC47A1E047C.root # AOD
# PARENT=root://cms-xrd-global.cern.ch//store/hidata/XeXeRun2017/HIMinimumBias8/RAW/v1/000/304/899/00000/D847E14A-60B0-E711-AF0A-02163E011E6D.root # RAW

CONFIG=expHLT_101X_XeXe_cfg

hltGetConfiguration $MENU \
   --globaltag 100X_dataRun2_v1 \
   --input $FILE \
   --customise HLTrigger/Configuration/customizeHLTforCMSSW.customiseFor2017DtUnpacking,FWCore/ParameterSet/MassReplace.massReplaceInputTag \
   --setup /dev/CMSSW_10_1_0/GRun \
   --process MYHLT --full --offline --data --unprescale --max-events 1000 > ${CONFIG}.py

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

echo '
process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
    ignoreTotal = cms.untracked.int32(0),
    # showMallocInfo = cms.untracked.bool(False),
    # oncePerEventMode = cms.untracked.bool(True),
    # jobReportOutputOnly = cms.untracked.bool(False),
    # M_MMAP_MAX = cms.untracked.int32(-1),
    # M_TRIM_THRESHOLD = cms.untracked.int32(-1),
    # M_TOP_PAD = cms.untracked.int32(-1),
    # M_MMAP_THRESHOLD = cms.untracked.int32(-1),
    # dump = cms.untracked.bool(False),
    monitorPssAndPrivate = cms.untracked.bool(True),
    moduleMemorySummary = cms.untracked.bool(True)
)' >> ${CONFIG}.py

