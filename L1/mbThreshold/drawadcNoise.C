#include "adcVstowerE.h"

void drawadcNoise(TString inputname, TString tag="2018 low PU pp")
{
  xjjroot::setgstyle(1);
  gStyle->SetLineWidth(2);

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

  xjjroot::sethempty(hAdc_zb);

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
  cadc->SaveAs("plots/cAdcNoise.pdf");
}

int main(int argc, char* argv[])
{
  if(argc==3) { drawadcNoise(argv[1], argv[2]); return 0; }
  return 1;
}
