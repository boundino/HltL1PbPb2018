#!/bin/bash

INDEX=(0 1)

INPUTFILE=(
    "/export/d00/scratch/jwang/L1XeXe/crab_L1NtupleMatchedHiForestAOD_20180912_HIMinimumBias7_XeXeRun2017_v1_Run304906_lumi292-396.root"
    "/export/d00/scratch/jwang/L1PbPb/crab_L1NtupleMatchedHiForestAOD_20180912_Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018_adc.root"
)
OUTPUT=(
    "rootfiles/root_splithiBin_HIMinimumBias7_XeXeRun2017_v1_Run304906_lumi292-396"
    "rootfiles/root_splithiBin_Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018"
)
TAG=(
    "Run 304906 (XeXe MB)"
    "PbPb MB MC (Drum5Ev8)"
)
OUTPUTEDGE=(
    0
    1
)

g++ splithiBin.C $(root-config --libs --cflags) -g -o splithiBin.exe || exit 1
g++ drawhiBin.C $(root-config --libs --cflags) -g -o drawhiBin.exe || exit 1

mkdir -p rootfiles
mkdir -p plots

set -x
[[ ${1:-0} -eq 1 ]] && { for i in ${INDEX[@]} ; do { ./splithiBin.exe ${INPUTFILE[i]} ${OUTPUT[i]} -1 ${OUTPUTEDGE[i]}; } ; done ; }
[[ ${2:-0} -eq 1 ]] && { for i in ${INDEX[@]} ; do { ./drawhiBin.exe ${OUTPUT[i]}.root "${TAG[i]}" ; } ; done ; }
set +x

rm drawhiBin.exe
rm splithiBin.exe