#include <TChain.h>
#include "TProofServ.h"
#include "TProof.h"
//#include "EffMaker.h"

using std::vector;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif

void MakeEff()
{
  TChain *Effchain = new TChain("LostLeptonExpectation");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");

  Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9_ext1-v1_MINIAODSIM/*root");
  Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9_ext1-v1_MINIAODSIM/*root");
  Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9_ext1-v1_MINIAODSIM/*root");
  Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  // //Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  // //Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");


  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2_MINIAODSIM/*root");
  // Effchain->Add("/hadoop/cms/store/user/jbradmil/trees_911/Expectation/13TeV_25ns20PU.WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1_MINIAODSIM/*root");
  
  Effchain->Process("EffMaker.C+");
}
