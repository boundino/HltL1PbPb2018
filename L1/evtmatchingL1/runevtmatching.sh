#!/bin/bash

# FOREST="/export/d00/scratch/jwang/L1ppLowPU2018/matchingl1forest/crab_HiForestAOD_20180730_lowPUpp_ZeroBias_Run319460.root"
# L1="/export/d00/scratch/jwang/L1ppLowPU2018/matchingl1forest/crab_L1_20180730_lowPUpp_ZeroBias_Run319460.root"
# OUTPUT="/export/d00/scratch/jwang/L1ppLowPU2018/matchingl1forest/crab_HiForestAOD_match_L1_20180730_lowPUpp_ZeroBias_Run319460.root"

FOREST="/export/d00/scratch/jwang/L1ppLowPU2018/matchingl1forest/crab_HiForestAOD_20180730_lowPUpp_ZeroBias_Run319462_319464.root"
L1="/export/d00/scratch/jwang/L1ppLowPU2018/matchingl1forest/crab_L1_20180730_lowPUpp_ZeroBias_Run319462_319464.root"
OUTPUT="/export/d00/scratch/jwang/L1ppLowPU2018/matchingl1forest/crab_HiForestAOD_match_L1_20180730_lowPUpp_ZeroBias_Run319462_319464.root"

g++ evtmatching.C $(root-config --libs --cflags) -g -o evtmatching.exe

[[ ! -f $FOREST || ! -f $L1 ]] && { echo "no file: $FOREST $L1" ; exit 1 ; }
./evtmatching.exe $FOREST $L1 $OUTPUT

rm evtmatching.exe