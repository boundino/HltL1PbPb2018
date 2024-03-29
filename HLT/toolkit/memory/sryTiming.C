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

typedef std::pair<std::string, float> spair;
void sryTiming(std::string inputname, const int nevt, const int outputline=-1, const int nline=-1, bool verbose=false)
{
  std::map<std::string, float> ntime;
  std::map<std::string, float> avgtime;
  std::map<std::string, float> mintime;
  std::map<std::string, float> maxtime;
  std::map<std::string, float> imax;

  std::map<int, float> evttime;
  std::map<int, int> nmods;

  std::map<int, float> evttime_tracking;
  std::map<int, float> evttime_heavyflavor;

  std::vector<std::string> mod_tracking;
  std::vector<std::string> mod_heavyflavor;

  std::ifstream getdata(inputname.c_str());
  for(int i=0;i<nline || nline<0;i++)
    {
      std::string temp, mod, modtype;
      float del_time;
      int event;
      getdata >> temp;
      if(getdata.eof()) { break; }
      getdata >> event >> temp >> mod >> modtype >> del_time;
      std::string name = modtype+":"+mod;
      if(verbose) { std::cout << std::left << std::setw(10) << event << std::setw(100) << name << std::setw(10) << del_time << std::endl; }

      if(ntime.find(name)==ntime.end())
        {
          ntime.insert(std::pair<std::string, float>(name, 1));
          avgtime.insert(std::pair<std::string, float>(name, del_time));
          mintime.insert(std::pair<std::string, float>(name, del_time));
          maxtime.insert(std::pair<std::string, float>(name, del_time));
          imax.insert(std::pair<std::string, float>(name, 0));
        }
      else
        {
          ntime[name] += 1;
          avgtime[name] += del_time;
          if(del_time > maxtime[name]) { maxtime[name] = del_time; imax[name] = ntime[name]-1; }
          if(del_time < mintime[name]) mintime[name] = del_time;
        }
      float iftracking = 0;
      float ifheavyflavor = 0;
      if(xjjc::str_contains(mod, "HLT") || xjjc::str_contains(mod, "hlt"))
        {
          if(xjjc::str_contains(mod, "Dpt")) { ifheavyflavor = del_time; if(std::find(mod_heavyflavor.begin(), mod_heavyflavor.end(), mod)==mod_heavyflavor.end()) { mod_heavyflavor.push_back(mod); } }
          else if(xjjc::str_contains(mod, "HighPt") || xjjc::str_contains(mod, "ZeroBias")) { ; }
          else { iftracking = del_time; if(std::find(mod_tracking.begin(), mod_tracking.end(), mod)==mod_tracking.end()) { mod_tracking.push_back(mod); } }
        }
      if((xjjc::str_contains(mod, "HLT") || xjjc::str_contains(mod, "hlt")) && !xjjc::str_contains(mod, "Dpt") && !xjjc::str_contains(mod, "HighPt") && !xjjc::str_contains(mod, "ZeroBias"))  
        if(evttime.find(event)==evttime.end())
          {
            nmods.insert(std::pair<int, int>(event, 1));
            evttime.insert(std::pair<int, float>(event, del_time));
            evttime_tracking.insert(std::pair<int, float>(event, iftracking));
            evttime_heavyflavor.insert(std::pair<int, float>(event, ifheavyflavor));
          }
        else
          {
            nmods[event] += 1;
            evttime[event] += del_time;
            evttime_tracking[event] += iftracking;
            evttime_heavyflavor[event] += ifheavyflavor;
          }
    }

  std::vector<spair> ntime_sort;
  for(auto& it : avgtime) { ntime_sort.push_back(it); } // sort by
  std::sort(ntime_sort.begin(), ntime_sort.end(), xjjc::sortbysecond_des<std::string, float>); 
  int i = 0;
  std::cout<<std::endl;
  std::cout<<std::string(200, '-')<<std::endl;
  std::cout<<" -- #event = \033[38;5;210;1m"<<nevt<<"\033[0m"<<std::endl;
  std::cout<<std::string(200, '-')<<std::endl;
  std::cout<<std::left
           <<std::setw(5)<<"#"
           <<std::setw(110)<<"Module"
           <<std::setw(10)<<"Appear"
           <<std::setw(20)<<"avg TIME (sec)"
           <<std::setw(20)<<"min TIME (sec)"
           <<std::setw(20)<<"max TIME (sec)"
           <<std::setw(15)<<"max TIME evt"
           <<"\033[0m"<<std::endl;
  std::cout<<std::string(200, '-')<<std::endl;
  std::string outputname = xjjc::str_replaceall(xjjc::str_replaceall(inputname, ".", "-"), "/", "-");
  TFile* outf = new TFile(std::string("rootfiles/"+outputname+".root").c_str(), "recreate");
  outf->cd();
  TTree* rcd = new TTree("rcd", "");
  for(auto const it : ntime_sort)
    {
      std::string name = it.first;
      std::string modname(name);
      modname.erase(0, name.find(':')+1);
      std::string fcolor = xjjc::str_contains(name, "Dpt")?"2;251;242;188":(xjjc::str_contains(name, "PPOnAA") || xjjc::str_contains(name, "Strip")?"2;255;176;176":"5;15");
      std::string bcolor = i%2==0?"2;36;87;98":"2;21;52;58";
      std::string color = "\033[48;"+bcolor+";38;"+fcolor+";1m";
      avgtime[name] /= ntime[name]; 
      std::vector<float>* modrss = new std::vector<float>{ntime[name], avgtime[name], mintime[name], maxtime[name]};
      rcd->Branch(modname.c_str(), modrss);     
      i++;
      if(i > outputline && outputline > 0) { continue; }
      std::cout<<std::left<<color
               <<std::setw(5)<<i
               <<std::setw(110)<<name
               <<std::setw(10)<<ntime[name]
               <<std::setw(20)<<avgtime[name]
               <<std::setw(20)<<mintime[name]
               <<std::setw(20)<<maxtime[name]
               <<std::setw(15)<<imax[name]
               <<"\033[0m"<<std::endl;
    }
  rcd->Fill();
  rcd->Write();

  outf->cd();
  TTree* evttree = new TTree("evt", "");
  int fevtno; evttree->Branch("evtno", &fevtno);
  float fevttime; evttree->Branch("evttime", &fevttime);
  float fevttime_tracking; evttree->Branch("evttime_tracking", &fevttime_tracking);
  float fevttime_heavyflavor; evttree->Branch("evttime_heavyflavor", &fevttime_heavyflavor);
  if(evttime.size() == evttime_tracking.size() && evttime.size() == evttime_heavyflavor.size())
    {
      for(auto& it : evttime) 
        { 
          int ievt = it.first;
          fevtno = ievt;
          fevttime = evttime[ievt];
          fevttime_tracking = evttime_tracking[ievt];
          fevttime_heavyflavor = evttime_heavyflavor[ievt];
          evttree->Fill();    
        }
      evttree->Write();
    }
  else { std::cout << evttime.size() << "  " << evttime_tracking.size() << evttime_heavyflavor.size() << std::endl; }
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==5) { sryTiming(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4])); return 0; }
  if(argc==4) { sryTiming(argv[1], atoi(argv[2]), atoi(argv[3])); return 0; }
  if(argc==3) { sryTiming(argv[1], atoi(argv[2])); return 0; }
  return 1;
}
