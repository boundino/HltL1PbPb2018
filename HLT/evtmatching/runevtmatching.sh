#!/bin/bash

FOREST="/export/d00/scratch/jwang/HltPbPb2018MC/crab_DfinderMC_20180814_D0_Pythia8_prompt_Pthat100_Cymbal5Ev8_2018_Dpt4tk2p5dls2_v2.root"
HLT="/export/d00/scratch/jwang/HltPbPb2018MC/crab_openHLT_20180815_D0_Pythia8_prompt_Pthat100_Cymbal5Ev8_2018_iter0to3.root"
OUTPUT="/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180815_D0_Pythia8_prompt_Pthat100_Cymbal5Ev8_2018_iter0to3_Dpt4tk2p5dls2_v2.root"

g++ evtmatching.C $(root-config --libs --cflags) -g -o evtmatching.exe

[[ ! -f $FOREST || ! -f $HLT ]] && { echo "no file: $FOREST $HLT" ; exit 1 ; }
./evtmatching.exe $FOREST $HLT $OUTPUT
rm evtmatching.exe