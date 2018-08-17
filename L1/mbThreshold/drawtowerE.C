#include "adcVstowerE.h"

void drawtowerE(TString inputname, TString tag="2018 low PU pp")
{
  xjjroot::setgstyle(1);
  gStyle->SetLineWidth(2);

  TString tagname(tag);
  tagname.ReplaceAll(' ','_');

  TFile* inf = new TFile(inputname.Data());
  TH1F* hEtlead[nFGthre];
  TH1F* hEtlead_ADCtower[nFGthre];
  TH1F* hEt[nFGthre];
  for(int k=0;k<nFGthre;k++)
    {
      hEtlead[k] = (TH1F*)inf->Get(Form("hEtlead%d",k));
      hEtlead[k]->Sumw2();
      hEtlead[k]->SetLineColor(xjjroot::colorlist_dark[k]);
      hEtlead[k]->SetFillColor(xjjroot::colorlist_light[k]);
      hEtlead[k]->SetLineWidth(3);

      hEtlead_ADCtower[k] = (TH1F*)inf->Get(Form("hEtlead_ADCtower%d",k));
      hEtlead_ADCtower[k]->Sumw2();
      hEtlead_ADCtower[k]->SetLineColor(xjjroot::colorlist_dark[k]);
      hEtlead_ADCtower[k]->SetFillColor(xjjroot::colorlist_light[k]);
      hEtlead_ADCtower[k]->SetLineWidth(3);

      hEt[k] = (TH1F*)inf->Get(Form("hEt%d",k));
      hEt[k]->Sumw2();
      hEt[k]->SetLineColor(xjjroot::colorlist_dark[k]);
      hEt[k]->SetFillColor(xjjroot::colorlist_light[k]);
      hEt[k]->SetLineWidth(3);
    }
  // TH1F* htowerE = (TH1F*)inf->Get("htowerE");
  // htowerE->Sumw2();
  // htowerE->SetLineColor(kRed-3);
  // htowerE->SetLineWidth(3);
  
  TH1F* hAdc = (TH1F*)inf->Get("hAdc");
  hAdc->Sumw2();
  xjjroot::sethempty(hAdc);
  hAdc->SetLineWidth(2);
  hAdc->SetLineColor(kBlack);
  TH1F* hAdcmax = (TH1F*)inf->Get("hAdcmax");
  hAdcmax->Sumw2();
  hAdcmax->SetLineWidth(2);
  hAdcmax->SetLineColor(kRed-3);

  xjjroot::sethempty(hEtlead[0]);
  xjjroot::sethempty(hEtlead_ADCtower[0]);
  xjjroot::sethempty(hEt[0]);
  // xjjroot::sethempty(htowerE);
  xjjroot::sethempty(hAdcmax);
  TLegend* leg = new TLegend(0.57, 0.80-0.054*nFGthre, 0.92, 0.80);
  xjjroot::setleg(leg);
  for(int k=0;k<nFGthre;k++)
    { leg->AddEntry(hEtlead[k], Form("ADC > %d",FGthre[k])); }
  TLegend* leglog = new TLegend(0.57, 0.45-0.054*nFGthre, 0.92, 0.45);
  xjjroot::setleg(leglog);
  for(int k=0;k<nFGthre;k++)
    { leglog->AddEntry(hEtlead[k], Form("ADC > %d",FGthre[k])); }

  TCanvas* c = new TCanvas("c", "", 600, 600);
  hEtlead[0]->Draw("histe");
  for(int k=1;k<nFGthre;k++) { hEtlead[k]->Draw("same histe"); }
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  leg->Draw();
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.82, 0.84, "ZeroBias +", 0.04, 32, 62);
  c->SaveAs(Form("plots/chEtlead_%s.pdf",tagname.Data()));
  c->SetLogy();
  c->SetLogx();
  hEtlead[0]->Draw("histe");
  for(int k=1;k<nFGthre;k++) { hEtlead[k]->Draw("same histe"); }
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  leglog->Draw();
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.82, 0.49, "ZeroBias +", 0.04, 32, 62);
  c->SaveAs(Form("plots/chEtleadlog_%s.pdf",tagname.Data()));

  TCanvas* cEtAdctower = new TCanvas("cEtAdctower", "", 600, 600);
  hEtlead_ADCtower[0]->Draw("histe");
  for(int k=1;k<nFGthre;k++) { hEtlead_ADCtower[k]->Draw("same histe"); }
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  leg->Draw();
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.82, 0.84, "ZeroBias +", 0.04, 32, 62);
  cEtAdctower->SaveAs(Form("plots/chEtlead_ADCtower_%s.pdf",tagname.Data()));
  cEtAdctower->SetLogy();
  cEtAdctower->SetLogx();
  hEtlead_ADCtower[0]->Draw("histe");
  for(int k=1;k<nFGthre;k++) { hEtlead_ADCtower[k]->Draw("same histe"); }
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  leglog->Draw();
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.82, 0.49, "ZeroBias +", 0.04, 32, 62);
  cEtAdctower->SaveAs(Form("plots/chEtlead_ADCtowerlog_%s.pdf",tagname.Data()));

  // TCanvas* ctower = new TCanvas("ctower", "", 600, 600);
  // ctower->SetLogy();
  // htowerE->Draw("histe");
  // gPad->RedrawAxis();
  // xjjroot::drawCMS("", "", 0, 0, false);
  // xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  // ctower->SaveAs(Form("plots/chtowerE_%s.pdf",tagname.Data()));

  TCanvas* cadcmax = new TCanvas("cadcmax", "", 600, 600);
  // cadcmax->SetLogy();
  hAdcmax->Draw("histe");
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  cadcmax->SaveAs(Form("plots/cadcmax_%s.pdf",tagname.Data()));

}

int main(int argc, char* argv[])
{
  if(argc==3) { drawtowerE(argv[1], argv[2]); return 0; }
  return 1;
}
