#!/bin/bash

cmsDriver.py step2 --data --eventcontent RECOSIM --datatier GEN-SIM-RECO --conditions 101X_dataRun2_Prompt_v11 --step RAW2DIGI,L1Reco,RECO \
    --nThreads 4 --geometry DB:Extended --era Run2_2018 --no_exec \
    --filein=root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/RAW/v1/000/319/462/00000/507C6921-2684-E811-BA3A-02163E01A8DF.root

sed -i "/Schedule definition/i \\
# hiCentrality\\
from RecoHI.HiCentralityAlgos.HiCentrality_cfi import *\\
process.hiCentrality.producePixelTracks = False\\
process.hiCentrality.srcTracks = cms.InputTag("'"'"generalTracks"'"'")\\
process.hiCentrality.srcVertex = cms.InputTag("'"'"offlinePrimaryVertices"'"'")\\
process.hicentrality_step = cms.Path(process.hiCentrality)\\
" step2_RAW2DIGI_L1Reco_RECO.py

sed -i "/Additional output definition/i \\
process.RECOSIMoutput.outputCommands.extend(cms.untracked.vstring('keep *_hiCentrality_*_*'))\\
" step2_RAW2DIGI_L1Reco_RECO.py

sed -i "s/process\.endjob_step,/process.hicentrality_step,process.endjob_step,/g" step2_RAW2DIGI_L1Reco_RECO.py

diff --report-identical-files --old-group-format=$'\e[31;1m%<\e[0m' --new-group-format=$'\e[36;1m%>\e[0m' --unchanged-group-format='' step2_RAW2DIGI_L1Reco_RECO.py step2_RAW2DIGI_L1Reco_RECO_example.py