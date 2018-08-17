#include "adcVstowerE.h"

void drawadcNoise(TString inputname, TString tag="2018 low PU pp")
{
  xjjroot::setgstyle(1);
  gStyle->SetLineWidth(2);

  TString tagname(tag);
  tagname.ReplaceAll(' ','_');

  TFile* inf = new TFile(inputname.Data());
  
  TH1F* hAdc_zb = (TH1F*)inf->Get("hAdc_zb");
  hAdc_zb->Sumw2();
  xjjroot::sethempty(hAdc_zb);
  hAdc_zb->SetLineWidth(2);
  hAdc_zb->SetLineColor(kBlack);
  TH1F* hAdc_eb = (TH1F*)inf->Get("hAdc_eb");
  hAdc_eb->Sumw2();
  xjjroot::sethempty(hAdc_eb);
  hAdc_eb->SetLineWidth(2);
  hAdc_eb->SetLineColor(kRed-3);

  TH1F* hAdcmax_zb = (TH1F*)inf->Get("hAdcmax_zb");
  hAdcmax_zb->Sumw2();
  xjjroot::sethempty(hAdcmax_zb);
  hAdcmax_zb->SetLineWidth(3);
  hAdcmax_zb->SetLineColor(kBlack);
  TH1F* hAdcmax_eb = (TH1F*)inf->Get("hAdcmax_eb");
  hAdcmax_eb->Sumw2();
  xjjroot::sethempty(hAdcmax_eb);
  hAdcmax_eb->SetLineWidth(2);
  hAdcmax_eb->SetLineColor(kRed-3);

  TH1F* hAdcmax_zb_thre[nFGthre];
  for(int k=0;k<nFGthre;k++)
    {
      hAdcmax_zb_thre[k] = (TH1F*)hAdcmax_zb->Clone(Form("hAdcmax_zb_thre%d",k));
      hAdcmax_zb_thre[k]->SetLineWidth(0);
      hAdcmax_zb_thre[k]->SetLineColor(xjjroot::colorlist_light[k]);
      hAdcmax_zb_thre[k]->SetFillColor(xjjroot::colorlist_light[k]);
      for(int j=0;j<50;j++) { if(j<=FGthre[k]) { hAdcmax_zb_thre[k]->SetBinContent(j+1, 0); hAdcmax_zb_thre[k]->SetBinError(j+1, 0); }}
    }

  TCanvas* cadc = new TCanvas("cadc", "", 600, 600);
  cadc->SetLogy();
  hAdc_zb->Draw("histe");
  hAdc_eb->Draw("same histe");
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  TLegend* legadc = new TLegend(0.50, 0.69, 0.90, 0.80);
  xjjroot::setleg(legadc);
  legadc->AddEntry(hAdc_zb, "ZeroBias");
  legadc->AddEntry(hAdc_eb, "EmptyBX");
  legadc->Draw();
  cadc->SaveAs(Form("plots/cAdcNoise_%s.pdf",tagname.Data()));

  TCanvas* cadcmax = new TCanvas("cadcmax", "", 600, 600);
  hAdcmax_zb->Draw("histe");
  for(int k=0;k<nFGthre;k++) { hAdcmax_zb_thre[k]->Draw("hist same"); }
  hAdcmax_zb->Draw("histe same");
  // hAdcmax_eb->Draw("same histe");
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
  TLegend* legadcmax = new TLegend(0.50, 0.69, 0.90, 0.80);
  xjjroot::setleg(legadcmax);
  legadcmax->AddEntry(hAdcmax_zb, "ZeroBias");
  // legadcmax->AddEntry(hAdcmax_eb, "EmptyBX");
  legadcmax->Draw();
  cadcmax->SaveAs(Form("plots/cAdcmaxNoise_%s.pdf",tagname.Data()));
}

int main(int argc, char* argv[])
{
  if(argc==3) { drawadcNoise(argv[1], argv[2]); return 0; }
  return 1;
}
