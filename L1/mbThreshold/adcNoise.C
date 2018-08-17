#include "adcVstowerE.h"

void adcNoise(TString infZeroBias, TString infEmptyBX, TString outFileName)
{
  TFile* inZeroBias = TFile::Open(infZeroBias);
  TFile* inEmptyBX = TFile::Open(infEmptyBX);

  TTree* l1Adc_zb = (TTree*)inZeroBias->Get("MBefficiency/adc");
  int nampl_zb; l1Adc_zb->SetBranchAddress("nampl", &nampl_zb);
  int ampl_zb[4000]; l1Adc_zb->SetBranchAddress("ampl", ampl_zb);
  int ieta_zb[4000]; l1Adc_zb->SetBranchAddress("ieta", ieta_zb);
  TTree* l1Adc_eb = (TTree*)inEmptyBX->Get("MBefficiency/adc");
  int nampl_eb; l1Adc_eb->SetBranchAddress("nampl", &nampl_eb);
  int ampl_eb[4000]; l1Adc_eb->SetBranchAddress("ampl", ampl_eb);
  int ieta_eb[4000]; l1Adc_eb->SetBranchAddress("ieta", ieta_eb);

  TH1F* hAdc_zb = new TH1F("hAdc_zb", ";ADC;", 50, 0, 50);
  TH1F* hAdc_eb = new TH1F("hAdc_eb", ";ADC;", 50, 0, 50);
  TH1F* hAdcmax_zb = new TH1F("hAdcmax_zb", ";max ADC;", 50, 0, 50);
  TH1F* hAdcmax_eb = new TH1F("hAdcmax_eb", ";max ADC;", 50, 0, 50);

  int nentries_zb = l1Adc_zb->GetEntries();
  for(int i=0;i<nentries_zb;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<nentries_zb<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/nentries_zb,"%")<<"\033[0m"<<"\r"<<std::flush;

      l1Adc_zb->GetEntry(i);
      int amplmax = 0;
      for(int l=0;l<nampl_zb;l++)
        { 
          if(TMath::Abs(ieta_zb[l]) > 28) 
            {
              hAdc_zb->Fill(ampl_zb[l]); 
              if(ampl_zb[l]>amplmax) { amplmax = ampl_zb[l]; }
            }
        }
      hAdcmax_zb->Fill(amplmax);
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<nentries_zb<<"\033[0m out of\033[1;31m "<<nentries_zb<<"\033[0m event(s)."<<std::endl;
  int nentries_eb = l1Adc_eb->GetEntries();
  for(int i=0;i<nentries_eb;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<nentries_eb<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/nentries_eb,"%")<<"\033[0m"<<"\r"<<std::flush;

      l1Adc_eb->GetEntry(i);
      int amplmax = 0;
      for(int l=0;l<nampl_eb;l++)
        { 
          if(TMath::Abs(ieta_eb[l]) > 28) 
            {
              hAdc_eb->Fill(ampl_eb[l]); 
              if(ampl_eb[l]>amplmax) { amplmax = ampl_eb[l]; }
            }
        }
      hAdcmax_eb->Fill(amplmax);
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<nentries_eb<<"\033[0m out of\033[1;31m "<<nentries_eb<<"\033[0m event(s)."<<std::endl;

  hAdc_eb->Scale(nentries_zb*1./nentries_eb);

  TFile* output = new TFile(Form("%s.root", outFileName.Data()), "recreate");
  hAdc_zb->Write();
  hAdc_eb->Write();
  hAdcmax_zb->Write();
  hAdcmax_eb->Write();
  output->Close();

}

int main(int argc, char* argv[])
{
  if(argc==4) { adcNoise(argv[1], argv[2], argv[3]); return 0; } 
  return 1;
}
