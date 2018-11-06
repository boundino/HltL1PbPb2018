#!/bin/bash

INPUT=/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20181031_V56_20181020_D0_Pythia8_prompt_Cymbal5Ev8_Dpt4tk2p5dls2_1030_pthatweight.root
# TAG="V56trk2GeV"
TAG="V56"
# INPUT=/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20181031_V56_20181020_D0_Pythia8_prompt_Pthat10_Cymbal5Ev8_Dpt4tk2p5dls2_1030.root
RUN=${1:-0}
DRAW=${2:-0}

g++ dcount.C $(root-config --libs --cflags) -g -o dcount.exe || exit 1
g++ drawdcount.C $(root-config --libs --cflags) -g -o drawdcount.exe || exit 1

mkdir -p rootfiles
mkdir -p plots

# for i in 1
for i in {0..2}
do
    set -x
    [[ $RUN -eq 1 ]] && { ./dcount.exe $INPUT ${TAG} $i -1 ; }
    [[ $DRAW -eq 1 ]] && { ./drawdcount.exe ${TAG} ${TAG} $i ; }
    set +x
done

rm drawdcount.exe
rm dcount.exe