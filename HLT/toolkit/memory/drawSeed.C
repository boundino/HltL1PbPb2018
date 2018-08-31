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

#include "mapTracking_TrackCandidates.h"

void drawSeed(std::vector<std::string> vinput, std::vector<int> vishlt, std::string output)
{
  if(nmaptrkhlt != nmaptrkoffline) return;
  xjjroot::setgstyle(1);

  for(int k=0;k<nmaptrkhlt;k++)
    {
      std::vector<TH1F*> vhnseed(vinput.size());
      std::vector<TH1F*> vhntrk(vinput.size());
      TCanvas* c = new TCanvas("c", "", 1500, 1500);
      TLegend* leg = new TLegend(0.70, 0.88-0.04*vinput.size(), 0.92, 0.88);
      xjjroot::setleg(leg, 0.04);
      int j = 0; float yaxismax = 0;
      for(auto &it : vinput) 
        {
          std::string name(it.begin()+10, it.end()-5);
          TFile* inf = new TFile(it.c_str());
          std::string maptrk[nmaptrkhlt] = vishlt[j]?maptrkhlt:maptrkoffline; 
          vhnseed[j] = (TH1F*)inf->Get(std::string("hnseed"+maptrk[k]).c_str());
          if(vhnseed[j]->GetMaximum() > yaxismax) { yaxismax = vhnseed[j]->GetMaximum(); }
          xjjroot::setthgrstyle(vhnseed[j], xjjroot::colorlist_middle[j+1], 21, 1.3, xjjroot::colorlist_middle[j+1]);
          vhntrk[j] = (TH1F*)inf->Get(std::string("hntrk"+maptrk[k]).c_str());
          if(vhntrk[j]->GetMaximum() > yaxismax) { yaxismax = vhntrk[j]->GetMaximum(); }
          xjjroot::setthgrstyle(vhntrk[j], xjjroot::colorlist_middle[j+1], 25, 1.3, xjjroot::colorlist_middle[j+1]);
          leg->AddEntry(vhnseed[j], std::string(std::string(name.begin()+25, name.end()-4)).c_str(), "p");
          // leg->AddEntry(vhntrk[j], std::string(std::string(name.begin()+25, name.end()-4)+" N_{trajectory}").c_str(), "p");
          j++;
        }
      TH1F* hempty = (TH1F*)vhnseed[0]->Clone("hempty");
      hempty->SetTitle(";event;N_{seed}");
      hempty->SetMaximum(yaxismax * 1.2);
      xjjroot::sethempty(hempty, 0, 0);
      hempty->Draw("p");
      for(auto &it : vhnseed) { it->Draw("lp same"); }
      // for(auto &it : vhntrk) { it->Draw("lp same"); }
      leg->Draw();
      xjjroot::drawtex(0.96, 0.93, maptrkhlt[k].c_str(), 0.04, 32, 42);
      c->SaveAs(std::string("plots/cseed_"+output+"_"+maptrkhlt[k]+".pdf").c_str());
      
      delete hempty;
      delete leg;
      delete c;
      
    }
}

int main(int argc, char* argv[])
{
  if(argc >= 4)
    {
      std::vector<std::string> vinput;
      std::vector<int> vishlt;
      for(int i=1;i<argc-1;i+=2) { vinput.push_back(argv[i]); vishlt.push_back(atoi(argv[i+1])); }
      for(auto& it : vinput) { std::cout<<it<<std::endl; }
      drawSeed(vinput, vishlt, argv[argc-1]);
      return 0;
    }
  std::cout<<argc<<std::endl;
  return 1;
}
