#include "adcVstowerE.h"

void adcVstowerE(TString inputname, TString outputname, int nevt = -1)
{
  TFile* inf = new TFile(inputname.Data());
  TTree* l1Adc = (TTree*)inf->Get("MBefficiency/adc");
  TTree* hiroot = (TTree*)inf->Get("hiEvtAnalyzer/HiTree");

  //
  int nampl; l1Adc->SetBranchAddress("nampl", &nampl);
  int ampl[4000]; l1Adc->SetBranchAddress("ampl", ampl);
  int ieta[4000]; l1Adc->SetBranchAddress("ieta", ieta);
  int iphi[4000]; l1Adc->SetBranchAddress("iphi", iphi);
  int depth[4000]; l1Adc->SetBranchAddress("depth", depth);

  int ntower; hiroot->SetBranchAddress("ntower", &ntower);
  float towerEmax; hiroot->SetBranchAddress("towerEmax", &towerEmax);
  std::vector<float>* towerE = 0; hiroot->SetBranchAddress("towerE", &towerE);
  std::vector<int>* towerieta = 0; hiroot->SetBranchAddress("towerieta", &towerieta);
  std::vector<int>* toweriphi = 0; hiroot->SetBranchAddress("toweriphi", &toweriphi);

  //
  TH2F* hcorrTowerADC_E = new TH2F("hcorrTowerADC_E", ";HF tower E;ADC", 100, 0, 10, 50, 0, 50);
  TH2F* hcorrTowerADC_Emax = new TH2F("hcorrTowerADC_Emax", ";leading HF tower E;ADC", 100, 0, 10, 50, 0, 50);
  TH1F* hEtlead[nFGthre];
  TH1F* hEt[nFGthre];
  TH1F* hEtlead_ADCtower[nFGthre];
  for(int k=0;k<nFGthre;k++) 
    { 
      hEtlead[k] = new TH1F(Form("hEtlead%d",k), ";HF leading tower E_{max} (GeV);", 200, 1, 101); 
      hEt[k] = new TH1F(Form("hEt%d",k), ";HF tower E (GeV);", 200, 1, 101); 
      hEtlead_ADCtower[k] = new TH1F(Form("hEtlead_ADCtower%d",k), ";HF leading tower E_{max} (GeV);", 200, 1, 101); 
    }
  TH1F* htowerE = new TH1F("htowerE", ";HF tower energy (GeV);", 200, 0, 200);
  TH1F* hAdc = new TH1F("hAdc", ";ADC;", 50, 0, 50);
  TH1F* hAdcmax = new TH1F("hAdcmax", ";max ADC;", 50, 0, 50);
  TH1F* hAdctower = new TH1F("hAdctower", ";ADC / tower;", 50, 0, 50);
  TH1F* hAdcdepth[4]; for(int k=0;k<4;k++) { hAdcdepth[k] = new TH1F(Form("hAdcdepth%d",k+1), ";ADC;", 50, 0, 50); }
  // TH1F* hAdcdepth_del[4]; for(int k=0;k<4;k++) { hAdcdepth_del[k] = new TH1F(Form("hAdcdepth_del%d",k+1), ";ADC;", 50, 0, 50); }
  TH2F* hAdcmaxVsAdcmax_nodepth = new TH2F("hAdcmaxVsAdcmax_nodepth", ";max ADC;max ADC in depth=1&2", 50, 0, 50, 50, 0, 50);
  TH1F* hdebug = new TH1F("hdebug", ";ieta;", 85, -42, 42);

  int nentries = nevt>0&&nevt<l1Adc->GetEntries()?nevt:l1Adc->GetEntries();
  for(int i=0;i<nentries;i++)
    {
      if(i%10000==0) { std::cout<<std::setiosflags(std::ios::left)<<std::setw(12)<<i<<" / "<<nentries<<"\r"<<std::flush; }
      l1Adc->GetEntry(i);
      hiroot->GetEntry(i);

      const int NBIN_IETA = 101, NBIN_IPHI = 80; 
      std::vector<int> ampltower(NBIN_IETA*100 + NBIN_IPHI, 0);
      std::vector<int> nampltower(NBIN_IETA*100 + NBIN_IPHI, 0);
      int amplmax = 0, amplmax_nodepth = 0, amplsum = 0, namplcell = 0;
      for(int l=0;l<nampl;l++)
        {
          if(TMath::Abs(ieta[l]) < 29) continue;
          if(i%1000==0) { hAdc->Fill(ampl[l]); hAdcdepth[depth[l]-1]->Fill(ampl[l]); }
          if(ampl[l] > amplmax && depth[l]>0 && depth[l]<3) { amplmax = ampl[l]; } ///
          if(ampl[l] > amplmax_nodepth) { amplmax_nodepth = ampl[l]; } ///
          amplsum += ampl[l];
          int index = (ieta[l]+50) * 100 + iphi[l];
          if(nampltower[index]==0) { namplcell++; }
          ampltower[index] += ampl[l];
          nampltower[index] += 1;
          // if(depth[l]==1 || depth[l]==2) { if(ampl[l] > ampltower[index]) { ampltower[index] = ampl[l]; nampltower[index] = 1; } }
        }
      hAdcmax->Fill(amplmax);
      hAdcmaxVsAdcmax_nodepth->Fill(amplmax_nodepth,amplmax);
      int ampltowermin = -1;
      for(auto& iampltower : ampltower) 
        { 
          hAdctower->Fill(iampltower, 1./namplcell); 
          if(iampltower<ampltowermin || ampltowermin<0) { ampltowermin = iampltower; } 
        }
      // std::sort(ampltower.begin(), ampltower.end(), xjjc::sortbydes<int>);
      for(int k=0;k<nFGthre;k++) 
        { 
          // if(amplmax >= FGthre[k]) { hEtlead[k]->Fill(towerEmax); }  ///////
          if(amplmax_nodepth > FGthre[k]) { hEtlead[k]->Fill(towerEmax); }  ///////
          if(ampltowermin >= FGthre[k]) { hEtlead_ADCtower[k]->Fill(towerEmax); }
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
          for(int k=0;k<nFGthre;k++) { if(amplmax > FGthre[k]) { hEt[k]->Fill((*towerE)[j]); } }
          if((*towerE)[j] > 6 && thisampl < 16) { hdebug->Fill((*towerieta)[j]); /*std::cout<<"test--> ieta: "<<(*towerieta)[j]<<" iphi: "<<(*toweriphi)[j]<<" ncell: "<<nampltower[index]<<std::endl;*/ }
        }
      hcorrTowerADC_Emax->Fill(towermax, thisamplmax);
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<nentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<std::endl;
  TFile* output = new TFile(Form("%s.root", outputname.Data()), "recreate");
  hAdc->Write();
  hAdcmax->Write();
  hAdcmaxVsAdcmax_nodepth->Write();
  hAdctower->Write();
  for(int k=0;k<4;k++) { hAdcdepth[k]->Write(); }
  htowerE->Write();
  for(int k=0;k<nFGthre;k++) 
    { 
      hEtlead[k]->Write(); 
      hEt[k]->Write(); 
      hEtlead_ADCtower[k]->Write();
    }
  hcorrTowerADC_E->Write();
  hcorrTowerADC_Emax->Write();
  hdebug->Write();
  output->Close();

}

int main(int argc, char* argv[])
{
  if(argc==3) { adcVstowerE(argv[1], argv[2]); return 0;}
  if(argc==4) { adcVstowerE(argv[1], argv[2], atoi(argv[3])); return 0;}
  return 1;
}

