#!/bin/bash

###
# INPUTFILE="/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180903_V20_20180814_D0_Pythia8_prompt_Cymbal5Ev8_Dpt4tk2p5dls2_noweight.root"
# OUTPUTFILE="/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180903_V20_20180814_D0_Pythia8_prompt_Cymbal5Ev8_Dpt4tk2p5dls2_pthatweight.root"
# INPUTFILE="/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180903_V20_20180814_Ds_Prompt_phikkpi_Pythia_Dpt4tk2p5dls2_noweight.root"
# OUTPUTFILE="/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180903_V20_20180814_Ds_Prompt_phikkpi_Pythia_Dpt4tk2p5dls2_pthatweight.root"
INPUTFILE="/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180903_V20_20180827_D0_Pythia8_prompt_Cymbal5Ev8_HiForestAOD_trkPt2_noweight.root"
OUTPUTFILE="/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180903_V20_20180827_D0_Pythia8_prompt_Cymbal5Ev8_HiForestAOD_trkPt2_pthatweight.root"

# Dzero prompt
sed '1iconst int nBins=4; float pthatBin[nBins]={10, 20, 50, 100}; float crosssec[nBins+1]={2.069e+08, 2.040e+07, 6.378e+05, 2.893e+04, 0.}; int genSignal[2]={1,2};' weighPurePthat.C > weighPurePthat_tmp.C

# Ds prompt
# sed '1iconst int nBins=4; float pthatBin[nBins]={10, 20, 50, 100}; float crosssec[nBins+1]={3.79e+07, 3.65e+06, 1.16e+05, 6.26e+03, 0.}; int genSignal[2]={7,8};' weighPurePthat.C > weighPurePthat_tmp.C

###

cp "$INPUTFILE" "$OUTPUTFILE"
g++ weighPurePthat_tmp.C $(root-config --cflags --libs) -g -o weighPurePthat_tmp.exe 
./weighPurePthat_tmp.exe "$INPUTFILE" "$OUTPUTFILE"
rm weighPurePthat_tmp.exe

rm weighPurePthat_tmp.C
