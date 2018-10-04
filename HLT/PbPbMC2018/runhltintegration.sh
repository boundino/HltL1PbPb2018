#!/bin/bash

MENU="/users/wangj/PbPb2018/HLTPbPb2018Import/V32"
CONFIG=expHLT_102X_ImportV32L1_cfg
# MENU="/users/wangj/PbPb2018/HLTPbPb2018Import/V29"
# CONFIG=expHLT_102X_ImportV29L1_cfg
# FILE=file:/afs/cern.ch/work/w/wangj/public/PbPb2018MCMB/RAW/FE243EFA-6DAB-E811-BFDE-9CB654AD72EC.root # MB MC 2018
FILE=file:/afs/cern.ch/work/w/wangj/public/PbPb2018MCDs/raw/step1_DIGI_L1_DIGI2RAW_HLT_PU_184.root # Ds pthat100

emuL1org=/afs/cern.ch/user/i/icali/public/L1Menu_CollisionsHeavyIons2018_v3.xml
emulL1="L1Menu_CollisionsHeavyIons2018_v3.xml"
# emuL1org=/afs/cern.ch/user/w/wangj/public/menu/L1Menu_CollisionsHeavyIons2018_v3_rmAsyCent.xml
# emulL1="--l1-emulator FullMC --l1Xml=L1Menu_CollisionsHeavyIons2018_v3_rmAsyCent.xml"
# emulL1=""

mkdir -p ../L1Trigger/L1TGlobal/data/Luminosity/startup
cp $emuL1org ../L1Trigger/L1TGlobal/data/Luminosity/startup/

# hltIntegrationTests $MENU -s /dev/CMSSW_10_1_0/GRun -i $FILE  --mc -x "--globaltag 103X_upgrade2018_realistic_HI_v5"  -x " --l1-emulator FullMC " -x " --l1Xml $emulL1 "
hltIntegrationTests $MENU -s /dev/CMSSW_10_1_0/GRun -i $FILE  --mc -x "--globaltag auto:run2_mc_GRun"  -x " --l1-emulator FullMC " -x " --l1Xml $emulL1 "
