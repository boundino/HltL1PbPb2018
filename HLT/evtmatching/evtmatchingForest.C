#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <TString.h>

#include "xjjcuti.h"

int evtmatching(TString infforest, TString infhlt, TString outfile, Long64_t nentries = -1)
{
  TFile* fforest = new TFile(infforest);
  TFile* fhlt = new TFile(infhlt);

  TTree* hiroot = (TTree*)fforest->Get("hiEvtAnalyzer/HiTree");
  TTree* trackTree = (TTree*)fforest->Get("ppTrack/trackTree");
  TTree* hlt = (TTree*)fhlt->Get("hltbitanalysis/HltTree");

  TFile* outf = new TFile(outfile,"recreate");
  TDirectory* dhiEvtAnalyzer = outf->mkdir("hiEvtAnalyzer", "");
  TDirectory* dppTrack = outf->mkdir("ppTrack", "");
  TDirectory* dhltbitanalysis = outf->mkdir("hltbitanalysis", "");

  dhiEvtAnalyzer->cd();
  TTree* new_hiroot = hiroot->CloneTree(0);
  dppTrack->cd();
  TTree* new_trackTree = trackTree->CloneTree(0);
  dhltbitanalysis->cd();
  TTree* new_hlt = hlt->CloneTree(0);

  UInt_t run; hiroot->SetBranchAddress("run", &run);
  ULong64_t evt; hiroot->SetBranchAddress("evt", &evt);
  UInt_t lumi; hiroot->SetBranchAddress("lumi", &lumi);  
  Int_t Run; hlt->SetBranchAddress("Run", &Run);
  ULong64_t Event; hlt->SetBranchAddress("Event", &Event);
  Int_t LumiBlock; hlt->SetBranchAddress("LumiBlock", &LumiBlock);

  std::cout<<"---- Check evt no. for four trees"<<std::endl;
  std::cout<<hiroot->GetEntries()<<", "<<trackTree->GetEntries()<<", "<<hlt->GetEntries()<<std::endl;
  Long64_t nhiroot = hiroot->GetEntries();
  Long64_t nhlt = hlt->GetEntries();
  std::cout<<"---- Event reading"<<std::endl;
  Long64_t entries = (nentries<nhiroot&&nentries>0)?nentries:nhiroot;
  std::vector<UInt_t> hlt_Run;
  std::vector<ULong64_t> hlt_Event;
  std::vector<UInt_t> hlt_LumiBlock;
  for(Long64_t k = 0; k<nhlt; k++)
    {
      if(k % 100 == 0) { xjjc::progressbar(k, nhlt); }
      hlt->GetEntry(k); //
      hlt_Run.push_back(Run);
      hlt_Event.push_back(Event);
      hlt_LumiBlock.push_back(LumiBlock);      
    }
  std::cout<<std::endl<<"---- Extracted event info + matching"<<std::endl;
  int countmatch = 0;
  std::vector<Long64_t> matchingtable;
  for(Long64_t j = 0; j<entries; j++)
    {
      if(j % 100 == 0) { xjjc::progressbar(j, entries); }

      hiroot->GetEntry(j); //
      Long64_t k = 0;
      for(; k < nhlt; k++)
        {
          if(hlt_Event[k]==evt && hlt_LumiBlock[k]==lumi && hlt_Run[k]==run)
            { break; }
        }
      if(k>=nhlt) { k = -1; }
      matchingtable.push_back(k);
      if(k>=0) { countmatch++; }
    }
  std::cout<<std::endl;
  std::cout<<"countmatch = "<<countmatch<<std::endl;

  std::cout<<"---- Writing to tree"<<std::endl;
  for(Long64_t j = 0; j<entries; j++)
    {
      if(j % 100 == 0) { xjjc::progressbar(j, entries); }
      Long64_t k = matchingtable[j];
      if(k<0) continue;
      hiroot->GetEntry(j); //
      trackTree->GetEntry(j); //
      hlt->GetEntry(k); //

      dhiEvtAnalyzer->cd();
      new_hiroot->Fill();
      dppTrack->cd();
      new_trackTree->Fill();
      dhltbitanalysis->cd();
      new_hlt->Fill();
    }
  std::cout<<std::endl;

  outf->Write();
  std::cout<<"---- Writing tree done"<<std::endl;
  outf->Close();
  std::cout<<outfile<<std::endl;

  return 0;
}

int main(int argc, char* argv[])
{
  if(argc==4) { return evtmatching(argv[1], argv[2], argv[3]); }
  if(argc==5) { return evtmatching(argv[1], argv[2], argv[3], atoi(argv[4])); }
  return 1;
}

