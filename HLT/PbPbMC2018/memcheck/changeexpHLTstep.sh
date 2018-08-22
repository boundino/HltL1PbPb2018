#!/bin/bash

# CONFIG=expHLT_102X_ImportV17_cfg
CONFIG=expHLT_102X_TrkV43_cfg

VERBOSE=1

set -x
edmConfigDump ${CONFIG}.py >& ${CONFIG}_modv2_DUMP_default.py
sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_modv2_DUMP_default.py
set +x

cp ${CONFIG}.py ${CONFIG}_modv2.py

echo "-----------------------------"

# step 1 : useSimpleMF

echo '
# closer to offline
process.hltFullIter0CtfWithMaterialTracksPreSplittingPPOnAA.useSimpleMF = cms.bool(False)
' >> ${CONFIG}_modv2.py
for i in {0..10}
do
    echo '
process.hltFullIter'${i}'CtfWithMaterialTracksPPOnAA.useSimpleMF = cms.bool(False)' >> ${CONFIG}_modv2.py
done
set -x
cp ${CONFIG}_modv2.py ${CONFIG}_modv2_step1.py
edmConfigDump ${CONFIG}_modv2_step1.py >& ${CONFIG}_modv2_DUMP_step1.py
sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_modv2_DUMP_step1.py
rm ${CONFIG}_modv2_step1.pyc
rm ${CONFIG}_modv2_step1.py
set +x

diff --report-identical-files --old-group-format=$'\e[38;2;210;106;112m%<\e[0m' --new-group-format=$'\e[38;2;132;192;127;1m%>\e[0m' --unchanged-group-format='' ${CONFIG}_modv2_DUMP_default.py  ${CONFIG}_modv2_DUMP_step1.py

echo "-----------------------------"

# step 2 : numHitsForSeedCleaner

for i in {0..9}
do
    echo '
process.hltFullIter'${i}'CkfTrackCandidatesPPOnAA.numHitsForSeedCleaner = cms.int32(50)
process.hltFullIter'${i}'CkfTrackCandidatesPPOnAA.onlyPixelHitsForSeedCleaner = cms.bool(True)' >> ${CONFIG}_modv2.py
done
set -x
cp ${CONFIG}_modv2.py ${CONFIG}_modv2_step2.py
edmConfigDump ${CONFIG}_modv2_step2.py >& ${CONFIG}_modv2_DUMP_step2.py
sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_modv2_DUMP_step2.py
rm ${CONFIG}_modv2_step2.pyc
rm ${CONFIG}_modv2_step2.py
set +x

diff --report-identical-files --old-group-format=$'\e[38;2;210;106;112m%<\e[0m' --new-group-format=$'\e[38;2;132;192;127;1m%>\e[0m' --unchanged-group-format='' ${CONFIG}_modv2_DUMP_step1.py  ${CONFIG}_modv2_DUMP_step2.py

echo "-----------------------------"

# step 3 : RefRemoval.trackClassifier

for i in {1..9}
do
    echo '
process.hltFullIter'${i}'ClustersRefRemovalPPOnAA.trackClassifier = cms.InputTag("hltFullIter'$(($i-1))'TrackMVAClassifierPPOnAA","QualityMasks")
' >> ${CONFIG}_modv2.py
done
set -x
cp ${CONFIG}_modv2.py ${CONFIG}_modv2_step3.py
edmConfigDump ${CONFIG}_modv2_step3.py >& ${CONFIG}_modv2_DUMP_step3.py
sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_modv2_DUMP_step3.py
rm ${CONFIG}_modv2_step3.pyc
rm ${CONFIG}_modv2_step3.py
set +x

diff --report-identical-files --old-group-format=$'\e[38;2;210;106;112m%<\e[0m' --new-group-format=$'\e[38;2;132;192;127;1m%>\e[0m' --unchanged-group-format='' ${CONFIG}_modv2_DUMP_step2.py  ${CONFIG}_modv2_DUMP_step3.py

