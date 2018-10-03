#!/bin/bash

MENU="/users/wangj/PbPb2018/HLTPbPb2018Import/V33"
CONFIG=expHLT_102X_ImportV33L1_cfg

FILE=file:/afs/cern.ch/work/w/wangj/public/PbPb2018MCMB/RAW/FE243EFA-6DAB-E811-BFDE-9CB654AD72EC.root # MB MC 2018

emuL1org=/afs/cern.ch/user/i/icali/public/L1Menu_CollisionsHeavyIons2018_v3.xml
emulL1="--l1-emulator FullMC --l1Xml=L1Menu_CollisionsHeavyIons2018_v3.xml"
# emuL1org=/afs/cern.ch/user/w/wangj/public/menu/L1Menu_CollisionsHeavyIons2018_v3_rmAsyCent.xml
# emulL1="--l1-emulator FullMC --l1Xml=L1Menu_CollisionsHeavyIons2018_v3_rmAsyCent.xml"
# emulL1=""

mkdir -p ../L1Trigger/L1TGlobal/data/Luminosity/startup
cp $emuL1org ../L1Trigger/L1TGlobal/data/Luminosity/startup/

hltGetConfiguration $MENU \
    --globaltag 103X_upgrade2018_realistic_HI_v5 \
    --input $FILE \
    --customise L1Trigger/Configuration/customiseSettings.L1TSettingsToCaloParams_2018_v1_4 \
    --setup /dev/CMSSW_10_1_0/GRun \
    --process MYHLT --full --offline --mc --unprescale --max-events 10 $emulL1 > ${CONFIG}.py

sed -i 's/L1_ZeroBias/L1GlobalDecision/g' ${CONFIG}.py
# sed -i 's/ptMin = cms\.double( 0\.. )/ptMin = cms.double( 5.0 )/g' ${CONFIG}.py
sed -i 's/numberOfThreads = cms.untracked\.uint32( 4 )/numberOfThreads = cms.untracked.uint32( 1 )/g' ${CONFIG}.py
sed -i 's/process\.DQMStore\.enableMultiThread = True/process.DQMStore.enableMultiThread = False/g' ${CONFIG}.py

# 10_0_X BS
echo '
import CalibTracker.Configuration.Common.PoolDBESSource_cfi
process.newBS = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(connect = cms.string('"'"'frontier://FrontierProd/CMS_CONDITIONS'"'"'), toGet = cms.VPSet(cms.PSet(record = cms.string('"'"'BeamSpotObjectsRcd'"'"'), tag = cms.string('"'"'BeamSpotObjects_Realistic25ns_13TeVCollisions_Early2017_v1_mc'"'"'))))
process.prefer_PreferNewBS = cms.ESPrefer('"'"'PoolDBESSource'"'"', '"'"'newBS'"'"')
' >> ${CONFIG}.py
# L1 customization
echo '
# muon
process.simEmtfDigis.CSCInputBXShift = cms.int32(-6)
# EG
process.caloStage2Params.egBypassExtHOverE = cms.uint32(1)
process.caloStage2Params.egBypassShape = cms.uint32(1)
process.caloStage2Params.egBypassECALFG = cms.uint32(1)
process.caloStage2Params.egHOverEcutBarrel = cms.int32(1)
process.caloStage2Params.egHOverEcutEndcap = cms.int32(1)
process.caloStage2Params.egEtaCut = cms.int32(24)
# jet
process.caloStage2Params.hiMode = cms.uint32(1)
process.caloStage2Params.jetPUSType = cms.string('"'"'PhiRing2'"'"')
# centrality
process.caloStage2Params.etSumCentralityLower = cms.vdouble(0.0, 2.5,  13.5,  133.0, 411.5,  1101.5, 2494.5, 65535.0)
process.caloStage2Params.etSumCentralityUpper = cms.vdouble(8.0, 25.5, 208.0, 567.5, 1349.5, 2790.5, 5114.0, 65535.0)

process.GlobalTag.toGet = cms.VPSet(cms.PSet(record = cms.string('"'"'HcalElectronicsMapRcd'"'"'), tag = cms.string('"'"'HcalElectronicsMap_2018_v3.0_mc'"'"'), connect = cms.string('"'"'frontier://FrontierProd/CMS_CONDITIONS'"'"'), globaltag=cms.string('"'"'103X_upgrade2018_realistic_v4'"'"')))
' >> ${CONFIG}.py

echo '
# hltbitanalysis
process.load("HLTrigger.HLTanalyzers.HLTBitAnalyser_cfi")
process.hltbitanalysis.HLTProcessName = cms.string("MYHLT")
process.hltbitanalysis.hltresults = cms.InputTag( "TriggerResults","","MYHLT" )
process.hltbitanalysis.l1results = cms.InputTag("hltGtStage2Digis","","MYHLT")
process.hltbitanalysis.UseTFileService = cms.untracked.bool(True)
process.hltbitanalysis.RunParameters = cms.PSet(
    isData = cms.untracked.bool(True))
process.hltBitAnalysis = cms.EndPath(process.hltbitanalysis)
process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string("openHLT.root"))' >> ${CONFIG}.py

echo '
# process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#     ignoreTotal = cms.untracked.int32(2),
#     # oncePerEventMode = cms.untracked.bool(True),
#     monitorPssAndPrivate = cms.untracked.bool(True),
#     moduleMemorySummary = cms.untracked.bool(True)
# )
process.Timing = cms.Service("Timing",
summaryOnly = cms.untracked.bool(False),
useJobReport = cms.untracked.bool(True)
)' >> ${CONFIG}.py

set -x
edmConfigDump ${CONFIG}.py >& ${CONFIG}_DUMP.py
set +x

[[ "x$emulL1" != "x" ]] && { sed -i '1s/^/# /' ${CONFIG}_DUMP.py ; sed -i '/hgcal/s/^/# /' ${CONFIG}_DUMP.py; }
