#include "adcVstowerE.h"

void drawtowerE(TString inputname, TString tag="2018 low PU pp")
{
  xjjroot::setgstyle(1);
  gStyle->SetLineWidth(2);

  TString tagname(tag);
  tagname.ReplaceAll(' ','_');

  TFile* inf = new TFile(inputname.Data());

  TH1F* hEff = (TH1F*)inf->Get("hEff");
  xjjroot::sethempty(hEff);
  xjjroot::setthgrstyle(hEff, kAzure-3, 25, 1.2, kAzure-3);
  hEff->SetMaximum(1.2);
  TH1F* hEffsumls = (TH1F*)inf->Get("hEffsumls");
  xjjroot::sethempty(hEffsumls);
  xjjroot::setthgrstyle(hEffsumls, kRed-3, 25, 1.2, kRed-3);
  TCanvas* chEff = new TCanvas("chEff", "", 600, 600);
  hEff->Draw("ep");
  hEffsumls->Draw("ep same");
  for(int k=0;k<nFGthre;k++) { xjjroot::drawline(FGthre[k], 0, FGthre[k], 1.2, kGray, 2, 2); }
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "ZeroBias (no evt sel)", 0.04, 12, 62);
  TLegend* legEff = new TLegend(0.20, 0.20, 0.55, 0.20+2*0.045);
  xjjroot::setleg(legEff);
  legEff->AddEntry(hEff, "max{{long},{short}} > thre", "pl");
  legEff->AddEntry(hEffsumls, "max{#Sigmalong,#Sigmashort} > thre", "pl");
  legEff->Draw();
  chEff->SaveAs(Form("plots/chEff_%s.pdf",tagname.Data()));  

  TH1F* hEffEvtsel = (TH1F*)inf->Get("hEffEvtsel");
  xjjroot::sethempty(hEffEvtsel);
  xjjroot::setthgrstyle(hEffEvtsel, kAzure-3, 25, 1.2, kAzure-3);
  hEffEvtsel->SetMaximum(1.2);
  TH1F* hEffEvtselsumls = (TH1F*)inf->Get("hEffEvtselsumls");
  xjjroot::sethempty(hEffEvtselsumls);
  xjjroot::setthgrstyle(hEffEvtselsumls, kRed-3, 25, 1.2, kRed-3);
  TCanvas* chEffEvtsel = new TCanvas("chEffEvtsel", "", 600, 600);
  hEffEvtsel->Draw("ep");
  hEffEvtselsumls->Draw("ep same");
  for(int k=0;k<nFGthre;k++) { xjjroot::drawline(FGthre[k], 0, FGthre[k], 1.2, kGray, 2, 2); }
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "ZeroBias (single trk event)", 0.04, 12, 62);
  TLegend* legEffEvtsel = new TLegend(0.20, 0.20, 0.55, 0.20+2*0.045);
  xjjroot::setleg(legEffEvtsel);
  legEffEvtsel->AddEntry(hEffEvtsel, "max{{long},{short}} > thre", "pl");
  legEffEvtsel->AddEntry(hEffEvtselsumls, "max{#Sigmalong,#Sigmashort} > thre", "pl");
  legEffEvtsel->Draw();
  chEffEvtsel->SaveAs(Form("plots/chEffEvtsel_%s.pdf",tagname.Data()));  
  // TH2F* hemptyzoomhEff = new TH2F("hemptyzoomhEff","",10, 10, 20, 100, 0, 60);
  // xjjroot::sethempty(hemptyzoomhEff);
  // hemptyzoomhEff->GetXaxis()->SetNdivisions(505);
  // hemptyzoomhEff->GetYaxis()->SetNdivisions(50506);
  // hemptyzoomhEff->GetXaxis()->SetLabelSize(0.12);
  // hemptyzoomhEff->GetYaxis()->SetLabelSize(0.12);

  TH2F* hcorrmaxAdc_maxAdcsum = (TH2F*)inf->Get("hcorrmaxAdc_maxAdcsum");
  xjjroot::sethempty(hcorrmaxAdc_maxAdcsum);
  TCanvas* chcorrmaxAdc_maxAdcsum = new TCanvas("hcorrmaxAdc_maxAdcsum", "", 600, 600);
  hcorrmaxAdc_maxAdcsum->Draw();
  for(int k=0;k<nFGthre;k++)
    {
      xjjroot::drawline(FGthre[k], 0, FGthre[k], 40, xjjroot::colorlist_light[k], 2, 2);
      xjjroot::drawline(0, FGthre[k], 40, FGthre[k], xjjroot::colorlist_light[k], 2, 2);
    }
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "ZeroBias (no evt sel)", 0.04, 12, 62);
  chcorrmaxAdc_maxAdcsum->SaveAs(Form("plots/chcorrmaxAdc_maxAdcsum_%s.pdf",tagname.Data()));
  
  TH1F* hAdcmax = (TH1F*)inf->Get("hAdcmax");
  hAdcmax->Sumw2();
  xjjroot::setthgrstyle(hAdcmax, -1, -1, -1, kRed-3, -1, 2);
  xjjroot::sethempty(hAdcmax);
  TCanvas* cadcmax = new TCanvas("cadcmax", "", 600, 600);
  hAdcmax->Draw("histe");
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  cadcmax->SaveAs(Form("plots/cadcmax_%s.pdf",tagname.Data()));

  TH1F* hEtlead[nFGthre];
  TH1F* hEtleadsum[nFGthre];
  for(int k=0;k<nFGthre;k++)
    {
      hEtlead[k] = (TH1F*)inf->Get(Form("hEtlead%d",k));
      hEtlead[k]->Sumw2();
      xjjroot::setthgrstyle(hEtlead[k], -1, -1, -1, xjjroot::colorlist_dark[k], -1, 3, xjjroot::colorlist_light[k]);
      hEtleadsum[k] = (TH1F*)inf->Get(Form("hEtleadsum%d",k));
      hEtleadsum[k]->Sumw2();
      xjjroot::setthgrstyle(hEtleadsum[k], -1, -1, -1, xjjroot::colorlist_dark[k], -1, 3, xjjroot::colorlist_light[k]);
    }
  xjjroot::sethempty(hEtlead[0]);
  xjjroot::sethempty(hEtleadsum[0]);
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

  TCanvas* cEtleadsum = new TCanvas("cEtleadsum", "", 600, 600);
  hEtleadsum[0]->Draw("histe");
  for(int k=1;k<nFGthre;k++) { hEtleadsum[k]->Draw("same histe"); }
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  leg->Draw();
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.82, 0.84, "ZeroBias +", 0.04, 32, 62);
  cEtleadsum->SaveAs(Form("plots/chEtleadsum_%s.pdf",tagname.Data()));
  cEtleadsum->SetLogy();
  cEtleadsum->SetLogx();
  hEtleadsum[0]->Draw("histe");
  for(int k=1;k<nFGthre;k++) { hEtleadsum[k]->Draw("same histe"); }
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  leglog->Draw();
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.82, 0.49, "ZeroBias +", 0.04, 32, 62);
  cEtleadsum->SaveAs(Form("plots/chEtleadsumlog_%s.pdf",tagname.Data()));

}

int main(int argc, char* argv[])
{
  if(argc==3) { drawtowerE(argv[1], argv[2]); return 0; }
  return 1;
}
