#include <iostream>
#include <string>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>

#include "dcount.h"
#include "xjjrootuti.h"

void drawdcount(std::string inputname, std::string outputname, int icase)
{
  auto inf = TFile::Open(Form("rootfiles/root_%s_%s.root", inputname.c_str(), case_name[icase].c_str()));
  TH1F* hDpt_HF =(TH1F*)inf->Get("hDpt_HF");
  TH1F* hDpt_MBall =(TH1F*)inf->Get("hDpt_MBall");
  TH1F* hDpt_MBred =(TH1F*)inf->Get("hDpt_MBred");
  TH1F* hDpt_MBfull =(TH1F*)inf->Get("hDpt_MBfull");
  TH1F* hDpt_HF_MBred =(TH1F*)inf->Get("hDpt_HF_MBred");
  TH1F* hDpt_HF_MBfull =(TH1F*)inf->Get("hDpt_HF_MBfull");
  TH1F* hDpt_HF_MBall =(TH1F*)inf->Get("hDpt_HF_MBall");

  hDpt_HF_MBall->SetMaximum(hDpt_HF_MBall->GetMaximum()*5); 
  xjjroot::sethempty(hDpt_HF_MBall);
  hDpt_HF_MBred->SetMaximum(hDpt_HF_MBred->GetMaximum()*5); 
  xjjroot::sethempty(hDpt_HF_MBred);
  hDpt_HF_MBfull->SetMaximum(hDpt_HF_MBfull->GetMaximum()*5); 
  xjjroot::sethempty(hDpt_HF_MBfull);

  xjjroot::setthgrstyle(hDpt_HF, xjjroot::colorlist_dark[0], 21, 0, xjjroot::colorlist_dark[0], 1, 2, xjjroot::colorlist_light[0], 1001);
  xjjroot::setthgrstyle(hDpt_HF_MBall, xjjroot::colorlist_dark[0], 21, 0, xjjroot::colorlist_dark[0], 1, 2, xjjroot::colorlist_light[0], 1001);
  xjjroot::setthgrstyle(hDpt_MBall, xjjroot::colorlist_dark[1], 21, 0, xjjroot::colorlist_dark[1], 1, 2, xjjroot::colorlist_light[1], 1001);
  xjjroot::setthgrstyle(hDpt_HF_MBred, xjjroot::colorlist_dark[0], 21, 0, xjjroot::colorlist_dark[0], 1, 2, xjjroot::colorlist_light[0], 1001);
  xjjroot::setthgrstyle(hDpt_MBred, xjjroot::colorlist_dark[3], 21, 0, xjjroot::colorlist_dark[3], 1, 2, xjjroot::colorlist_light[3], 1001);
  xjjroot::setthgrstyle(hDpt_HF_MBfull, xjjroot::colorlist_dark[0], 21, 0, xjjroot::colorlist_dark[0], 1, 2, xjjroot::colorlist_light[0], 1001);
  xjjroot::setthgrstyle(hDpt_MBfull, xjjroot::colorlist_dark[2], 21, 0, xjjroot::colorlist_dark[2], 1, 2, xjjroot::colorlist_light[2], 1001);
  
  xjjroot::setgstyle(1);

  TCanvas* c_HF_MBall = new TCanvas("c_HF_MBall", "", 600, 600);
  c_HF_MBall->SetLogy();
  hDpt_HF_MBall->Draw("hist e");
  hDpt_HF_MBall->Draw("e same");
  hDpt_MBall->Draw("hist e same");
  hDpt_MBall->Draw("e same");
  xjjroot::drawCMSleft();
  xjjroot::drawCMSright("Embeded MC");
  xjjroot::drawtex(0.20, 0.85, case_desc[icase].c_str(), 0.038, 12, 62);
  TLegend* leg_HF_MBall = new TLegend(0.55, 0.77, 0.87, 0.87);
  xjjroot::setleg(leg_HF_MBall, 0.031);
  leg_HF_MBall->AddEntry(hDpt_HF_MBall, "All MB || HF");
  leg_HF_MBall->AddEntry(hDpt_MBall, "All MB");
  leg_HF_MBall->Draw();
  gPad->RedrawAxis();
  c_HF_MBall->SaveAs(Form("plots/c_%s_%s_HF_MBall.pdf", outputname.c_str(), case_name[icase].c_str()));
  TCanvas* c_HF_MBred = new TCanvas("c_HF_MBred", "", 600, 600);
  c_HF_MBred->SetLogy();
  hDpt_HF_MBred->Draw("hist e");
  hDpt_HF_MBred->Draw("e same");
  hDpt_MBred->Draw("hist e same");
  hDpt_MBred->Draw("e same");
  xjjroot::drawCMSleft();
  xjjroot::drawCMSright("Embeded MC");
  xjjroot::drawtex(0.20, 0.85, case_desc[icase].c_str(), 0.038, 12, 62);
  TLegend* leg_HF_MBred = new TLegend(0.55, 0.77, 0.87, 0.87);
  xjjroot::setleg(leg_HF_MBred, 0.031);
  leg_HF_MBred->AddEntry(hDpt_HF_MBred, "Reduc-Form MB || HF");
  leg_HF_MBred->AddEntry(hDpt_MBred, "Reduc-Form MB");
  leg_HF_MBred->Draw();
  gPad->RedrawAxis();
  c_HF_MBred->SaveAs(Form("plots/c_%s_%s_HF_MBred.pdf", outputname.c_str(), case_name[icase].c_str()));
  TCanvas* c_HF_MBfull = new TCanvas("c_HF_MBfull", "", 600, 600);
  c_HF_MBfull->SetLogy();
  hDpt_HF_MBfull->Draw("hist e");
  hDpt_HF_MBfull->Draw("e same");
  hDpt_MBfull->Draw("hist e same");
  hDpt_MBfull->Draw("e same");
  xjjroot::drawCMSleft();
  xjjroot::drawCMSright("Embeded MC");
  xjjroot::drawtex(0.20, 0.85, case_desc[icase].c_str(), 0.038, 12, 62);
  TLegend* leg_HF_MBfull = new TLegend(0.55, 0.77, 0.87, 0.87);
  xjjroot::setleg(leg_HF_MBfull, 0.031);
  leg_HF_MBfull->AddEntry(hDpt_HF_MBfull, "Full-Form MB || HF");
  leg_HF_MBfull->AddEntry(hDpt_MBfull, "Full-Form MB");
  leg_HF_MBfull->Draw();
  gPad->RedrawAxis();
  c_HF_MBfull->SaveAs(Form("plots/c_%s_%s_HF_MBfull.pdf", outputname.c_str(), case_name[icase].c_str()));

}

int main(int argc, char* argv[])
{
  if(argc==4) { drawdcount(argv[1], argv[2], atoi(argv[3])); return 0; }
  return 1;
}
