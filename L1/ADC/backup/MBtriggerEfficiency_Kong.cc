
// system include files
#include <memory>
#include <iostream>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CalibFormats/CaloTPG/interface/CaloTPGTranscoder.h"
#include "CalibFormats/CaloTPG/interface/CaloTPGRecord.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"

#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDetId/interface/HcalElectronicsId.h"
#include "DataFormats/HcalDigi/interface/HcalQIESample.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile2D.h"


//add L1 stuff
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "L1Trigger/RegionalCaloTrigger/interface/L1RCTProducer.h"
#include "DataFormats/L1TCalorimeter/interface/CaloTower.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/L1Trigger/interface/EtSum.h"

#include "DataFormats/L1TGlobal/interface/GlobalAlgBlk.h"
#include "DataFormats/L1TGlobal/interface/GlobalExtBlk.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GtObject.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtFdlWord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtLogicParser.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtObject.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtTriggerMenuLite.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloRegion.h"

#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"



// class declaration
//

class MBtriggerEfficiency : public edm::EDAnalyzer {
public:
  explicit MBtriggerEfficiency(const edm::ParameterSet&);
  ~MBtriggerEfficiency();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  TFile* outputFile;
  TH1F* allChanSignalLong;
  TH1F* allChanSignalShort;
  TH1F* allChanSignal;
  TH1F* sigPerChanLong[26][36];
  TH1F* sigPerChanShort[26][36];
  TH1F* amplVSsampl;
  
  TH1F* sig[40][26][36];
  
  /* 
  TProfile2D* sigAboveThr1;
  TProfile2D* sigAboveThrShort1;
  TProfile2D* sigProfile;
  TProfile2D* sigProfileShort;
  */

  TH1F* accPerEvt;
  TH1F* accPerEvtAnd;
  TH1F* accPerEvtPlus;
  TH1F* accPerEvtMinus;
  TH1F* accPerEvt2sliceFront;
  TH1F* accPerEvt2sliceBack;

  TH2F* allChanEtaPhi;
  TH1F* nChanLong;
  TH1F* nChanShort;
  
  TH2F* chanAboveThrFileLong;
  TH2F* chanAboveThrFileShort;
  TH1F* accPerEvtThrFile;
  TH1F* accPerEvtThrFileAnd;
  TH1F* accPerEvtThrFileDeno;
  
  //adding 2D
  TH2F* accPerEvtThrFile2D;
  TH2F* accPerEvtThrFileAnd2D;

  TH1F* accPerEvtThrFileSumEtDeno;
  
  //adding 2D
  TH2F* accPerEvtThrFileSumEt2D;
  TH2F* accPerEvtThrFileSumEtAnd2D;



  TH2F* crossCheck_TP;

  TH1F* idFired;
  TH1F* idFired_frac;
  TH1F* nMBHF1_firedBX;
  TH1F* nMBHF2_firedBX;

  TH1F* crossTest_HF1;
  TH1F* crossTest_HF2;

  TH1F* jetCrossTest8;
  TH1F* jetCrossTest12;

  TH1F* bxNum;
  
  int evtsTot;

  TH1F* HF1_OR_vsLumi;
  TH1F* HF2_OR_vsLumi;
  
  TH1F* ZB_vsLumi;

  TH1F* hL1jetsEta8;
  TH1F* hL1jetsEta12;
  
  double thresholdsLong[26][36];
  double thresholdsShort[26][36];
  
  uint32_t totalTime;
  
  std::vector<std::string> trgList;

  std::string outfname;
  edm::InputTag gtDigiTag;
  edm::InputTag gctDigiTag;
  edm::InputTag l1GtRecordInputTag;
  edm::InputTag l1GtReadoutRecordInputTag;
  edm::InputTag l1GtTriggerMenuLiteInputTag;
  //edm::EDGetTokenT<HFDigiCollection> hfDigiTag;
  edm::EDGetTokenT<QIE10DigiCollection> hfDigiTag;
  edm::EDGetTokenT<L1GlobalTriggerReadoutRecord> gtDigiToken;
  edm::EDGetTokenT<CaloTowerCollection> caloTowerTag;
  edm::EDGetTokenT<HFRecHitCollection> hfRechitTag;
  edm::EDGetTokenT<reco::CaloJetCollection> caloJetTag;
  edm::EDGetTokenT<edm::View<reco::Track> > trackSrc_;
  edm::EDGetTokenT<reco::VertexCollection> vertexSrc_;

  edm::InputTag digis_;

  edm::InputTag m_l1stage2globalAlgBlk;
  edm::EDGetTokenT<GlobalAlgBlkBxCollection> l1tStage2uGtSource_;

  // edm::EDGetTokenT<l1extra::L1JetParticleCollection>  m_l1CenJetToken;
  // edm::EDGetTokenT<l1extra::L1JetParticleCollection>  m_l1ForJetToken;
  // edm::EDGetTokenT<l1extra::L1JetParticleCollection>  m_l1TauJetToken;

  bool useReco;
  bool useMC;
  bool useBPTXplus;
  bool useBPTXminus;
  bool doMultDepend;

  vector<int> beam1_empty_bx;
  vector<int> beam2_empty_bx;

  vector<int> selected_lumi;

