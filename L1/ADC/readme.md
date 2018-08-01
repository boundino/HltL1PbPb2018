
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

process.L1TReEmul = cms.Sequence(process.simEcalTriggerPrimitiveDigis+process.simHcalTriggerPrimitiveDigis+process.SimL1Emulator+process.MBefficiency)
