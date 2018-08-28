#include "adcVstowerE.h"
#define MAXTRACKS 60000
#define MAXVTX 100

void adcVstowerE(TString inputname, TString outputname, int nevt = -1)
{
  TFile* inf = new TFile(inputname.Data());
  TTree* l1Adc = (TTree*)inf->Get("HFAdcana/adc");
  TTree* hiroot = (TTree*)inf->Get("hiEvtAnalyzer/HiTree");
  TTree* trktree = (TTree*)inf->Get("ppTrack/trackTree");

  //
  std::vector<int>* ampl = 0; l1Adc->SetBranchAddress("ampl", &ampl);
  std::vector<int>* ieta = 0; l1Adc->SetBranchAddress("ieta", &ieta);
  std::vector<int>* iphi = 0; l1Adc->SetBranchAddress("iphi", &iphi);
  std::vector<int>* depth = 0; l1Adc->SetBranchAddress("depth", &depth);

  int ntower; hiroot->SetBranchAddress("ntower", &ntower);
  float towerEmax; hiroot->SetBranchAddress("towerEmax", &towerEmax);
  std::vector<float>* towerE = 0; hiroot->SetBranchAddress("towerE", &towerE);
  std::vector<int>* towerieta = 0; hiroot->SetBranchAddress("towerieta", &towerieta);
  std::vector<int>* toweriphi = 0; hiroot->SetBranchAddress("toweriphi", &toweriphi);

  int nTrk; trktree->SetBranchAddress("nTrk", &nTrk);
  bool highPurity[MAXTRACKS]; trktree->SetBranchAddress("highPurity", highPurity);
  float trkEta[MAXTRACKS]; trktree->SetBranchAddress("trkEta", trkEta);
  float trkPtError[MAXTRACKS]; trktree->SetBranchAddress("trkPtError", trkPtError);
  float trkPt[MAXTRACKS]; trktree->SetBranchAddress("trkPt", trkPt);
  float trkDz1[MAXTRACKS]; trktree->SetBranchAddress("trkDz1", trkDz1);
  float trkDzError1[MAXTRACKS]; trktree->SetBranchAddress("trkDzError1", trkDzError1);
  float trkDxy1[MAXTRACKS]; trktree->SetBranchAddress("trkDxy1", trkDxy1);
  float trkDxyError1[MAXTRACKS]; trktree->SetBranchAddress("trkDxyError1", trkDxyError1);
  float trkChi2[MAXTRACKS]; trktree->SetBranchAddress("trkChi2", trkChi2);
  unsigned char trkNdof[MAXTRACKS]; trktree->SetBranchAddress("trkNdof", trkNdof);
  unsigned char trkNHit[MAXTRACKS]; trktree->SetBranchAddress("trkNHit", trkNHit);
  unsigned char trkNlayer[MAXTRACKS]; trktree->SetBranchAddress("trkNlayer", trkNlayer);
  unsigned char trkAlgo[MAXTRACKS]; trktree->SetBranchAddress("trkAlgo", trkAlgo);
  
  //
  TH1F* hEff = new TH1F("hEff", ";HF threshold (ADC);Efficiency", 40, 0, 40); hEff->Sumw2();
  TH1F* hEffsumls = new TH1F("hEffsumls", ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffsumls->Sumw2();
  TH1F* hEffden = new TH1F("hEffden", ";HF threshold (ADC);", 40, 0, 40); hEffden->Sumw2();
  TH1F* hEffEvtsel = new TH1F("hEffEvtsel", ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffEvtsel->Sumw2();
  TH1F* hEffEvtselsumls = new TH1F("hEffEvtselsumls", ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffEvtselsumls->Sumw2();
  TH1F* hEffEvtselden = new TH1F("hEffEvtselden", ";HF threshold (ADC);", 40, 0, 40); hEffEvtselden->Sumw2();
  TH2F* hcorrmaxAdc_maxAdcsum = new TH2F("hcorrmaxAdc_maxAdcsum", ";max{{long}, {short}};max{#Sigmalong, #Sigmashort}", 40, 0, 40, 40, 0, 40);
  TH2F* hcorrTowerADC_E = new TH2F("hcorrTowerADC_E", ";HF tower E;ADC", 100, 0, 10, 50, 0, 50);
  TH2F* hcorrTowerADC_Emax = new TH2F("hcorrTowerADC_Emax", ";leading HF tower E;ADC", 100, 0, 10, 50, 0, 50);
  TH1F* hEtlead[nFGthre];
  TH1F* hEtleadsum[nFGthre];
  for(int k=0;k<nFGthre;k++) 
    { 
      hEtlead[k] = new TH1F(Form("hEtlead%d",k), ";HF leading tower E_{max} (GeV);", 200, 1, 101); 
      hEtleadsum[k] = new TH1F(Form("hEtleadsum%d",k), ";HF tower E (GeV);", 200, 1, 101); 
    }
  TH1F* htowerE = new TH1F("htowerE", ";HF tower energy (GeV);", 200, 0, 200);
  TH1F* hAdc = new TH1F("hAdc", ";ADC;", 50, 0, 50);
  TH1F* hAdcmax = new TH1F("hAdcmax", ";max ADC;", 50, 0, 50);
  TH1F* hAdctower = new TH1F("hAdctower", ";ADC / tower;", 50, 0, 50);

  int nentries = nevt>0&&nevt<l1Adc->GetEntries()?nevt:l1Adc->GetEntries();
  for(int i=0;i<nentries;i++)
    {
      if(i%10000==0) { xjjc::progressbar(i, nentries); }
      l1Adc->GetEntry(i);
      hiroot->GetEntry(i);
      trktree->GetEntry(i);

      int nampl = ampl->size();
      const int NBIN_IETA = 101, NBIN_IPHI = 80; 
      std::vector<int> ampltower(NBIN_IETA*100 + NBIN_IPHI, 0);
      std::vector<int> nampltower(NBIN_IETA*100 + NBIN_IPHI, 0);
      std::vector<int> nampllong(NBIN_IETA*100 + NBIN_IPHI, 0);
      std::vector<int> namplshort(NBIN_IETA*100 + NBIN_IPHI, 0);
      std::vector<int> ampllong(NBIN_IETA*100 + NBIN_IPHI, 0);
      std::vector<int> amplshort(NBIN_IETA*100 + NBIN_IPHI, 0);
      int amplmax = 0, namplcell = 0;
      for(int l=0;l<nampl;l++)
        {
          if(TMath::Abs((*ieta)[l]) < 29) { /*std::cout<<"warning: hAdcVsGeV saves units not HF: ieta = "<<(*ieta)[l]<<std::endl;*/ continue; }
          if(i%1000==0) { hAdc->Fill((*ampl)[l]); }
          if((*ampl)[l] > amplmax) { amplmax = (*ampl)[l]; } //
          int index = ((*ieta)[l]+50) * 100 + (*iphi)[l];
          if(nampltower[index]==0) { namplcell++; }
          ampltower[index] += (*ampl)[l];
          nampltower[index] += 1;
          if((*depth)[l]==1 || (*depth)[l]==3) { ampllong[index] += (*ampl)[l]; nampllong[index] += 1; }
          if((*depth)[l]==2 || (*depth)[l]==4) { amplshort[index] += (*ampl)[l]; namplshort[index] += 1; }
        }
      hAdcmax->Fill(amplmax);
      int amplsummax_long = 0, amplsummax_short = 0;
      for(int index=0; index<NBIN_IETA*100 + NBIN_IPHI; index++)
        {
          if(nampllong[index]==1 || namplshort[index]==1) { std::cout<<"warning: only one depth for short/long"<<std::endl; continue; }
          if(ampllong[index] > amplsummax_long) { amplsummax_long = ampllong[index]; }
          if(amplshort[index] > amplsummax_short) { amplsummax_short = amplshort[index]; }
        }
      int amplsummax = amplsummax_long>amplsummax_short?amplsummax_long:amplsummax_short;
      hcorrmaxAdc_maxAdcsum->Fill(amplmax, amplsummax);
      bool singletrackfilter = false;
      for(int t=0;t<nTrk;t++)
        {
          if(highPurity[t] && TMath::Abs(trkPtError[t]/trkPt[t]) < 0.1 && 
             TMath::Abs(trkDz1[t]/trkDzError1[t]) < 3 && TMath::Abs(trkDxy1[t]/trkDxyError1[t]) < 3 && 
             TMath::Abs(trkEta[t]) < 2.4 && trkPt[t] > 0.4) { singletrackfilter = true; break; }
        }
      for(int j=0;j<40;j++)
        {
          hEffden->Fill(j, 1);
          if(amplmax > j) { hEff->Fill(j, 1); }
          if(amplsummax > j) { hEffsumls->Fill(j, 1); }
          if(!singletrackfilter) { continue; }
          hEffEvtselden->Fill(j, 1);
          if(amplmax > j) { hEffEvtsel->Fill(j, 1); }
          if(amplsummax > j) { hEffEvtselsumls->Fill(j, 1); }          
        }
      for(auto& iampltower : ampltower) 
        { 
          hAdctower->Fill(iampltower, 1./namplcell); 
        }
      // std::sort(ampltower.begin(), ampltower.end(), xjjc::sortbydes<int>);
      for(int k=0;k<nFGthre;k++) 
        { 
          if(amplmax > FGthre[k]) { hEtlead[k]->Fill(towerEmax); }
          if(amplsummax > FGthre[k]) { hEtleadsum[k]->Fill(towerEmax); }
        }
      float towermax = 0;
      int thisamplmax = 0;
      for(int j=0;j<ntower;j++) 
        { 
          htowerE->Fill((*towerE)[j]); 
          int index = ((*towerieta)[j]+50) * 100 + (*toweriphi)[j];
          int thisampl = ampltower[index];
          int nthisampl = nampltower[index];
          hcorrTowerADC_E->Fill((*towerE)[j], thisampl);
          if((*towerE)[j] > towermax) { towermax = (*towerE)[j]; thisamplmax = thisampl; }
        }
      hcorrTowerADC_Emax->Fill(towermax, thisamplmax);
    }
  xjjc::progressbar_summary(nentries);

  hEff->Divide(hEffden);
  hEffsumls->Divide(hEffden);
  hEffEvtsel->Divide(hEffEvtselden);
  hEffEvtselsumls->Divide(hEffEvtselden);

  TFile* output = new TFile(Form("%s.root", outputname.Data()), "recreate");
  hEff->Write();
  hEffsumls->Write();
  hEffEvtsel->Write();
  hEffEvtselsumls->Write();
  hcorrmaxAdc_maxAdcsum->Write();
  hAdc->Write();
  hAdcmax->Write();
  hAdctower->Write();
  htowerE->Write();
  for(int k=0;k<nFGthre;k++) 
    { 
      hEtlead[k]->Write(); 
      hEtleadsum[k]->Write(); 
    }
  hcorrTowerADC_E->Write();
  hcorrTowerADC_Emax->Write();
  output->Close();

}

int main(int argc, char* argv[])
{
  if(argc==3) { adcVstowerE(argv[1], argv[2]); return 0;}
  if(argc==4) { adcVstowerE(argv[1], argv[2], atoi(argv[3])); return 0;}
  return 1;
}

