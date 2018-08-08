#!/bin/bash

MENU="/users/wangj/PbPb2018/HLTPbPb2018Import/V11"
FILE=file:/afs/cern.ch/work/w/wangj/public/XeXeMB8/B2E50951-92AF-E711-A534-02163E01A2FC.root # raw
# FILE=root://cms-xrd-global.cern.ch//store/hidata/XeXeRun2017/HIMinimumBias8/AOD/13Dec2017-v1/10000/F2F884C7-76F9-E711-AE1F-0CC47A1E047C.root # AOD
# PARENT=root://cms-xrd-global.cern.ch//store/hidata/XeXeRun2017/HIMinimumBias8/RAW/v1/000/304/899/00000/D847E14A-60B0-E711-AF0A-02163E011E6D.root # RAW

CONFIG=expmenu_l1emulator

hltGetConfiguration $MENU \
   --globaltag 100X_dataRun2_v1 \
   --input $FILE \
   --customise HLTrigger/Configuration/customizeHLTforCMSSW.customiseFor2017DtUnpacking,FWCore/ParameterSet/MassReplace.massReplaceInputTag \
   --setup /dev/CMSSW_10_1_0/GRun \
   --process MYHLT --full --offline --data --unprescale --max-events 100 \
   --l1-emulator Full > ${CONFIG}.py

set -x
edmConfigDump ${CONFIG}.py >& ${CONFIG}_DUMP.py
set +x

sed -i 's/rawDataCollector/rawDataRepacker/g' ${CONFIG}_DUMP.py
sed -i '/hgcal/s/^/# /' ${CONFIG}_DUMP.py
sed -i '1s/^/# /' ${CONFIG}_DUMP.py
# sed -i 's/numberOfThreads = cms.untracked\.uint32(4)/numberOfThreads = cms.untracked.uint32(1)/g' ${CONFIG}_DUMP.py
# sed -i 's/enableMultiThread = cms\.untracked\.bool(True)/enableMultiThread = cms.untracked.bool(False)/g' ${CONFIG}_DUMP.py

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
                                   fileName=cms.string("openHLT_l1emulator.root"))' >> ${CONFIG}.py
