#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include <TCanvas.h>
#include <TH1F.h>
#include "xjjrootuti.h"

typedef std::pair<std::string, float> spair;
bool sortbysec(const spair &a, const spair &b) { return (a.second > b.second); }
bool str_contains(std::string str1, std::string str2) { return str1.find(str2)!=std::string::npos; }

void sryMemory(std::string inputname, const int nline, const int nevt, bool verbose=false)
{
  std::map<std::string, int> nrss;
  std::map<std::string, int> nrss_cond;
  std::map<std::string, float> sumrss;
  std::map<std::string, float> sumrss_cond;
  std::map<std::string, int> nvsize;
  std::map<std::string, float> sumvsize;
  std::vector<float> vrss;

  float maxrss = 0;
  float maxvsize = 0;
  
  std::ifstream getdata(inputname.c_str());
  for(int i=0;i<nline;i++)
    {
      std::string temp, name;
      float vsize, del_vsize, rss, del_rss;
      getdata>>temp>>temp>>name>>temp>>vsize>>del_vsize>>temp>>rss>>del_rss;
      if(verbose) { std::cout<<std::left<<std::setw(100)<<name<<std::setw(10)<<vsize<<std::setw(10)<<del_vsize<<std::setw(10)<<rss<<std::setw(10)<<del_rss<<std::endl; }
      vrss.push_back(rss);
      if(rss>maxrss) maxrss = rss;
      if(vsize>maxvsize) maxvsize = vsize;
      int ncond = del_rss>5?1:0;
      float delrsscond = del_rss>5?del_rss:0;
      float nthisvsize = del_vsize?1:0;
      if(nrss.find(name)==nrss.end())
        {
          nrss.insert(std::pair<std::string, int>(name, 1));
          nrss_cond.insert(std::pair<std::string, int>(name, ncond));
          sumrss.insert(std::pair<std::string, float>(name, del_rss));
          sumrss_cond.insert(std::pair<std::string, float>(name, delrsscond));
          nvsize.insert(std::pair<std::string, int>(name, nthisvsize));
          sumvsize.insert(std::pair<std::string, float>(name, del_vsize));
        }
      else
        {
          nrss.at(name) += 1;
          nrss_cond.at(name) += ncond;
          sumrss.at(name) += del_rss;
          sumrss_cond.at(name) += delrsscond;
          nvsize.at(name) += nthisvsize;
          sumvsize.at(name) += del_vsize;
        }
    }
  std::vector<spair> nrss_sort;
  for(auto it : sumrss_cond) { nrss_sort.push_back(it); }
  std::sort(nrss_sort.begin(), nrss_sort.end(), sortbysec); 
  int i = 0;
  std::cout<<std::endl;
  std::cout<<std::string(195, '-')<<std::endl;
  std::cout<<" -- peak RSS = \033[38;5;210;1m"<<maxrss<<" MB\033[0m"<<" -- peak VSIZE = \033[38;5;210;1m"<<maxvsize<<" MB\033[0m"<<" -- #event = \033[38;5;210;1m"<<nevt<<"\033[0m"<<std::endl;
  std::cout<<std::string(195, '-')<<std::endl;
  std::cout<<std::left
           <<std::setw(5)<<"#"
           <<std::setw(110)<<"Module"
           <<std::setw(10)<<"Times"
           <<std::setw(20)<<"total RSS (MB)"
           <<std::setw(20)<<"total RSS(>5MB)"
           <<std::setw(10)<<"#VSIZE"
           <<std::setw(20)<<"total VSIZE (MB)"
           <<"\033[0m"<<std::endl;
  std::cout<<std::string(195, '-')<<std::endl;
  for(auto const it : nrss_sort)
    {
      i++;
      std::string name = it.first;
      std::string fcolor = str_contains(name, "Dpt")?"2;251;242;188":(str_contains(name, "PPOnAA") || str_contains(name, "Strip")?"2;255;176;176":"5;15");
      std::string bcolor = i%2==0?"2;36;87;98":"2;21;52;58";
      std::string color = "\033[48;"+bcolor+";38;"+fcolor+";1m";
      std::cout<<std::left<<color
               <<std::setw(5)<<i
               <<std::setw(110)<<name
               <<std::setw(10)<<nrss[name]
               <<std::setw(20)<<sumrss[name]
               <<std::setw(20)<<sumrss_cond[name]
               <<std::setw(10)<<nvsize[name]
               <<std::setw(20)<<sumvsize[name]
               <<"\033[0m"<<std::endl;
    }

  // TH1F* hrss = new TH1F("hrss", ";---- time ---->;RSS", vrss.size(),0,vrss.size());
  // xjjroot::sethempty(hrss);
  // for(int i=0;i<vrss.size();i++) { hrss->SetBinContent(i+1, vrss[i]); }
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