  const CaloGeometry* geo;
  
  TH1F* hCaloTowerET[8];
  TH1F* hCaloTowerETtrig8[8];
  TH1F* hCaloTowerETtrig12[8];
  TH1F* hCaloTowerETtrigMB[8];

  TH1F* hRecHitET[8];
  TH1F* hRecHitETtrig8[8];
  TH1F* hRecHitETtrig12[8];
  TH1F* hRecHitETtrigMB[8];

  TH1F* hCaloJetPlusET;
  TH1F* hCaloJetPlusETtrig8;
  TH1F* hCaloJetPlusETtrig12;
  TH1F* hCaloJetPlusETtrigMB;

  TH1F* hCaloJetMinusET;
  TH1F* hCaloJetMinusETtrig8;
  TH1F* hCaloJetMinusETtrig12;
  TH1F* hCaloJetMinusETtrigMB;

private:
  L1GtUtils m_l1GtUtils;
  
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  
  // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MBtriggerEfficiency::MBtriggerEfficiency(const edm::ParameterSet& iConfig):
  digis_(iConfig.getParameter<edm::InputTag>("triggerPrimitives")),
  m_l1GtUtils(iConfig, consumesCollector(), true)//this is important for 80x to compile

{
  consumes<HcalTrigPrimDigiCollection>(digis_);

  m_l1stage2globalAlgBlk = edm::InputTag("hltGtStage2Digis");

  l1tStage2uGtSource_ = consumes<GlobalAlgBlkBxCollection>( m_l1stage2globalAlgBlk );

  l1GtRecordInputTag = iConfig.getParameter<edm::InputTag>("l1GtRecordInputTag");
  l1GtReadoutRecordInputTag = iConfig.getParameter<edm::InputTag>("l1GtReadoutRecordInputTag");
  l1GtTriggerMenuLiteInputTag = iConfig.getParameter<edm::InputTag>("l1GtTriggerMenuLiteInputTag");
  outfname=iConfig.getParameter<std::string>("outputFileName");
  gtDigiTag=iConfig.getParameter<edm::InputTag>("gtDigiTag");
  gctDigiTag=iConfig.getParameter<edm::InputTag>("gctDigiTag");
  caloTowerTag=consumes<CaloTowerCollection>(iConfig.getParameter<edm::InputTag>("caloTowerTag"));
  gtDigiToken = consumes<L1GlobalTriggerReadoutRecord>(iConfig.getParameter<edm::InputTag>("gtDigiToken"));
  hfRechitTag = consumes<HFRecHitCollection>(iConfig.getParameter<edm::InputTag>("hfRechitTag"));
  caloJetTag = consumes<reco::CaloJetCollection>(iConfig.getParameter<edm::InputTag>("caloJetTag"));
  //hfDigiTag = consumes<HFDigiCollection>(iConfig.getParameter<edm::InputTag>("hfDigiTag"));
  hfDigiTag = consumes<QIE10DigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("hfDigiTag"));
  trackSrc_ = consumes<edm::View<reco::Track> >(iConfig.getParameter<edm::InputTag>("trackSrc")),
  vertexSrc_ = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertexSrc")),

  useReco=iConfig.getParameter<bool>("useReco");
  useMC=iConfig.getParameter<bool>("useMC");
  useBPTXplus=iConfig.getParameter<bool>("useBPTXplus");
  useBPTXminus=iConfig.getParameter<bool>("useBPTXminus");
  doMultDepend=iConfig.getParameter<bool>("doMultDepend");

  beam1_empty_bx = iConfig.getUntrackedParameter<std::vector<int>>("beam1_empty_bx");
  beam2_empty_bx = iConfig.getUntrackedParameter<std::vector<int>>("beam2_empty_bx");
  selected_lumi = iConfig.getUntrackedParameter<std::vector<int>>("selected_lumi");

  trgList.push_back("L1Tech_BPTX_plus_AND_NOT_minus.v0");
  trgList.push_back("L1Tech_BPTX_minus_AND_not_plus.v0");
  trgList.push_back("L1Tech_BPTX_quiet.v0");
  trgList.push_back("L1_ZeroBias");
  trgList.push_back("L1_MinimumBiasHF1_OR");
  trgList.push_back("L1_MinimumBiasHF2_OR");
  trgList.push_back("L1_MinimumBiasHF1_AND");
  trgList.push_back("L1_MinimumBiasHF2_AND");
  trgList.push_back("L1_SingleJet36");
  trgList.push_back("L1_SingleJet52");
  trgList.push_back("L1_SingleJet16");
  trgList.push_back("L1_DoubleJet20");
  
