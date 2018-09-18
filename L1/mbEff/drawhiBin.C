#include "adcEffcent.h"

void drawhiBin(TString inputname, TString tag="2017 XeXe MinBias")
{
  xjjroot::setgstyle(1);
  gStyle->SetLineWidth(2);

  TString tagname(tag);
  tagname.ReplaceAll(' ','_');
  tagname.ReplaceAll('(','_');
  tagname.ReplaceAll(')','_');

  TFile* inf = new TFile(inputname.Data());

  TH2F* hempty = new TH2F("hempty", ";hiBin;hiHF", 200, 0, 200, 10, 5, 5000);
  xjjroot::sethempty(hempty);

  TH1F* hhiHF = (TH1F*)inf->Get("hhiHF");
  TH1F* hhiBincal = (TH1F*)inf->Get("hhiBincal");
  hhiBincal->SetMinimum(0);
  hhiBincal->SetMaximum(hhiBincal->GetMaximum()*1.2);
  TH1F* hhiBin = (TH1F*)inf->Get("hhiBin");
  hhiBin->SetMinimum(0);
  hhiBin->SetMaximum(hhiBincal->GetMaximum());
  TH2F* hhiHFvshiBin = (TH2F*)inf->Get("hhiHFvshiBin");
  TGraph* grhiHFvshiBin = (TGraph*)inf->Get("grhiHFvshiBin");
  std::vector<TH1F*> hhiBincalcent(nhiBins), hhiHFcent(nhiBins);
  for(int k=0;k<nhiBins;k++) 
    {
      hhiBincalcent[nhiBins-1-k] = (TH1F*)inf->Get(Form("hhiBincalcent%d",nhiBins-1-k));
      hhiHFcent[nhiBins-1-k] = (TH1F*)inf->Get(Form("hhiHFcent%d",nhiBins-1-k));
      xjjroot::setthgrstyle(hhiBincalcent[nhiBins-1-k], -1, -1, -1, 0, 0, 0, xjjroot::colorlist_middle[k]);
      xjjroot::setthgrstyle(hhiHFcent[nhiBins-1-k], -1, -1, -1, 0, 0, 0, xjjroot::colorlist_middle[k]);
    }

  xjjroot::sethempty(hhiHF);
  xjjroot::sethempty(hhiBin);
  xjjroot::sethempty(hhiBincal);
  xjjroot::sethempty(hhiHFvshiBin);
  xjjroot::setthgrstyle(hhiHF, kBlack, 21, 0.5, kBlack, 1, 2);
  xjjroot::setthgrstyle(hhiBin, kBlack, 21, 0.5, kBlack, 1, 2);
  xjjroot::setthgrstyle(hhiBincal, kBlack, 21, 0.5, kBlack, 1, 2);
  xjjroot::setthgrstyle(grhiHFvshiBin, kRed-3, 21, 0.5, kRed-3, 1, 3);

  TCanvas* chiHF = new TCanvas("chiHF", "", 800, 600);
  chiHF->SetLogy();
  TLegend* leghiHF = new TLegend(0.50, 0.68, 0.95, 0.86);
  xjjroot::setleg(leghiHF, 0.038);
  leghiHF->SetNColumns(2);
  hhiHF->Draw("hist e");
  for(int k=0;k<nhiBins;k++) { hhiHFcent[k]->Draw("hist same"); leghiHF->AddEntry(hhiHFcent[k], Form("Cent. %.0f-%.0f%s", hiBins[k]/2., hiBins[k+1]/2., "%"), "f");}
  hhiHF->Draw("hist e same");
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "No event selection", 0.04, 12, 62);
  leghiHF->Draw();
  gPad->RedrawAxis();
  chiHF->SaveAs(Form("plots/chiHF_%s.pdf",tagname.Data()));

  TCanvas* chiBin = new TCanvas("chiBin", "", 800, 600);
  hhiBin->Draw("hist e");
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "No event selection", 0.04, 12, 62);
  gPad->RedrawAxis();
  chiBin->SaveAs(Form("plots/chiBin_%s.pdf",tagname.Data()));

  TCanvas* chiBincal = new TCanvas("chiBincal", "", 800, 600);
  hhiBincal->Draw("hist e");
  for(int k=0;k<nhiBins;k++) { hhiBincalcent[k]->Draw("hist same"); }
  hhiBincal->Draw("hist e same");
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "No event selection", 0.04, 12, 62);
  gPad->RedrawAxis();
  chiBincal->SaveAs(Form("plots/chiBincal_%s.pdf",tagname.Data()));

  // std::ifstream getdata("hfedges.list");
  // std::vector<float> vhiBincal(200), vhiHF(200); 
  // for(int k=0;k<200;k++) { vhiBincal[k] = k; getdata>>vhiHF[k]; }
  // TGraph* grhiBintable;
  // if(tag.Contains("XeXe")) 
  //   { 
  //     grhiBintable = new TGraph(200, vhiBincal.data(), vhiHF.data()); 
  //     grhiBintable->SetName("grhiBintable"); 
  //     xjjroot::setthgrstyle(grhiBintable, kAzure-3, 21, 0.5, kAzure-3, 1, 2);
  //   }
  TCanvas* chiHFvshiBin = new TCanvas("chiHFvshiBin", "", 600, 600);
  chiHFvshiBin->SetLogy();
  hempty->Draw();
  hhiHFvshiBin->Draw("same");
  grhiHFvshiBin->Draw("l same");
  // if(tag.Contains("XeXe")) { grhiBintable->Draw("l same"); }
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "No event selection", 0.04, 12, 62);
  chiHFvshiBin->SaveAs(Form("plots/chiHFvshiBin_%s.pdf",tagname.Data()));
}

int main(int argc, char* argv[])
{
  if(argc==3) { drawhiBin(argv[1], argv[2]); return 0; }
  return 1;
}
