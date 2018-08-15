#!/bin/bash

CONFIG="expHLT_102X_cfg_DUMP"

sed 's/'"'"'hltFullIter10TrackMVAClassifierPPOnAA'"'"'/# '"'"'hltFullIter10TrackMVAClassifierPPOnAA'"'"'/g' ${CONFIG}.py > ${CONFIG}_iter0to9.py
sed -i 's/\([^(]\)"hltFullIter10CtfWithMaterialTracksPPOnAA"/\1# "hltFullIter10CtfWithMaterialTracksPPOnAA"/g' ${CONFIG}_iter0to9.py
sed -i 's/+process\.HLTFullIterativeTrackingIteration10PPOnAA+process\.hltFullIterativeTrackingMergedPPOnAA/+process.hltFullIterativeTrackingMergedPPOnAA/g' ${CONFIG}_iter0to9.py

sed 's/'"'"'hltFullIter9TrackMVAClassifierPPOnAA'"'"'/# '"'"'hltFullIter9TrackMVAClassifierPPOnAA'"'"'/g' ${CONFIG}_iter0to9.py > ${CONFIG}_iter0to8.py
sed -i 's/\([^(]\)"hltFullIter9CtfWithMaterialTracksPPOnAA"/\1# "hltFullIter9CtfWithMaterialTracksPPOnAA"/g' ${CONFIG}_iter0to8.py
sed -i 's/+process\.HLTFullIterativeTrackingIteration9PPOnAA+process\.hltFullIterativeTrackingMergedPPOnAA/+process.hltFullIterativeTrackingMergedPPOnAA/g' ${CONFIG}_iter0to8.py

sed 's/'"'"'hltFullIter8TrackMVAClassifierPPOnAA'"'"'/# '"'"'hltFullIter8TrackMVAClassifierPPOnAA'"'"'/g' ${CONFIG}_iter0to8.py > ${CONFIG}_iter0to7.py
sed -i 's/\([^(]\)"hltFullIter8CtfWithMaterialTracksPPOnAA"/\1# "hltFullIter8CtfWithMaterialTracksPPOnAA"/g' ${CONFIG}_iter0to7.py
sed -i 's/+process\.HLTFullIterativeTrackingIteration8PPOnAA+process\.hltFullIterativeTrackingMergedPPOnAA/+process.hltFullIterativeTrackingMergedPPOnAA/g' ${CONFIG}_iter0to7.py

sed 's/'"'"'hltFullIter7TrackMVAClassifierPPOnAA'"'"'/# '"'"'hltFullIter7TrackMVAClassifierPPOnAA'"'"'/g' ${CONFIG}_iter0to7.py > ${CONFIG}_iter0to6.py
sed -i 's/\([^(]\)"hltFullIter7CtfWithMaterialTracksPPOnAA"/\1# "hltFullIter7CtfWithMaterialTracksPPOnAA"/g' ${CONFIG}_iter0to6.py
sed -i 's/+process\.HLTFullIterativeTrackingIteration7PPOnAA+process\.hltFullIterativeTrackingMergedPPOnAA/+process.hltFullIterativeTrackingMergedPPOnAA/g' ${CONFIG}_iter0to6.py

sed 's/'"'"'hltFullIter6TrackMVAClassifierPPOnAA'"'"'/# '"'"'hltFullIter6TrackMVAClassifierPPOnAA'"'"'/g' ${CONFIG}_iter0to6.py > ${CONFIG}_iter0to5.py
sed -i 's/\([^(]\)"hltFullIter6CtfWithMaterialTracksPPOnAA"/\1# "hltFullIter6CtfWithMaterialTracksPPOnAA"/g' ${CONFIG}_iter0to5.py
sed -i 's/+process\.HLTFullIterativeTrackingIteration6PPOnAA+process\.hltFullIterativeTrackingMergedPPOnAA/+process.hltFullIterativeTrackingMergedPPOnAA/g' ${CONFIG}_iter0to5.py

