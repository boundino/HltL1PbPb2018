#include "adcVstowerE.h"

void drawMB(TString inputname, std::vector<TString> tag={"HF12"}, TString output="2018 low PU pp")
{
  xjjroot::setgstyle(1);
  gStyle->SetLineWidth(2);

  std::cout<<tag.size()<<std::endl;

  TString outputname(output);
  outputname.ReplaceAll(' ','_');

  for(int k=0;k<tag.size();k++) { tag[k].ReplaceAll("Run", "Run "); tag[k].ReplaceAll("(", " ("); }

  TFile* inf = new TFile(inputname.Data());
  std::vector<TH1F*> hEtlead(tag.size());
  for(int k=0;k<tag.size();k++)
    {
      hEtlead[k] = (TH1F*)inf->Get(Form("hEtlead%d",k));
      hEtlead[k]->Sumw2();
      hEtlead[k]->Scale(1.*hEtlead[0]->GetBinContent(80)/hEtlead[k]->GetBinContent(80));
      hEtlead[k]->SetLineColor(xjjroot::colorlist_dark[k+1]);
      hEtlead[k]->SetFillColor(xjjroot::colorlist_light[k+1]);
      hEtlead[k]->SetLineWidth(3);
    }

  xjjroot::sethempty(hEtlead[0]);  
  TLegend* leg = new TLegend(0.50, 0.80-0.054*tag.size(), 0.90, 0.80);
  xjjroot::setleg(leg);
  for(int k=0;k<tag.size();k++)
    { leg->AddEntry(hEtlead[k], Form("%s",tag[k].Data())); }
  TLegend* leglog = new TLegend(0.52, 0.45-0.054*tag.size(), 0.92, 0.45);
  xjjroot::setleg(leglog);
  for(int k=0;k<tag.size();k++)
    { leglog->AddEntry(hEtlead[k], Form("%s",tag[k].Data())); }

  TCanvas* c = new TCanvas("c", "", 600, 600);
  hEtlead[0]->Draw("histe");
  for(int k=1;k<tag.size();k++) { hEtlead[k]->Draw("same histe"); }
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  leg->Draw();
  xjjroot::drawtex(0.96, 0.93, output.Data(), 0.04, 32);
  xjjroot::drawtex(0.87, 0.84, "MinimumBias3", 0.04, 32, 62);
  c->SaveAs(Form("plots/cMBhEtlead_%s.pdf",outputname.Data()));
  c->SetLogy();
  c->SetLogx();
  hEtlead[0]->Draw("histe");
  for(int k=1;k<tag.size();k++) { hEtlead[k]->Draw("same histe"); }
  gPad->RedrawAxis();
  xjjroot::drawCMS("", "", 0, 0, false);
  leglog->Draw();
  xjjroot::drawtex(0.96, 0.93, output.Data(), 0.04, 32);
  xjjroot::drawtex(0.87, 0.84, "MinimumBias3", 0.04, 32, 62);
  c->SaveAs(Form("plots/cMBhEtleadlog_%s.pdf",outputname.Data()));
}

int main(int argc, char* argv[])
{
  if(argc>=4) 
    { 
      std::vector<TString> tags;
      for(int i=2;i<argc-1;i++) { tags.push_back(argv[i]); }
      drawMB(argv[1], tags, argv[argc-1]); 
      return 0; 
    }
  return 1;
}
