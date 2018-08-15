#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include <TCanvas.h>
#include <TH1F.h>
#include <TFile.h>
#include "xjjrootuti.h"

void sryMemory(std::string inputname, const int nline, const int nevt, bool verbose=false)
{
  std::vector<float> vrss;
  std::ifstream getdata(inputname.c_str());
  for(int i=0;i<nline;i++)
    {
      std::string temp, name;
      float vsize, del_vsize, rss, del_rss;
      getdata>>temp;
      if(getdata.eof()) break;
      getdata>>temp>>temp>>temp>>vsize>>del_vsize>>temp>>rss>>del_rss;
      if(verbose) { std::cout<<std::left<<std::setw(100)<<name<<std::setw(10)<<vsize<<std::setw(10)<<del_vsize<<std::setw(10)<<rss<<std::setw(10)<<del_rss<<std::endl; }
      vrss.push_back(rss);
    }

  // TH1F* hrss = new TH1F("hrss", ";Event;RSS (MB)", vrss.size(),0,vrss.size());
  TH1F* hrss = new TH1F("hrss", ";Event;RSS (MB)", nevt, 0, nevt);
  xjjroot::sethempty(hrss, 0.03);
  for(int i=0;i<vrss.size();i++) { hrss->SetBinContent(i+1, vrss[i]); }
  std::string outputname(inputname.begin()+5, inputname.end()-4);
  outputname = "rootfiles/"+outputname+".root";
  TFile* outf = new TFile(outputname.c_str(), "recreate");
  outf->cd();
  hrss->Write();
  outf->Close();
  // hrss->SetLineWidth(3);
  // hrss->SetLineColor(kRed+2);
  // xjjroot::setgstyle();
  // TCanvas* c = new TCanvas("c", "", 600, 600);
  // hrss->Draw("C");
  // inputname.erase(inputname.find(".txt"), 4);
  // c->SaveAs(Form("cRSS_%s.pdf",inputname.c_str()));  
}

int main(int argc, char* argv[])
{
  if(argc==4) { sryMemory(argv[1], atoi(argv[2]), atoi(argv[3])); return 0; }
  return 1;
}
