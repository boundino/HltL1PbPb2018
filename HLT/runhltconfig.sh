#!/bin/bash

MENU="/users/wangj/PbPb2018/HLTPbPb2018Import/V10"
FILE=file:/afs/cern.ch/work/w/wangj/public/XeXeMB8/B2E50951-92AF-E711-A534-02163E01A2FC.root # raw
# FILE=root://cms-xrd-global.cern.ch//store/hidata/XeXeRun2017/HIMinimumBias8/AOD/13Dec2017-v1/10000/F2F884C7-76F9-E711-AE1F-0CC47A1E047C.root # AOD
# FILE=root://cms-xrd-global.cern.ch//store/hidata/XeXeRun2017/HIMinimumBias8/RAW/v1/000/304/899/00000/D847E14A-60B0-E711-AF0A-02163E011E6D.root # RAW

CONFIG=expmenu

hltGetConfiguration $MENU \
   --globaltag 100X_dataRun2_v1 \
   --input $FILE \
   --customise HLTrigger/Configuration/customizeHLTforCMSSW.customiseFor2017DtUnpacking,FWCore/ParameterSet/MassReplace.massReplaceInputTag \
   --setup /dev/CMSSW_10_1_0/GRun \
   --process MYHLT --full --offline --data --unprescale --max-events 10 \
   --l1-emulator Full > ${CONFIG}.py

set -x
edmConfigDump ${CONFIG}.py >& ${CONFIG}_DUMP.py
set +x

sed -i 's/rawDataCollector/rawDataRepacker/g' ${CONFIG}_DUMP.py
sed -i '/hgcal/s/^/# /' ${CONFIG}_DUMP.py
sed -i '1s/^/# /' ${CONFIG}_DUMP.py
# sed -i 's/numberOfThreads = cms.untracked\.uint32( 4 )/numberOfThreads = cms.untracked.uint32( 1 )/g' ${CONFIG}_DUMP.py

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


# ----------------------------------------------------------------------------------------------------------------------------------- #

# /store/hidata/XeXeRun2017/HIMinimumBias8/RAW/v1/000/304/899/00000/D847E14A-60B0-E711-AF0A-02163E011E6D.root # 137
# /store/hidata/XeXeRun2017/HIMinimumBias8/RAW/v1/000/304/899/00000/CAA72D95-91AF-E711-B97C-02163E019BE0.root # 123, 124
# /store/hidata/XeXeRun2017/HIMinimumBias8/RAW/v1/000/304/899/00000/B662A9FF-90AF-E711-B5BA-02163E01375A.root # 125
# /store/hidata/XeXeRun2017/HIMinimumBias8/RAW/v1/000/304/899/00000/94DD0347-8CAF-E711-B1AA-02163E019E14.root # 35
# /store/hidata/XeXeRun2017/HIMinimumBias8/RAW/v1/000/304/899/00000/54CD3B96-91AF-E711-A3AC-02163E01A6CC.root # 121, 122
# /store/hidata/XeXeRun2017/HIMinimumBias8/RAW/v1/000/304/899/00000/48ADAA6C-8CAF-E711-866A-02163E019B21.root # 39
# /store/hidata/XeXeRun2017/HIMinimumBias8/RAW/v1/000/304/899/00000/20B1759C-5FB0-E711-9565-02163E0141CD.root # 192

# hltGetConfiguration $MENU \
#    --globaltag 100X_dataRun2_v1 \
#    --input $FILE \
#    --customise HLTrigger/Configuration/customizeHLTforCMSSW.customiseFor2017DtUnpacking \
#    --setup /dev/CMSSW_10_1_0/GRun \
#    --customise=L1Trigger/Configuration/customiseReEmul.L1TReEmulFromRAW \
#    --customise=L1Trigger/L1TNtuples/customiseL1Ntuple.L1NtupleEMU \
#    --customise=L1Trigger/Configuration/customiseUtils.L1TTurnOffUnpackStage2GtGmtAndCalo \
#    --customise=FWCore/ParameterSet/MassReplace.massReplaceInputTag \
#    --process MYHLT --full --offline --data --unprescale --max-events 1000 \
#    --l1-emulator Full > $CONFIG.py

