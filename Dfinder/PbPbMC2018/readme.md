
<pre>
# setup forest: https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiForestSetup
cmsrel CMSSW_10_2_0
cd CMSSW_10_2_0/src
cmsenv
git cms-merge-topic -u bi-ran:forest_CMSSW_10_1_0_pre2

# get clone Bfinder
git clone -b Dfinder_9XX https://github.com/taweiXcms/Bfinder.git

# get config
git clone https://github.com/boundino/HltL1PbPb2018.git
./HltL1PbPb2018/Dfinder/setupDfinder.sh 

# compile
scram build -j4

# run Dfinder
cd HltL1PbPb2018/Dfinder/PbPbMC2018
cmsRun finder_PbPb_102X_cfg.py
</pre>
