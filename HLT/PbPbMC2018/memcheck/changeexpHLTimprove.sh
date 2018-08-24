#!/bin/bash

CONFIG=expHLT_102X_ImportV18_cfg
# CONFIG=expHLT_102X_TrkV43_cfg

cp ${CONFIG}.py ${CONFIG}_modv2.py

## change parameters i

# echo '
# # closer to offline
# process.hltFullIter0CtfWithMaterialTracksPreSplittingPPOnAA.useSimpleMF = cms.bool(False)
# ' >> ${CONFIG}_modv2.py
# for i in {0..10}
# do
#     echo '
# process.hltFullIter'${i}'CtfWithMaterialTracksPPOnAA.useSimpleMF = cms.bool(False)' >> ${CONFIG}_modv2.py
#     [[ $i -eq 10 ]] && continue
#     echo '
# process.hltFullIter'${i}'CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.int32(50)
# process.hltFullIter'${i}'CkfTrackCandidatesPPOnAA.onlyPixelHitsForSeedCleaner = cms.bool(True)' >> ${CONFIG}_modv2.py
#     [[ $i -eq 0 ]] && continue
#     echo '
# process.hltFullIter'${i}'ClustersRefRemovalPPOnAA.trackClassifier = cms.InputTag("hltFullIter'$(($i-1))'TrackMVAClassifierPPOnAA","QualityMasks")
# ' >> ${CONFIG}_modv2.py
# done

# change parameters ii

echo '
process.hltFullIter10JetCoreHitDoubletsPPOnAA.produceIntermediateHitDoublets = cms.bool(False)
process.hltFullIter6PixelHitDoubletsAPPOnAA.produceIntermediateHitDoublets = cms.bool(False)
process.hltFullIter6PixelHitDoubletsBPPOnAA.produceIntermediateHitDoublets = cms.bool(False)
process.hltFullIter9TobTecHitDoubletsPairPPOnAA.produceIntermediateHitDoublets = cms.bool(False)
process.hltFullIter2PixelHitDoubletsPPOnAA.produceSeedingHitSets = cms.bool(False)
process.hltFullIter3PixelHitDoubletsPPOnAA.produceSeedingHitSets = cms.bool(False)
process.hltFullIter4PixelHitDoubletsPPOnAA.produceSeedingHitSets = cms.bool(False)
process.hltFullIter5PixelHitDoubletsPPOnAA.produceSeedingHitSets = cms.bool(False)
process.hltFullIter7MixedHitDoubletsAPPOnAA.produceSeedingHitSets = cms.bool(False)
process.hltFullIter7MixedHitDoubletsBPPOnAA.produceSeedingHitSets = cms.bool(False)
' >> ${CONFIG}_modv2.py

# change parameters iii

# echo '
# process.hltFullIter10JetCoreTrackingRegionsPPOnAA.RegionPSet.howToUseMeasurementTracker = cms.string('"'"'Never'"'"')
# process.hltFullIter9CtfWithMaterialTracksPPOnAA.TrajectoryInEvent = cms.bool(False)
# process.hltSiPixelClustersPPOnAA.ChannelThreshold = cms.int32(10)
# ' >> ${CONFIG}_modv2.py

set -x
edmConfigDump ${CONFIG}_modv2.py >& ${CONFIG}_modv2_DUMP.py
rm ${CONFIG}_modv2.pyc
rm ${CONFIG}_modv2.py
set +x

sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_modv2_DUMP.py

# remove repeated strip clusterizer

# sed -i 's/hltSiStripRawToClustersFacilityFull\([^[:space:]]\)/hltSiStripRawToClustersFacility\1/g' ${CONFIG}_modv2_DUMP.py

# move to after-splitting pixel clusters

cp ${CONFIG}_modv2_DUMP.py ${CONFIG}_modv2_temp.py
sed -i 's/hltSiPixelClustersPPOnAA\(["'"'"']\)/hltSiPixelClustersAfterSplittingPPOnAA\1/g' ${CONFIG}_modv2_temp.py
echo '
process.hltFullIter0PixelClusterCheckPreSplittingPPOnAA.PixelClusterCollectionLabel = cms.InputTag("hltSiPixelClustersPPOnAA")
process.hltSiPixelClustersAfterSplittingPPOnAA.pixelClusters = cms.InputTag("hltSiPixelClustersPPOnAA")
process.hltSiPixelClustersCachePPOnAA.src = cms.InputTag("hltSiPixelClustersPPOnAA")
process.hltSiPixelRecHitsPPOnAA.src = cms.InputTag("hltSiPixelClustersPPOnAA")
process.hltSiStripClustersPPOnAA.pixelClusterProducer = cms.string('"'"'hltSiPixelClustersPPOnAA'"'"')
' >> ${CONFIG}_modv2_temp.py
sed -i 's/hltSiPixelClustersCachePPOnAA\(["'"'"']\)/hltSiPixelClustersCacheAfterSplittingPPOnAA\1/g' ${CONFIG}_modv2_temp.py
echo '
process.hltFullIter0PixelHitQuadrupletsPreSplittingPPOnAA.SeedComparitorPSet.clusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCachePPOnAA")
process.hltFullIter0PixelSeedsPreSplittingPPOnAA.SeedComparitorPSet.ClusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCachePPOnAA")
' >> ${CONFIG}_modv2_temp.py
sed -i 's/hltSiPixelRecHitsPPOnAA\(["'"'"']\)/hltSiPixelRecHitsAfterSplittingPPOnAA\1/g' ${CONFIG}_modv2_temp.py
echo '
process.hltFullIter0PixelQuadrupletsPreSplittingPPOnAA.BPix.HitProducer = cms.string('"'"'hltSiPixelRecHitsPPOnAA'"'"')
process.hltFullIter0PixelQuadrupletsPreSplittingPPOnAA.FPix.HitProducer = cms.string('"'"'hltSiPixelRecHitsPPOnAA'"'"')
' >> ${CONFIG}_modv2_temp.py

set -x
edmConfigDump ${CONFIG}_modv2_temp.py >& ${CONFIG}_modv2improve_DUMP.py
rm ${CONFIG}_modv2_temp.pyc
rm ${CONFIG}_modv2_temp.py
set +x
