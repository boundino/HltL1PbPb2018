#!/bin/bash

# CONFIG=expHLT_102X_ImportV22L1_cfg
CONFIG=expHLT_102X_TrkV50_cfg

##
emulL1="--l1-emulator FullMC --l1Xml=L1Menu_CollisionsHeavyIons2018_v3_rmAsyCent.xml"
# emulL1=""

cp setup_dev_CMSSW_10_1_0_GRun_cff.py setup_dev_CMSSW_10_1_0_GRun_trajectorypset_cff.py

echo '
HLTPSetInitialStepTrajectoryFilterPPOnAA = HLTPSetInitialStepTrajectoryFilter.clone( )
HLTPSetJetCoreStepTrajectoryFilterPPOnAA = HLTPSetJetCoreStepTrajectoryFilter.clone( )
HLTPSetLowPtQuadStepTrajectoryFilterPPOnAA = HLTPSetLowPtQuadStepTrajectoryFilter.clone( )
HLTPSetHighPtTripletStepTrajectoryFilterPPOnAA = HLTPSetHighPtTripletStepTrajectoryFilter.clone( )
HLTPSetLowPtTripletStepTrajectoryFilterPPOnAA = HLTPSetLowPtTripletStepTrajectoryFilter.clone( )
HLTPSetDetachedQuadStepTrajectoryFilterPPOnAA = HLTPSetDetachedQuadStepTrajectoryFilter.clone( )
HLTPSetDetachedTripletStepTrajectoryFilterPPOnAA = HLTPSetDetachedTripletStepTrajectoryFilter.clone( )
HLTPSetPixelPairStepTrajectoryFilterPPOnAA = HLTPSetPixelPairStepTrajectoryFilter.clone( )
HLTPSetMixedTripletStepTrajectoryFilterPPOnAA = HLTPSetMixedTripletStepTrajectoryFilter.clone( )
HLTPSetPixelLessStepTrajectoryFilterPPOnAA = HLTPSetPixelLessStepTrajectoryFilter.clone( )
HLTPSetTobTecStepInOutTrajectoryFilterPPOnAA = HLTPSetTobTecStepInOutTrajectoryFilter.clone( )
HLTPSetTobTecStepTrajectoryFilterPPOnAA = HLTPSetTobTecStepTrajectoryFilter.clone( )

HLTPSetInitialStepTrajectoryBuilderPPOnAA = HLTPSetInitialStepTrajectoryBuilder.clone( )
HLTPSetJetCoreStepTrajectoryBuilderPPOnAA = HLTPSetJetCoreStepTrajectoryBuilder.clone( )
HLTPSetLowPtQuadStepTrajectoryBuilderPPOnAA = HLTPSetLowPtQuadStepTrajectoryBuilder.clone( )
HLTPSetHighPtTripletStepTrajectoryBuilderPPOnAA = HLTPSetHighPtTripletStepTrajectoryBuilder.clone( )
HLTPSetLowPtTripletStepTrajectoryBuilderPPOnAA = HLTPSetLowPtTripletStepTrajectoryBuilder.clone( )
HLTPSetDetachedQuadStepTrajectoryBuilderPPOnAA = HLTPSetDetachedQuadStepTrajectoryBuilder.clone( )
HLTPSetDetachedTripletStepTrajectoryBuilderPPOnAA = HLTPSetDetachedTripletStepTrajectoryBuilder.clone( )
HLTPSetPixelPairStepTrajectoryBuilderPPOnAA = HLTPSetPixelPairStepTrajectoryBuilder.clone( )
HLTPSetMixedTripletStepTrajectoryBuilderPPOnAA = HLTPSetMixedTripletStepTrajectoryBuilder.clone( )
HLTPSetPixelLessStepTrajectoryBuilderPPOnAA = HLTPSetPixelLessStepTrajectoryBuilder.clone( )
HLTPSetTobTecStepTrajectoryBuilderPPOnAA = HLTPSetTobTecStepTrajectoryBuilder.clone( )

HLTPSetInitialStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetInitialStepTrajectoryFilterPPOnAA'"'"')
HLTPSetJetCoreStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetJetCoreStepTrajectoryFilterPPOnAA'"'"')
HLTPSetLowPtQuadStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetLowPtQuadStepTrajectoryFilterPPOnAA'"'"')
HLTPSetHighPtTripletStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetHighPtTripletStepTrajectoryFilterPPOnAA'"'"')
HLTPSetLowPtTripletStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetLowPtTripletStepTrajectoryFilterPPOnAA'"'"')
HLTPSetDetachedQuadStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetDetachedQuadStepTrajectoryFilterPPOnAA'"'"')
HLTPSetDetachedTripletStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetDetachedTripletStepTrajectoryFilterPPOnAA'"'"')
HLTPSetPixelPairStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetPixelPairStepTrajectoryFilterPPOnAA'"'"')
HLTPSetMixedTripletStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetMixedTripletStepTrajectoryFilterPPOnAA'"'"')
HLTPSetPixelLessStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetPixelLessStepTrajectoryFilterPPOnAA'"'"')
HLTPSetTobTecStepTrajectoryBuilderPPOnAA.trajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetTobTecStepTrajectoryFilterPPOnAA'"'"')

HLTPSetInitialStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetJetCoreStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetLowPtQuadStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetHighPtTripletStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetLowPtTripletStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetDetachedQuadStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetDetachedTripletStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
# pixelpair
HLTPSetMixedTripletStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetPixelLessStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetTobTecStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetTobTecStepInOutTrajectoryFilterPPOnAA'"'"')

HLTPSetCkfBaseTrajectoryFilter_block = cms.PSet(
    ComponentType = cms.string('"'"'CkfBaseTrajectoryFilter'"'"'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('"'"'HLTSiStripClusterChargeCutNone'"'"')
    ),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.9),
    minimumNumberOfHits = cms.int32(5),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

HLTPSetInitialStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetJetCoreStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetLowPtQuadStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetHighPtTripletStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetLowPtTripletStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetDetachedQuadStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetDetachedTripletStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetMixedTripletStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
HLTPSetPixelLessStepTrajectoryBuilderPPOnAA.inOutTrajectoryFilter.refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')

HLTPSetInitialStepTrajectoryFilterPPOnAA.minPt = cms.double(0.6)
HLTPSetJetCoreStepTrajectoryFilterPPOnAA.minPt = cms.double(5.0)
HLTPSetLowPtQuadStepTrajectoryFilterPPOnAA.minPt = cms.double(0.49)
HLTPSetHighPtTripletStepTrajectoryFilterPPOnAA.minPt = cms.double(0.7)
HLTPSetLowPtTripletStepTrajectoryFilterPPOnAA.minPt = cms.double(0.49)
HLTPSetDetachedQuadStepTrajectoryFilterPPOnAA.minPt = cms.double(0.9)
HLTPSetDetachedTripletStepTrajectoryFilterPPOnAA.minPt = cms.double(0.9)
HLTPSetPixelPairStepTrajectoryFilterPPOnAA.minPt = cms.double(0.1)
HLTPSetMixedTripletStepTrajectoryFilterPPOnAA.minPt = cms.double(0.4)
HLTPSetPixelLessStepTrajectoryFilterPPOnAA.minPt = cms.double(2.0)
HLTPSetTobTecStepInOutTrajectoryFilterPPOnAA.minPt = cms.double(2.0)
HLTPSetTobTecStepTrajectoryFilterPPOnAA.minPt = cms.double(2.0)

