### HiForest Configuration
# Collisions: PbPb
# Type: Data
# Input: AOD

# This apparently cleans bad PF candidates. Should it be True or False?
cleanJets = False

# Imports CMS-specific python classes and functions.
import FWCore.ParameterSet.Config as cms
process = cms.Process('HiForest')

###############################################################################
# HiForest labelling info
###############################################################################

process.load("HeavyIonsAnalysis.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest 103X")
import subprocess, os
version = subprocess.check_output(['git',
    '-C', os.path.expandvars('$CMSSW_BASE/src'), 'describe', '--tags'])
if version == '':
    version = 'no git info'
process.HiForest.HiForestVersion = cms.string(version)

###############################################################################
# Input source
###############################################################################

process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring())

# Number of events we want to process, -1 = all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
    )

###############################################################################
# Load Global Tag, Geometry, etc.
###############################################################################

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_v2', '')
process.HiForest.GlobalTagLabel = process.GlobalTag.globaltag

print('\n\033[31m~*~ USING CENTRALITY TABLE FOR PbPb 2018 DATA ~*~\033[0m\n')
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
        tag = cms.string("CentralityTable_HFtowers200_DataPbPb_periHYDJETshape_run2v1031x02_offline"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        label = cms.untracked.string("HFtowers")
        ),
    ])

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")

process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("BTagTrackProbability3DRcd"),
             tag = cms.string("JPcalib_Data103X_2018PbPb_v1"),
             connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS")

         )
      ])

###############################################################################
# Define tree output
###############################################################################

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("HiForestAOD.root"))

###############################################################################
# Additional Reconstruction and Analysis: Main Body
###############################################################################

#############################
# Jets
#############################
# jet reco sequence
process.load('HeavyIonsAnalysis.JetAnalysis.fullJetSequence_pponAA_data_cff')

process.load('HeavyIonsAnalysis.JetAnalysis.hiFJRhoAnalyzer_cff')
process.load("HeavyIonsAnalysis.JetAnalysis.pfcandAnalyzer_cfi")
process.pfcandAnalyzer.doTrackMatching  = cms.bool(True)
process.akCs3PFJetAnalyzer.doWTARecluster = cms.untracked.bool(True)

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import overrideJEC_DATA_PbPb5020_2018
process = overrideJEC_DATA_PbPb5020_2018(process)

###############################################################################

############################
# Event Analysis
############################
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.l1object_cfi')

from HeavyIonsAnalysis.EventAnalysis.hltobject_cfi import trigger_list_data
process.hltobject.triggerNames = trigger_list_data

###############################################################################

#########################
# Track Analyzer
#########################
process.load('HeavyIonsAnalysis.TrackAnalysis.ExtraTrackReco_cff')
process.load('HeavyIonsAnalysis.TrackAnalysis.TrkAnalyzers_cff')

# Use this instead for track corrections
# process.load('HeavyIonsAnalysis.TrackAnalysis.TrkAnalyzers_Corr_cff')

###############################################################################

#####################
# Photons
#####################
SSHIRun2018A = "HeavyIonsAnalysis/PhotonAnalysis/data/SSHIRun2018A.dat"
process.load('HeavyIonsAnalysis.PhotonAnalysis.correctedElectronProducer_cfi')
process.correctedElectrons.correctionFile = SSHIRun2018A

process.load('HeavyIonsAnalysis.PhotonAnalysis.ggHiNtuplizer_cfi')
process.ggHiNtuplizer.doGenParticles = False
process.ggHiNtuplizerGED.doGenParticles = False
process.ggHiNtuplizerGED.gsfElectronLabel = "correctedElectrons"
process.ggHiNtuplizerGED.doEffectiveAreas = cms.bool(True)
process.ggHiNtuplizerGED.doPhoERegression = cms.bool(True)

###############################################################################

