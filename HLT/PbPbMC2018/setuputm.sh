#!/bin/bash

[[ $0 == "-bash" ]] || { echo "do [ source setuputm.sh ] or [ . setuputm.sh ]" ; exit 1 ; }

set -x

cmsrel CMSSW_10_2_1
cd CMSSW_10_2_1/src
cmsenv
git-cms-init

## get Aaron's integration tag
git remote add cms-l1t-offline git@github.com:cms-l1t-offline/cmssw.git
git fetch cms-l1t-offline l1t-integration-CMSSW_10_2_1
git cms-merge-topic -u cms-l1t-offline:l1t-integration-v100.0
git cms-addpkg L1Trigger/L1TCommon
git cms-addpkg L1Trigger/L1TMuon
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TMuon.git L1Trigger/L1TMuon/data
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TCalorimeter.git L1Trigger/L1TCalorimeter/data

## get changes for uGT emulator
git cms-addpkg DataFormats/L1TGlobal
git cms-addpkg L1Trigger/L1TGlobal
git pull https://github.com/apana/cmssw.git apana-HIprelim

## copy the xml into the L1Trigger/L1TGlobal/data/Luminosity/startup directory
mkdir -p L1Trigger/L1TGlobal/data/Luminosity/startup
cp /afs/cern.ch/user/a/apana/public/uGT/HI2018/L1Menu_CollisionsHeavyIons2018_v2-d1_LA.xml L1Trigger/L1TGlobal/data/Luminosity/startup

## now setup the utm library
cd $CMSSW_BASE
git clone https://gitlab.cern.ch/cms-l1t-utm/utm.git
cd utm
git checkout utm_0_7_x_dev

## scram tool info xerces-c
## setenv XERCES_C_BASE <XERCES_C_BASE directory printed by the above command>
## scram tool info boost
## setenv BOOST_BASE <BOOST_BASE directory printed by the above command>
export $(scram tool info xerces-c | grep color=auto XERCES_C_BASE)
export $(scram tool info boost | grep color=auto BOOST_BASE)
make all
make install

cd $CMSSW_BASE/src
## Almost there. Edit ../config/toolbox/${SCRAM_ARCH}/tools/selected/utm.xml and
## change the default for the UTM_BASE variable to the directory pointed to by the output of "echo $CMSSW_BASE/utm", then
## sed -i 's/ptMin = cms\.double( 0\.. )/ptMin = cms.double( 5.0 )/g' ${CONFIG}.py
echo $CMSSW_BASE/utm > utmpath.temp
sed -i 's/"UTM_BASE" default=".*"/"UTM_BASE" default="'$(sed 's/\//\\\//g' utmpath.temp)'"/g' test.xml
rm utmpath.temp

scram setup utm
scram b -j7

set +x