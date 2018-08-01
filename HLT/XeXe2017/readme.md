
cmsrel CMSSW_10_1_2
cd CMSSW_10_1_2/src
cmsenv
git cms-init
git remote add cms-l1t-offline git@github.com:cms-l1t-offline/cmssw.git
git fetch cms-l1t-offline l1t-integration-CMSSW_10_1_2
git cms-merge-topic -u cms-l1t-offline:l1t-integration-v97.27.1-CMSSW_10_1_2
git cms-addpkg L1Trigger/L1TCommon
git cms-addpkg L1Trigger/L1TMuon
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TMuon.git L1Trigger/L1TMuon/data
git cms-addpkg L1Trigger/L1TCalorimeter
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TCalorimeter.git L1Trigger/L1TCalorimeter/data
git cms-addpkg HLTrigger/Configuration
scram build -j 8


cmsRun expmenu.py 2>&1 | tee logs/menulog.txt
