// divides all efficiency histograms in the DY file by the histograms in the lost lepton (e.g. ttbar) file
// use this to compare efficiencies for each parametrization
// adapted from https://twiki.ppe.gla.ac.uk/pub/ATLAS/WebHome/RootManual.pdf

#include<iostream>
#include<vector>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TKey.h"
#include "TChain.h"
#include "TCut.h"
#include "TExec.h"
#include "jack_style.h"

using namespace std;

void MakePlot(TString var, TString title, int nbinsx, double xlow, double xhigh, TCut cuts="", bool logy=false) {

  
  TH1::SetDefaultSumw2(true);
  TH2::SetDefaultSumw2(true);
  
  // open input files
  TChain* ttbar = new TChain("LostLeptonExpectation");
  ttbar->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  ttbar->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  ttbar->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  ttbar->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  ttbar->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  ttbar->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9_ext1-v1_MINIAODSIM/*root");
  ttbar->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9_ext1-v1_MINIAODSIM/*root");
  ttbar->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  TChain* dy = new TChain("LostLeptonExpectation");
  dy->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  dy->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  dy->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  dy->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");

  TH1D* httbar = new TH1D("httbar",title,nbinsx,xlow,xhigh);
  TH1D* hdy = new TH1D("hdy",title,nbinsx,xlow,xhigh);

  httbar->SetStats(0);
  hdy->SetStats(0);
  
  TCut selection  = cuts*"Weight";
  ttbar->Project("httbar",var, selection);
  dy->Project("hdy",var, selection);

  httbar->Scale(1/httbar->Integral(1,nbinsx+1));
  hdy->Scale(1/hdy->Integral(1,nbinsx+1));

  // now make the 1D ratio plots
  TCanvas * c1 = new TCanvas("c1", "c1", 700, 700);
  c1->SetLogy(logy);

  httbar->SetLineColor(1000);
  httbar->SetLineWidth(3);
  hdy->SetLineColor(1002);
  hdy->SetLineWidth(3);
  TLegend * leg = new TLegend(0.72, 0.70, 0.94, 0.90);
  set_style(leg, 0.035);
  leg->AddEntry(httbar, "t#bar{t}", "pel");
  leg->AddEntry(hdy, "DY+jets", "pel");
  double max = httbar->GetMaximum();
  if (hdy->GetMaximum()>max) max = hdy->GetMaximum();
  httbar->SetMaximum(1.2*max);
  httbar->SetMinimum(0);
  httbar->Draw("e1,hist");
  hdy->Draw("e1,hist,same");
  httbar->GetYaxis()->SetLabelSize(0.025);
  httbar->GetYaxis()->SetTitleSize(0.025);
  httbar->GetYaxis()->SetTitleOffset(1.3);
  leg->Draw();
  TString plot_title = "compare_dists/";
  plot_title+=var;
  plot_title+="_ttbar_vs_dy.pdf";
  gPad->Print(plot_title);


  delete c1;
  delete httbar;
  delete hdy;
  delete ttbar;
  delete dy;
}

void CompareTTDY() {
  //  MakePlot("selectedIDMuons_MiniIso", ";I_{mini}(#mu);Fraction of events",50,0.,1.,"selectedIDMuons.Pt()>10");
  MakePlot("selectedIDIsoMuons_MT2Activity", ";Activity;Fraction of events",250,0.,1.,"selectedIDIsoMuons.Pt()>10",true);
  MakePlot("selectedIDIsoMuons.Pt()", ";p_{T}(#mu) [GeV];Fraction of events",250,0.,500.,"selectedIDIsoMuons.Pt()>0");
  MakePlot("selectedIDIsoElectrons_MT2Activity", ";Activity;Fraction of events",250,0.,1.,"selectedIDIsoElectrons.Pt()>10",true);
  MakePlot("selectedIDIsoElectrons.Pt()", ";p_{T}(#mu) [GeV];Fraction of events",250,0.,500.,"selectedIDIsoElectrons.Pt()>0");
}
