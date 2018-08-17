#!/bin/bash

INPUTFILE="/eos/cms/store/group/phys_heavyions/wangj/lowPUppRECO/ZeroBias/forestmatchL1/L1NtupleHiForestAOD_lowPUpp_ZeroBias_Run319462_319464_101-5.root"
OUTPUT="rootfiles/root_adcToGeV_Run319464"
TAG="Run 319464"

g++ adcToGeV.C $(root-config --libs --cflags) -g -o adcToGeV.exe || exit 1
g++ drawadcToGeV.C $(root-config --libs --cflags) -g -o drawadcToGeV.exe || exit 1

mkdir -p rootfiles
mkdir -p plots

[[ ${1:-0} -eq 1 ]] && ./adcToGeV.exe $INPUTFILE $OUTPUT
[[ ${2:-0} -eq 1 ]] && ./drawadcToGeV.exe ${OUTPUT}.root "$TAG"

rm drawadcToGeV.exe
rm adcToGeV.exe