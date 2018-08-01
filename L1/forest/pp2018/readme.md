
<pre>
cmsrel CMSSW_10_1_5
cd CMSSW_10_1_5/src
cmsenv
git cms-merge-topic -u bi-ran:forest_CMSSW_10_1_0_pre2
# Switch to the branch HEAD
git remote add  biran git@github.com:bi-ran/cmssw.git
git fetch biran
git checkout -b forest_CMSSW_10_1_0_pre2 remotes/biran/forest_CMSSW_10_1_0_pre2
scram build -j4
# run the tests before making any changes to make sure that you have a working env: (cd into (HeavyIonsAnalysis/JetAnalysis/test/) first and then run)
./runtest.sh
</pre>
