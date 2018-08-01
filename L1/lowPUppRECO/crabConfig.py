#

from CRABClient.UserUtilities import config
config = config()
config.General.transferOutputs = True
config.General.requestName = 'step2_RAW2DIGI_L1Reco_RECO_pp_20180730_ZeroBias_Run2018C_v1_319466'
config.General.workArea = 'crab_projects'
config.JobType.psetName = 'step2_RAW2DIGI_L1Reco_RECO.py'
config.JobType.pluginName = 'Analysis'
#config.JobType.inputFiles = ['rssLimit']
config.JobType.pyCfgParams = ['noprint']
config.JobType.outputFiles = ['step2_RAW2DIGI_L1Reco_RECO.root']
config.JobType.numCores = 4

config.Data.inputDataset = '/ZeroBias/Run2018C-v1/RAW'
config.Data.totalUnits = -1
config.Data.unitsPerJob = 2000
#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'EventAwareLumiBased'
#config.Data.splitting = 'LumiBased'
config.Data.runRange = '319466-319466'

config.Site.storageSite = 'T2_CH_CERN'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/wangj/lowPUppRECO'
#config.Site.storageSite = 'T2_US_MIT'
#config.Site.whitelist = ['T2_US_MIT']
#config.Site.ignoreGlobalBlacklist = True
config.Data.publication = True
# config.Data.outputPrimaryDataset = 'RAW2DIGI_RECO_pp_ZeroBias_Run2018C_Run319460_319460'
config.Data.outputDatasetTag = 'lowPUppRECO_Run319466'

config.section_("Debug")
config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']