  outputFile=new TFile(outfname.c_str(),"RECREATE");
  allChanSignalLong=new TH1F("allChanSignalLong","allChanSignalLong",1000,0,1000);
  allChanSignalShort=new TH1F("allChanSignalShort","allChanSignalShort",1000,0,1000);
  allChanSignal=new TH1F("allChanSignal","allChanSignal",1000,0,1000);
  allChanEtaPhi=new TH2F("allChanEtaPhi","allChanEtaPhi",100,-50,50,73,0,73);
  nChanLong=new TH1F("nChanLong","nChanLong",10000,0,10000);
  nChanShort=new TH1F("nChanShort","nChanShort",10000,0,10000);
  /*
  sigAboveThr1=new TProfile2D("sigAboveThr1","sigAboveThr1",100,-50,50,73,0,73,0,10000);
  sigAboveThrShort1=new TProfile2D("sigAboveThrShort1","sigAboveThrShort1",100,-50,50,73,0,73,0,10000);
  sigProfile=new TProfile2D("sigProfile","sigProfile",100,-50,50,73,0,73,0,10000);
  sigProfileShort=new TProfile2D("sigProfileShort","sigProfileShort",100,-50,50,73,0,73,0,10000);
  */
  chanAboveThrFileLong=new TH2F("chanAboveThrFileLong","chanAboveThrFileLong",100,-50,50,73,0,73);
  chanAboveThrFileShort=new TH2F("chanAboveThrFileShort","chanAboveThrFileShort",100,-50,50,73,0,73);
  accPerEvtThrFile=new TH1F("accPerEvtThrFile","accPerEvtThrFile",1000,0,1000); 
  accPerEvtThrFileAnd=new TH1F("accPerEvtThrFileAnd","accPerEvtThrFileAnd",1000,0,1000); 
  accPerEvtThrFileDeno=new TH1F("accPerEvtThrFileDeno","accPerEvtThrFileDeno",1000,0,1000);
  accPerEvtThrFile2D=new TH2F("accPerEvtThrFile2D","accPerEvtThrFile2D",40,0,40,1000,0,1000); 
  accPerEvtThrFileAnd2D=new TH2F("accPerEvtThrFileAnd2D","accPerEvtThrFileAnd2D",40,0,40,1000,0,1000); 

  accPerEvtThrFileSumEtDeno=new TH1F("accPerEvtThrFileSumEtDeno","accPerEvtThrFileSumEtDeno",5000,0,5000);
  accPerEvtThrFileSumEt2D=new TH2F("accPerEvtThrFileSumEt2D","accPerEvtThrFileSumEt2D",40,0,40,5000,0,5000); 
  accPerEvtThrFileSumEtAnd2D=new TH2F("accPerEvtThrFileSumEtAnd2D","accPerEvtThrFileSumEtAnd2D",40,0,40,5000,0,5000); 
  

  crossCheck_TP=new TH2F("crossCheck_TP","crossCheck_TP",2,0,2,2,0,2); 

  bxNum=new TH1F("bxNum","bxNum",5000,0,5000);
  
  idFired=new TH1F("idFired","idFired",13,0,13);
  idFired_frac=new TH1F("idFired_frac","idFired_frac",13,0,13);

  nMBHF1_firedBX=new TH1F("nMBHF1_firedBX","nMBHF1_firedBX",10000,0,10000);
  nMBHF2_firedBX=new TH1F("nMBHF2_firedBX","nMBHF2_firedBX",10000,0,10000);

  HF1_OR_vsLumi=new TH1F("HF1_OR_vsLumi","HF1_OR_vsLumi",1000,0,1000);
  HF2_OR_vsLumi=new TH1F("HF2_OR_vsLumi","HF2_OR_vsLumi",1000,0,1000);
  
  ZB_vsLumi=new TH1F("ZB_vsLumi","ZB_vsLumi",1000,0,1000);

  crossTest_HF1=new TH1F("crossTestHF1","crossTestHF1",3,0,3);
  crossTest_HF2=new TH1F("crossTestHF2","crossTestHF2",3,0,3);

  jetCrossTest8=new TH1F("jetCrossTest8","jetCrossTest8",3,0,3);
  jetCrossTest12=new TH1F("jetCrossTest12","jetCrossTest12",3,0,3);

  hL1jetsEta8=new TH1F("hL1jetsEta8","hL1jetsEta8",110,-5.5,5.5);
  hL1jetsEta12=new TH1F("hL1jetsEta12","hL1jetsEta12",110,-5.5,5.5);

  char tmp[100];

