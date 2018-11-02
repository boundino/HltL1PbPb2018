#!/bin/bash

INPUT=/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20181031_V56_20181020_D0_Pythia8_prompt_Cymbal5Ev8_Dpt4tk2p5dls2_1030_pthatweight.root
RUN=${1:-0}

g++ dcount.C $(root-config --libs --cflags) -g -o dcount.exe || exit 1

[[ $RUN -eq 1 ]] || { exit 0 ; }

mkdir -p rootfiles

for i in {0..10}
do
    set -x
    ./dcount.exe $INPUT V56 $i -1
    set +x
done

rm dcount.exe