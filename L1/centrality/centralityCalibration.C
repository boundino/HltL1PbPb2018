#include "centrality.h"

Float_t variation = 0.02;
std::vector<float> fEvCparam = {16166.1, -275.793, 0.796373, 0.0107866, -8.15243e-05, 1.60609e-07};
void centralityCalibration(TString inHiForestFileName = "/export/d00/scratch/jwang/L1PbPb/HiForestAOD_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV_2018.root",
                           TString inL1FileName = "/export/d00/scratch/jwang/L1PbPb/crab_L1_20180423_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV_2018.root",
                           TString outFileName = "output", bool montecarlo = false)
{
  TF1* fEvC = new TF1("fEvC","pol5", 0, 200);
  for(int p=0;p<6;p++) fEvC->SetParameter(p, fEvCparam[p]);

  Bool_t useHFLUTfalse = outFileName.Contains("useHFLUTfalse");
  if(useHFLUTfalse) maxL1etsum = 18000;
  if(outFileName=="output_PbPb_useHFLUTfalse") maxL1etsum = 50000;
  nL1etsum = maxL1etsum / 100;

  TFile* inHiForestFile = TFile::Open(inHiForestFileName);
  TTree* fEvtTree = (TTree*)inHiForestFile->Get("hiEvtAnalyzer/HiTree");
  TFile* inL1File = TFile::Open(inL1FileName);
  TTree* l1EvtTree = (TTree*)inL1File->Get("l1EventTree/L1EventTree");
  TTree* l1Tree = (TTree*)inL1File->Get("l1CaloTowerEmuTree/L1CaloTowerTree");

  TH1F* hPassofflineCent[nlimit];
  std::vector<Float_t> etsumlimitLow(nlimit);
  std::vector<Float_t> etsumlimitHigh(nlimit);
  for(int l=0;l<nlimit;l++) 
    {
      hPassofflineCent[l] = new TH1F(Form("hPassofflineCent_%d",l), ";offline centrality;", nBins, minCent, maxCent);
      etsumlimitLow[l] = fEvC->Eval(limitsLow[l] * (1-variation));
      etsumlimitHigh[l] = fEvC->Eval(limitsHigh[l] * (1+variation));
      if(limitsLow[l]==0) etsumlimitLow[l] = 1.e+6;
      if(limitsHigh[l]>175) etsumlimitHigh[l] = 0.;
      std::cout<<etsumlimitLow[l]<<" "<<etsumlimitHigh[l]<<std::endl;
    }
  std::cout<<std::endl;

  ULong64_t f_evt;
  UInt_t f_run;
  UInt_t f_lumi;
  Int_t hiBin;
  float hiHF;

  fEvtTree->SetBranchStatus("*", 0);
  fEvtTree->SetBranchStatus("evt", 1);
  fEvtTree->SetBranchStatus("run", 1);
  fEvtTree->SetBranchStatus("lumi", 1);
  fEvtTree->SetBranchStatus("hiBin", 1);
  fEvtTree->SetBranchStatus("hiHF", 1);
  fEvtTree->SetBranchAddress("evt", &f_evt);
  fEvtTree->SetBranchAddress("run", &f_run);
  fEvtTree->SetBranchAddress("lumi", &f_lumi);
  fEvtTree->SetBranchAddress("hiBin", &hiBin);
  fEvtTree->SetBranchAddress("hiHF", &hiHF);

  L1Analysis::L1AnalysisEventDataFormat *Event = new L1Analysis::L1AnalysisEventDataFormat();
  L1Analysis::L1AnalysisL1CaloTowerDataFormat *L1CaloTower = new L1Analysis::L1AnalysisL1CaloTowerDataFormat();

  l1EvtTree->SetBranchAddress("Event", &Event);
  l1Tree->SetBranchAddress("L1CaloTower", &L1CaloTower);

  TH2D* hcorrl1EtsumPlusVscorrl1EtsumMinus = new TH2D("hcorrl1EtsumPlusVscorrl1EtsumMinus", "L1 EtsumPlus vs L1 EtsumMinus; L1 EtsumMinus ; L1 EtsumPlus", 100, 0, maxL1etsum/2, 100, 0, maxL1etsum/2); 
  TH2D* hcorrl1EtsumVsofflineCent = new TH2D("hcorrl1EtsumVsofflineCent", "L1 Etsum vs offline centrality; offline centrality ; L1 Etsum", nBins, minCent, maxCent, nL1etsum, 0, maxL1etsum);
  TH2D* hcorrofflineCentVsl1Etsum = new TH2D("hcorrofflineCentVsl1Etsum", "Offline centrality vs L1 Etsum; L1 Etsum ; offline centrality", nL1etsum, 0, maxL1etsum, nBins, minCent, maxCent);  
  TH2D* hcorrL1CentVsofflineCent = new TH2D("hcorrL1CentVsofflineCent", "Online centrality vs offline centrality; L1 Etsum ; offline centrality", nBins, minCent, maxCent, nBins, minCent, maxCent);  
  TH1D* hofflineCent = new TH1D("hofflineCent", "Offline cent; Offline centrality; Entries", nBins, minCent, maxCent);
  TH1D* hl1Etsum = new TH1D("hl1Etsum", "L1 Etsum ; L1 Etsum; Entries ", nL1etsum, 0, maxL1etsum);
  TH1D* hofflineEtsum = new TH1D("hofflineEtsum", "Offline Etsum ; Offline Etsum; Entries ", nOfflineetsum, 0, maxOfflineetsum);
  TH2D* hcorrOfflineEtsumVsL1Etsum = new TH2D("hcorrOfflineEtsumVsL1Etsum", "Offline Etsum vs L1 Etsum; Offline Etsum; L1 Etsum", nOfflineetsum, 0, maxOfflineetsum, nL1etsum, 0, maxL1etsum);
  TProfile* profilel1EtsumVsofflineCent_Calibration = new TProfile("profilel1EtsumVsofflineCent_Calibration", "L1 Etsum vs Offline centrality; offline centrality ; L1 Etsum", nBins, minCent, maxCent, 0, maxL1etsum);
  TProfile* profilesofflineCentVl1Etsum_Calibration = new TProfile("profileofflineCentVsl1Etsum_Calibration", "Offline centrality vs L1 Etsum; L1 Etsum ; offline centrality", nL1etsum, 0, maxL1etsum, minCent, maxCent);

  int countCalib = 0;
  Long64_t nentries = 10000;
  Long64_t nl1entries = l1EvtTree->GetEntries();
  Long64_t entries = (nentries<nl1entries&&nentries>0)?nentries:nl1entries;
  Long64_t nfentries = fEvtTree->GetEntries();

  std::vector<int>* vl1Cent = new std::vector<int>;

  for(Long64_t j = 0; j<entries; j++)
    {
      if(j % 1000 == 0) std::cout<<j<<" / "<<entries<<"\r"<<std::flush;

      l1EvtTree->GetEntry(j);
      // std::cout<<Event->event<<" "<<Event->lumi<<" "<<Event->run<<std::endl;

      Long64_t k = 0;
      for(; k < nfentries; k++)
        {
          fEvtTree->GetEntry(k);
          if(f_evt==Event->event && f_lumi==Event->lumi && f_run==Event->run)
            break;
        }
      if(k>=nfentries) continue;

      l1Tree->GetEntry(j);
      int etsum = 0;
      int l1_etsumPlus = 0;
      int l1_etsumMinus = 0;

      for (int i=0;i<L1CaloTower->nTower;i++)
        {
          if (L1CaloTower->ieta[i] > 29) l1_etsumPlus += L1CaloTower->iet[i];   
          if (L1CaloTower->ieta[i] < -29) l1_etsumMinus += L1CaloTower->iet[i];   
        }
      etsum = l1_etsumPlus + l1_etsumMinus;

      Float_t f_hiBin = hiBin;

      hcorrl1EtsumPlusVscorrl1EtsumMinus->Fill(l1_etsumMinus, l1_etsumPlus);
      hcorrl1EtsumVsofflineCent->Fill(f_hiBin, etsum);
      hcorrofflineCentVsl1Etsum->Fill(etsum, f_hiBin);
      hofflineCent->Fill(f_hiBin);
      hl1Etsum->Fill(etsum);
      hofflineEtsum->Fill(hiHF);
      hcorrOfflineEtsumVsL1Etsum->Fill(hiHF, etsum); 
      profilel1EtsumVsofflineCent_Calibration->Fill(f_hiBin, etsum);
      profilesofflineCentVl1Etsum_Calibration->Fill(etsum, f_hiBin);

      // int l = 0;
      for(int l=0;l<nlimit;l++)
        {
          if(etsum < etsumlimitLow[l] && etsum >= etsumlimitHigh[l])
            {
              hPassofflineCent[l]->Fill(f_hiBin);
              // break;
            }
        }
      // std::cout<<etsum<<" "<<l<<std::endl;
      // if(l==nlimit) { std::cout<<" error: invalid limits"<<std::endl; return;}

      countCalib++;
    }
  std::cout<<std::endl;
  std::cout<<"countCalib = "<<countCalib<<std::endl;

  TFile *outFile = new TFile(Form("%s.root",outFileName.Data()), "RECREATE");
  outFile->cd();
  hcorrl1EtsumPlusVscorrl1EtsumMinus->Write();
  hcorrl1EtsumVsofflineCent->Write();
  hcorrofflineCentVsl1Etsum->Write();
  hofflineCent->Write();
  hcorrOfflineEtsumVsL1Etsum->Write();
  hcorrL1CentVsofflineCent->Write();
  profilel1EtsumVsofflineCent_Calibration->Write();
  profilesofflineCentVl1Etsum_Calibration->Write();
  hl1Etsum->Write();
  hofflineEtsum->Write();
  for(int l=0;l<nlimit;l++)
    {
      hPassofflineCent[l]->Write();
    }
  outFile->Close();
} 

int main(int argc, char **argv)
{
  if(argc == 1)
    {
      centralityCalibration();
      return 0;
    }
  if(argc == 4)
    {
      centralityCalibration(argv[1], argv[2], argv[3]);
      return 0;
    }
  std::cout << "Usage: \nmakeTurnOn_fromSameFile.exe <input_HiForest_file> <output_file>" << std::endl;
  return 1;
}
