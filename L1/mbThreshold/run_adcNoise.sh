#!/bin/bash

RUN=(0 1)

FILE_ZeroBias=(
    "/export/d00/scratch/jwang/L1ppLowPU2018/noise/L1Ntuple_ZeroBias_319460.root"
    "/export/d00/scratch/jwang/L1XeXe/noise/L1Ntuple_HIZeroBias_304906.root"
)
FILE_EmptyBX=(
    "/export/d00/scratch/jwang/L1ppLowPU2018/noise/L1Ntuple_EmptyBX_319460.root"
    "/export/d00/scratch/jwang/L1XeXe/noise/L1Ntuple_HIEmptyBX_304906.root"
)
OUTPUT=(
    "rootfiles/root_adcNoise_lowPUpp_run319460"
    "rootfiles/root_adcNoise_XeXe_run304906"
)
TAG=(
    "Run 319460"
    "Run 304906"
)

g++ adcNoise.C $(root-config --libs --cflags) -g -o adcNoise.exe || exit 1
g++ drawadcNoise.C $(root-config --libs --cflags) -g -o drawadcNoise.exe || exit 1

mkdir -p rootfiles
mkdir -p plots

[[ ${1:-0} -eq 1 ]] && { for i in ${RUN[@]} ; do ./adcNoise.exe ${FILE_ZeroBias[i]} ${FILE_EmptyBX[i]} ${OUTPUT[i]} ; done ; }
[[ ${2:-0} -eq 1 ]] && { for i in ${RUN[@]} ; do ./drawadcNoise.exe ${OUTPUT[i]}.root "${TAG[i]}" ; done ; }

rm drawadcNoise.exe
rm adcNoise.exe