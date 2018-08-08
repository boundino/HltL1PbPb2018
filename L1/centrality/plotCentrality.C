#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TH2F.h>
#include <TF1.h>
#include "xjjrootuti.h"
#include "centrality.h"

void plotCentrality(TString inputname="output_new.root", TString collsyst = "PbPbMC", TString snn = "snn")
{
  xjjroot::setgstyle(1);
  TFile* inf = new TFile(Form("%s.root",inputname.Data()));

  Bool_t useHFLUTfalse = inputname.Contains("useHFLUTfalse");
  if(useHFLUTfalse) maxL1etsum = 18000;
  if(collsyst=="PbPb") maxL1etsum = 50000;
  nL1etsum = maxL1etsum / 100;

  TH2D* hcorrl1EtsumPlusVscorrl1EtsumMinus = (TH2D*)inf->Get("hcorrl1EtsumPlusVscorrl1EtsumMinus");
  TH2D* hcorrl1EtsumVsofflineCent = (TH2D*)inf->Get("hcorrl1EtsumVsofflineCent");
  TH2D* hcorrofflineCentVsl1Etsum = (TH2D*)inf->Get("hcorrofflineCentVsl1Etsum");
  TH2D* hcorrL1CentVsofflineCent = (TH2D*)inf->Get("hcorrL1CentVsofflineCent");
  TH1D* hofflineCent = (TH1D*)inf->Get("hofflineCent");
  TH1D* hl1Etsum = (TH1D*)inf->Get("hl1Etsum");
  TH1D* hofflineEtsum = (TH1D*)inf->Get("hofflineEtsum");
  TH2D* hcorrOfflineEtsumVsL1Etsum = (TH2D*)inf->Get("hcorrOfflineEtsumVsL1Etsum");
  TProfile* profilel1EtsumVsofflineCent_Calibration = (TProfile*)inf->Get("profilel1EtsumVsofflineCent_Calibration");
  TProfile* profileofflineCentVl1Etsum_Calibration = (TProfile*)inf->Get("profilesofflineCentVl1Etsum_Calibration");

  TCanvas* chcorrl1EtsumVsofflineCent = new TCanvas("chcorrl1EtsumVsofflineCent", "", 600, 600);
  TH2F* hempty = new TH2F("hempty", ";offline centrality;L1 Etsum", 10, 0, 200, 10, 0, maxL1etsum);
  xjjroot::sethempty(hempty, 0, 0.4);
  hempty->Draw();
  hcorrl1EtsumVsofflineCent->Draw("same");
  xjjroot::drawCMS(collsyst, snn);
  chcorrl1EtsumVsofflineCent->SaveAs(Form("plotcent/chcorrl1EtsumVsofflineCent_%s.pdf",inputname.Data()));

  TCanvas* chcorrOfflineEtsumVsL1Etsum = new TCanvas("chcorrOfflineEtsumVsL1Etsum", "", 600, 600);
  TH2F* hemptyEvE = new TH2F("hemptyEvE", ";offline Etsum;L1 Etsum", 10, 0, maxOfflineetsum, 10, 0, maxL1etsum);
  xjjroot::sethempty(hemptyEvE, 0, 0.4);
  hemptyEvE->Draw();
  hcorrOfflineEtsumVsL1Etsum->Draw("same");
  xjjroot::drawCMS(collsyst, snn);
  chcorrOfflineEtsumVsL1Etsum->SaveAs(Form("plotcent/chcorrOfflineEtsumVsL1Etsum_%s.pdf",inputname.Data()));

  TCanvas* cprofilel1EtsumVsofflineCent_Calibration = new TCanvas("cprofilel1EtsumVsofflineCent_Calibration", "", 600, 600);
  cprofilel1EtsumVsofflineCent_Calibration->SetLogy();
  TH2F* hemptyaEvC = new TH2F("hemptyaEvC", ";offline centrality;< L1 Etsum >", 10, 0, 200, 10, 1.e-2, 2.e+5);
  xjjroot::sethempty(hemptyaEvC, 0, 0.4);
  hemptyaEvC->Draw();
  xjjroot::setthgrstyle(profilel1EtsumVsofflineCent_Calibration, kBlack, 25, 1.2, kBlack);
  profilel1EtsumVsofflineCent_Calibration->Draw("same pe");
  TF1* fEvC = new TF1("fEvC","pol5", 0, 200);
  // fEvC->FixParameter(5, 0);
  fEvC->SetParameter(0, 8.13911e+03);
  fEvC->SetParameter(1, -2.82161e+02);
  fEvC->SetParameter(2, 4.06148e+00);
  fEvC->SetParameter(3, -3.01090e-02);
  fEvC->SetParameter(4, 1.14041e-04);
  fEvC->SetParameter(5, 0);
  Float_t fitmax = useHFLUTfalse?170:155;
  profilel1EtsumVsofflineCent_Calibration->Fit("fEvC", "L", "", 0, fitmax);
  profilel1EtsumVsofflineCent_Calibration->Fit("fEvC", "L", "", 0, fitmax);
  profilel1EtsumVsofflineCent_Calibration->Fit("fEvC", "m", "", 0, fitmax);
  xjjroot::drawCMS(collsyst, snn);
  cprofilel1EtsumVsofflineCent_Calibration->SaveAs(Form("plotcent/cprofilel1EtsumVsofflineCent_Calibration_%s.pdf",inputname.Data()));

  // TCanvas* cprofileofflineCentVl1Etsum_Calibration = new TCanvas("cprofileofflineCentVl1Etsum_Calibration", "", 600, 600);
  // // cprofileofflineCentVl1Etsum_Calibration->SetLogy();
  // TH2F* hemptyaCvE = new TH2F("hemptyaCvE", ";< L1 Etsum >;offline centrality", 10, 0, maxL1etsum, 10, 0, 200);
  // xjjroot::sethempty(hemptyaCvE, 0, 0.4);
  // hemptyaCvE->Draw();
  // xjjroot::setthgrstyle(profileofflineCentVl1Etsum_Calibration, kBlack, 25, 1.2, kBlack);
  // profileofflineCentVl1Etsum_Calibration->Draw("same pe");
  // TF1* fCvE = new TF1("fCvE","pol5", -1, maxL1etsum);
  // profileofflineCentVl1Etsum_Calibration->Fit("fCvE", "qL", "", -1, maxL1etsum);
  // profileofflineCentVl1Etsum_Calibration->Fit("fCvE", "qm", "", -1, maxL1etsum);
  // xjjroot::drawCMS(collsyst, snn);
  // cprofileofflineCentVl1Etsum_Calibration->SaveAs(Form("plotcent/cprofileofflineCentVl1Etsum_Calibration_%s.pdf",inputname.Data()));

  std::cout<<"\033[1;32m"<<"std::vector<float> fEvCparam = {";
  for(int p=0; p<6; p++) std::cout<<fEvC->GetParameter(p)<<((p<5)?", ":"};");
  std::cout<<"\033[0m"<<std::endl;
  // std::cout<<"std::vector<float> fCvEparam = {";
  // for(int p=0; p<6; p++) std::cout<<fCvE->GetParameter(p)<<((p<5)?", ":"};");
  // std::cout<<std::endl;

}

int main(int argc, char* argv[])
{
  if(argc==1) { plotCentrality(); return 0; }
  if(argc==4) { plotCentrality(argv[1], argv[2], argv[3]); return 0; }
  return 1;
}
