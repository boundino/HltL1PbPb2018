#include "adcEffcent.h"

void splithiBin(TString inputname, TString outputname, int nevt = -1, bool isoutputedge=false)
{
  bool isXeXe = inputname.Contains("XeXe");
  
  TFile* inf = new TFile(inputname.Data());
  TTree* hiroot = (TTree*)inf->Get("hiEvtAnalyzer/HiTree");

  //
  float hiHF; hiroot->SetBranchAddress("hiHF", &hiHF);
  int hiBin; hiroot->SetBranchAddress("hiBin", &hiBin);

  TH1F* hhiHF = new TH1F("hhiHF", ";hiHF;", 500, 0, 5000); hhiHF->Sumw2();
  TH1F* hhiBin = new TH1F("hhiBin", ";hiBin;", 200, 0, 200); hhiBin->Sumw2();
  TH1F* hhiBincal = new TH1F("hhiBincal", ";hiBin;", 200, 0, 200); hhiBincal->Sumw2();
  TH2F* hhiHFvshiBin = new TH2F("hhiHFvshiBin", ";hiBin;hiHF", 200, 0, 200, 5000, 0, 5000);

  std::vector<TH1F*> hhiBincalcent(nhiBins);
  for(int k=0;k<nhiBins;k++) { hhiBincalcent[k] = new TH1F(Form("hhiBincalcent%d",k), "", 200, 0, 200); }

  std::vector<float> vhiHF;

  int nentries = nevt>0&&nevt<hiroot->GetEntries()?nevt:hiroot->GetEntries();
  for(int i=0;i<nentries;i++)
    {
      if(i%100==0) { xjjc::progressbar(i, nentries); }
      hiroot->GetEntry(i);

      vhiHF.push_back(hiHF);
      hhiHF->Fill(hiHF);
      hhiBin->Fill(hiBin);
      hhiHFvshiBin->Fill(hiBin, hiHF);
    }
  xjjc::progressbar_summary(nentries);

  std::sort(vhiHF.begin(), vhiHF.end(), xjjc::sortbydes<float>);

  if(isoutputedge)
    {
      std::ofstream outputedge("hfedge_PbPbMCMB.list");
      for(int k=1;k<=200;k++) { outputedge<<vhiHF[int((k/200.)*vhiHF.size())-1]<<std::endl; }
      outputedge.close();
    }

  std::string listname = isXeXe?"hfedges.list":"hfedge_PbPbMCMB.list";
  std::ifstream getdata(listname.c_str());
  std::vector<float> vhiHFcal(200, 0);
  std::vector<float> vhiBincal(200, 0);
  for(int k=0;k<200;k++) { getdata>>vhiHFcal[k]; vhiBincal[k] = k; }
  std::vector<TH1F*> hhiHFcent(nhiBins);
  for(int k=0;k<nhiBins;k++) { hhiHFcent[k] = new TH1F(Form("hhiHFcent%d",k), "", 500, 0, 5000); }
  // std::vector<float> vhiHFcalcent(nhiBins+1);
  // vhiHFcalcent[0] = 5000;
  // for(int k=1;k<nhiBins+1;k++) { vhiHFcalcent[k] = vhiHFcal[hiBins[k]-1]; }
  // std::sort(vhiHFcalcent.begin(), vhiHFcalcent.end());
  // for(int k=0;k<nhiBins;k++) { hhiHFcent[k] = new TH1F(Form("hhiHFcent%d",k), "", nhiBins, vhiHFcalcent.data()); }
  for(int i=0;i<nentries;i++)
    {
      if(i%100==0) { xjjc::progressbar(i, nentries); }
      hiroot->GetEntry(i);

      int hiBincal;
      for(int k=0;k<vhiHFcal.size();k++) 
        {           
          if(hiHF > vhiHFcal[k])  { hiBincal = k; break; }
        }
      hhiBincal->Fill(hiBincal);
      for(int k=0;k<nhiBins;k++) 
        { 
          if(hiBincal < hiBins[k+1]) { hhiBincalcent[k]->Fill(hiBincal); hhiHFcent[k]->Fill(hiHF); break; } 
        }
    }
  xjjc::progressbar_summary(nentries);

  TGraph* grhiHFvshiBin = new TGraph(200, vhiBincal.data(), vhiHFcal.data());
  grhiHFvshiBin->SetName("grhiHFvshiBin");
  
  // std::cout<<std::left<<std::setw(15)<<"int hiBins[] = "<<"{";
  // for(int k=0;k<=nhiBins;k++) { std::cout<<std::left<<std::setw(17)<<Form("%.0f%s",calhiBin[k],(k==nhiBins?"};":",")); }
  // std::cout<<std::endl;
  std::cout<<std::left<<"int hiHFs"<<(isXeXe?"_XeXe":"_PbPbMC")<<"[] = "<<"{";
  for(int k=0;k<200;k++) { std::cout<<std::left<<Form("%f%s",vhiHFcal[k],(k==199?"};":", ")); }
  std::cout<<std::endl<<std::endl;

  TFile* output = new TFile(Form("%s.root", outputname.Data()), "recreate");
  hhiHF->Write();
  hhiBin->Write();
  hhiBincal->Write();
  hhiHFvshiBin->Write();
  grhiHFvshiBin->Write();
  for(int k=0;k<nhiBins;k++) { hhiBincalcent[k]->Write(); hhiHFcent[k]->Write(); }
  output->Close();

}

int main(int argc, char* argv[])
{
  if(argc==3) { splithiBin(argv[1], argv[2]); return 0; }
  if(argc==4) { splithiBin(argv[1], argv[2], atoi(argv[3])); return 0; }
  if(argc==5) { splithiBin(argv[1], argv[2], atoi(argv[3]), atoi(argv[4])); return 0; }
  return 1;
}

