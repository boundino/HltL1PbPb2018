#include "adcEffcent.h"

void drawEffcent(TString inputname, TString tag="2017 XeXe MinBias", bool iftrk=false)
{
  xjjroot::setgstyle(1);
  // gStyle->SetLineWidth(2);

  TString tagname(tag);
  tagname.ReplaceAll(' ','_');
  tagname.ReplaceAll('(','_');
  tagname.ReplaceAll(')','_');

  TFile* inf = new TFile(inputname.Data());

  TH2F* hempty = new TH2F("hempty", ";HF threshold (ADC);Efficiency", 10, 0, 40, 10, 0, 1.2);
  xjjroot::sethempty(hempty, 0, 0.04);
  TH2F* hemptyzoom = new TH2F("hemptyzoom", ";HF threshold (ADC);Efficiency", 10, 0, 40, 10, 0.9, 1.02);
  xjjroot::sethempty(hemptyzoom, 0, 0.04);

  // OR
  TEfficiency* hEff = (TEfficiency*)inf->Get("hEff");
  xjjroot::setthgrstyle(hEff, kBlack, 25, 0.9, kBlack);
  std::vector<TEfficiency*> hEffcent(nhiBins);
  for(int k=0;k<nhiBins;k++) { hEffcent[nhiBins-1-k] = (TEfficiency*)inf->Get(Form("hEffcent%d",nhiBins-1-k)); 
    xjjroot::setthgrstyle(hEffcent[nhiBins-1-k], xjjroot::colorlist_middle[k], 25, 1, xjjroot::colorlist_middle[k]); }

  TEfficiency* hEffEvtsel = (TEfficiency*)inf->Get("hEffEvtsel");
  xjjroot::setthgrstyle(hEffEvtsel, kBlack, 25, 0.9, kBlack);
  std::vector<TEfficiency*> hEffEvtselcent(nhiBins);
  for(int k=0;k<nhiBins;k++) { hEffEvtselcent[nhiBins-1-k] = (TEfficiency*)inf->Get(Form("hEffEvtselcent%d",nhiBins-1-k)); 
    xjjroot::setthgrstyle(hEffEvtselcent[nhiBins-1-k], xjjroot::colorlist_middle[k], 25, 1, xjjroot::colorlist_middle[k]); }

  TEfficiency* hEffEvtfil = (TEfficiency*)inf->Get("hEffEvtfil");
  xjjroot::setthgrstyle(hEffEvtfil, kBlack, 25, 0.9, kBlack);
  std::vector<TEfficiency*> hEffEvtfilcent(nhiBins);
  for(int k=0;k<nhiBins;k++) { hEffEvtfilcent[nhiBins-1-k] = (TEfficiency*)inf->Get(Form("hEffEvtfilcent%d",nhiBins-1-k)); 
    xjjroot::setthgrstyle(hEffEvtfilcent[nhiBins-1-k], xjjroot::colorlist_middle[k], 25, 1, xjjroot::colorlist_middle[k]); }

  // AND
  TEfficiency* hEffAnd = (TEfficiency*)inf->Get("hEffAnd");
  xjjroot::setthgrstyle(hEffAnd, kBlack, 21, 0.9, kBlack);
  std::vector<TEfficiency*> hEffAndcent(nhiBins);
  for(int k=0;k<nhiBins;k++) { hEffAndcent[nhiBins-1-k] = (TEfficiency*)inf->Get(Form("hEffAndcent%d",nhiBins-1-k)); 
    xjjroot::setthgrstyle(hEffAndcent[nhiBins-1-k], xjjroot::colorlist_middle[k], 21, 1, xjjroot::colorlist_middle[k]); }

  TEfficiency* hEffAndEvtsel = (TEfficiency*)inf->Get("hEffAndEvtsel");
  xjjroot::setthgrstyle(hEffAndEvtsel, kBlack, 21, 0.9, kBlack);
  std::vector<TEfficiency*> hEffAndEvtselcent(nhiBins);
  for(int k=0;k<nhiBins;k++) { hEffAndEvtselcent[nhiBins-1-k] = (TEfficiency*)inf->Get(Form("hEffAndEvtselcent%d",nhiBins-1-k)); 
    xjjroot::setthgrstyle(hEffAndEvtselcent[nhiBins-1-k], xjjroot::colorlist_middle[k], 21, 1, xjjroot::colorlist_middle[k]); }

  TEfficiency* hEffAndEvtfil = (TEfficiency*)inf->Get("hEffAndEvtfil");
  xjjroot::setthgrstyle(hEffAndEvtfil, kBlack, 21, 0.9, kBlack);
  std::vector<TEfficiency*> hEffAndEvtfilcent(nhiBins);
  for(int k=0;k<nhiBins;k++) { hEffAndEvtfilcent[nhiBins-1-k] = (TEfficiency*)inf->Get(Form("hEffAndEvtfilcent%d",nhiBins-1-k)); 
    xjjroot::setthgrstyle(hEffAndEvtfilcent[nhiBins-1-k], xjjroot::colorlist_middle[k], 21, 1, xjjroot::colorlist_middle[k]); }

  TCanvas* chEff = new TCanvas("chEff", "", 1200, 600);
  chEff->Divide(2, 1);
  chEff->cd(1);
  hempty->Draw();
  hEff->Draw("ep same");
  hEffAnd->Draw("ep same");
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "No event selection", 0.04, 12, 62);
  TLegend* legEff = new TLegend(0.20, 0.20, 0.55, 0.20+0.045*2);
  xjjroot::setleg(legEff);
  legEff->AddEntry(hEffAnd, "AND", "pl");
  legEff->AddEntry(hEff, "OR", "pl");
  legEff->Draw();
  chEff->cd(2);
  hemptyzoom->Draw();
  hEff->Draw("ep same");
  hEffAnd->Draw("ep same");
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "No event selection", 0.04, 12, 62);
  xjjroot::drawtex(0.21, 0.81, "Zoom in", 0.04, 12, 62);
  legEff->Draw();
  chEff->SaveAs(Form("plots/chEff_%s.pdf",tagname.Data()));  

  TCanvas* chEffEvtsel = new TCanvas("chEffEvtsel", "", 1200, 600);
  chEffEvtsel->Divide(2, 1);
  chEffEvtsel->cd(1);
  hempty->Draw();
  hEffEvtsel->Draw("ep same");
  hEffAndEvtsel->Draw("ep same");
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "Single track events", 0.04, 12, 62);
  legEff->Draw();
  chEffEvtsel->cd(2);
  hemptyzoom->Draw();
  hEffEvtsel->Draw("ep same");
  hEffAndEvtsel->Draw("ep same");
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "Single track events", 0.04, 12, 62);
  xjjroot::drawtex(0.21, 0.81, "Zoom in", 0.04, 12, 62);
  legEff->Draw();
  chEffEvtsel->SaveAs(Form("plots/chEffEvtsel_%s.pdf",tagname.Data()));  

  TCanvas* chEffEvtfil = new TCanvas("chEffEvtfil", "", 1200, 600);
  chEffEvtfil->Divide(2, 1);
  chEffEvtfil->cd(1);
  hempty->Draw();
  hEffEvtfil->Draw("ep same");
  hEffAndEvtfil->Draw("ep same");
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "pcollisionEventSelection", 0.04, 12, 62);
  legEff->Draw();
  chEffEvtfil->cd(2);
  hemptyzoom->Draw();
  hEffEvtfil->Draw("ep same");
  hEffAndEvtfil->Draw("ep same");
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "pcollisionEventSelection", 0.04, 12, 62);
  legEff->Draw();
  chEffEvtfil->SaveAs(Form("plots/chEffEvtfil_%s.pdf",tagname.Data()));  

  // CENT
  TLegend* legEffcent = new TLegend(0.20, 0.20, 0.55, 0.20+7*0.045);
  xjjroot::setleg(legEffcent);
  for(int k=0;k<nhiBins;k++) { legEffcent->AddEntry(hEffAndcent[k], Form("%.0f-%.0f%s", hiBins[k]/2., hiBins[k+1]/2., "%"), "pl"); }
  TLegend* legAnd = new TLegend(0.70, 0.82, 0.93, 0.86);
  xjjroot::setleg(legAnd);
  legAnd->SetNColumns(2);
  legAnd->AddEntry(hEffAnd, "AND", "p");
  legAnd->AddEntry(hEff, "OR", "p");

  TCanvas* chEffcent = new TCanvas("chEffcent", "", 1200, 600);
  chEffcent->Divide(2, 1);
  chEffcent->cd(1);
  hempty->Draw();
  for(int k=0;k<nhiBins;k++) { hEffcent[k]->Draw("ep same"); }
  for(int k=0;k<nhiBins;k++) { hEffAndcent[k]->Draw("ep same"); }
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "No event selection", 0.04, 12, 62);
  legEffcent->Draw();
  legAnd->Draw();
  chEffcent->cd(2);
  hemptyzoom->Draw();
  for(int k=0;k<nhiBins;k++) { hEffcent[k]->Draw("ep same"); }
  for(int k=0;k<nhiBins;k++) { hEffAndcent[k]->Draw("ep same"); }
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "No event selection", 0.04, 12, 62);
  xjjroot::drawtex(0.21, 0.81, "Zoom in", 0.04, 12, 62);
  legEffcent->Draw();
  legAnd->Draw();
  chEffcent->SaveAs(Form("plots/chEffcent_%s.pdf",tagname.Data()));  

  TCanvas* chEffEvtselcent = new TCanvas("chEffEvtselcent", "", 1200, 600);
  chEffEvtselcent->Divide(2, 1);
  chEffEvtselcent->cd(1);
  hempty->Draw();
  for(int k=0;k<nhiBins;k++) { hEffEvtselcent[k]->Draw("ep same"); }
  for(int k=0;k<nhiBins;k++) { hEffAndEvtselcent[k]->Draw("ep same"); }
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "Single track events", 0.04, 12, 62);
  legEffcent->Draw();
  legAnd->Draw();
  chEffEvtselcent->cd(2);
  hemptyzoom->Draw();
  for(int k=0;k<nhiBins;k++) { hEffEvtselcent[k]->Draw("ep same"); }
  for(int k=0;k<nhiBins;k++) { hEffAndEvtselcent[k]->Draw("ep same"); }
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "Single track events", 0.04, 12, 62);
  xjjroot::drawtex(0.21, 0.81, "Zoom in", 0.04, 12, 62);
  legEffcent->Draw();
  legAnd->Draw();
  chEffEvtselcent->SaveAs(Form("plots/chEffEvtselcent_%s.pdf",tagname.Data()));  
  
  TCanvas* chEffEvtfilcent = new TCanvas("chEffEvtfilcent", "", 1200, 600);
  chEffEvtfilcent->Divide(2, 1);
  chEffEvtfilcent->cd(1);
  hempty->Draw();
  for(int k=0;k<nhiBins;k++) { hEffEvtfilcent[k]->Draw("ep same"); }
  for(int k=0;k<nhiBins;k++) { hEffAndEvtfilcent[k]->Draw("ep same"); }
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "pcollisionEventSelection", 0.04, 12, 62);
  legEffcent->Draw();
  legAnd->Draw();
  chEffEvtfilcent->cd(2);
  hemptyzoom->Draw();
  for(int k=0;k<nhiBins;k++) { hEffEvtfilcent[k]->Draw("ep same"); }
  for(int k=0;k<nhiBins;k++) { hEffAndEvtfilcent[k]->Draw("ep same"); }
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.21, 0.85, "pcollisionEventSelection", 0.04, 12, 62);
  xjjroot::drawtex(0.21, 0.81, "Zoom in", 0.04, 12, 62);
  legEffcent->Draw();
  legAnd->Draw();
  chEffEvtfilcent->SaveAs(Form("plots/chEffEvtfilcent_%s.pdf",tagname.Data()));  
  
  //
  
  TH1F* hAdcmax = (TH1F*)inf->Get("hAdcmax");
  std::vector<TH1F*> hAdcmaxcent(nhiBins);
  TH1F* hAdcmaxEvtsel = (TH1F*)inf->Get("hAdcmaxEvtsel");
  std::vector<TH1F*> hAdcmaxEvtselcent(nhiBins);
  TH1F* hAdcmaxEvtfil = (TH1F*)inf->Get("hAdcmaxEvtfil");
  std::vector<TH1F*> hAdcmaxEvtfilcent(nhiBins);
  for(int k=0;k<nhiBins;k++)
    {
      hAdcmaxcent[nhiBins-k-1] = (TH1F*)inf->Get(Form("hAdcmax%d",nhiBins-k-1));
      xjjroot::setthgrstyle(hAdcmaxcent[nhiBins-k-1], -1, -1, -1, 0, 0, 0, xjjroot::colorlist_middle[k]);
      hAdcmaxEvtselcent[nhiBins-k-1] = (TH1F*)inf->Get(Form("hAdcmaxEvtsel%d",nhiBins-k-1));
      xjjroot::setthgrstyle(hAdcmaxEvtselcent[nhiBins-k-1], -1, -1, -1, 0, 0, 0, xjjroot::colorlist_middle[k]);
      hAdcmaxEvtfilcent[nhiBins-k-1] = (TH1F*)inf->Get(Form("hAdcmaxEvtfil%d",nhiBins-k-1));
      xjjroot::setthgrstyle(hAdcmaxEvtfilcent[nhiBins-k-1], -1, -1, -1, 0, 0, 0, xjjroot::colorlist_middle[k]);
    }
  xjjroot::setthgrstyle(hAdcmax, -1, -1, -1, kBlack, -1, 3);
  xjjroot::sethempty(hAdcmax);
  xjjroot::setthgrstyle(hAdcmaxEvtsel, -1, -1, -1, kBlack, -1, 3);
  xjjroot::sethempty(hAdcmaxEvtsel);
  xjjroot::setthgrstyle(hAdcmaxEvtfil, -1, -1, -1, kBlack, -1, 3);
  xjjroot::sethempty(hAdcmaxEvtfil);

  TCanvas* cadcmax = new TCanvas("cadcmax", "", 600, 600);
  TLegend* legadcmax = new TLegend(0.20, 0.52, 0.40, 0.87);
  xjjroot::setleg(legadcmax, 0.038);
  hAdcmax->Draw("histe");
  for(int k=0;k<nhiBins;k++) { hAdcmaxcent[k]->Draw("hist same"); legadcmax->AddEntry(hAdcmaxcent[k], Form("%.0f-%.0f%s", hiBins[k]/2., hiBins[k+1]/2., "%"), "f");}
  hAdcmax->Draw("histe same");
  legadcmax->Draw();
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.90, 0.85, "No event selection", 0.04, 32, 62);
  cadcmax->SaveAs(Form("plots/cadcmax_%s.pdf",tagname.Data()));

  TCanvas* cadcmaxevtsel = new TCanvas("cadcmaxevtsel", "", 600, 600);
  hAdcmaxEvtsel->Draw("histe");
  for(int k=0;k<nhiBins;k++) { hAdcmaxEvtselcent[k]->Draw("hist same"); }
  hAdcmaxEvtsel->Draw("histe same");
  legadcmax->Draw();
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.90, 0.85, "Single track events", 0.04, 32, 62);
  cadcmaxevtsel->SaveAs(Form("plots/cadcmaxevtsel_%s.pdf",tagname.Data()));

  TCanvas* cadcmaxevtfil = new TCanvas("cadcmaxevtfil", "", 600, 600);
  hAdcmaxEvtfil->Draw("histe");
  for(int k=0;k<nhiBins;k++) { hAdcmaxEvtfilcent[k]->Draw("hist same"); }
  hAdcmaxEvtfil->Draw("histe same");
  legadcmax->Draw();
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  xjjroot::drawtex(0.96, 0.925, tag.Data(), 0.04, 32);
  xjjroot::drawtex(0.90, 0.85, "pcollisionEventSelection", 0.04, 32, 62);
  cadcmaxevtfil->SaveAs(Form("plots/cadcmaxevtfil_%s.pdf",tagname.Data()));
}

int main(int argc, char* argv[])
{
  if(argc==3) { drawEffcent(argv[1], argv[2]); return 0; }
  if(argc==4) { drawEffcent(argv[1], argv[2], atoi(argv[3])); return 0; }
  return 1;
}
