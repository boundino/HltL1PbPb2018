#include <vector>

#include <TFile.h>
#include <TH2F.h>
#include <TString.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TLegend.h>
#include <TF1.h>

#include "xjjrootuti.h"

void drawadcToGeV(TString inputname, TString tag="2018 low PU pp")
{
  xjjroot::setgstyle(1);
  gStyle->SetLineWidth(2);

  TString tagname(tag);
  tagname.ReplaceAll(' ','_');

  TFile* inf = new TFile(inputname.Data());
  std::vector<TH2F*> vhist;
  TH2F* hcorr_ADC_Eped = (TH2F*)inf->Get("hcorr_ADC_Eped");
  vhist.push_back(hcorr_ADC_Eped);
  TH2F* hcorr_ADC_Epedplus = (TH2F*)inf->Get("hcorr_ADC_Epedplus");
  vhist.push_back(hcorr_ADC_Epedplus);
  TH2F* hcorr_ADC_Epedminus = (TH2F*)inf->Get("hcorr_ADC_Epedminus");
  vhist.push_back(hcorr_ADC_Epedminus);
  TH2F* hcorr_ADC_E = (TH2F*)inf->Get("hcorr_ADC_E");
  vhist.push_back(hcorr_ADC_E);
  TH2F* hcorr_Eped_E = (TH2F*)inf->Get("hcorr_Eped_E");
  vhist.push_back(hcorr_Eped_E);
  TH2F* hcorr_fCped_Eped = (TH2F*)inf->Get("hcorr_fCped_Eped");
  vhist.push_back(hcorr_fCped_Eped);
  TH2F* hcorrtower_ADC_Eoffline = (TH2F*)inf->Get("hcorrtower_ADC_Eoffline");
  vhist.push_back(hcorrtower_ADC_Eoffline);
  TH2F* hcorrtower_E_Eoffline = (TH2F*)inf->Get("hcorrtower_E_Eoffline");
  vhist.push_back(hcorrtower_E_Eoffline);
  
  TF1* f1 = new TF1("f1", "x*0.5", 0, 30);
  f1->SetLineStyle(2);
  f1->SetLineWidth(3);
  f1->SetLineColor(kAzure-3);
  TF1* f2 = new TF1("f2", "x*0.8", 0, 30);
  f2->SetLineStyle(2);
  f2->SetLineWidth(3);
  f2->SetLineColor(kAzure-3);

  for ( auto& i : vhist )
    {
      int nline = TString(i->GetName()).Contains("ADC")?2:1;
      xjjroot::sethempty(i, 0., 0.);
      TProfile* p = i->ProfileX("_pfx", 0, i->GetNbinsY()+1);
      p->SetLineWidth(3);
      p->SetLineColor(kRed+1);
      TCanvas* c = new TCanvas("c", "", 600, 600);
      // c->SetLogz();
      i->Draw("");
      p->Draw("l same");
      if(nline==2) 
        { 
          f1->Draw("same"); f2->Draw("same"); 
          xjjroot::drawline(15, 0, 15, 20, kOrange+6, 3, 3);
          xjjroot::drawline(12, 0, 12, 20, kOrange+6, 3, 3);
          xjjroot::drawline(17, 0, 17, 20, kOrange+6, 3, 3);
        }
      xjjroot::drawCMS("", "", 0, 0, false);
      xjjroot::drawtex(0.96, 0.93, tag.Data(), 0.04, 32);
      xjjroot::drawtex(0.22, 0.84, "ZeroBias", 0.04, 12, 62);
      TLegend* leg = new TLegend(0.21, 0.79-0.045*nline, 0.55, 0.79);
      xjjroot::setleg(leg);
      leg->AddEntry(p, "ProfileX", "l");
      if(nline==2) { leg->AddEntry(f1, "0.5-0.8 GeV/ADC", "l"); }
      leg->Draw();
      c->SaveAs(std::string("plots/chist_"+tagname+i->GetName()+".pdf").c_str());
      delete leg;
      delete c;
      delete p;
    }
}

int main(int argc, char* argv[])
{
  if(argc==3) { drawadcToGeV(argv[1], argv[2]); return 0; }
  return 1;
}
