#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include "xjjrootuti.h"
#include "xjjcuti.h"

typedef std::pair<std::string, float> spair;
void sryMemory(std::string inputname, const int nevt, const int outputline=-1, const int nline=-1, bool verbose=false)
{
  std::map<std::string, float> nrss;
  std::map<std::string, float> avgrss;
  std::map<std::string, float> minrss;
  std::map<std::string, float> maxrss;
  std::map<std::string, float> avgvsize;

  float maxrss_ = 0;
  float maxvsize_ = 0;
  
  std::ifstream getdata(inputname.c_str());
  for(int i=0;i<nline || nline<0;i++)
    {
      std::string temp, name;
      float vsize, del_vsize, rss, del_rss;
      getdata >> temp;
      if(getdata.eof()) { break; }
      getdata >> temp >> name >> temp >> vsize >> del_vsize >> temp >> rss >> del_rss;
      if(verbose) { std::cout << std::left << std::setw(100) << name
                              << std::setw(10) << vsize << std::setw(10) << del_vsize
                              << std::setw(10) << rss << std::setw(10) << del_rss << std::endl; }
      if(rss>maxrss_) maxrss_ = rss;
      if(vsize>maxvsize_) maxvsize_ = vsize;
      if(nrss.find(name)==nrss.end())
        {
          nrss.insert(std::pair<std::string, int>(name, 1));
          avgrss.insert(std::pair<std::string, float>(name, del_rss));
          avgvsize.insert(std::pair<std::string, float>(name, del_vsize));
          minrss.insert(std::pair<std::string, float>(name, del_rss));
          maxrss.insert(std::pair<std::string, float>(name, del_rss));
        }
      else
        {
          nrss[name] += 1;
          avgrss[name] += del_rss;
          avgvsize[name] += del_vsize;
          if(del_rss > maxrss[name]) maxrss[name] = del_rss;
          if(del_rss < minrss[name]) minrss[name] = del_rss;
        }
    }
  std::vector<spair> nrss_sort;
  for(auto& it : maxrss) { nrss_sort.push_back(it); } // sort by
  std::sort(nrss_sort.begin(), nrss_sort.end(), xjjc::sortbysecond_des<std::string, float>); 
  int i = 0;
  std::cout<<std::endl;
  std::cout<<std::string(195, '-')<<std::endl;
  std::cout<<" -- peak RSS = \033[38;5;210;1m"<<maxrss_<<" MB\033[0m"<<" -- peak VSIZE = \033[38;5;210;1m"<<maxvsize_<<" MB\033[0m"<<" -- #event = \033[38;5;210;1m"<<nevt<<"\033[0m"<<std::endl;
  std::cout<<std::string(195, '-')<<std::endl;
  std::cout<<std::left
           <<std::setw(5)<<"#"
           <<std::setw(110)<<"Module"
           <<std::setw(10)<<"Appear"
           <<std::setw(20)<<"avg RSS (MB)"
           <<std::setw(20)<<"min RSS (MB)"
           <<std::setw(20)<<"max RSS (MB)"
           <<std::setw(20)<<"avg VSIZE (MB)"
           <<"\033[0m"<<std::endl;
  std::cout<<std::string(195, '-')<<std::endl;
  std::string outputname = xjjc::str_replaceall(xjjc::str_replaceall(inputname, ".", "-"), "/", "-");
  TFile* outf = new TFile(std::string("rootfiles/"+outputname+".root").c_str(), "recreate");
  outf->cd();
  TTree* rcd = new TTree("rcd", "");
  for(auto const it : nrss_sort)
    {
      std::string name = it.first;
      std::string modname(name);
      modname.erase(0, name.find(':')+1);
      std::string fcolor = xjjc::str_contains(name, "Dpt")?"2;251;242;188":(xjjc::str_contains(name, "PPOnAA") || xjjc::str_contains(name, "Strip")?"2;255;176;176":"5;15");
      std::string bcolor = i%2==0?"2;36;87;98":"2;21;52;58";
      std::string color = "\033[48;"+bcolor+";38;"+fcolor+";1m";
      avgrss[name] /= nrss[name];
      avgvsize[name] /= nrss[name];
      std::vector<float>* modrss = new std::vector<float>{nrss[name], avgrss[name], minrss[name], maxrss[name], avgvsize[name]};
      rcd->Branch(modname.c_str(), modrss);
      i++;
      if(i > outputline && outputline > 0) { continue; }
      std::cout<<std::left<<color
               <<std::setw(5)<<i
               <<std::setw(110)<<name
               <<std::setw(10)<<nrss[name]
               <<std::setw(20)<<avgrss[name]
               <<std::setw(20)<<minrss[name]
               <<std::setw(20)<<maxrss[name]
               <<std::setw(20)<<avgvsize[name]
               <<"\033[0m"<<std::endl;
    }
  rcd->Fill();
  rcd->Write();
  outf->Close();
}

int main(int argc, char* argv[])
{
  if(argc==5) { sryMemory(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4])); return 0; }
  if(argc==4) { sryMemory(argv[1], atoi(argv[2]), atoi(argv[3])); return 0; }
  if(argc==3) { sryMemory(argv[1], atoi(argv[2])); return 0; }
  return 1;
}