#######################
# B-tagging
######################
# replace pp CSVv2 with PbPb CSVv2 (positive and negative taggers unchanged!)
process.load('RecoBTag.CSVscikit.csvscikitTagJetTags_cfi')
process.load('RecoBTag.CSVscikit.csvscikitTaggerProducer_cfi')
process.akPu4PFCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
process.akPu4PFCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
    cms.InputTag("akPu4PFImpactParameterTagInfos"),
    cms.InputTag("akPu4PFSecondaryVertexTagInfos"))
process.akCs4PFCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
process.akCs4PFCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
    cms.InputTag("akCs4PFImpactParameterTagInfos"),
    cms.InputTag("akCs4PFSecondaryVertexTagInfos"))
process.akPu4CaloCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
process.akPu4CaloCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
    cms.InputTag("akPu4CaloImpactParameterTagInfos"),
    cms.InputTag("akPu4CaloSecondaryVertexTagInfos"))

# trained on CS jets
process.CSVscikitTags.weightFile = cms.FileInPath(
    'HeavyIonsAnalysis/JetAnalysis/data/TMVA_Btag_CsJets_PbPb2018_BDTG.weights.xml')

###############################################################################

#########################
# RecHits & pfTowers (HF, Castor & ZDC)
#########################
# ZDC RecHit Producer
process.load('RecoHI.ZDCRecHit.QWZDC2018Producer_cfi')
process.load('RecoHI.ZDCRecHit.QWZDC2018RecHit_cfi')

process.load('HeavyIonsAnalysis.JetAnalysis.rechitanalyzer_cfi')
process.rechitanalyzerpp.doZDCRecHit = True
process.rechitanalyzerpp.zdcRecHitSrc = cms.InputTag("QWzdcreco")
process.pfTowerspp.doHF = False

###############################################################################
#Recover peripheral primary vertices
#https://twiki.cern.ch/twiki/bin/view/CMS/HITracking2018PbPb#Peripheral%20Vertex%20Recovery
process.load("RecoVertex.PrimaryVertexProducer.OfflinePrimaryVerticesRecovery_cfi")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

# clean bad PF candidates
if cleanJets:
    process.load("RecoHI.HiJetAlgos.HiBadParticleFilter_cfi")
    process.pfBadCandAnalyzer = process.pfcandAnalyzer.clone(pfCandidateLabel = cms.InputTag("filteredParticleFlow","cleaned"))
    process.pfFilter = cms.Path(process.filteredParticleFlow + process.pfBadCandAnalyzer)

#########################
# Main analysis list
#########################

process.ana_step = cms.Path(
    # process.offlinePrimaryVerticesRecovery +
    process.HiForest +
    process.hltanalysis +
    process.hltobject +
    process.l1object +
    process.centralityBin +
    process.hiEvtAnalyzer +
    process.jetSequence +
    # process.hiPuRhoR3Analyzer + 
    process.correctedElectrons +
    process.ggHiNtuplizer +
    process.ggHiNtuplizerGED 
    # process.hiFJRhoAnalyzer +
    # process.hiFJRhoAnalyzerFinerBins +
    # process.pfcandAnalyzer +
    # process.pfcandAnalyzerCS +
    # process.trackSequencesPP +
    # process.zdcdigi +
    # process.QWzdcreco +
    # process.rechitanalyzerpp
    )

# # edm output for debugging purposes
# process.output = cms.OutputModule(
#     "PoolOutputModule",
#     fileName = cms.untracked.string('HiForestEDM.root'),
#     outputCommands = cms.untracked.vstring(
#         'keep *',
#         # drop aliased products
#         'drop *_akULPu3PFJets_*_*',
#         'drop *_akULPu4PFJets_*_*',
#         )
#     )

# process.output_path = cms.EndPath(process.output)

###############################################################################

#########################
# Event Selection
#########################

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.pclusterCompatibilityFilter = cms.Path(process.clusterCompatibilityFilter)
process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter)
process.pBeamScrapingFilter = cms.Path(process.beamScrapingFilter)
process.collisionEventSelectionAOD = cms.Path(process.collisionEventSelectionAOD)
process.collisionEventSelectionAODv2 = cms.Path(process.collisionEventSelectionAODv2)

