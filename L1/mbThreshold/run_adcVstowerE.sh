#!/bin/bash

INPUTFILE="/export/d00/scratch/jwang/L1ppLowPU2018/matchingl1forest/crab_HiForestAOD_match_L1_20180827_lowPUpp_ZeroBias_Run319462_319464_HFnTrk_HFAdcToGeVv2.root"
# INPUTFILE="/export/d00/scratch/jwang/L1ppLowPU2018/matchingl1forest/crab_HiForestAOD_match_L1_20180810_lowPUpp_ZeroBias_Run319462_319464_v4v3.root"
OUTPUT="rootfiles/root_adcVstowerE_lowPUpp_HiForestAOD_match_L1_319462-464_HFAdcToGeV"
TAG="Run 319462-319464"

# INPUTFILE="/export/d00/scratch/jwang/L1ppLowPU2018/matchingl1forest/crab_HiForestAOD_match_L1_20180730_lowPUpp_ZeroBias_Run319460_319464.root"
# OUTPUT="rootfiles/root_adcVstowerE_lowPUpp_run319460_319464"
# TAG="Run 319460-319464"

g++ adcVstowerE.C $(root-config --libs --cflags) -g -o adcVstowerE.exe || exit 1
g++ drawtowerE.C $(root-config --libs --cflags) -g -o drawtowerE.exe || exit 1

mkdir -p rootfiles
mkdir -p plots

[[ ${1:-0} -eq 1 ]] && ./adcVstowerE.exe $INPUTFILE $OUTPUT
[[ ${2:-0} -eq 1 ]] && ./drawtowerE.exe ${OUTPUT}.root "$TAG"

rm drawtowerE.exe
rm adcVstowerE.exe