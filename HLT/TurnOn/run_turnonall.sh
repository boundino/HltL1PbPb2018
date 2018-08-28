#!/bin/bash

CASES=(5)

##

OUTPUTNAME=(
    "D0_v17iter0-3_HLT_ph100"
    "D0_v17improve_HLT_ph100"
    "Ds_v17improve_HLT_ph100"
    "D0_v17V49pv_HLT_ph100"
    "Ds_v17V49pv_HLT_ph100"
    "trk_v17V49pv_HLT_D0ph100"
)
INPUTFILE=(
    "/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180815_D0_Pythia8_prompt_Pthat100_Cymbal5Ev8_2018_iter0to3_Dpt4tk2p5dls2_v2.root"
    "/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180821_V17spl4_20180815_D0_Pythia8_prompt_Pthat100_Cymbal5Ev8_Dpt4tk2p5dls2.root"
    "/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180821_V17spl1_20180814_Ds_Prompt_phikkpi_ph100_Pythia_Dpt4tk2p5dls2.root"
    "/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180827_V17V49pv4c_20180814_D0_Pythia8_prompt_Pthat100_Cymbal5Ev8_Dpt4tk2p5dls2.root"
    "/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180827_V17V49pv4c_20180814_Ds_Prompt_phikkpi_ph100_Pythia_Dpt4tk2p5dls2.root"
    "/export/d00/scratch/jwang/HltPbPb2018MC/Matched_20180827_V17V49pv4c_20180814_D0_Pythia8_prompt_Pthat100_Cymbal5Ev8_HiForestAODtrkPt2.root"
)
WEIGHT=(
    "1"
    "1"
    "1"
    "1"
    "1"
    "1"
)
XTITLE=(
    "leading D^{0} p_{T} (GeV/c)"
    "leading D^{0} p_{T} (GeV/c)"
    "leading D_{s} p_{T} (GeV/c)"
    "leading D^{0} p_{T} (GeV/c)"
    "leading D_{s} p_{T} (GeV/c)"
    "leading trk p_{T} (GeV/c)"
)
TREENAME=(
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
    "Dfinder/ntDPhikkpi"
    "Dfinder/ntDkpi"
    "Dfinder/ntDPhikkpi"
    "ppTrack/trackTree"
)
SELECTIONS=(
    "Dmass>1.7&&Dmass<2.0&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.20&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>6&&TMath::Abs(Dtrk1Eta)<1.5&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.3&&Dtrk2highPurity&&Dtrk2Pt>6&&TMath::Abs(Dtrk2Eta)<1.5&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.3&&Dalpha<0.2"
    "Dmass>1.7&&Dmass<2.0&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.20&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>6&&TMath::Abs(Dtrk1Eta)<1.5&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.3&&Dtrk2highPurity&&Dtrk2Pt>6&&TMath::Abs(Dtrk2Eta)<1.5&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.3&&Dalpha<0.2"
    "Dmass>1.91&&Dmass<2.11&&TMath::Abs(DtktkResmass-1.01945)<0.01&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.20&&Dtrk1highPurity&&Dtrk1Pt>6&&TMath::Abs(Dtrk1Eta)<1.5&&DRestrk1highPurity&&DRestrk1Pt>6&&TMath::Abs(DRestrk1Eta)<1.5&&DRestrk2highPurity&&DRestrk2Pt>6&&TMath::Abs(DRestrk2Eta)<1.5&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.3&&TMath::Abs(DRestrk1PtErr/DRestrk1Pt)<0.3&&TMath::Abs(DRestrk2PtErr/DRestrk2Pt)<0.3&&Dalpha<0.2"
    "Dmass>1.7&&Dmass<2.0&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.20&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>6&&TMath::Abs(Dtrk1Eta)<1.5&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.3&&Dtrk2highPurity&&Dtrk2Pt>6&&TMath::Abs(Dtrk2Eta)<1.5&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.3&&Dalpha<0.2"
    "Dmass>1.91&&Dmass<2.11&&TMath::Abs(DtktkResmass-1.01945)<0.01&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.20&&Dtrk1highPurity&&Dtrk1Pt>6&&TMath::Abs(Dtrk1Eta)<1.5&&DRestrk1highPurity&&DRestrk1Pt>6&&TMath::Abs(DRestrk1Eta)<1.5&&DRestrk2highPurity&&DRestrk2Pt>6&&TMath::Abs(DRestrk2Eta)<1.5&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.3&&TMath::Abs(DRestrk1PtErr/DRestrk1Pt)<0.3&&TMath::Abs(DRestrk2PtErr/DRestrk2Pt)<0.3&&Dalpha<0.2"
    "highPurity&&TMath::Abs(trkEta)<1.&&trkAlgo!=11&&TMath::Abs(trkPtError/trkPt)<0.1&&TMath::Abs(trkDz1/trkDzError1)<3&&TMath::Abs(trkDxy1/trkDxyError1)<3&&trkNHit>=11&&((trkChi2/trkNdof)/trkNlayer)<0.15"
)
BRANCHNAME=(
    "Max"'$'"(Dpt*(${SELECTIONS[0]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[1]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[2]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[3]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[4]}))"
    "Max"'$'"(trkPt*(${SELECTIONS[5]}))"
)

