### HiForest Configuration
# Collisions: pp
# Type: Data
# Input: AOD

import FWCore.ParameterSet.Config as cms
process = cms.Process('HiForest')
process.options = cms.untracked.PSet()


#####################################################################################
# HiForest labelling info
#####################################################################################

process.load("HeavyIonsAnalysis.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest V3",)
import subprocess
version = subprocess.Popen(["(cd $CMSSW_BASE/src && git describe --tags)"], stdout=subprocess.PIPE, shell=True).stdout.read()
if version == '':
    version = 'no git info'
process.HiForest.HiForestVersion = cms.string(version)

#####################################################################################
# Input source
#####################################################################################

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
        'file:/eos/cms/store/group/phys_heavyions/wangj/lowPUppRECO/ZeroBias/lowPUppRECO_Run319460/180730_211328/0000/step2_RAW2DIGI_L1Reco_RECO_9.root'
        # 'root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/PromptReco-v2/000/319/462/00000/2A0D50B3-6D86-E811-BA6F-FA163E396B84.root'
                                #'/store/data/Run2017G/HighEGJet/AOD/PromptReco-v1/000/306/563/00000/02297D5D-88C9-E711-AA36-02163E01A740.root'
                                #'/store/data/Run2017F/JetHT/AOD/PromptReco-v1/000/305/040/00000/04C8A716-E9B1-E711-9998-02163E01A3EE.root'
                                #'/store/data/Run2015E/HighPtJet80/AOD/PromptReco-v1/000/262/272/00000/803A4255-7696-E511-B178-02163E0142DD.root'
                            ),
                            inputCommands=cms.untracked.vstring(
                              'keep *',
                              'drop TotemTimingDigiedmDetSetVector_totemTimingRawToDigi_TotemTiming_RECO',
                              'drop TotemTimingRecHitedmDetSetVector_totemTimingRecHits__RECO'
                              )
                            # lumisToProcess = cms.untracked.VLuminosityBlockRange('1:1-319462:6')
)

# Number of events we want to process, -1 = all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10))


#####################################################################################
# Load Global Tag, Geometry, etc.
#####################################################################################

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
# process.GlobalTag = GlobalTag(process.GlobalTag, '92X_dataRun2_Prompt_v11', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '101X_dataRun2_Prompt_v11', '')
process.HiForest.GlobalTagLabel = process.GlobalTag.globaltag

# from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import overrideJEC_pp5020
# process = overrideJEC_pp5020(process)

#####################################################################################
# Define tree output
#####################################################################################

process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string("HiForestAOD.root")
                                  )

#####################################################################################
# Additional Reconstruction and Analysis: Main Body
#####################################################################################

####################################################################################


############################
# Event Analysis
############################
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')
process.hiEvtAnalyzer.Vertex = cms.InputTag("offlinePrimaryVertices")
process.hiEvtAnalyzer.doCentrality = cms.bool(True)
process.hiEvtAnalyzer.CentralitySrc = cms.InputTag("hiCentrality")
process.hiEvtAnalyzer.CentralityBinSrc = cms.InputTag("centralityBin","HFtowers")
process.hiEvtAnalyzer.doEvtPlane = cms.bool(False)
process.hiEvtAnalyzer.TowerSrc = cms.InputTag("towerMaker")

process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cff')
from HeavyIonsAnalysis.EventAnalysis.dummybranches_cff import addHLTdummybranchesForPP
addHLTdummybranchesForPP(process)

# process.load("HeavyIonsAnalysis.JetAnalysis.pfcandAnalyzer_cfi")
# process.pfcandAnalyzer.skipCharged = False
# process.pfcandAnalyzer.pfPtMin = 0
# process.pfcandAnalyzer.pfCandidateLabel = cms.InputTag("particleFlow")
# process.pfcandAnalyzer.doVS = cms.untracked.bool(False)
# process.pfcandAnalyzer.doUEraw_ = cms.untracked.bool(False)
# process.pfcandAnalyzer.genLabel = cms.InputTag("genParticles")
# process.load("HeavyIonsAnalysis.JetAnalysis.hcalNoise_cff")

#####################################################################################

#########################
# Main analysis list
#########################


process.ana_step = cms.Path(# process.hltanalysisReco*
			    # process.hltobject *
                            process.hiEvtAnalyzer *
                            process.HiForest 
                            )

#####################################################################################

#########################
# Event Selection
#########################

# process.load('HeavyIonsAnalysis.JetAnalysis.EventSelection_cff')
# process.pHBHENoiseFilterResultProducer = cms.Path( process.HBHENoiseFilterResultProducer )
# process.HBHENoiseFilterResult = cms.Path(process.fHBHENoiseFilterResult)
# process.HBHENoiseFilterResultRun1 = cms.Path(process.fHBHENoiseFilterResultRun1)
# process.HBHENoiseFilterResultRun2Loose = cms.Path(process.fHBHENoiseFilterResultRun2Loose)
# process.HBHENoiseFilterResultRun2Tight = cms.Path(process.fHBHENoiseFilterResultRun2Tight)
# process.HBHEIsoNoiseFilterResult = cms.Path(process.fHBHEIsoNoiseFilterResult)

# process.PAprimaryVertexFilter = cms.EDFilter("VertexSelector",
#     src = cms.InputTag("offlinePrimaryVertices"),
#     cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
#     filter = cms.bool(True), # otherwise it won't filter the events
# )

# process.NoScraping = cms.EDFilter("FilterOutScraping",
#  applyfilter = cms.untracked.bool(True),
#  debugOn = cms.untracked.bool(False),
#  numtrack = cms.untracked.uint32(10),
#  thresh = cms.untracked.double(0.25)
# )

# process.pPAprimaryVertexFilter = cms.Path(process.PAprimaryVertexFilter)
# process.pBeamScrapingFilter=cms.Path(process.NoScraping)

# process.load("HeavyIonsAnalysis.VertexAnalysis.PAPileUpVertexFilter_cff")

# process.pVertexFilterCutG = cms.Path(process.pileupVertexFilterCutG)
# process.pVertexFilterCutGloose = cms.Path(process.pileupVertexFilterCutGloose)
# process.pVertexFilterCutGtight = cms.Path(process.pileupVertexFilterCutGtight)
# process.pVertexFilterCutGplus = cms.Path(process.pileupVertexFilterCutGplus)
# process.pVertexFilterCutE = cms.Path(process.pileupVertexFilterCutE)
# process.pVertexFilterCutEandG = cms.Path(process.pileupVertexFilterCutEandG)

# process.pAna = cms.EndPath(process.skimanalysis)


