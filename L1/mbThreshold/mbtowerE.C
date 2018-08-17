#include "adcVstowerE.h"

void mbtowerE(std::vector<TString> inputname, TString outputname)
{
  std::cout<<inputname.size()<<std::endl;

  std::vector<TFile*> inf(inputname.size());
  std::vector<TTree*> hiroot(inputname.size());
  for(int k=0;k<inputname.size();k++)
    {
      inf[k] = new TFile(inputname[k].Data());
      hiroot[k] = (TTree*)inf[k]->Get("hiEvtAnalyzer/HiTree");
    }
  
  std::vector<TH1F*> hEtlead(inputname.size());
  for(int k=0;k<inputname.size();k++) { hEtlead[k] = new TH1F(Form("hEtlead%d",k), ";HF tower E_{max} (GeV);", 200, 1, 101); }

  for(int k=0;k<inputname.size();k++)
    {
      float towerEmax; hiroot[k]->SetBranchAddress("towerEmax", &towerEmax);
      int nentries = hiroot[k]->GetEntries();
      for(int i=0;i<nentries;i++)
        {
          if(i%10000==0) { std::cout<<std::setiosflags(std::ios::left)<<std::setw(12)<<i<<" / "<<nentries<<"\r"<<std::flush; }
          hiroot[k]->GetEntry(i);

          hEtlead[k]->Fill(towerEmax);
        }
      std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<nentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<std::endl;
      std::cout<<std::endl;
    }

  TFile* output = new TFile(Form("%s.root", outputname.Data()), "recreate");
  for(int k=0;k<inputname.size();k++) { hEtlead[k]->Write(); }
  output->Close();

}

int main(int argc, char* argv[])
{
  if(argc>=3)
    {
      std::vector<TString> input;
      for(int i=1;i<argc-1;i++) { input.push_back(argv[i]); }
      mbtowerE(input, argv[argc-1]); 
      return 0; 
    }
  return 1;
}

