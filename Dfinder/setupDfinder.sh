#!/bin/bash

BfinderPath='./Bfinder/'

sed -i 's/process.patTrigger\.collections\.remove("hltL3MuonCandidates")/# process.patTrigger.collections.remove("hltL3MuonCandidates")/g' ${BfinderPath}/finderMaker/python/finderMaker_75X_cff.py
cat ${BfinderPath}/finderMaker/python/finderMaker_75X_cff.py | grep remove\(\"hltL3MuonCandidates\"\)

