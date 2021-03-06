#define SyncMaker_cxx
// The class definition in SyncMaker.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("SyncMaker.C")
// Root > T->Process("SyncMaker.C","some options")
// Root > T->Process("SyncMaker.C+")
//

#include "SyncMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>


void SyncMaker::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
	 tOut_=NULL;

}

void SyncMaker::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
	 tOut_ = new TTree("LostLeptonExpectation","a simple Tree with simple variables");
	 tOut_->SetAutoSave(10000000000);
	 //  tOut_->SetAutoFlush(1000000);
	 tOut_->Branch("HT",&HT,"HT/F");
	 tOut_->Branch("MHT",&MHT,"MHT/F");
	 tOut_->Branch("NJets",&NJets,"NJets/s");
	 tOut_->Branch("BTags",&BTags,"BTags/s");
	 tOut_->Branch("Leptons",&Leptons,"Leptons/s");
	 tOut_->Branch("isoTracks",&isoTracks,"isoTracks/s");
	 tOut_->Branch("NVtx",&NVtx,"NVtx/s");
	 tOut_->Branch("DeltaPhi1",&DeltaPhi1,"DeltaPhi1/F");
	 tOut_->Branch("DeltaPhi2",&DeltaPhi2,"DeltaPhi2/F");
	 tOut_->Branch("DeltaPhi3",&DeltaPhi3,"DeltaPhi3/F");
	 tOut_->Branch("minDeltaPhiN",&minDeltaPhiN,"minDeltaPhiN/F");
	 tOut_->Branch("DeltaPhiN1",&DeltaPhiN1,"DeltaPhiN1/F");
	 tOut_->Branch("DeltaPhiN2",&DeltaPhiN2,"DeltaPhiN2/F");
	 tOut_->Branch("DeltaPhiN3",&DeltaPhiN3,"DeltaPhiN3/F");
	 tOut_->Branch("Weight", &Weight, "Weight/F");
	 tOut_->Branch("MET",&METPt,"MET/F");
	 tOut_->Branch("METPhi",&METPhi,"METPhi/F");
	 tOut_->Branch("IsolatedTracksNum",&IsolatedTracksNum,"IsolatedTracksNum/s");
	 tOut_->Branch("selectedIDIsoMuonsNum",&selectedIDIsoMuonsNum,"selectedIDIsoMuonsNum/s");
	 tOut_->Branch("selectedIDIsoElectronsNum",&selectedIDIsoElectronsNum,"selectedIDIsoElectronsNum/s");
	 ResetVariables();
	 std::cout<<"Applying filters: "<<applyFilters_<<std::endl;
	 std::cout<<"************************************\n"
	 <<"*    Row   *     event *     mht30 *\n"
	 <<"************************************\n";

}

Bool_t SyncMaker::Process(Long64_t entry)
{
	fChain->GetTree()->GetEntry(entry);
	if(applyFilters_ &&  !FiltersPass() ) return kTRUE;
	all++;
	alld+=Weight;
	if(EvtNum==124734)std::cout<<"NJets: "<<NJets <<" HT: "<<HT<<" MHT: "<<MHT<<"\n";
	if(NJets>=4)
	{
		nJetcut++;
		nJetcutd+=Weight;
		if(HT>500)
		{
			htcut++;
			htcutd+=Weight;
			if(MHT>200)
			{
			  
				mhtcut++;
				mhtcutd+=Weight;
				if(selectedIDIsoMuonsNum==0)
				{
					muveto++;
					muvetod+=Weight;
					if(selectedIDIsoElectronsNum==0)
					{
						elecveto++;
						elecvetod+=Weight;
						if(minDeltaPhiN>4)
						{
							deltaphiNcut++;
							deltaphiNcutd+=Weight;
							if(isoTracks==0)
							{
								isotrakveto++;
								isotrakvetod+=Weight;
								if(BTags==0)
								{
									btag0++;
									btag0d+=Weight;
								}
								if(BTags==1)
								{
									btag1++;
									btag1d+=Weight;
								}
								if(BTags==2)
								{
									btag2++;
									btag2d+=Weight;
								}
								if(BTags>=3)
								{
									btag3++;
									btag3d+=Weight;
								}
							}
						}
					}
				}
			}
			//else std::cout<<"*     "<<all<<" *     "<<EvtNum<<" * "<<MHT<<" *\n";
		  
		}
	}
	if(GenMuNum>0)
	{
		for(unsigned int i=0; i<GenMuNum;i++)
		{
			if(GenMuPt[i]>10 && abs(GenMuEta[i])<2.4)
			{
				GenMuonPtEtaCut++;
				GenMuonPtEtaCutd+=Weight;
			}
			
		}
	}
	if(slimmedMuonsNum>0)
	{
	  for(unsigned int i=0; i<slimmedMuonsNum;i++)
	  {
	    if(slimmedMuonsPt[i]>10 && abs(slimmedMuonsEta[i])<2.4)
	    {
	      muonPtEtaCut++;
	      muonPtEtaCutd+=Weight;
	      break;
	    }
	  }
	  if(selectedIDMuonsNum>0)
	  {
	    muonID++;
	    muonIDd+=Weight;
	  }
	  if(selectedIDIsoMuonsNum>0)
	  {
	    muonIso++;
	    muonIsod+=Weight;
	  }
	}
	if(slimmedElectronsNum>0)
	{
	  for(unsigned int i=0; i<slimmedElectronsNum;i++)
	  {
	    if(slimmedElectronsPt[i]>10 && abs(slimmedElectronsEta[i])<2.5)
	    {
	      elecPtEtaCut++;
	      elecPtEtaCutd+=Weight;
	      break;
	    }
	  }
	  if(selectedIDElectronsNum>0)
	  {
	    elecID++;
	    elecIDd+=Weight;
	  }
	  if(selectedIDIsoElectronsNum>0)
	  {
	    elecIso++;
	    elecIsod+=Weight;
	  }
	}
	tOut_->Fill();



   return kTRUE;
}

