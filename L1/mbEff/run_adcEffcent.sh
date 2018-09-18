#!/bin/bash

INDEX=(0 1 2)

INPUTFILE=(
    "/export/d00/scratch/jwang/L1XeXe/crab_L1NtupleMatchedHiForestAOD_20180912_HIMinimumBias7_XeXeRun2017_v1_Run304906_lumi292-396_v2.root"
    # "/export/d00/scratch/jwang/L1PbPb/crab_L1NtupleMatchedHiForestAOD_20180912_Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018_adc_v2.root"
    "/export/d00/scratch/jwang/L1PbPb/crab_L1NtupleMatchedHiForestAOD_20180912_Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018_adc_cGT_v2.root"
    "/export/d00/scratch/jwang/L1XeXe/crab_L1NtupleMatchedHiForestAOD_20180912_HIZeroBias_XeXeRun2017_v1_Run304906_lumi292-730_v2.root"
)
OUTPUT=(
    "rootfiles/root_adcEffcent_HIMinimumBias7_XeXeRun2017_v1_Run304906_lumi292-396"
    "rootfiles/root_adcEffcent_Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018"
    "rootfiles/root_adcEffcent_HIZeroBias_XeXeRun2017_v1_Run304906_lumi292-730"
)
TAG=(
    "Run 304906 (XeXe MB)"
    "PbPb MB MC (Drum5Ev8)"
    "Run 304906 (XeXe ZB)"
)
IFTRK=(
    1
    0
    1
)
IFSKIM=(
    1
    3
    1
)

g++ adcEffcent.C $(root-config --libs --cflags) -g -o adcEffcent.exe || exit 1
g++ drawEffcent.C $(root-config --libs --cflags) -g -o drawEffcent.exe || exit 1

mkdir -p rootfiles
mkdir -p plots

[[ ${1:-0} -eq 1 ]] && { for i in ${INDEX[@]} ; do { ./adcEffcent.exe ${INPUTFILE[i]} ${OUTPUT[i]} -1 ${IFTRK[i]} ${IFSKIM[i]} ; } ; done ; }
[[ ${2:-0} -eq 1 ]] && { for i in ${INDEX[@]} ; do { ./drawEffcent.exe ${OUTPUT[i]}.root "${TAG[i]}" ${IFTRK[i]}; } ; done ; }

rm drawEffcent.exe
rm adcEffcent.exe