process.load('HeavyIonsAnalysis.Configuration.hfCoincFilter_cff')
process.phfCoincFilter1Th3 = cms.Path(process.hfCoincFilterTh3)
process.phfCoincFilter2Th3 = cms.Path(process.hfCoincFilter2Th3)
process.phfCoincFilter3Th3 = cms.Path(process.hfCoincFilter3Th3)
process.phfCoincFilter4Th3 = cms.Path(process.hfCoincFilter4Th3)
process.phfCoincFilter5Th3 = cms.Path(process.hfCoincFilter5Th3)
process.phfCoincFilter1Th4 = cms.Path(process.hfCoincFilterTh4)
process.phfCoincFilter2Th4 = cms.Path(process.hfCoincFilter2Th4)
process.phfCoincFilter3Th4 = cms.Path(process.hfCoincFilter3Th4)
process.phfCoincFilter4Th4 = cms.Path(process.hfCoincFilter4Th4)
process.phfCoincFilter5Th4 = cms.Path(process.hfCoincFilter5Th4)
process.phfCoincFilter1Th5 = cms.Path(process.hfCoincFilterTh5)
process.phfCoincFilter4Th2 = cms.Path(process.hfCoincFilter4Th2)

process.load("HeavyIonsAnalysis.VertexAnalysis.PAPileUpVertexFilter_cff")
process.pVertexFilterCutG = cms.Path(process.pileupVertexFilterCutG)
process.pVertexFilterCutGloose = cms.Path(process.pileupVertexFilterCutGloose)
process.pVertexFilterCutGtight = cms.Path(process.pileupVertexFilterCutGtight)
process.pVertexFilterCutGplus = cms.Path(process.pileupVertexFilterCutGplus)
process.pVertexFilterCutE = cms.Path(process.pileupVertexFilterCutE)
process.pVertexFilterCutEandG = cms.Path(process.pileupVertexFilterCutEandG)

process.load('HeavyIonsAnalysis.JetAnalysis.EventSelection_cff')
process.pHBHENoiseFilterResultProducer = cms.Path(process.HBHENoiseFilterResultProducer)
process.HBHENoiseFilterResult = cms.Path(process.fHBHENoiseFilterResult)
process.HBHENoiseFilterResultRun1 = cms.Path(process.fHBHENoiseFilterResultRun1)
process.HBHENoiseFilterResultRun2Loose = cms.Path(process.fHBHENoiseFilterResultRun2Loose)
process.HBHENoiseFilterResultRun2Tight = cms.Path(process.fHBHENoiseFilterResultRun2Tight)
process.HBHEIsoNoiseFilterResult = cms.Path(process.fHBHEIsoNoiseFilterResult)

process.pAna = cms.EndPath(process.skimanalysis)

from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
process = MassReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"

if cleanJets == True:
    from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
    process = MassReplaceInputTag(process,"particleFlow","filteredParticleFlow")                                                                                                               
    process.filteredParticleFlow.PFCandidates  = "particleFlow"

###############################################################################

# Customization
# KT : filter events on reco photons
# photon selection
process.selectedPhotons = cms.EDFilter("PhotonSelector",
    src = cms.InputTag("gedPhotons"),
    cut = cms.string('abs(eta) < 2.5')
)

# leading photon E_T filter
process.photonFilter = cms.EDFilter("EtMinPhotonCountFilter",
    src = cms.InputTag("selectedPhotons"),
    etMin = cms.double(25.0),
    minNumber = cms.uint32(1)
)

process.photonFilterSequence = cms.Sequence(process.selectedPhotons *
                                            process.photonFilter
)

# needed to apply the filter on skimanalysis tree
process.superFilterPath = cms.Path(process.photonFilterSequence)
process.skimanalysis.superFilters = cms.vstring("superFilterPath")

for path in process.paths:
  getattr(process,path)._seq = process.photonFilterSequence * getattr(process,path)._seq