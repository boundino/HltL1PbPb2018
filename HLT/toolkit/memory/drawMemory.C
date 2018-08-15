#include <vector>
#include <string>
#include <algorithm>

#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "xjjrootuti.h"

void drawMemory(std::vector<std::string> vinput, std::string output)
{
  std::vector<TH1F*> vhrss;  
  int count = 0;
  TLegend* leg = new TLegend(0.20, 0.60, 0.65, 0.85);
  leg->SetNColumns(2);
  xjjroot::setleg(leg);
  for(auto &i : vinput) 
    {
      std::string name(i.begin()+10, i.end()-5);
      TFile* inf = new TFile(i.c_str());
      TH1F* hrss = (TH1F*)inf->Get("hrss");
      hrss->SetName(std::string("hrss_"+name).c_str());
      hrss->SetMaximum(17000);
      hrss->SetLineWidth(2);
      if(count < xjjroot::ncolor) 
        {
          hrss->SetLineColor(xjjroot::colorlist_dark[count]);
          hrss->SetFillColor(xjjroot::colorlist_light[count]);
        }
      vhrss.push_back(hrss);      
      leg->AddEntry(vhrss[count], std::string(name.begin()+13, name.end()).c_str(), "f");
      count++;
    }
  vhrss.at(vhrss.size()-1)->SetTitle(";Event;RSS (MB)");
  xjjroot::sethempty(vhrss[vhrss.size()-1], 0., 0.25);
  xjjroot::setgstyle();
  TCanvas* c = new TCanvas("c", "", 600, 600);
  for(auto it = vhrss.rbegin(); it != vhrss.rend(); ++it)
    {
      std::string opt = it==vhrss.rbegin()?"hist":"hist same";
      (*it)->Draw(opt.c_str());
    }
  leg->Draw();
  gPad->RedrawAxis();
  c->SaveAs(std::string("plots/cRSSevt_"+output+".pdf").c_str());
}

int main(int argc, char* argv[])
{
  if(argc > 3)
    {
      std::vector<std::string> vinput;
      for(int i=1;i<argc-1;i++) { vinput.push_back(argv[i]); }
      std::sort(vinput.begin(), vinput.end()); 
      drawMemory(vinput, argv[argc-1]);
      return 0;
    }
  return 1;
}
