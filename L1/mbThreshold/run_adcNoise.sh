#!/bin/bash

FILE_ZeroBias="/export/d00/scratch/jwang/L1ppLowPU2018/noise/L1Ntuple_ZeroBias_319460.root"
FILE_EmptyBX="/export/d00/scratch/jwang/L1ppLowPU2018/noise/L1Ntuple_EmptyBX_319460.root"
OUTPUT="rootfiles/root_adcNoise_lowPUpp_run319460"
TAG="Run319460"

g++ adcNoise.C $(root-config --libs --cflags) -g -o adcNoise.exe || exit 1
g++ drawadcNoise.C $(root-config --libs --cflags) -g -o drawadcNoise.exe || exit 1

mkdir -p rootfiles
mkdir -p plots

[[ ${1:-0} -eq 1 ]] && ./adcNoise.exe $FILE_ZeroBias $FILE_EmptyBX $OUTPUT
[[ ${2:-0} -eq 1 ]] && ./drawadcNoise.exe $OUTPUT.root "$TAG"

rm drawadcNoise.exe
rm adcNoise.exe