void SyncMaker::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}
bool SyncMaker::FiltersPass()
{
  bool result = true;
  if(!JetID) result=false;
  return result;
}


void SyncMaker::Terminate()
{
	TFile *outPutFile = new TFile("Sync.root","RECREATE"); 
	outPutFile->cd();
	tOut_->Write();
	std::cout<<"Sync (unweighted) event count:"<<std::endl;
	std::cout<<"All:                   "<<alld<<" ("<<all<<")"<<std::endl;
	std::cout<<"NJets>=4:              "<<nJetcutd<<" ("<<nJetcut<<")"<<std::endl;
	std::cout<<"HT>500:                "<<htcutd<<" ("<<htcut<<")"<<std::endl;
	std::cout<<"MHT>200:               "<<mhtcutd<<" ("<<mhtcut<<")"<<std::endl;
	std::cout<<"IsoMu veto:            "<<muvetod<<" ("<<muveto<<")"<<std::endl;
// 	std::cout<<"IsoMu veto:            "<<muvetod<<" ("<<muveto<<")"<<std::endl;
	std::cout<<"IsoElec veto:          "<<elecvetod<<" ("<<elecveto<<")"<<std::endl;
	std::cout<<"DeltaPhiN>4:           "<<deltaphiNcutd<<" ("<<deltaphiNcut<<")"<<std::endl;
	std::cout<<"IsoTrack(mt<100) veto: "<<isotrakvetod<<" ("<<isotrakveto<<")"<<std::endl;
	std::cout<<"btag=0:                "<<btag0d<<" ("<<btag0<<")"<<std::endl;
	std::cout<<"btag=1:                "<<btag1d<<" ("<<btag1<<")"<<std::endl;
	std::cout<<"btag=2:                "<<btag2d<<" ("<<btag2<<")"<<std::endl;
	std::cout<<"btag>=3:               "<<btag3d<<" ("<<btag3<<")"<<std::endl;
	std::cout<<"-------------------------------------------------"<<std::endl;
	std::cout<<"Muon:               "<<std::endl;
	std::cout<<"Gen pt eta cut:            "<<GenMuonPtEtaCutd<<" ("<<GenMuonPtEtaCut<<")"<<std::endl;
	std::cout<<"pt eta cut:            "<<muonPtEtaCutd<<" ("<<muonPtEtaCut<<")"<<std::endl;
	std::cout<<"ID:                    "<<muonIDd<<" ("<<muonID<<")"<<std::endl;
	std::cout<<"miniIso:               "<<muonIsod<<" ("<<muonIso<<")"<<std::endl;
	std::cout<<"Electron:               "<<std::endl;
	std::cout<<"pt eta cut:            "<<elecPtEtaCutd<<" ("<<elecPtEtaCut<<")"<<std::endl;
	std::cout<<"ID:                    "<<elecIDd<<" ("<<elecID<<")"<<std::endl;
	std::cout<<"miniIso:               "<<elecIsod<<" ("<<elecIso<<")"<<std::endl;
}
void SyncMaker::ResetVariables()
{
	all=0;
	nJetcut=0;
	htcut=0;
	mhtcut=0;
	muveto=0;
	elecveto=0;
	deltaphiNcut=0;
	isotrakveto=0;
	btag0=0;
	btag1=0;
	btag2=0;
	btag3=0;
	
	alld=0.;
	nJetcutd=0.;
	htcutd=0.;
	mhtcutd=0.;
	muvetod=0.;
	elecvetod=0.;
	deltaphiNcutd=0.;
	isotrakvetod=0.;
	btag0d=0.;
	btag1d=0.;
	btag2d=0.;
	btag3d=0.;
	
	muonPtEtaCut=0;
	muonID=0;
	muonIso=0;
	muonPtEtaCutd=0.;
	muonIDd=0.;
	muonIsod=0.;
	
	elecPtEtaCut=0;
	elecID=0;
	elecIso=0;
	elecPtEtaCutd=0.;
	elecIDd=0.;
	elecIsod=0.;

}
