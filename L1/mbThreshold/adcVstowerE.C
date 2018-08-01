#include "adcVstowerE.h"

void adcVstowerE(TString inputname, TString outputname)
{
  TFile* inf = new TFile(inputname.Data());
  TTree* l1Adc = (TTree*)inf->Get("MBefficiency/adc");
  TTree* hiroot = (TTree*)inf->Get("hiEvtAnalyzer/HiTree");

  int nampl; l1Adc->SetBranchAddress("nampl", &nampl);
  int ampl[4000]; l1Adc->SetBranchAddress("ampl", ampl);
  int ieta[4000]; l1Adc->SetBranchAddress("ieta", ieta);

  int ntower; hiroot->SetBranchAddress("ntower", &ntower);
  float towerEmax; hiroot->SetBranchAddress("towerEmax", &towerEmax);
  std::vector<float>* towerE = 0; hiroot->SetBranchAddress("towerE", &towerE);

  TH1F* hEtlead[nFGthre];
  for(int k=0;k<nFGthre;k++) { hEtlead[k] = new TH1F(Form("hEtlead%d",k), ";HF tower E_{max} (GeV);", 200, 1, 101); }
  TH1F* htowerE = new TH1F("htowerE", ";HF tower energy (GeV);", 200, 0, 200);
  TH1F* hAdc = new TH1F("hAdc", ";ADC;", 50, 0, 50);
  TH1F* hAdclead = new TH1F("hAdclead", ";max ADC;", 50, 0, 50);

  // int nentries = 1000;
  int nentries = l1Adc->GetEntries();
  for(int i=0;i<nentries;i++)
    {
      if(i%10000==0) { std::cout<<std::setiosflags(std::ios::left)<<std::setw(12)<<i<<" / "<<nentries<<"\r"<<std::flush; }
      l1Adc->GetEntry(i);
      hiroot->GetEntry(i);

      for(int j=0;j<ntower;j++) { htowerE->Fill((*towerE)[j]); }
      int ampllead = 0;
      for(int l=0;l<nampl;l++)
        {
          if(i%1000==0) hAdc->Fill(ampl[l]);
          if(ampl[l] > ampllead) { ampllead = ampl[l]; }
        }
      hAdclead->Fill(ampllead);
      for(int k=0;k<nFGthre;k++) 
        { if(ampllead >= FGthre[k]) { hEtlead[k]->Fill(towerEmax); } }

    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<nentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<std::endl;
  TFile* output = new TFile(Form("%s.root", outputname.Data()), "recreate");
  hAdc->Write();
  hAdclead->Write();
  htowerE->Write();
  for(int k=0;k<nFGthre;k++) { hEtlead[k]->Write(); }
  output->Close();

}

int main(int argc, char* argv[])
{
  if(argc==3) { adcVstowerE(argv[1], argv[2]); return 0;}
  return 1;
}

