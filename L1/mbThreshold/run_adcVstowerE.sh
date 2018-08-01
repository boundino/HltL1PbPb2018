#!/bin/bash

INPUTFILE="/export/d00/scratch/jwang/L1ppLowPU2018/matchingl1forest/crab_HiForestAOD_match_L1_20180730_lowPUpp_ZeroBias_Run319460_319464.root"
OUTPUT="rootfiles/root_adcVstowerE_lowPUpp_run319460_319464"
TAG="2018 low PU pp"

g++ adcVstowerE.C $(root-config --libs --cflags) -g -o adcVstowerE.exe || exit 1
g++ drawtowerE.C $(root-config --libs --cflags) -g -o drawtowerE.exe || exit 1

mkdir -p rootfiles
mkdir -p plots

[[ ${1:-0} -eq 1 ]] && ./adcVstowerE.exe $INPUTFILE $OUTPUT
[[ ${2:-0} -eq 1 ]] && ./drawtowerE.exe ${OUTPUT}.root "$TAG"

rm drawtowerE.exe
rm adcVstowerE.exe