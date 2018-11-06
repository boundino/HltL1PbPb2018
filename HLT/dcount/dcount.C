#include <iostream>
#include <vector>
#include <string>
#include "xjjcuti.h"
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TRandom.h>

#include "getDntuple.h"
#include "djtweight.h"
#include "dcount.h"

void dcount(std::string inputname, std::string outputname, int icase, int entries = -1)
{
  auto inf = TFile::Open(inputname.c_str());
  auto root = (TTree*)inf->Get("Dfinder/ntDkpi");
  auto hlt = (TTree*)inf->Get("hltbitanalysis/HltTree");
  auto hi = (TTree*)inf->Get("hiEvtAnalyzer/HiTree");

  djtweight::init();
  objstructure::getDntuple nt(root);
  for(int ip=0; ip<npath; ip++) 
    { hlt->SetBranchAddress(str_HLT_HIDmesonPPTrackingGlobal_DptX_v1[ip].c_str(), &(HLT_HIDmesonPPTrackingGlobal_DptX_v1[ip])); }
  float pthatweight;
  hi->SetBranchAddress("pthatweight", &pthatweight);
  float pthat;
  hi->SetBranchAddress("pthat", &pthat);

  std::vector<int> thiscase = case_time_week[icase];

  float ptbins[] = {15, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
  const int npt = sizeof(ptbins) / sizeof(ptbins[0]) - 1;
  TH1F* hDpt_HF = new TH1F("hDpt_HF", ";signal D^{0} p_{T} (GeV/c);N(reco signal D) [after all eff]", npt, ptbins); hDpt_HF->Sumw2();
  TH1F* hDpt_MBall = new TH1F("hDpt_MBall", ";signal D^{0} p_{T} (GeV/c);N(reco signal D) [after all eff]", npt, ptbins); hDpt_MBall->Sumw2();
  TH1F* hDpt_MBred = new TH1F("hDpt_MBred", ";signal D^{0} p_{T} (GeV/c);N(reco signal D) [after all eff]", npt, ptbins); hDpt_MBred->Sumw2();
  TH1F* hDpt_MBfull = new TH1F("hDpt_MBfull", ";signal D^{0} p_{T} (GeV/c);N(reco signal D) [after all eff]", npt, ptbins); hDpt_MBfull->Sumw2();
  TH1F* hDpt_HF_MBred = new TH1F("hDpt_HF_MBred", ";signal D^{0} p_{T} (GeV/c);N(reco signal D) [after all eff]", npt, ptbins); hDpt_HF_MBred->Sumw2();
  TH1F* hDpt_HF_MBfull = new TH1F("hDpt_HF_MBfull", ";signal D^{0} p_{T} (GeV/c);N(reco signal D) [after all eff]", npt, ptbins); hDpt_HF_MBfull->Sumw2();
  TH1F* hDpt_HF_MBall = new TH1F("hDpt_HF_MBall", ";signal D^{0} p_{T} (GeV/c);N(reco signal D) [after all eff]", npt, ptbins); hDpt_HF_MBall->Sumw2();

  TRandom* ran = new TRandom(0);
  int nentries = (entries>0&&entries<root->GetEntries())?entries:root->GetEntries();
  for(int i=0; i<nentries; i++)
    {
      hlt->GetEntry(i);
      root->GetEntry(i);
      hi->GetEntry(i);
      if(i%100==0) xjjc::progressbar(i, nentries);
      for(int ico=0; ico<rate.size(); ico++)
        {
          // std::cout<<ico<<" ";
          int thisrate = rate[ico]; 
          std::vector<int> thisps = prescale[ico];
          // for(auto ips : thisps) { std::cout<<ips<<" "; }
          // std::cout<<" -- "<<thiscase[ico]<<std::endl;
          if(thiscase[ico]==0) continue;
          bool pass_HF = false;
          bool pass_MBred = false;
          bool pass_MBfull = false;
          for(int ip=0; ip<npath; ip++)
            {
              int randint = ran->Integer(thisps[ip]);
              // std::cout<<str_HLT_HIDmesonPPTrackingGlobal_DptX_v1[ip]<<" ==> "<<thisps[ip]<<" ==> "<<randint<<std::endl;
              if(ip==0) 
                { 
                  if(HLT_HIDmesonPPTrackingGlobal_DptX_v1[ip] && randint>=0 && randint<=1) { pass_MBfull = true; } 
                  if(HLT_HIDmesonPPTrackingGlobal_DptX_v1[ip] && randint>=2 && randint<=25) { pass_MBred = true; } 
                }
              else if(HLT_HIDmesonPPTrackingGlobal_DptX_v1[ip] && randint>=0 && randint<=0) { pass_HF = true; }
            }
          // std::cout<<"---"<<pass_HF<<" "<<pass_MBred<<" "<<pass_MBfull<<std::endl;
          // if(!pass) continue;
          for(int j=0; j<nt.Dsize; j++)
            {
              if(!nt.iscandsel(j)) continue;
              float thisweight = pthatweight*djtweight::getDptweight(nt.Dgenpt[j], 0)*thisrate*1.e+3*thiscase[ico]*sec_aweek*taa;
              bool istrk6 = nt.Dtrk1Pt[j] > 6 && nt.Dtrk2Pt[j] > 6;
              bool istrk2 = nt.Dtrk1Pt[j] > 2 && nt.Dtrk2Pt[j] > 2;
              if(pthat < 50 && nt.Dpt[j] > 50) { std::cout<<pthat<<" "<<pthatweight<<" "<<djtweight::getDptweight(nt.Dgenpt[j], 0)<<std::endl; continue; }
              if(pass_HF && istrk6) { hDpt_HF->Fill(nt.Dpt[j], thisweight); }
              if((pass_MBred && istrk2)  || (pass_MBfull && istrk2)) { hDpt_MBall->Fill(nt.Dpt[j], thisweight); }
              if((pass_MBred && istrk2)) { hDpt_MBred->Fill(nt.Dpt[j], thisweight); }
              if((pass_MBfull && istrk2)) { hDpt_MBfull->Fill(nt.Dpt[j], thisweight); }
              if((pass_HF && istrk6) || (pass_MBred && istrk2) || (pass_MBfull && istrk2)) { hDpt_HF_MBall->Fill(nt.Dpt[j], thisweight); }
              if((pass_HF && istrk6) || (pass_MBred && istrk2)) { hDpt_HF_MBred->Fill(nt.Dpt[j], thisweight); }
              if((pass_HF && istrk6) || (pass_MBfull && istrk2)) { hDpt_HF_MBfull->Fill(nt.Dpt[j], thisweight); }
            }
        }
    }
  xjjc::progressbar_summary(nentries);

  auto outf = new TFile(Form("rootfiles/root_%s_%s.root", outputname.c_str(), case_name[icase].c_str()), "recreate");
  hDpt_HF->Write();
  hDpt_MBall->Write();
  hDpt_MBred->Write();
  hDpt_MBfull->Write();
  hDpt_HF_MBred->Write();
  hDpt_HF_MBfull->Write();
  hDpt_HF_MBall->Write();
  outf->Close();
  
}

int main(int argc, char* argv[])
{
  if(argc==5) { dcount(argv[1], argv[2], atoi(argv[3]), atoi(argv[4])); return 0; }
  if(argc==4) { dcount(argv[1], argv[2], atoi(argv[3])); return 0; }
  return 1;
}
