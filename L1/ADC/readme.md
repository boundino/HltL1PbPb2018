
<pre>
process.HFAdcana = cms.EDAnalyzer("HFAdcToGeV",
    digiLabel = cms.untracked.InputTag("hcalDigis")
)

process.MBefficiency = cms.EDAnalyzer("MBtriggerEfficiency",
    # hcalToken = cms.untracked.InputTag("simHcalTriggerPrimitiveDigis"),
    # triggerPrimitives = cms.InputTag("simHcalTriggerPrimitiveDigis"),
    outputFileName = cms.string("testMBeff.root"),
    hfDigiTag = cms.untracked.InputTag("hcalDigis"),
    caloTowerTag = cms.InputTag("towerMaker"),
    # caloTowerTag = cms.InputTag("simCaloStage2Layer1Digis"),
    trackTag = cms.InputTag("generalTracks"),
    vertexTag = cms.InputTag("offlinePrimaryVertices"),
)
</pre>