PATHS=(
    "HLT_HIDmesonPPTrackingGlobal_Dpt15_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt20_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt30_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt40_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt50_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt60_v1 HLT_ZeroBias_v6"
    "HLT_HIDmesonPPTrackingGlobal_Dpt15_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt20_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt30_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt40_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt50_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt60_v1 HLT_ZeroBias_v6"
    "HLT_HIDsPPTrackingGlobal_Dpt15_v1 HLT_ZeroBias_v6 HLT_HIDsPPTrackingGlobal_Dpt20_v1 HLT_ZeroBias_v6 HLT_HIDsPPTrackingGlobal_Dpt30_v1 HLT_ZeroBias_v6 HLT_HIDsPPTrackingGlobal_Dpt40_v1 HLT_ZeroBias_v6 HLT_HIDsPPTrackingGlobal_Dpt50_v1 HLT_ZeroBias_v6 HLT_HIDsPPTrackingGlobal_Dpt60_v1 HLT_ZeroBias_v6"
    "HLT_HIDmesonPPTrackingGlobal_Dpt15_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt20_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt30_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt40_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt50_v1 HLT_ZeroBias_v6 HLT_HIDmesonPPTrackingGlobal_Dpt60_v1 HLT_ZeroBias_v6"
    "HLT_HIDsPPTrackingGlobal_Dpt15_v1 HLT_ZeroBias_v6 HLT_HIDsPPTrackingGlobal_Dpt20_v1 HLT_ZeroBias_v6 HLT_HIDsPPTrackingGlobal_Dpt30_v1 HLT_ZeroBias_v6 HLT_HIDsPPTrackingGlobal_Dpt40_v1 HLT_ZeroBias_v6 HLT_HIDsPPTrackingGlobal_Dpt50_v1 HLT_ZeroBias_v6 HLT_HIDsPPTrackingGlobal_Dpt60_v1 HLT_ZeroBias_v6"
    "HLT_HIFullTracks2018_HighPt8_v1 HLT_ZeroBias_v6 HLT_HIFullTracks2018_HighPt18_v1 HLT_ZeroBias_v6 HLT_HIFullTracks2018_HighPt24_v1 HLT_ZeroBias_v6 HLT_HIFullTracks2018_HighPt34_v1 HLT_ZeroBias_v6 HLT_HIFullTracks2018_HighPt45_v1 HLT_ZeroBias_v6"
)

BINNING=(
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={0, 2, 4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
)

mkdir -p plots

##
for i in ${CASES[@]}
do
    sed '1i'"${BINNING[i]}" turnonall.C > turnonall_tmp.C
    g++ turnonall_tmp.C $(root-config --cflags --libs) -g -o turnonall_tmp.exe
    set -x
    ./turnonall_tmp.exe "${INPUTFILE[i]}" "${OUTPUTNAME[i]}_${WEIGHT[i]}" "${TREENAME[i]}" "${BRANCHNAME[i]}" "${XTITLE[i]}" "${WEIGHT[i]}" "${SELECTIONS[i]}" ${PATHS[i]}
    set +x
    rm turnonall_tmp.exe
    rm turnonall_tmp.C
done


# PATHS=(
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "L1_SingleJet8_Final 1 L1_SingleJet16_Final 1 L1_SingleJet24_Final 1 L1_SingleJet32_Final 1 L1_SingleJet44_Final 1 L1_SingleJet60_Final 1"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_copy_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_copy_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_copy_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
#     "HLT_HIDmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_Final HLT_HIDmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_HIDmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_HIDmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final HLT_HIDmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final HLT_HIDmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
# )

