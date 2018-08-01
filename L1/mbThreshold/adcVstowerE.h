#include <iostream>
#include <iomanip>

#include <TString.h>
#include <TFile.h>
#include <TTree.h>
// #include "L1AnalysisL1CaloTowerDataFormat.h"
#include <TH1F.h>
#include <TMath.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <vector>

#include "xjjrootuti.h"


int FGthre[] = {10, 12, 15, 17};
const int nFGthre = sizeof(FGthre) / sizeof(FGthre[0]);

Color_t colorlist_light[] = {kRed-9, kOrange-4, kGreen-8, kAzure-9};
Color_t colorlist_middle[] = {kRed-3, kOrange-3, kGreen+2, kAzure-3};

