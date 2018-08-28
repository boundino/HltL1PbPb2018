#!/bin/bash

FOREST="/export/d00/scratch/jwang/HltPbPb2018MC/crab_HiForestAOD_20180827_D0_Pythia8_prompt_Pthat100_Cymbal5Ev8_2018_trkPt2.root"
HLT="/export/d00/scratch/jwang/HltPbPb2018MC/crab_openHLT_20180827_V17_D0_Pythia8_prompt_Pthat100_Cymbal5Ev8_V49pv4c.root"
OUTPUT="/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180827_V17V49pv4c_20180814_D0_Pythia8_prompt_Pthat100_Cymbal5Ev8_HiForestAODtrkPt2.root"

g++ evtmatchingForest.C $(root-config --libs --cflags) -g -o evtmatchingForest.exe

[[ ! -f $FOREST || ! -f $HLT ]] && { echo "no file: $FOREST $HLT" ; exit 1 ; }
./evtmatchingForest.exe $FOREST $HLT $OUTPUT
rm evtmatchingForest.exe