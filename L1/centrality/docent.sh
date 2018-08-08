#!/bin/bash

INDEX=(0 1 2 3 4 5 6)

INPUT_FOREST=(
    /export/d00/scratch/jwang/L1PbPb/crab_HiForestAOD_20180402_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV_2018.root
    /export/d00/scratch/jwang/L1PbPb/crab_HiForestAOD_20180402_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV_2018.root
    /export/d00/scratch/cfmcginn/TransferGeneral/XeXeSkim/HiForestAOD_HIMinimumBias7_HighPtL1Skim_NOCUT_MERGED_20180131.root
    /export/d00/scratch/jwang/L1PbPb/forest_HIRun2015-PromptReco-v1-Run263233-263284-FOREST_4_lumill1000.root
    /export/d00/scratch/cfmcginn/TransferGeneral/XeXeSkim/HiForestAOD_HIMinimumBias7_HighPtL1Skim_NOCUT_MERGED_20180131.root
    /export/d00/scratch/jwang/L1PbPb/crab_HiForestAOD_20180402_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV_2018.root
    /export/d00/scratch/jwang/L1PbPb/crab_HiForestAOD_20180402_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV_2018.root
)
INPUT_L1=(
    /export/d00/scratch/jwang/L1PbPb/crab_L1_20180423_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV_2018.root
    /export/d00/scratch/jwang/L1PbPb/crab_L1_20180423_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV_2018_useHFLUTfalse.root
    /export/d00/scratch/jwang/L1PbPb/crab_L1_PromptReco_XeXe_20180130_HIMinimumBias7_XeXeRun2017_v1_304899_304907_threshold16.root
    /export/d00/scratch/jwang/L1PbPb/crab_L1_PromptReco_PbPb_20180318_HIMinimumBias2_HIRun2017_v1_263261.root
    /export/d00/scratch/jwang/L1PbPb/crab_L1_PromptReco_XeXe_20180130_HIMinimumBias7_XeXeRun2017_v1_304899_304907_useHFLUTfalse_v2.root
    /export/d00/scratch/jwang/L1PbPb/crab_L1_20180605_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV_2018.root
    /export/d00/scratch/jwang/L1PbPb/crab_L1_20180629_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV_2018_Aaron_forcecali1.root
)
OUTPUT=(
    output_PbPbMC 
    output_PbPbMC_useHFLUTfalse
    output_XeXe
    output_PbPb_useHFLUTfalse
    output_XeXe_useHFLUTfalse
    output_PbPbMC_AaronDriver
    output_PbPbMC_AaronDriver_forcecali1
)
fEvC=(
    "std::vector<float> fEvCparam = {8183.03, -286.132, 4.17883, -0.0316286, 0.000122998, -1.9495e-07};"
    "std::vector<float> fEvCparam = {17569, -347.973, 2.16314, -0.00138932, -2.97425e-05, 7.56601e-08};"
    "std::vector<float> fEvCparam = {3563.72, -122.236, 1.76168, -0.013251, 5.15708e-05, -8.22939e-08};"
    "std::vector<float> fEvCparam = {53215.4, -1036.32, 9.21008, -0.0541518, 0.000211088, -3.75259e-07};"
    "std::vector<float> fEvCparam = {10877.3, -218.55, 1.46868, -0.00256726, -9.02296e-06, 2.80831e-08};"
    "std::vector<float> fEvCparam = {9647.25, -213.836, 1.27742, 0.00355141, -5.92461e-05, 1.54104e-07};"
    "std::vector<float> fEvCparam = {7744.98, -167.817, 1.02607, 0.00164067, -3.59596e-05, 9.24097e-08};"
)
COLLSYST=(
    "PbPbMC 5.02" 
    "PbPbMC 5.02"
    "XeXe 5.44"
    "PbPb 5.02"
    "XeXe 5.44"
    "PbPbMC 5.02" 
    "PbPbMC 5.02" 
)

DO_CALI=${1:-0}
DO_FIT=${2:-0}
DO_PLOT=${3:-0}

mkdir -p plotcent rootfiles

for i in ${INDEX[@]}
do
    echo 
    echo -e "Processing \033[1;33m${OUTPUT[i]}\033[0m"
    echo
    sed -i "s/std::vector<float> fEvCparam.*/${fEvC[i]}/g" centralityCalibration.C
    g++ centralityCalibration.C $(root-config --libs --cflags) -g -o centralityCalibration.exe
    set -x
    [[ $DO_CALI -eq 1 ]] && ./centralityCalibration.exe ${INPUT_FOREST[i]} ${INPUT_L1[i]} ${OUTPUT[i]}
    set +x
    rm centralityCalibration.exe 
    sed -i 's/std::vector<float> fEvCparam.*/std::vector<float> fEvCparam = {16166.1, -275.793, 0.796373, 0.0107866, -8.15243e-05, 1.60609e-07};/g' centralityCalibration.C

    g++ plotCentrality.C $(root-config --libs --cflags) -g -o plotCentrality.exe
    set -x
    [[ $DO_FIT -eq 1 ]] && ./plotCentrality.exe ${OUTPUT[i]} ${COLLSYST[i]}
    set +x
    rm plotCentrality.exe 

    g++ plotCentTurnon.C $(root-config --libs --cflags) -g -o plotCentTurnon.exe
    set -x
    [[ $DO_PLOT -eq 1 ]] && ./plotCentTurnon.exe ${OUTPUT[i]} ${COLLSYST[i]}
    set +x
    rm plotCentTurnon.exe 
done

[[ -f output*.root ]] && mv output*.root rootfiles/