echo "-----------------------------"

# step 4 : produceSeed

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
set -x
cp ${CONFIG}_modv2.py ${CONFIG}_modv2_step4.py
edmConfigDump ${CONFIG}_modv2_step4.py >& ${CONFIG}_modv2_DUMP_step4.py
sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_modv2_DUMP_step4.py
rm ${CONFIG}_modv2_step4.pyc
rm ${CONFIG}_modv2_step4.py
set +x

diff --report-identical-files --old-group-format=$'\e[38;2;210;106;112m%<\e[0m' --new-group-format=$'\e[38;2;132;192;127;1m%>\e[0m' --unchanged-group-format='' ${CONFIG}_modv2_DUMP_step3.py  ${CONFIG}_modv2_DUMP_step4.py

echo "-----------------------------"


# step 5 : ChannelThreshold

echo '
process.hltFullIter10JetCoreTrackingRegionsPPOnAA.RegionPSet.howToUseMeasurementTracker = cms.string('"'"'Never'"'"')
process.hltFullIter9CtfWithMaterialTracksPPOnAA.TrajectoryInEvent = cms.bool(False)
process.hltSiPixelClustersPPOnAA.ChannelThreshold = cms.int32(10)
' >> ${CONFIG}_modv2.py
set -x
cp ${CONFIG}_modv2.py ${CONFIG}_modv2_step5.py
edmConfigDump ${CONFIG}_modv2_step5.py >& ${CONFIG}_modv2_DUMP_step5.py
sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_modv2_DUMP_step5.py
rm ${CONFIG}_modv2_step5.pyc
rm ${CONFIG}_modv2_step5.py
set +x

diff --report-identical-files --old-group-format=$'\e[38;2;210;106;112m%<\e[0m' --new-group-format=$'\e[38;2;132;192;127;1m%>\e[0m' --unchanged-group-format='' ${CONFIG}_modv2_DUMP_step4.py  ${CONFIG}_modv2_DUMP_step5.py

echo "-----------------------------"


## step 6 --> 7 ##

set -x
edmConfigDump ${CONFIG}_modv2.py >& ${CONFIG}_modv2_DUMP_step6.py
rm ${CONFIG}_modv2.pyc
rm ${CONFIG}_modv2.py
sed -i 's/rawDataRepacker/rawDataCollector/g' ${CONFIG}_modv2_DUMP_step6.py
set +x

# step 6 : remove repeated strip clusterizer

sed -i 's/hltSiStripRawToClustersFacilityFull\([^[:space:]]\)/hltSiStripRawToClustersFacility\1/g' ${CONFIG}_modv2_DUMP_step6.py

diff --report-identical-files --old-group-format=$'\e[38;2;210;106;112m%<\e[0m' --new-group-format=$'\e[38;2;132;192;127;1m%>\e[0m' --unchanged-group-format='' ${CONFIG}_modv2_DUMP_step5.py  ${CONFIG}_modv2_DUMP_step6.py

echo "-----------------------------"

# step 7 : move to after-splitting pixel clusters

cp ${CONFIG}_modv2_DUMP_step6.py ${CONFIG}_modv2_temp.py
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
cp ${CONFIG}_modv2_temp.py ${CONFIG}_modv2_temp_step7.py
edmConfigDump ${CONFIG}_modv2_temp_step7.py >& ${CONFIG}_modv2_DUMP_step7.py
rm ${CONFIG}_modv2_temp_step7.pyc
rm ${CONFIG}_modv2_temp_step7.py
rm ${CONFIG}_modv2_temp.py
set +x

diff --report-identical-files --old-group-format=$'\e[38;2;210;106;112m%<\e[0m' --new-group-format=$'\e[38;2;132;192;127;1m%>\e[0m' --unchanged-group-format='' ${CONFIG}_modv2_DUMP_step6.py  ${CONFIG}_modv2_DUMP_step7.py

echo "-----------------------------"

# end