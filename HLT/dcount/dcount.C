#include <iostream>
#include <vector>
#include <string>
#include "xjjcuti.h"
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>

#include "getDntuple.h"
#include "dcount.h"

void dcount(std::string inputname, std::string outputname, int icase, int entries = -1)
{
  auto inf = TFile::Open(inputname.c_str());
  auto root = (TTree*)inf->Get("Dfinder/ntDkpi");
  auto hlt = (TTree*)inf->Get("hltbitanalysis/HltTree");
  auto hi = (TTree*)inf->Get("hiEvtAnalyzer/HiTree");

  objstructure::getDntuple nt(root);
  for(int ip=0; ip<npath; ip++) 
    { hlt->SetBranchAddress(str_HLT_HIDmesonPPTrackingGlobal_DptX_v1[ip].c_str(), &(HLT_HIDmesonPPTrackingGlobal_DptX_v1[ip])); }
  float pthatweight;
  hi->SetBranchAddress("pthatweight", &pthatweight);

  int thisrate = rate[icase];
  std::vector<int> thisps = prescale[icase];

  TH1F* hDpt = new TH1F("hDpt", ";signal D^{0} p_{T} (GeV/c);", 40, 10, 90);
  hDpt->Sumw2();

  int nentries = (entries>0&&entries<root->GetEntries())?entries:root->GetEntries();
  for(int i=0; i<nentries; i++)
    {
      hlt->GetEntry(i);
      if(i%100==0) xjjc::progressbar(i, nentries);
      bool pass = false;
      for(int ip=0; ip<npath; ip++)
        {
          if(HLT_HIDmesonPPTrackingGlobal_DptX_v1[ip] && i%thisps[ip]==0) { pass = true; break; }
        }
      if(!pass) continue;

      root->GetEntry(i);
      hi->GetEntry(i);
      for(int j=0; j<nt.Dsize; j++)
        {
          if(!nt.iscandsel(j)) continue;
          hDpt->Fill(nt.Dpt[j], pthatweight);
        }
    }
  xjjc::progressbar_summary(nentries);

  auto outf = new TFile(Form("rootfiles/root_%s_%dkHz.root", outputname.c_str(), thisrate), "recreate");
  hDpt->Write();
  outf->Close();
  
}

int main(int argc, char* argv[])
{
  if(argc==5) { dcount(argv[1], argv[2], atoi(argv[3]), atoi(argv[4])); return 0; }
  if(argc==4) { dcount(argv[1], argv[2], atoi(argv[3])); return 0; }
  return 1;
}