sed 's/'"'"'hltFullIter5TrackMVAClassifierPPOnAA'"'"'/# '"'"'hltFullIter5TrackMVAClassifierPPOnAA'"'"'/g' ${CONFIG}_iter0to5.py > ${CONFIG}_iter0to4.py
sed -i 's/\([^(]\)"hltFullIter5CtfWithMaterialTracksPPOnAA"/\1# "hltFullIter5CtfWithMaterialTracksPPOnAA"/g' ${CONFIG}_iter0to4.py
sed -i 's/+process\.HLTFullIterativeTrackingIteration5PPOnAA+process\.hltFullIterativeTrackingMergedPPOnAA/+process.hltFullIterativeTrackingMergedPPOnAA/g' ${CONFIG}_iter0to4.py

sed 's/'"'"'hltFullIter4TrackMVAClassifierPPOnAA'"'"'/# '"'"'hltFullIter4TrackMVAClassifierPPOnAA'"'"'/g' ${CONFIG}_iter0to4.py > ${CONFIG}_iter0to3.py
sed -i 's/\([^(]\)"hltFullIter4CtfWithMaterialTracksPPOnAA"/\1# "hltFullIter4CtfWithMaterialTracksPPOnAA"/g' ${CONFIG}_iter0to3.py
sed -i 's/+process\.HLTFullIterativeTrackingIteration4PPOnAA+process\.hltFullIterativeTrackingMergedPPOnAA/+process.hltFullIterativeTrackingMergedPPOnAA/g' ${CONFIG}_iter0to3.py

sed 's/'"'"'hltFullIter3TrackMVAClassifierPPOnAA'"'"'/# '"'"'hltFullIter3TrackMVAClassifierPPOnAA'"'"'/g' ${CONFIG}_iter0to3.py > ${CONFIG}_iter0to2.py
sed -i 's/\([^(]\)"hltFullIter3CtfWithMaterialTracksPPOnAA"/\1# "hltFullIter3CtfWithMaterialTracksPPOnAA"/g' ${CONFIG}_iter0to2.py
sed -i 's/+process\.HLTFullIterativeTrackingIteration3PPOnAA+process\.hltFullIterativeTrackingMergedPPOnAA/+process.hltFullIterativeTrackingMergedPPOnAA/g' ${CONFIG}_iter0to2.py

sed 's/'"'"'hltFullIter2TrackMVAClassifierPPOnAA'"'"'/# '"'"'hltFullIter2TrackMVAClassifierPPOnAA'"'"'/g' ${CONFIG}_iter0to2.py > ${CONFIG}_iter0to1.py
sed -i 's/\([^(]\)"hltFullIter2CtfWithMaterialTracksPPOnAA"/\1# "hltFullIter2CtfWithMaterialTracksPPOnAA"/g' ${CONFIG}_iter0to1.py
sed -i 's/+process\.HLTFullIterativeTrackingIteration2PPOnAA+process\.hltFullIterativeTrackingMergedPPOnAA/+process.hltFullIterativeTrackingMergedPPOnAA/g' ${CONFIG}_iter0to1.py

sed 's/'"'"'hltFullIter1TrackMVAClassifierPPOnAA'"'"'/# '"'"'hltFullIter1TrackMVAClassifierPPOnAA'"'"'/g' ${CONFIG}_iter0to1.py > ${CONFIG}_iter0to0.py
sed -i 's/\([^(]\)"hltFullIter1CtfWithMaterialTracksPPOnAA"/\1# "hltFullIter1CtfWithMaterialTracksPPOnAA"/g' ${CONFIG}_iter0to0.py
sed -i 's/+process\.HLTFullIterativeTrackingIteration1PPOnAA+process\.hltFullIterativeTrackingMergedPPOnAA/+process.hltFullIterativeTrackingMergedPPOnAA/g' ${CONFIG}_iter0to0.py