HLTPSetInitialStepTrajectoryBuilderPreSplittingPPOnAA = cms.PSet(
    ComponentType = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"'),
    MeasurementTrackerName = cms.string('"'"''"'"'),
    TTRHBuilder = cms.string('"'"'hltESPTTRHBWithTrackAngle'"'"'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('"'"'hltESPInitialStepChi2ChargeMeasurementEstimator30'"'"'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('"'"'HLTPSetCkfBaseTrajectoryFilter_block'"'"')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('"'"'PropagatorWithMaterialParabolicMf'"'"'),
    propagatorOpposite = cms.string('"'"'PropagatorWithMaterialParabolicMfOpposite'"'"'),
    requireSeedHitsInRebuild = cms.bool(True),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('"'"'HLTPSetInitialStepTrajectoryFilterPreSplittingPPOnAA'"'"')
    ),
    updator = cms.string('"'"'hltESPKFUpdator'"'"'),
    useSameTrajFilter = cms.bool(True)
)

HLTPSetInitialStepTrajectoryFilterPreSplittingPPOnAA = cms.PSet(
    ComponentType = cms.string('"'"'CompositeTrajectoryFilter'"'"'),
    filters = cms.VPSet(
        cms.PSet(
            refToPSet_ = cms.string('"'"'HLTPSetInitialStepTrajectoryFilterBasePreSplittingPPOnAA'"'"')
        ),
        cms.PSet(
            refToPSet_ = cms.string('"'"'HLTPSetInitialStepTrajectoryFilterShapePreSplittingPPOnAA'"'"')
        )
    )
)

HLTPSetInitialStepTrajectoryFilterBasePreSplittingPPOnAA = cms.PSet(
    ComponentType = cms.string('"'"'CkfBaseTrajectoryFilter'"'"'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('"'"'HLTSiStripClusterChargeCutLoose'"'"')
    ),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.2),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

HLTPSetInitialStepTrajectoryFilterShapePreSplittingPPOnAA = cms.PSet(
    ComponentType = cms.string('"'"'StripSubClusterShapeTrajectoryFilter'"'"'),
    layerMask = cms.PSet(
        TEC = cms.bool(False),
        TIB = cms.vuint32(1, 2),
        TID = cms.vuint32(1, 2),
        TOB = cms.bool(False)
    ),
    maxNSat = cms.uint32(3),
    maxTrimmedSizeDiffNeg = cms.double(1.0),
    maxTrimmedSizeDiffPos = cms.double(0.7),
    seedCutMIPs = cms.double(0.35),
    seedCutSN = cms.double(7.0),
    subclusterCutMIPs = cms.double(0.45),
    subclusterCutSN = cms.double(12.0),
    subclusterWindow = cms.double(0.7),
    trimMaxADC = cms.double(30.0),
    trimMaxFracNeigh = cms.double(0.25),
    trimMaxFracTotal = cms.double(0.15)
)

HLTPSetJetCoreStepTrajectoryBuilderPPOnAA.foundHitBonus = cms.double(10.0)
HLTPSetHighPtTripletStepTrajectoryFilterPPOnAA.seedPairPenalty = cms.int32(0)

' >> setup_dev_CMSSW_10_1_0_GRun_trajectorypset_cff.py

cp ${CONFIG}.py ${CONFIG}_trajectorypset.py

echo '
process.hltFullIter0CkfTrackCandidatesPreSplittingPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetInitialStepTrajectoryBuilderPreSplittingPPOnAA'"'"')
process.hltFullIter0CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetInitialStepTrajectoryBuilderPPOnAA'"'"')
process.hltFullIter1CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetLowPtQuadStepTrajectoryBuilderPPOnAA'"'"')
process.hltFullIter2CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetHighPtTripletStepTrajectoryBuilderPPOnAA'"'"')
process.hltFullIter3CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetLowPtTripletStepTrajectoryBuilderPPOnAA'"'"')
process.hltFullIter4CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetDetachedQuadStepTrajectoryBuilderPPOnAA'"'"')
process.hltFullIter5CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetDetachedTripletStepTrajectoryBuilderPPOnAA'"'"')
process.hltFullIter6CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetPixelPairStepTrajectoryBuilderPPOnAA'"'"')
process.hltFullIter7CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetMixedTripletStepTrajectoryBuilderPPOnAA'"'"')
process.hltFullIter8CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetPixelLessStepTrajectoryBuilderPPOnAA'"'"')
process.hltFullIter9CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetTobTecStepTrajectoryBuilderPPOnAA'"'"')
process.hltFullIter10CkfTrackCandidatesPPOnAA.TrajectoryBuilderPSet.refToPSet_ = cms.string('"'"'HLTPSetJetCoreStepTrajectoryBuilderPPOnAA'"'"')

process.hltFullIter0CkfTrackCandidatesPreSplittingPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
process.hltFullIter0CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
process.hltFullIter1CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
process.hltFullIter2CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
process.hltFullIter3CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
process.hltFullIter4CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
process.hltFullIter5CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
process.hltFullIter6CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
# process.hltFullIter7CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
process.hltFullIter8CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
process.hltFullIter9CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')
process.hltFullIter10CkfTrackCandidatesPPOnAA.TrajectoryBuilder = cms.string('"'"'GroupedCkfTrajectoryBuilder'"'"')

process.hltFullIter0CkfTrackCandidatesPreSplittingPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)
process.hltFullIter0CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)
process.hltFullIter1CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)
process.hltFullIter2CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)
process.hltFullIter3CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)
process.hltFullIter4CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)
process.hltFullIter5CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)
process.hltFullIter6CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)
process.hltFullIter7CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)
process.hltFullIter8CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)
process.hltFullIter9CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.untracked.int32(50)

