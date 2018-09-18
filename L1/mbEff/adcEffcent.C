#include "adcEffcent.h"
#define MAXTRACKS 60000
#define MAXVTX 100

void adcEffcent(TString inputname, TString outputname, int nevt = -1, bool iftrk = true, int ifskim = 0)
{
  TFile* inf = new TFile(inputname.Data());
  TTree* l1Adc = (TTree*)inf->Get("HFAdcana/adc");
  TTree* hiroot = (TTree*)inf->Get("hiEvtAnalyzer/HiTree");
  TTree* trktree = (TTree*)inf->Get("ppTrack/trackTree");
  TTree* skimtree = (TTree*)inf->Get("skimanalysis/HltTree");

  std::cout<<inputname.Contains("XeXe")<<std::endl;
  std::vector<float> hiHFs = inputname.Contains("XeXe")?hiHFs_XeXe:hiHFs_PbPbMC;
  std::vector<float> vhiHFs;
  vhiHFs.push_back(hiHFs[0]);
  for(int k=1;k<nhiBins+1;k++) { vhiHFs.push_back(hiHFs[hiBins[k]-1]); }

  //
  std::vector<int>* ampl = 0; l1Adc->SetBranchAddress("ampl", &ampl);
  std::vector<int>* ieta = 0; l1Adc->SetBranchAddress("ieta", &ieta);
  std::vector<int>* iphi = 0; l1Adc->SetBranchAddress("iphi", &iphi);
  std::vector<int>* depth = 0; l1Adc->SetBranchAddress("depth", &depth);

  int nTrk; if(iftrk) { trktree->SetBranchAddress("nTrk", &nTrk); }
  bool highPurity[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("highPurity", highPurity); }
  float trkEta[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkEta", trkEta); }
  float trkPtError[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkPtError", trkPtError); }
  float trkPt[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkPt", trkPt); }
  float trkDz1[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkDz1", trkDz1); }
  float trkDzError1[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkDzError1", trkDzError1); }
  float trkDxy1[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkDxy1", trkDxy1); }
  float trkDxyError1[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkDxyError1", trkDxyError1); }
  float trkChi2[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkChi2", trkChi2); }
  unsigned char trkNdof[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkNdof", trkNdof); }
  unsigned char trkNHit[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkNHit", trkNHit); }
  unsigned char trkNlayer[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkNlayer", trkNlayer); }
  unsigned char trkAlgo[MAXTRACKS]; if(iftrk) { trktree->SetBranchAddress("trkAlgo", trkAlgo); }

  int hiBin; hiroot->SetBranchAddress("hiBin", &hiBin);
  float hiHF; hiroot->SetBranchAddress("hiHF", &hiHF);

  int pprimaryVertexFilter; if(ifskim) { skimtree->SetBranchAddress((ifskim==1?"pPAprimaryVertexFilter":"pprimaryVertexFilter"), &pprimaryVertexFilter); }
  int pclusterCompatibilityFilter; if(ifskim) { skimtree->SetBranchAddress("pclusterCompatibilityFilter", &pclusterCompatibilityFilter); }
  int phfCoincFilter3; if(ifskim) { skimtree->SetBranchAddress("phfCoincFilter3", &phfCoincFilter3); }
  int pcollisionEventSelection; if(ifskim==3) { skimtree->SetBranchAddress("pcollisionEventSelection", &pcollisionEventSelection); }

  //
  TH1F* hEffnom = new TH1F("hEffnom", ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffnom->Sumw2();
  TH1F* hEffden = new TH1F("hEffden", ";HF threshold (ADC);", 40, 0, 40); hEffden->Sumw2();
  TH1F* hEffEvtselnom = new TH1F("hEffEvtselnom", ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffEvtselnom->Sumw2();
  TH1F* hEffEvtselden = new TH1F("hEffEvtselden", ";HF threshold (ADC);", 40, 0, 40); hEffEvtselden->Sumw2();
  TH1F* hEffEvtfilnom = new TH1F("hEffEvtfilnom", ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffEvtfilnom->Sumw2();
  TH1F* hEffEvtfilden = new TH1F("hEffEvtfilden", ";HF threshold (ADC);", 40, 0, 40); hEffEvtfilden->Sumw2();

  TH1F* hEffAndnom = new TH1F("hEffAndnom", ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffAndnom->Sumw2();
  TH1F* hEffAndden = new TH1F("hEffAndden", ";HF threshold (ADC);", 40, 0, 40); hEffAndden->Sumw2();
  TH1F* hEffAndEvtselnom = new TH1F("hEffAndEvtselnom", ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffAndEvtselnom->Sumw2();
  TH1F* hEffAndEvtselden = new TH1F("hEffAndEvtselden", ";HF threshold (ADC);", 40, 0, 40); hEffAndEvtselden->Sumw2();
  TH1F* hEffAndEvtfilnom = new TH1F("hEffAndEvtfilnom", ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffAndEvtfilnom->Sumw2();
  TH1F* hEffAndEvtfilden = new TH1F("hEffAndEvtfilden", ";HF threshold (ADC);", 40, 0, 40); hEffAndEvtfilden->Sumw2();

  std::vector<TH1F*> hEffnomcent(nhiBins), hEffdencent(nhiBins);
  std::vector<TH1F*> hEffEvtselnomcent(nhiBins), hEffEvtseldencent(nhiBins);
  std::vector<TH1F*> hEffEvtfilnomcent(nhiBins), hEffEvtfildencent(nhiBins);

  std::vector<TH1F*> hEffAndnomcent(nhiBins), hEffAnddencent(nhiBins);
  std::vector<TH1F*> hEffAndEvtselnomcent(nhiBins), hEffAndEvtseldencent(nhiBins);
  std::vector<TH1F*> hEffAndEvtfilnomcent(nhiBins), hEffAndEvtfildencent(nhiBins);
  for(int k=0;k<nhiBins;k++)
    { 
      hEffnomcent[k] = new TH1F(Form("hEffnomcent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffnomcent[k]->Sumw2();
      hEffEvtselnomcent[k] = new TH1F(Form("hEffEvtselnomcent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffEvtselnomcent[k]->Sumw2();
      hEffEvtfilnomcent[k] = new TH1F(Form("hEffEvtfilnomcent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffEvtfilnomcent[k]->Sumw2();
      hEffdencent[k] = new TH1F(Form("hEffdencent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffdencent[k]->Sumw2();
      hEffEvtseldencent[k] = new TH1F(Form("hEffEvtseldencent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffEvtseldencent[k]->Sumw2();
      hEffEvtfildencent[k] = new TH1F(Form("hEffEvtfildencent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffEvtfildencent[k]->Sumw2();

      hEffAndnomcent[k] = new TH1F(Form("hEffAndnomcent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffAndnomcent[k]->Sumw2();
      hEffAndEvtselnomcent[k] = new TH1F(Form("hEffAndEvtselnomcent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffAndEvtselnomcent[k]->Sumw2();
      hEffAndEvtfilnomcent[k] = new TH1F(Form("hEffAndEvtfilnomcent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffAndEvtfilnomcent[k]->Sumw2();
      hEffAnddencent[k] = new TH1F(Form("hEffAnddencent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffAnddencent[k]->Sumw2();
      hEffAndEvtseldencent[k] = new TH1F(Form("hEffAndEvtseldencent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffAndEvtseldencent[k]->Sumw2();
      hEffAndEvtfildencent[k] = new TH1F(Form("hEffAndEvtfildencent%d",k), ";HF threshold (ADC);Efficiency", 40, 0, 40); hEffAndEvtfildencent[k]->Sumw2();
    }

  TH1F* hAdc = new TH1F("hAdc", ";ADC;", 50, 0, 50); hAdc->Sumw2();
  TH1F* hAdcmax = new TH1F("hAdcmax", ";max ADC;", 50, 0, 50); hAdcmax->Sumw2();
  TH1F* hAdcmaxEvtsel = new TH1F("hAdcmaxEvtsel", ";max ADC;", 50, 0, 50); hAdcmax->Sumw2();
  TH1F* hAdcmaxEvtfil = new TH1F("hAdcmaxEvtfil", ";max ADC;", 50, 0, 50); hAdcmax->Sumw2();
  std::vector<TH1F*> hAdcmaxcent(nhiBins);
  std::vector<TH1F*> hAdcmaxEvtselcent(nhiBins);
  std::vector<TH1F*> hAdcmaxEvtfilcent(nhiBins);
  for(int k=0;k<nhiBins;k++)
    { hAdcmaxcent[k] = new TH1F(Form("hAdcmax%d",k), ";max ADC;", 50, 0, 50); hAdcmaxcent[k]->Sumw2(); 
      hAdcmaxEvtselcent[k] = new TH1F(Form("hAdcmaxEvtsel%d",k), ";max ADC;", 50, 0, 50); hAdcmaxEvtselcent[k]->Sumw2(); 
      hAdcmaxEvtfilcent[k] = new TH1F(Form("hAdcmaxEvtfil%d",k), ";max ADC;", 50, 0, 50); hAdcmaxEvtfilcent[k]->Sumw2(); }
  int nentries = nevt>0&&nevt<l1Adc->GetEntries()?nevt:l1Adc->GetEntries();
  for(int i=0;i<nentries;i++)
    {
      if(i%100==0) { xjjc::progressbar(i, nentries); }
      l1Adc->GetEntry(i);
      hiroot->GetEntry(i);
      if(iftrk) { trktree->GetEntry(i); }
      if(ifskim) { skimtree->GetEntry(i); }

      int nampl = ampl->size();
      // std::cout<<nampl<<std::endl;
      int amplmax = 0, amplmax_pos = 0, amplmax_neg = 0;
      for(int l=0;l<nampl;l++)
        {
          if(TMath::Abs((*ieta)[l]) < 29) { /*std::cout<<"warning: hAdcVsGeV saves units not HF: ieta = "<<(*ieta)[l]<<std::endl;*/ continue; }
          if(i%1000==0) { hAdc->Fill((*ampl)[l]); }
          if((*ampl)[l] > amplmax) { amplmax = (*ampl)[l]; } //
          if((*ieta)[l] > 0 && (*ampl)[l] > amplmax_pos) { amplmax_pos = (*ampl)[l]; }
          if((*ieta)[l] < 0 && (*ampl)[l] > amplmax_neg) { amplmax_neg = (*ampl)[l]; }
        }
      hAdcmax->Fill(amplmax);
      bool singletrackfilter = false;
      if(!iftrk) { singletrackfilter = true; }
      else
        {
          for(int t=0;t<nTrk;t++)
            {
              if(highPurity[t] && TMath::Abs(trkPtError[t]/trkPt[t]) < 0.1 && 
                 TMath::Abs(trkDz1[t]/trkDzError1[t]) < 3 && TMath::Abs(trkDxy1[t]/trkDxyError1[t]) < 3 && 
                 TMath::Abs(trkEta[t]) < 2.4 && trkPt[t] > 0.4) { singletrackfilter = true; break; }
            }
        }
      if(singletrackfilter) { hAdcmaxEvtsel->Fill(amplmax); }
      bool pass_pcollisionEventSelection = false;
      if(!ifskim || (ifskim==3 && pcollisionEventSelection) || 
         ((ifskim==1 || ifskim==2) && pprimaryVertexFilter && pclusterCompatibilityFilter && phfCoincFilter3)) 
        { pass_pcollisionEventSelection = true; }
      if(pass_pcollisionEventSelection) { hAdcmaxEvtfil->Fill(amplmax); }
      int k = 0;
      for(k=0;k<nhiBins;k++) { if(hiHF > vhiHFs[k+1]) { break; } }
      for(int j=0;j<40;j++)
        {
          hEffden->Fill(j, 1);
          hEffAndden->Fill(j, 1);
          if(amplmax > j) { hEffnom->Fill(j, 1); }
          if(amplmax_pos > j && amplmax_neg > j) { hEffAndnom->Fill(j, 1); }
          hEffdencent[k]->Fill(j, 1); 
          hEffAnddencent[k]->Fill(j, 1); 
          if(amplmax > j) { hEffnomcent[k]->Fill(j, 1); } 
          if(amplmax_pos > j && amplmax_neg > j) { hEffAndnomcent[k]->Fill(j, 1); } 

          if(pass_pcollisionEventSelection)
            {
              hEffEvtfilden->Fill(j, 1);
              hEffAndEvtfilden->Fill(j, 1);
              if(amplmax > j) { hEffEvtfilnom->Fill(j, 1); }
              if(amplmax_pos > j && amplmax_neg > j) { hEffAndEvtfilnom->Fill(j, 1); }
              hEffEvtfildencent[k]->Fill(j, 1); 
              hEffAndEvtfildencent[k]->Fill(j, 1); 
              if(amplmax > j) { hEffEvtfilnomcent[k]->Fill(j, 1); }               
              if(amplmax_pos > j && amplmax_neg > j) { hEffAndEvtfilnomcent[k]->Fill(j, 1); }               
            }

          if(singletrackfilter)
            {
              hEffEvtselden->Fill(j, 1);
              hEffAndEvtselden->Fill(j, 1);
              if(amplmax > j) { hEffEvtselnom->Fill(j, 1); }
              if(amplmax_pos > j && amplmax_neg > j) { hEffAndEvtselnom->Fill(j, 1); }
              hEffEvtseldencent[k]->Fill(j, 1); 
              hEffAndEvtseldencent[k]->Fill(j, 1); 
              if(amplmax > j) { hEffEvtselnomcent[k]->Fill(j, 1); } 
              if(amplmax_pos > j && amplmax_neg > j) { hEffAndEvtselnomcent[k]->Fill(j, 1); } 
            }
        }
      for(int kk=0;kk<nhiBins;kk++) { hAdcmaxcent[kk]->Fill(amplmax); if(hiHF > vhiHFs[kk+1]) { break; } }
      if(singletrackfilter)
        { for(int kk=0;kk<nhiBins;kk++) { hAdcmaxEvtselcent[kk]->Fill(amplmax); if(hiHF > vhiHFs[kk+1]) { break; } } }
      if(pass_pcollisionEventSelection)
        { for(int kk=0;kk<nhiBins;kk++) { hAdcmaxEvtfilcent[kk]->Fill(amplmax); if(hiHF > vhiHFs[kk+1]) { break; } } }
    }
  xjjc::progressbar_summary(nentries);

  TEfficiency* hEff = new TEfficiency(*hEffnom, *hEffden);
  hEff->SetName("hEff");
  TEfficiency* hEffEvtsel = new TEfficiency(*hEffEvtselnom, *hEffEvtselden);
  hEffEvtsel->SetName("hEffEvtsel");
  TEfficiency* hEffEvtfil = new TEfficiency(*hEffEvtfilnom, *hEffEvtfilden);
  hEffEvtfil->SetName("hEffEvtfil");
  std::vector<TEfficiency*> hEffcent(nhiBins);
  std::vector<TEfficiency*> hEffEvtselcent(nhiBins);
  std::vector<TEfficiency*> hEffEvtfilcent(nhiBins);
  TEfficiency* hEffAnd = new TEfficiency(*hEffAndnom, *hEffAndden);
  hEffAnd->SetName("hEffAnd");
  TEfficiency* hEffAndEvtsel = new TEfficiency(*hEffAndEvtselnom, *hEffAndEvtselden);
  hEffAndEvtsel->SetName("hEffAndEvtsel");
  TEfficiency* hEffAndEvtfil = new TEfficiency(*hEffAndEvtfilnom, *hEffAndEvtfilden);
  hEffAndEvtfil->SetName("hEffAndEvtfil");
  std::vector<TEfficiency*> hEffAndcent(nhiBins);
  std::vector<TEfficiency*> hEffAndEvtselcent(nhiBins);
  std::vector<TEfficiency*> hEffAndEvtfilcent(nhiBins);
  for(int k=0;k<nhiBins;k++)
    { 
      hEffcent[k] = new TEfficiency(*(hEffnomcent[k]), *(hEffdencent[k])); 
      hEffcent[k]->SetName(Form("hEffcent%d", k));
      hEffEvtselcent[k] = new TEfficiency(*(hEffEvtselnomcent[k]), *(hEffEvtseldencent[k])); 
      hEffEvtselcent[k]->SetName(Form("hEffEvtselcent%d", k));
      hEffEvtfilcent[k] = new TEfficiency(*(hEffEvtfilnomcent[k]), *(hEffEvtfildencent[k])); 
      hEffEvtfilcent[k]->SetName(Form("hEffEvtfilcent%d", k));

      hEffAndcent[k] = new TEfficiency(*(hEffAndnomcent[k]), *(hEffAnddencent[k])); 
      hEffAndcent[k]->SetName(Form("hEffAndcent%d", k));
      hEffAndEvtselcent[k] = new TEfficiency(*(hEffAndEvtselnomcent[k]), *(hEffAndEvtseldencent[k])); 
      hEffAndEvtselcent[k]->SetName(Form("hEffAndEvtselcent%d", k));
      hEffAndEvtfilcent[k] = new TEfficiency(*(hEffAndEvtfilnomcent[k]), *(hEffAndEvtfildencent[k])); 
      hEffAndEvtfilcent[k]->SetName(Form("hEffAndEvtfilcent%d", k));
    }

  TFile* output = new TFile(Form("%s.root", outputname.Data()), "recreate");
  hEff->Write();
  hEffEvtsel->Write();
  hEffEvtfil->Write();
  for(int k=0;k<nhiBins;k++) 
    { hEffcent[k]->Write(); hEffEvtselcent[k]->Write(); hEffEvtfilcent[k]->Write(); 
      hAdcmaxcent[k]->Write(); hAdcmaxEvtselcent[k]->Write(); hAdcmaxEvtfilcent[k]->Write(); }
  hEffAnd->Write();
  hEffAndEvtsel->Write();
  hEffAndEvtfil->Write();
  for(int k=0;k<nhiBins;k++) 
    { hEffAndcent[k]->Write(); hEffAndEvtselcent[k]->Write(); hEffAndEvtfilcent[k]->Write(); }
  hAdc->Write();
  hAdcmax->Write();
  hAdcmaxEvtsel->Write();
  hAdcmaxEvtfil->Write();
  output->Close();

}

int main(int argc, char* argv[])
{
  if(argc==3) { adcEffcent(argv[1], argv[2]); return 0;}
  if(argc==4) { adcEffcent(argv[1], argv[2], atoi(argv[3])); return 0;}
  if(argc==5) { adcEffcent(argv[1], argv[2], atoi(argv[3]), atoi(argv[4])); return 0;}
  if(argc==6) { adcEffcent(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5])); return 0;}
  return 1;
}

