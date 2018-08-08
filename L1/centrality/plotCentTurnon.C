#include "centrality.h"

void plotCentTurnon(TString inputname = "output_new", TString collsyst = "PbPbMC", TString snn = "snn")
{
  xjjroot::setgstyle(1);

  TFile* inf = new TFile(Form("%s.root",inputname.Data()), "");
  TH1F* hPassofflineCent[nlimit];
  TEfficiency* hEffofflineCent[nlimit];
  TH1D* hofflineCent = (TH1D*)inf->Get("hofflineCent");
  for(int l=0;l<nlimit;l++)
    {
      hPassofflineCent[l] = (TH1F*)inf->Get(Form("hPassofflineCent_%d",l));
      hPassofflineCent[l]->SetBinContent(99, hofflineCent->GetBinContent(99));
      hPassofflineCent[l]->SetBinContent(100, hofflineCent->GetBinContent(100));
      hEffofflineCent[l] = new TEfficiency(*(hPassofflineCent[l]), *hofflineCent);
      xjjroot::setthgrstyle(hEffofflineCent[l], ncolor[l], 21, 1.0, ncolor[l], 1, 2);
    }

  TCanvas* c = new TCanvas("c", "", 600, 600);
  TH2F* hempty = new TH2F("hempty", ";Offline hiBin;Efficiency", 10, 0, 200, 10, 0, 1.3);
  xjjroot::sethempty(hempty, 0., 0.3);
  hempty->Draw();
  for(int l=0;l<nlimit;l++)
    xjjroot::drawline(limitsLow[l], 0, limitsLow[l], 1.3, kGray, 10, 2);
  TLegend* leg = new TLegend(0.3, 0.88-2*0.045, 0.90, 0.88);
  xjjroot::setleg(leg, 0.03);
  leg->SetNColumns(3);
  for(int l=0;l<nlimit;l++)
    {
      hEffofflineCent[l]->Draw("same e");
      leg->AddEntry(hEffofflineCent[l], Form("Cent%.0f-%.0f", limitsLow[l]/2., limitsHigh[l]/2.), "l");
    }
  leg->Draw();
  xjjroot::drawCMS(collsyst, snn);

  c->SaveAs(Form("plotcent/cTurnOn_%s.pdf",inputname.Data()));
  
}

int main(int argc, char* argv[])
{
  if(argc==1) { plotCentTurnon(); return 0; }
  if(argc==4) { plotCentTurnon(argv[1], argv[2], argv[3]); return 0; }
  return 1;
}
