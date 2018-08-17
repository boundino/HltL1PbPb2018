#!/bin/bash

INPUT=(
    "/export/d00/scratch/jwang/L1ppLowPU2018/tower/HiForestAOD_20180810_319462.root"
    "/export/d00/scratch/jwang/L1ppLowPU2018/tower/HiForestAOD_20180810_319463.root"
    "/export/d00/scratch/jwang/L1ppLowPU2018/tower/HiForestAOD_20180810_319464.root"
)

OUTPUT="rootfiles/root_mbtowerE_lowPUpp_run319462_3_4"
OUTNAME="2018 low PU pp"

TAG=(
    "Run319462(HF12)"
    "Run319463(HF15)"
    "Run319464(HF17)"
)

g++ mbtowerE.C $(root-config --libs --cflags) -g -o mbtowerE.exe || exit 1
g++ drawMB.C $(root-config --libs --cflags) -g -o drawMB.exe || exit 1

mkdir -p rootfiles
mkdir -p plots

set -x
[[ ${1:-0} -eq 1 ]] && ./mbtowerE.exe ${INPUT[@]} $OUTPUT
[[ ${2:-0} -eq 1 ]] && ./drawMB.exe $OUTPUT.root ${TAG[@]} "$OUTNAME"
set +x

rm drawMB.exe
rm mbtowerE.exe