  for (int i=0; i<8; i++)
    {
      sprintf(tmp,"hCaloTowerET_%d",i);
      hCaloTowerET[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hCaloTowerETtrig8_%d",i);
      hCaloTowerETtrig8[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hCaloTowerETtrig12_%d",i);
      hCaloTowerETtrig12[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hCaloTowerETtrigMB_%d",i);
      hCaloTowerETtrigMB[i]=new TH1F(tmp,tmp,1000,0,1000);

      sprintf(tmp,"hRecHitET_%d",i);
      hRecHitET[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hRecHitETtrig8_%d",i);
      hRecHitETtrig8[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hRecHitETtrig12_%d",i);
      hRecHitETtrig12[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hRecHitETtrigMB_%d",i);
      hRecHitETtrigMB[i]=new TH1F(tmp,tmp,1000,0,1000);
    }

  hCaloJetPlusET=new TH1F("hCaloJetPlusET","hCaloJetPlusET",1000,0,1000);
  hCaloJetPlusETtrig8=new TH1F("hCaloJetPlusETtrig8","hCaloJetPlusETtrig8",1000,0,1000);
  hCaloJetPlusETtrig12=new TH1F("hCaloJetPlusETtrig12","hCaloJetPlusETtrig12",1000,0,1000);
  hCaloJetPlusETtrigMB=new TH1F("hCaloJetPlusETtrigMB","hCaloJetPlusETtrigMB",1000,0,1000);

  hCaloJetMinusET=new TH1F("hCaloJetMinusET","hCaloJetMinusET",1000,0,1000);
  hCaloJetMinusETtrig8=new TH1F("hCaloJetMinusETtrig8","hCaloJetMinusETtrig8",1000,0,1000);
  hCaloJetMinusETtrig12=new TH1F("hCaloJetMinusETtrig12","hCaloJetMinusETtrig12",1000,0,1000);
  hCaloJetMinusETtrigMB=new TH1F("hCaloJetMinusETtrigMB","hCaloJetMinusETtrigMB",1000,0,1000);

  std::ifstream thrFileShort;
  thrFileShort.open("thresholdsShort_cosmic.txt");
  
  std::ifstream thrFileLong;
  thrFileLong.open("thresholdsLong_cosmic.txt");
  
  for (int l=0; l<26; l++)
    {
      for (int k=0; k<36; k++)
  {
    thrFileLong>>thresholdsLong[l][k];
    thrFileShort>>thresholdsShort[l][k];
    

    sprintf(tmp,"sigLong_%d_%d",l,k);
    sigPerChanLong[l][k]=new TH1F(tmp,tmp,1000,0,1000);
    sprintf(tmp,"sigShort_%d_%d",l,k);
    sigPerChanShort[l][k]=new TH1F(tmp,tmp,1000,0,1000);
    int eta, phi;
    if (l<13) eta=-29-l;
    else eta=16+l;
    phi=(k+1)*2-1;
    for (int p=0; p<10; p++)
      {
        sprintf(tmp,"sig_%d_%d_%d",p,eta,phi);
        sig[p][l][k]=new TH1F(tmp,tmp,1000,0,1000); 
      }
  }
      thrFileLong.getline(tmp,100,'\n');
      thrFileShort.getline(tmp,100,'\n');
    }
  
  amplVSsampl=new TH1F("amplVSsampl","amplVSsampl",10,0,10);
  
  accPerEvt=new TH1F("accPerEvt","accPerEvt",40,0,40);
  accPerEvt->TH1F::Sumw2();
  accPerEvtPlus=new TH1F("accPerEvtPlus","accPerEvtPlus",40,0,40);
  accPerEvtPlus->TH1F::Sumw2();
  accPerEvtMinus=new TH1F("accPerEvtMinus","accPerEvtMinus",40,0,40);
  accPerEvtMinus->TH1F::Sumw2();
  accPerEvtAnd=new TH1F("accPerEvtAnd","accPerEvtAnd",40,0,40);
  accPerEvtAnd->TH1F::Sumw2();
  accPerEvt2sliceFront=new TH1F("accPerEvt2sliceFront","accPerEvt2sliceFront",40,0,40);
  accPerEvt2sliceFront->TH1F::Sumw2();
  accPerEvt2sliceBack=new TH1F("accPerEvt2sliceBack","accPerEvt2sliceBack",40,0,40);
  accPerEvt2sliceBack->TH1F::Sumw2();
  
  evtsTot=0;
  //now do what ever initialization is needed
  
  totalTime=0;

}


MBtriggerEfficiency::~MBtriggerEfficiency()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void MBtriggerEfficiency::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  using namespace std;
  //select particular lumi, bunch, etc...
  int lsec=iEvent.eventAuxiliary().luminosityBlock();
  int bx=iEvent.eventAuxiliary().bunchCrossing();

  bool flag = false;
  for(unsigned i = 0; i < selected_lumi.size()/2; i++){
    if( lsec >= selected_lumi[2*i] && lsec <= selected_lumi[2*i+1] ){
      flag = true;
    }
  }
  if( flag == false ) return;

  if( useBPTXplus ){
    int count_plus = 0;
    for(unsigned i = 0; i < beam1_empty_bx.size(); i++){
      if( bx == beam1_empty_bx[i] ) count_plus++;
    }
    if( count_plus == 0 ) return;
  }
  if( useBPTXminus ){
    int count_minus = 0;
    for(unsigned i = 0; i < beam2_empty_bx.size(); i++){
      if( bx == beam2_empty_bx[i] ) count_minus++;
    }
    if( count_minus == 0 ) return;
  }

  bxNum->Fill(bx,1);
  ZB_vsLumi->Fill(lsec,1);

  evtsTot++;
  
  bool fire[40];
  bool fireFront[40];
  bool fireBack[40];
  bool firePlus[40];
  bool fireMinus[40];
  bool fireShortThr1=false;
  bool fireLongThr1=false;

  bool fireShortThr1_plus=false;
  bool fireShortThr1_minus=false;
  bool fireLongThr1_plus=false;
  bool fireLongThr1_minus=false;

  double etHFtowerSumPlus = 0.0;
  double etHFtowerSumMinus = 0.0;
  double etHFtowerSum = 0.0;

  if (!useReco){

    int nMult_ass_good = 1;
    if( doMultDepend ){

      nMult_ass_good = 0;


    edm::Handle<reco::VertexCollection> vertices;
    iEvent.getByToken(vertexSrc_,vertices);
    double bestvz=-999.9, bestvx=-999.9, bestvy=-999.9;
    double bestvzError=-999.9, bestvxError=-999.9, bestvyError=-999.9;
    const reco::Vertex & vtx = (*vertices)[0];
    bestvz = vtx.z(); 
    bestvx = vtx.x(); 
    bestvy = vtx.y();
    bestvzError = vtx.zError(); 
    bestvxError = vtx.xError(); 
    bestvyError = vtx.yError();

    edm::Handle<edm::View<reco::Track>> tracks;
    iEvent.getByToken(trackSrc_, tracks);

      for(unsigned it = 0; it < tracks->size(); it++){

        const reco::Track & trk = (*tracks)[it];

        math::XYZPoint bestvtx(bestvx,bestvy,bestvz);

        double dzvtx = trk.dz(bestvtx);
        double dxyvtx = trk.dxy(bestvtx);
        double dzerror = sqrt(trk.dzError()*trk.dzError()+bestvzError*bestvzError);
        double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+bestvxError*bestvyError);
        
        if(!trk.quality(reco::TrackBase::highPurity)) continue;
        if(fabs(trk.ptError())/trk.pt() > 0.1 ) continue;
        if(fabs(dzvtx/dzerror) > 3.0 ) continue;
        if(fabs(dxyvtx/dxyerror) > 3.0 ) continue;
        if( fabs(trk.eta()) < 2.4 && trk.pt() > 0.4 ){nMult_ass_good++;}// NtrkOffline        

      }


    edm::Handle<CaloTowerCollection> towers;
    iEvent.getByToken(caloTowerTag, towers);

    for( unsigned i = 0; i<towers->size(); ++ i){
       const CaloTower & tower = (*towers)[ i ];
       double eta = tower.eta();
       bool isHF = tower.ietaAbs() > 29;
          if(isHF && eta > 0){
            etHFtowerSumPlus += tower.pt();
          }
          if(isHF && eta < 0){
            etHFtowerSumMinus += tower.pt();
          }
    }
    etHFtowerSum=etHFtowerSumPlus + etHFtowerSumMinus;
    
    accPerEvtThrFileSumEtDeno->Fill(etHFtowerSum, 1);
    accPerEvtThrFileDeno->Fill(nMult_ass_good, 1); 
    }

    edm::Handle<QIE10DigiCollection> digi;
    //edm::Handle<HFDigiCollection> digi;
    iEvent.getByToken(hfDigiTag,digi);
    if(!iEvent.getByToken(hfDigiTag,digi)) cout << "invalid" << endl; 

    //QIE10DigiCollection::const_iterator i;
    
    for (int k=0; k<40; k++){
      fire[k]=false;
      fireFront[k]=false;
      fireBack[k]=false;
      firePlus[k]=false;
      fireMinus[k]=false;
    }
      
    int nChLong=0;
    int nChShort=0;
    
    //for (QIE10DigiCollection::const_iterator i=digi->begin(); i!=digi->end(); i++) {
      
    for(uint32_t i = 0; i < digi->size(); i++){
      
      QIE10DataFrame frame = static_cast<QIE10DataFrame>((*digi)[i]);


      HcalDetId cell = frame.detid();
      if(cell.subdet() != HcalForward) continue;

      int idepth=cell.depth();
      int ieta=cell.ieta();
      int iphi=cell.iphi();
      
      if( idepth > 4){
      cout << "depth = " << idepth << endl;
      cout << "rawid " << cell.rawId() << endl;
      }
      //if( ieta == 35 && iphi == 47 ) continue;
      //  if (abs(ieta)>36) continue;
      if (idepth==1) 
        {
          nChLong++;
          allChanEtaPhi->Fill(ieta,iphi,1);
        }
      if (idepth==2) nChShort++;
      
      int ampl=0;
      int amplFront=0;
      int amplBack=0;
      int digiSize=frame.samples();
      
      for (int k=0; k<digiSize; k++){
        QIE10DataFrame::Sample sam = frame[k];
        //HcalQIESample dSample;
        //int capid=dSample.capid();
        int adc=frame[k].adc();
        //int etaind, phiind;
        //if (ieta<0) etaind=abs(ieta)-29;
        //else etaind=ieta-16;
        //phiind=(iphi-1)/2;
        //sig[idepth-1][etaind][phiind]->Fill(adc,1);
        amplVSsampl->Fill(k,adc);
        if(sam.soi()) ampl+=adc; 
        //if (k==2) ampl+=adc;
        if (k==1) amplFront+=adc;
        if (k==3) amplBack+=adc;
      }
      if (idepth==1){
        allChanSignalLong->Fill(ampl,1);
        sigPerChanLong[abs(ieta/1000)][iphi]->Fill(ampl,1);
        //if (ampl>17) sigAboveThr1->Fill(ieta,iphi,ampl,1);
        //sigProfile->Fill(ieta,iphi,ampl,1);
        for (int p=0; p<40; p++){
          
          if (ampl>p) {fire[p]=true;}
          if (ampl>p&&ieta>0) firePlus[p]=true;
          if (ampl>p&&ieta<0) fireMinus[p]=true;
          if (amplFront+ampl>p) fireFront[p]=true;
          if (amplBack+ampl>p) fireBack[p]=true;
        }
        if (ampl>17){
          //thresholdsLong[etaind][phiind])
          chanAboveThrFileLong->Fill(ieta,iphi,1);
          fireLongThr1=true;

          if(ieta>0) fireLongThr1_plus=true;
          if(ieta<0) fireLongThr1_minus=true;
        }
      }
      if (idepth==2){
        allChanSignalShort->Fill(ampl,1);
        sigPerChanShort[abs(ieta/1000)][iphi]->Fill(ampl,1);
        //if (ampl>17) sigAboveThrShort1->Fill(ieta,iphi,ampl,1);
        //sigProfileShort->Fill(ieta,iphi,ampl,1);
        for (int p=0; p<40; p++){
          if (ampl>p) fire[p]=true;
          if (ampl>p&&ieta>0) firePlus[p]=true;
          if (ampl>p&&ieta<0) fireMinus[p]=true;
          if (amplFront>p||ampl>p) fireFront[p]=true;
          if (amplBack>p||ampl>p) fireBack[p]=true;
        }
        if (ampl>17){
          //adc>thresholdsShort[etaind][phiind])
          chanAboveThrFileShort->Fill(ieta,iphi,1);
          fireShortThr1=true; 

          if(ieta>0) fireShortThr1_plus=true;
          if(ieta<0) fireShortThr1_minus=true;                       
        }
      }
    }

    for (int k=0; k<40; k++){
      if (fire[k]) {accPerEvt->Fill(k,1); accPerEvtThrFile2D->Fill(k, nMult_ass_good,1); accPerEvtThrFileSumEt2D->Fill(k, etHFtowerSum,1);}
      if (fireFront[k]) accPerEvt2sliceFront->Fill(k,1);
      if (fireBack[k]) accPerEvt2sliceBack->Fill(k,1);
      if (firePlus[k]) accPerEvtPlus->Fill(k,1);
      if (fireMinus[k]) accPerEvtMinus->Fill(k,1);
      if (firePlus[k] && fireMinus[k]) {accPerEvtAnd->Fill(k,1); accPerEvtThrFileAnd2D->Fill(k, nMult_ass_good,1); accPerEvtThrFileSumEtAnd2D->Fill(k, etHFtowerSum,1);}
    }

    if (fireLongThr1||fireShortThr1){
      accPerEvtThrFile->Fill(nMult_ass_good, 1);
    }

    if( (fireLongThr1_plus && fireLongThr1_minus) || (fireShortThr1_plus && fireShortThr1_minus) ){
      accPerEvtThrFileAnd->Fill(nMult_ass_good, 1);
    }

    double hcalTP_emul = 0.0;
    if(fireLongThr1||fireShortThr1){
      hcalTP_emul = 1.0;
    }
    double hcalTP_data = 0.0;
   // if( tpFineGrainCount >= 1.0 ){
     // hcalTP_data = 1.0;
   // }

    crossCheck_TP->Fill(hcalTP_emul, hcalTP_data);

    nChanLong->Fill(nChLong,1);
    nChanShort->Fill(nChShort,1);
      //std::cout<<nChLong<<std::endl;
    
    }//end of !useReco
   
}
// ------------ method called once each job just before starting event loop  ------------
void 
MBtriggerEfficiency::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MBtriggerEfficiency::endJob() 
{
  outputFile->cd();
  accPerEvt->Scale(pow(evtsTot,-1));
  accPerEvt2sliceFront->Scale(pow(evtsTot,-1));
  accPerEvt2sliceBack->Scale(pow(evtsTot,-1));
  accPerEvtPlus->Scale(pow(evtsTot,-1));
  accPerEvtMinus->Scale(pow(evtsTot,-1));
  accPerEvtAnd->Scale(pow(evtsTot,-1));
  accPerEvtThrFile->Scale(pow(evtsTot,-1));
  accPerEvtThrFileAnd->Scale(pow(evtsTot,-1));
  accPerEvtThrFile2D->Scale(pow(evtsTot,-1));
  accPerEvtThrFileAnd2D->Scale(pow(evtsTot,-1));
  accPerEvtThrFileDeno->Scale(pow(evtsTot,-1));
  accPerEvtThrFileSumEt2D->Scale(pow(evtsTot,-1));
  accPerEvtThrFileSumEtAnd2D->Scale(pow(evtsTot,-1));
  accPerEvtThrFileSumEtDeno->Scale(pow(evtsTot,-1));
  crossCheck_TP->Scale(pow(evtsTot,-1));

  amplVSsampl->Write();
  outputFile->mkdir("channels");
  outputFile->cd("channels");
  for (int i=0; i<26; i++)
    {
      for (int j=0; j<36; j++)
  {
  sig[0][i][j]->Write();
  sig[1][i][j]->Write();
//    sigPerChanLong[i][j]->Write();
//    sigPerChanShort[i][j]->Write();
  }
    }
  outputFile->cd();
  allChanSignalLong->Write();
  allChanSignalShort->Write();
  allChanSignal->Write();
  accPerEvt->Write();
  accPerEvt2sliceFront->Write();
  accPerEvt2sliceBack->Write();
  accPerEvtPlus->Write();
  accPerEvtMinus->Write();
  accPerEvtAnd->Write();
  nChanLong->Write();
  nChanShort->Write();
  allChanEtaPhi->Write();
  //sigProfile->Write();
  //sigProfileShort->Write();
  //sigAboveThr1->Write();
  //sigAboveThrShort1->Write();
  crossCheck_TP->Write();

  chanAboveThrFileLong->Write();
  chanAboveThrFileShort->Write();
  accPerEvtThrFile->Write();
  accPerEvtThrFileAnd->Write();
  accPerEvtThrFile2D->Write();
  accPerEvtThrFileAnd2D->Write();
  accPerEvtThrFileDeno->Write();
  accPerEvtThrFileSumEt2D->Write();
  accPerEvtThrFileSumEtAnd2D->Write();
  accPerEvtThrFileSumEtDeno->Write();

  idFired->TH1F::Sumw2();
  idFired->SetBinContent(1,evtsTot);
  idFired_frac->Add(idFired,pow(evtsTot,-1));
  idFired->Write();
  idFired_frac->Write();

  bxNum->Write();
  nMBHF1_firedBX->Write();
  nMBHF2_firedBX->Write();

  TH1F* HF1_OR_frac_vsLumi=new TH1F("HF1_OR_frac_vsLumi","HF1_OR_frac_vsLumi",1000,0,1000);
  TH1F* HF2_OR_frac_vsLumi=new TH1F("HF2_OR_frac_vsLumi","HF2_OR_frac_vsLumi",1000,0,1000);

  HF1_OR_vsLumi->TH1F::Sumw2();
  HF2_OR_vsLumi->TH1F::Sumw2();
  ZB_vsLumi->TH1F::Sumw2();

  HF1_OR_frac_vsLumi->Divide(HF1_OR_vsLumi,ZB_vsLumi,1,1,"B");
  HF2_OR_frac_vsLumi->Divide(HF2_OR_vsLumi,ZB_vsLumi,1,1,"B");

  ZB_vsLumi->Write();
  
  HF1_OR_frac_vsLumi->Write();
  HF2_OR_frac_vsLumi->Write();

  HF1_OR_vsLumi->Write();
  HF2_OR_vsLumi->Write();
  ZB_vsLumi->Write();

  crossTest_HF1->Write();
  crossTest_HF2->Write();
 
  jetCrossTest8->Write();
  jetCrossTest12->Write();

  hL1jetsEta8->Write();
  hL1jetsEta12->Write();
  
  TDirectory *ctdir = outputFile->mkdir("CaloTowers");
  ctdir->cd();
  TH1F* hCaloTower_TrigEff8[8];
  TH1F* hCaloTower_TrigEff12[8];
  TH1F* hCaloTower_TrigEffMB[8];
  char tmp[100];
  for (int i=0; i<8; i++)
    {
      hCaloTowerETtrig8[i]->TH1F::Sumw2();
      hCaloTowerETtrig12[i]->TH1F::Sumw2();
      hCaloTowerETtrigMB[i]->TH1F::Sumw2();
      hCaloTowerET[i]->TH1F::Sumw2();
      
      sprintf(tmp,"hCaloTower_TrigEff8_%d",i);
      hCaloTower_TrigEff8[i]=new TH1F(tmp,tmp,1000,0,1000);
      hCaloTower_TrigEff8[i]->Divide(hCaloTowerETtrig8[i],hCaloTowerET[i],1,1,"B");
      
      sprintf(tmp,"hCaloTower_TrigEff12_%d",i);
      hCaloTower_TrigEff12[i]=new TH1F(tmp,tmp,1000,0,1000);
      hCaloTower_TrigEff12[i]->Divide(hCaloTowerETtrig12[i],hCaloTowerET[i],1,1,"B");
      
      sprintf(tmp,"hCaloTower_TrigEffMB_%d",i);
      hCaloTower_TrigEffMB[i]=new TH1F(tmp,tmp,1000,0,1000);
      hCaloTower_TrigEffMB[i]->Divide(hCaloTowerETtrigMB[i],hCaloTowerET[i],1,1,"B");
      
      hCaloTowerET[i]->Write();
      hCaloTowerETtrig8[i]->Write();
      hCaloTowerETtrig12[i]->Write();
      hCaloTowerETtrigMB[i]->Write();
      hCaloTower_TrigEff8[i]->Write();
      hCaloTower_TrigEff12[i]->Write();
      hCaloTower_TrigEffMB[i]->Write();
    }

  TDirectory *rhdir = outputFile->mkdir("RecHits");
  rhdir->cd();
  TH1F* hRecHit_TrigEff8[8];
  TH1F* hRecHit_TrigEff12[8];
  TH1F* hRecHit_TrigEffMB[8];
  for (int i=0; i<8; i++)
    {
      hRecHitETtrigMB[i]->TH1F::Sumw2();
      hRecHitETtrig8[i]->TH1F::Sumw2();
      hRecHitETtrig12[i]->TH1F::Sumw2();
      hRecHitET[i]->TH1F::Sumw2();
      
      sprintf(tmp,"hRecHit_TrigEff8_%d",i);
      hRecHit_TrigEff8[i]=new TH1F(tmp,tmp,1000,0,1000);
      hRecHit_TrigEff8[i]->Divide(hRecHitETtrig8[i],hRecHitET[i],1,1,"B");
      
      sprintf(tmp,"hRecHit_TrigEff12_%d",i);
      hRecHit_TrigEff12[i]=new TH1F(tmp,tmp,1000,0,1000);
      hRecHit_TrigEff12[i]->Divide(hRecHitETtrig12[i],hRecHitET[i],1,1,"B");
      
      sprintf(tmp,"hRecHit_TrigEffMB_%d",i);
      hRecHit_TrigEffMB[i]=new TH1F(tmp,tmp,1000,0,1000);
      hRecHit_TrigEffMB[i]->Divide(hRecHitETtrigMB[i],hRecHitET[i],1,1,"B");

      hRecHitET[i]->Write();
      hRecHitETtrig8[i]->Write();
      hRecHitETtrig12[i]->Write();
      hRecHitETtrigMB[i]->Write();

      hRecHit_TrigEff8[i]->Write();
      hRecHit_TrigEff12[i]->Write();
      hRecHit_TrigEffMB[i]->Write();
    }

  TDirectory *cjdir = outputFile->mkdir("CaloJets");
  cjdir->cd();
  TH1F* hCaloJetPlus_TrigEff8=new TH1F("hCaloJetPlus_TrigEff8","hCaloJetPlus_TrigEff8",1000,0,1000);
  TH1F* hCaloJetPlus_TrigEff12=new TH1F("hCaloJetPlus_TrigEff12","hCaloJetPlus_TrigEff12",1000,0,1000);
  TH1F* hCaloJetPlus_TrigEffMB=new TH1F("hCaloJetPlus_TrigEffMB","hCaloJetPlus_TrigEffMB",1000,0,1000);

  TH1F* hCaloJetMinus_TrigEff8=new TH1F("hCaloJetMinus_TrigEff8","hCaloJetMinus_TrigEff8",1000,0,1000);
  TH1F* hCaloJetMinus_TrigEff12=new TH1F("hCaloJetMinus_TrigEff12","hCaloJetMinus_TrigEff12",1000,0,1000);
  TH1F* hCaloJetMinus_TrigEffMB=new TH1F("hCaloJetMinus_TrigEffMB","hCaloJetMinus_TrigEffMB",1000,0,1000);
      
  hCaloJetPlusETtrig8->TH1F::Sumw2();
  hCaloJetPlusETtrig12->TH1F::Sumw2();
  hCaloJetPlusETtrigMB->TH1F::Sumw2();
  hCaloJetPlusET->TH1F::Sumw2();
  
  hCaloJetMinusETtrig8->TH1F::Sumw2();
  hCaloJetMinusETtrig12->TH1F::Sumw2();
  hCaloJetMinusETtrigMB->TH1F::Sumw2();
  hCaloJetMinusET->TH1F::Sumw2();

  hCaloJetPlusETtrig8->Write();
  hCaloJetPlusETtrig12->Write();
  hCaloJetPlusETtrigMB->Write();
  hCaloJetPlusET->Write();

  hCaloJetMinusETtrig8->Write();
  hCaloJetMinusETtrig12->Write();
  hCaloJetMinusETtrigMB->Write();
  hCaloJetMinusET->Write();
  
  hCaloJetPlus_TrigEff8->Divide(hCaloJetPlusETtrig8, hCaloJetPlusET,1,1,"B");
  hCaloJetPlus_TrigEff12->Divide(hCaloJetPlusETtrig12, hCaloJetPlusET,1,1,"B");
  hCaloJetPlus_TrigEffMB->Divide(hCaloJetPlusETtrigMB, hCaloJetPlusET,1,1,"B");

  hCaloJetMinus_TrigEff8->Divide(hCaloJetMinusETtrig8, hCaloJetMinusET,1,1,"B");
  hCaloJetMinus_TrigEff12->Divide(hCaloJetMinusETtrig12, hCaloJetMinusET,1,1,"B");
  hCaloJetMinus_TrigEffMB->Divide(hCaloJetMinusETtrigMB, hCaloJetMinusET,1,1,"B");

  hCaloJetPlus_TrigEff8->Write();
  hCaloJetPlus_TrigEff12->Write();
  hCaloJetPlus_TrigEffMB->Write();

  hCaloJetMinus_TrigEff8->Write();
  hCaloJetMinus_TrigEff12->Write();
  hCaloJetMinus_TrigEffMB->Write();

  std::cout<<"wrote stuff"<<std::endl;
}

// ------------ method called when starting to processes a run  ------------

void 
MBtriggerEfficiency::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
/*
  bool useL1EventSetup = true;
  bool useL1GtTriggerMenuLite = false;
  
  // could be added in beginRun(...) - if not added, the caching will be done in analyze/produce/filter method
  m_l1GtUtils.getL1GtRunCache(iRun, iSetup, useL1EventSetup, useL1GtTriggerMenuLite);
*/
}

// ------------ method called when ending the processing of a run  ------------
/*
void 
MBtriggerEfficiency::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
MBtriggerEfficiency::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
MBtriggerEfficiency::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MBtriggerEfficiency::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MBtriggerEfficiency);