process.hltFullIter0CkfTrackCandidatesPreSplittingPPOnAA.onlyPixelHitsForSeedCleaner = cms.untracked.bool(True)
process.hltFullIter0CkfTrackCandidatesPPOnAA.onlyPixelHitsForSeedCleaner = cms.untracked.bool(True)
process.hltFullIter1CkfTrackCandidatesPPOnAA.onlyPixelHitsForSeedCleaner = cms.untracked.bool(True)
process.hltFullIter2CkfTrackCandidatesPPOnAA.onlyPixelHitsForSeedCleaner = cms.untracked.bool(True)
process.hltFullIter3CkfTrackCandidatesPPOnAA.onlyPixelHitsForSeedCleaner = cms.untracked.bool(True)
process.hltFullIter4CkfTrackCandidatesPPOnAA.onlyPixelHitsForSeedCleaner = cms.untracked.bool(True)
process.hltFullIter5CkfTrackCandidatesPPOnAA.onlyPixelHitsForSeedCleaner = cms.untracked.bool(True)
process.hltFullIter6CkfTrackCandidatesPPOnAA.onlyPixelHitsForSeedCleaner = cms.untracked.bool(True)
process.hltFullIter9CkfTrackCandidatesPPOnAA.onlyPixelHitsForSeedCleaner = cms.untracked.bool(True)

process.hltFullIter0CkfTrackCandidatesPreSplittingPPOnAA.maxNSeeds = cms.uint32(500000)

process.hltFullIter1CkfTrackCandidatesPPOnAA.clustersToSkip = cms.untracked.InputTag("hltFullIter1ClustersRefRemovalPPOnAA")
process.hltFullIter2CkfTrackCandidatesPPOnAA.clustersToSkip = cms.untracked.InputTag("hltFullIter2ClustersRefRemovalPPOnAA")
process.hltFullIter3CkfTrackCandidatesPPOnAA.clustersToSkip = cms.untracked.InputTag("hltFullIter3ClustersRefRemovalPPOnAA")
process.hltFullIter4CkfTrackCandidatesPPOnAA.clustersToSkip = cms.untracked.InputTag("hltFullIter4ClustersRefRemovalPPOnAA")
process.hltFullIter5CkfTrackCandidatesPPOnAA.clustersToSkip = cms.untracked.InputTag("hltFullIter5ClustersRefRemovalPPOnAA")
process.hltFullIter6CkfTrackCandidatesPPOnAA.clustersToSkip = cms.untracked.InputTag("hltFullIter6ClustersRefRemovalPPOnAA")
process.hltFullIter7CkfTrackCandidatesPPOnAA.clustersToSkip = cms.untracked.InputTag("hltFullIter7ClustersRefRemovalPPOnAA")
process.hltFullIter8CkfTrackCandidatesPPOnAA.clustersToSkip = cms.untracked.InputTag("hltFullIter8ClustersRefRemovalPPOnAA")
process.hltFullIter9CkfTrackCandidatesPPOnAA.clustersToSkip = cms.untracked.InputTag("hltFullIter9ClustersRefRemovalPPOnAA")

' >> ${CONFIG}_trajectorypset.py

sed -i 's/setup_dev_CMSSW_10_1_0_GRun_cff/setup_dev_CMSSW_10_1_0_GRun_trajectorypset_cff/g' ${CONFIG}_trajectorypset.py


set -x
edmConfigDump ${CONFIG}_trajectorypset.py >& ${CONFIG}_trajectorypset_DUMP.py
set +x

sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_trajectorypset_DUMP.py
[[ "x$emulL1" != "x" ]] && { sed -i '1s/^/# /' ${CONFIG}_trajectorypset_DUMP.py ; sed -i '/hgcal/s/^/# /' ${CONFIG}_trajectorypset_DUMP.py; }