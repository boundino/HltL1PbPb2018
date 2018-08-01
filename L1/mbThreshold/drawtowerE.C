#include "adcVstowerE.h"

void drawtowerE(TString inputname, TString tag="2018 low PU pp")
{
  xjjroot::setgstyle(1);
  gStyle->SetLineWidth(2);

  TFile* inf = new TFile(inputname.Data());
  TH1F* hEtlead[nFGthre];
  for(int k=0;k<nFGthre;k++)
    {
      hEtlead[k] = (TH1F*)inf->Get(Form("hEtlead%d",k));
      hEtlead[k]->Sumw2();
      // hEtlead[k]->SetLineColor(kBlack);
      // hEtlead[k]->SetFillColor(colorlist_light[k]);
      // hEtlead[k]->SetLineStyle(2);
      hEtlead[k]->SetLineColor(colorlist_middle[k]);
      hEtlead[k]->SetLineWidth(3);
    }
  TH1F* htowerE = (TH1F*)inf->Get("htowerE");
  htowerE->Sumw2();
  htowerE->SetLineColor(kRed-3);
  htowerE->SetLineWidth(3);
  
  TH1F* hAdc = (TH1F*)inf->Get("hAdc");
  hAdc->Sumw2();
  xjjroot::sethempty(hAdc);
  hAdc->SetLineWidth(2);
  hAdc->SetLineColor(kBlack);
  TH1F* hAdclead = (TH1F*)inf->Get("hAdclead");
  hAdclead->Sumw2();
  hAdclead->SetLineWidth(2);
  hAdclead->SetLineColor(kRed-3);

  xjjroot::sethempty(hEtlead[0]);
  xjjroot::sethempty(htowerE);
  xjjroot::sethempty(hAdclead);
  TLegend* leg = new TLegend(0.50, 0.63, 0.90, 0.85);
  xjjroot::setleg(leg);
  for(int k=0;k<nFGthre;k++)
    { leg->AddEntry(hEtlead[k], Form("ADC >= %d",FGthre[k])); }
  TLegend* leglog = new TLegend(0.52, 0.23, 0.92, 0.45);
  xjjroot::setleg(leglog);
  for(int k=0;k<nFGthre;k++)
    { leglog->AddEntry(hEtlead[k], Form("ADC >= %d",FGthre[k])); }

  TCanvas* c = new TCanvas("c", "", 600, 600);
  hEtlead[0]->Draw("histe");
  for(int k=1;k<nFGthre;k++) { hEtlead[k]->Draw("same histe"); }
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  leg->Draw();
  xjjroot::drawtex(0.54, 0.55, tag.Data());
  c->SaveAs("plots/chEtlead.pdf");
  c->SetLogy();
  c->SetLogx();
  hEtlead[0]->Draw("histe");
  for(int k=1;k<nFGthre;k++) { hEtlead[k]->Draw("same histe"); }
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  leglog->Draw();
  xjjroot::drawtex(0.54, 0.55, tag.Data());
  c->SaveAs("plots/chEtlead_log.pdf");

  TCanvas* ctower = new TCanvas("ctower", "", 600, 600);
  ctower->SetLogy();
  htowerE->Draw("histe");
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.54, 0.55, tag.Data());
  ctower->SaveAs("plots/chtowerE.pdf");

  TCanvas* cadclead = new TCanvas("cadclead", "", 600, 600);
  // cadclead->SetLogy();
  hAdclead->Draw("histe");
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.54, 0.55, tag.Data());
  cadclead->SaveAs("plots/cadclead.pdf");

}

int main(int argc, char* argv[])
{
  if(argc==3) { drawtowerE(argv[1], argv[2]); return 0; }
  return 1;
}
