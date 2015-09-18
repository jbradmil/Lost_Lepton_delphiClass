// divides all efficiency histograms in the DY file by the histograms in the lost lepton (e.g. ttbar) file
// use this to compare efficiencies for each parametrization
// adapted from https://twiki.ppe.gla.ac.uk/pub/ATLAS/WebHome/RootManual.pdf

#include<iostream>
#include<vector>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TKey.h"
#include "TClass.h"
#include "TExec.h"
#include "jack_style.h"

using namespace std;

void GetEffRatios() {

  gStyle->SetPaintTextFormat("5.3f");
  
  TH1::SetDefaultSumw2(true);
  TH2::SetDefaultSumw2(true);
  
  // open input files
  TFile* fttbar = new TFile("backup_efficiencies/Efficiencies_ttbar.root");
  TDirectory *dEfficiencies_ttbar = (TDirectory*)fttbar->Get("Efficiencies");
  
   // iterator
  TIter nextkey1(dEfficiencies_ttbar->GetListOfKeys());
  TKey* key1(0);
  vector<TH1D*> ttbar_hists;
  vector<TH2D*> ttbar_2Dhists;

  // begin loop over contents
  while ( (key1 = (TKey*)nextkey1()) ) {
    dEfficiencies_ttbar->cd();
    // read THEff sub-directory
    TObject* obj = key1->ReadObj();
    // cout << "Loaded " << obj->GetName() << endl;
    TDirectory *subdir = (TDirectory*)dEfficiencies_ttbar->Get(obj->GetName());
    subdir->cd();
    // now loop over sub-directory
    TIter nextkey2(subdir->GetListOfKeys());
    TKey* key2(0);
    while ( (key2 = (TKey*)nextkey2()) ) {
      TObject* obj2 = key2->ReadObj();
      if (obj2->IsA()->InheritsFrom("TH2")) {
	// cast to hist
	// cout << "Loaded " << obj2->GetName() << endl;   
	// cout << "This is a 2D histogram!" << endl;
	TH2D* httbar2D = (TH2D*)(obj2);
	ttbar_2Dhists.push_back(httbar2D);
	break;
      }
      else if (obj2->IsA()->InheritsFrom("TH1")) {
	// cast to hist
	// cout << "Loaded " << obj2->GetName() << endl;   
	// cout << "This is a histogram!" << endl;
	TH1D* httbar = (TH1D*)(obj2);
	ttbar_hists.push_back(httbar);
	break;
      }
    } // end loop over sub-directory
  } // end loop over main directory

  // now do the same for DY
  TFile* fDY = new TFile("backup_efficiencies/Efficiencies_DY.root");
  TDirectory *dEfficiencies_dy = (TDirectory*)fDY->Get("Efficiencies");
  dEfficiencies_dy->cd();

  TIter nextkey2(dEfficiencies_dy->GetListOfKeys());
  TKey* key2(0);
  vector<TH1D*> dy_hists;
  vector<TH2D*> dy_2Dhists;
    while ( (key2 = (TKey*)nextkey2()) ) {
    dEfficiencies_dy->cd();
    // read THEff sub-directory
    TObject* obj = key2->ReadObj();
    // cout << "Loaded " << obj->GetName() << endl;
    TDirectory *subdir = (TDirectory*)dEfficiencies_dy->Get(obj->GetName());
    subdir->cd();
    // now loop over sub-directory
    TIter nextkey2(subdir->GetListOfKeys());
    TKey* key2(0);
    while ( (key2 = (TKey*)nextkey2()) ) {
      TObject* obj2 = key2->ReadObj();
      if (obj2->IsA()->InheritsFrom("TH2")) {
	// cast to hist
	// cout << "Loaded " << obj2->GetName() << endl;   
	// cout << "This is a 2D histogram!" << endl;
	TH2D* hdy2D = (TH2D*)(obj2);
	dy_2Dhists.push_back(hdy2D);
	break;
      }
      else if (obj2->IsA()->InheritsFrom("TH1")) {
	// cast to hist
	// cout << "Loaded " << obj2->GetName() << endl;   
	// cout << "This is a histogram!" << endl;
	TH1D* hdy = (TH1D*)(obj2);
	dy_hists.push_back(hdy);
	break;
      }
    } // end loop over sub-directory
  } // end loop over main directory
  
  printf("TTBar histograms: %d 1D, %d 2D\n", (int)ttbar_hists.size(), (int)ttbar_2Dhists.size());
  printf("DY histograms: %d 1D, %d 2D\n", (int)dy_hists.size(), (int)dy_2Dhists.size());

  // now make the 1D ratio plots
  TCanvas * c1 = new TCanvas("c1", "c1", 700, 700);
  TPad * pad1 = new TPad("pad1", "top pad" , 0.0, 0.3, 1.0, 1.0);
  pad1->SetBottomMargin(0.0);
  pad1->Draw();
  TPad * pad2 = new TPad("pad2", "bottom pad", 0.0, 0.0, 1.0, 0.3);
  pad2->SetTopMargin(0.0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();

  if (ttbar_hists.size()==dy_hists.size()) {
    for (uint ihist(0); ihist<ttbar_hists.size(); ihist++) {
      TH1D* httbar = ttbar_hists[ihist];
      httbar->SetLineColor(1000);
      httbar->SetLineWidth(2);
      TH1D* hdy = dy_hists[ihist];
      hdy->SetLineColor(1002);
      hdy->SetLineWidth(2);
      TLegend * leg = new TLegend(0.72, 0.70, 0.94, 0.90);
      set_style(leg, 0.035);
      leg->AddEntry(httbar, "t#bar{t}", "pel");
      leg->AddEntry(hdy, "DY+jets", "pel");
      TH1D * ratio = (TH1D *) httbar->Clone("ratio");
      ratio->SetTitle("");
      ratio->GetYaxis()->SetTitle("#epsilon (t#bar{t}) / #epsilon (DY)");
      ratio->Sumw2();
      ratio->SetMarkerSize(0.8);
      ratio->SetLineColor(1);
      ratio->GetXaxis()->SetLabelSize(0.065);
      ratio->GetXaxis()->SetTitleSize(0.1);
      ratio->GetXaxis()->SetTitleOffset(1.2);
      ratio->GetYaxis()->SetTitleSize(0.095);
      ratio->GetYaxis()->SetLabelSize(0.065);
      ratio->GetYaxis()->SetTitleOffset(0.5);
      ratio->Divide(httbar, hdy, 1., 1., "");
      TLine* ratiounity = new TLine(httbar->GetBinLowEdge(1),1,httbar->GetBinLowEdge(httbar->GetNbinsX()+1),1);
      ratiounity->SetLineStyle(2);
      pad1->cd();
      pad1->Clear();
      httbar->GetXaxis()->SetRangeUser(httbar->GetBinLowEdge(1), httbar->GetBinLowEdge(httbar->GetNbinsX()+1));
      httbar->SetMaximum(1.25);
      httbar->SetMinimum(0.5);
      httbar->Draw("e1");
      hdy->Draw("e1,same");
      ratiounity->Draw("same");
      pad2->cd();
      pad2->Clear();
      pad2->SetGridy(0);
      ratio->GetXaxis()->SetRangeUser(ratio->GetBinLowEdge(1), ratio->GetBinLowEdge(ratio->GetNbinsX()+1));
      ratio->SetMaximum(1.25);
      ratio->SetMinimum(0.75);
      ratio->Draw("e1");
      ratiounity->Draw("same");
      pad1->cd();
      leg->Draw();
      gPad->RedrawAxis();
      gPad->Modified();
      gPad->Update();
      pad2->cd();
      gPad->RedrawAxis();
      gPad->Modified();
      gPad->Update();
      c1->cd();
      TString plot_title = "Efficiencies_ratios/ratio_";
      plot_title+=httbar->GetName();
      plot_title+=".pdf";
      gPad->Print(plot_title);
    }
  }
  // now make the 2D ratio plots
  TCanvas *c3 = new TCanvas("c3", "c3", 2400, 700);
  c3->Divide(3,1);
    if (ttbar_2Dhists.size()==dy_2Dhists.size()) {
    for (uint ihist(0); ihist<ttbar_2Dhists.size(); ihist++) {
      TH2D* httbar = ttbar_2Dhists[ihist];
      httbar->SetMarkerSize(1.45);
      TString htitle = httbar->GetTitle();
      httbar->SetTitle("t#bar{t} "+htitle);
      TString hname = httbar->GetName();
      TH2D* hdy = dy_2Dhists[ihist];
      hdy->SetMarkerSize(1.45);
      hdy->SetTitle("DY "+htitle);
      TH2D * ratio = (TH2D *) httbar->Clone("ratio");
      ratio->SetTitle("t#bar{t} / DY");
      //      cout << ratio->GetMarkerSize() << endl;
      ratio->SetMarkerSize(1.45);
      //ratio->SetMarkerSize(0.055);
      ratio->Sumw2();
      // ratio->SetMarkerSize(0.8);
      ratio->Divide(httbar, hdy, 1., 1., "");

      set_avocado_palette();
      c3->cd(1);
      if (hname.Contains("PTActivity")) {
	gPad->SetLogx(1);
	gPad->SetLogy(1);
      }
      else {
	gPad->SetLogx(0);
	gPad->SetLogy(0);
      }
      httbar->SetMaximum(1);
      httbar->Draw("colz,text,E");
      c3->cd(2);
      if (hname.Contains("PTActivity")) {
	gPad->SetLogx(1);
	gPad->SetLogy(1);
      }
      else {
	gPad->SetLogx(0);
	gPad->SetLogy(0);
      }
      hdy->SetMaximum(1);
      hdy->Draw("colz,text,E");

      TExec *ex1 = new TExec("ex1","set_temperature_palette();");
      c3->cd(3);
      if (hname.Contains("PTActivity")) {
	gPad->SetLogx(1);
	gPad->SetLogy(1);
      }
      else {
	gPad->SetLogx(0);
	gPad->SetLogy(0);
      }
      ratio->SetMaximum(1.2);
      ratio->SetMinimum(0.8);
      ratio->Draw("axis");
      ex1->Draw();
      ratio->Draw("colz,text,E,same");
      
      c3->cd();
      TString plot_title = "Efficiencies_ratios/ratio2D_";
      plot_title+=httbar->GetName();
      plot_title+=".pdf";
      gPad->Print(plot_title);
    }
  }

    delete c1;
    delete c3;
    delete fttbar;
    delete fDY;
}
