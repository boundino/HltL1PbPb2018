#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TProfile.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TString.h>
#include <TLegendEntry.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>
#include <TEfficiency.h>
#include <TColor.h>

#include "L1AnalysisEventDataFormat.h"
#include "L1AnalysisL1CaloTowerDataFormat.h"

#include "xjjrootuti.h"

#include <vector>
#include <iostream>

// int limitsLow[]={0, 10, 20, 60, 100, 140};
// int limitsHigh[]={10, 20, 60, 100, 140, 200};
int limitsLow[] = {0, 20, 60, 100, 140};
int limitsHigh[] = {200, 200, 200, 200, 200};
const int nlimit = sizeof(limitsLow)/sizeof(limitsLow[0]);
const int nBins = 100;
Float_t minCent = 0, maxCent = 200.;

Float_t maxL1etsum = 9000;
Int_t nL1etsum;
Float_t maxOfflineetsum = 4000;
Int_t nOfflineetsum = 4000/100;
Color_t ncolor[] = {kRed-7, kAzure-4, kOrange-4, kGreen-5, kBlue-6, kMagenta-8};
