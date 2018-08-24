#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "xjjrootuti.h"
#include "xjjcuti.h"

#include "mapTracking.h"

void drawTiming(std::vector<std::string> vinput, std::vector<int> vishlt, std::string output)
{
  if(nmaptrkhlt != nmaptrkoffline) return;
  xjjroot::setgstyle(1);
  gStyle->SetPadRightMargin(0.04);
  gStyle->SetPadLeftMargin(0.37);
  gStyle->SetPadTopMargin(0.02);
  gStyle->SetPadBottomMargin(0.08);

  std::vector<std::pair<TH1F*,float>> vhavgtime;
  TLegend* leg = new TLegend(0.67, 0.50-0.04*vinput.size(), 0.90, 0.50);
  xjjroot::setleg(leg, 0.04);
  int j = 0;  
  for(auto &it : vinput) 
    {      
      std::string name(it.begin()+10, it.end()-5);
      TFile* inf = new TFile(it.c_str());
      TTree* rcd = (TTree*)inf->Get("rcd");
      std::string maptrk[nmaptrkhlt] = vishlt[j]?maptrkhlt:maptrkoffline; 
      TH1F* hrss = new TH1F(std::string("hrss_"+name).c_str(), "", nmaptrkhlt, 0, nmaptrkhlt);
      std::vector<std::vector<float>*> module(nmaptrkhlt);
      for(int k=0;k<nmaptrkhlt;k++)
        {
          module[k] = 0;
          rcd->SetBranchAddress(maptrk[k].c_str(), &(module[k]));
        }
      rcd->GetEntry(0);
      for(int k=0;k<nmaptrkhlt;k++)
        {
          hrss->SetBinContent(k+1, (*module[k])[1]);
          hrss->GetXaxis()->SetBinLabel(k+1, maptrk[k].c_str());
          hrss->GetXaxis()->SetLabelSize(0.03);
          hrss->GetYaxis()->CenterTitle();
          hrss->GetYaxis()->SetTitleOffset(1.0);
        }
      if(j < xjjroot::ncolor) 
        { hrss->SetFillColor(xjjroot::colorlist_middle[j]); }
      vhavgtime.push_back(std::pair<TH1F*,float>(hrss, hrss->GetMaximum()));
      leg->AddEntry(vhavgtime[j].first, std::string(name.begin()+40, name.end()-16).c_str(), "f");
      j++;
    }
  std::sort(vhavgtime.begin(), vhavgtime.end(), xjjc::sortbysecond_as<TH1F*,float>);
  vhavgtime.at(vhavgtime.size()-1).first->SetTitle(";;Average time/evt (sec)");
  TCanvas* c = new TCanvas("c", "", 1500, 1500);
  for(auto it = vhavgtime.rbegin(); it != vhavgtime.rend(); ++it)
    {
      std::string opt = it==vhavgtime.rbegin()?"HBAR":"HBAR same";
      it->first->Draw(opt.c_str());
    }
  leg->Draw();
  gPad->RedrawAxis();
  c->SaveAs(std::string("plots/ctiming_"+output+".pdf").c_str());
}

int main(int argc, char* argv[])
{
  if(argc >= 4)
    {
      std::vector<std::string> vinput;
      std::vector<int> vishlt;
      for(int i=1;i<argc-1;i+=2) { vinput.push_back(argv[i]); vishlt.push_back(atoi(argv[i+1])); }
      for(auto& it : vinput) { std::cout<<it<<std::endl; }
      // std::sort(vinput.begin(), vinput.end()); 
      drawTiming(vinput, vishlt, argv[argc-1]);
      return 0;
    }
  std::cout<<argc<<std::endl;
  return 1;
}
