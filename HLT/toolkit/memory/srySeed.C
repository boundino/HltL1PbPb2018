#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include "xjjrootuti.h"
#include "xjjcuti.h"

void srySeed(std::string inputname, const int nevt, const int outputline=-1, const int nline=-1, bool verbose=true)
{
  std::map<std::string, float> ntime;
  std::map<std::string, TH1F*> vhnseed;
  std::map<std::string, TH1F*> vhntrk;

  std::ifstream getdata(inputname.c_str());
  for(int i=0;i<nline || nline<0;i++)
    {
      std::string start, temp, mod, modtype;
      float del_time;
      float ntrk, nseed;
      int event;
      getdata >> start;
      if(getdata.eof()) { break; }
      if(start == "VICkfPattern") 
        {
          getdata >> temp >> temp >> temp >> temp >> ntrk >> temp >> nseed >> temp >> temp
                  >> temp >> event >> temp >> mod >> modtype >> del_time;
        }
      else if(start == "TimeModule>")
        {
          getdata >> event >> temp >> mod >> modtype >> del_time;
          ntrk = 0;
          nseed = 0;
        }
      else { std::cout<<"start=="<<start<<std::endl; return; }
      // std::string name = modtype+":"+mod;
      std::string name = mod;
      if(verbose) { std::cout << std::left << std::setw(10) << event << std::setw(100) << name << std::setw(10) << nseed << std::endl; }

      if(ntime.find(name)==ntime.end())
        {
          ntime.insert(std::pair<std::string, float>(name, 0));
          TH1F* hnseed = new TH1F(std::string("hnseed"+name).c_str(), "", nevt, 0, nevt);
          vhnseed.insert(std::pair<std::string, TH1F*>(name, hnseed));
          TH1F* hntrk = new TH1F(std::string("hntrk"+name).c_str(), "", nevt, 0, nevt);
          vhntrk.insert(std::pair<std::string, TH1F*>(name, hntrk));
        }
      ntime[name] += 1;
      vhnseed[name]->SetBinContent(ntime[name], nseed);
      vhntrk[name]->SetBinContent(ntime[name], ntrk);
    }
  std::string outputname = xjjc::str_replaceall(xjjc::str_replaceall(inputname, ".", "-"), "/", "-");
  TFile* outf = new TFile(std::string("rootfiles/"+outputname+".root").c_str(), "recreate");
  outf->cd();
  for(auto const it : vhnseed) { it.second->Write(); }
  for(auto const it : vhntrk) { it.second->Write(); }
  outf->Close();
}

int main(int argc, char* argv[])
{
  if(argc==5) { srySeed(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4])); return 0; }
  if(argc==4) { srySeed(argv[1], atoi(argv[2]), atoi(argv[3])); return 0; }
  if(argc==3) { srySeed(argv[1], atoi(argv[2])); return 0; }
  return 1;
}
