/*
 * HitFitAnalyser.h
 *
 *  Created on: Jul 5, 2011
 *      Author: senkin
 */

#ifndef HITFITANALYSER_H_
#define HITFITANALYSER_H_
#include <boost/shared_ptr.hpp>
#include "../../interface/TopPairEventCandidate.h"
#include "../../interface/HistHelpers/HistogramManager.h"
#include "BasicAnalyser.h"

#include "TopQuarkAnalysis/TopHitFit/interface/RunHitFit.h"
#include "TopQuarkAnalysis/TopHitFit/interface/Top_Decaykin.h"
#include "TopQuarkAnalysis/TopHitFit/interface/LeptonTranslatorBase.h"
#include "TopQuarkAnalysis/TopHitFit/interface/JetTranslatorBase.h"
#include "TopQuarkAnalysis/TopHitFit/interface/METTranslatorBase.h"

typedef hitfit::RunHitFit<BAT::Electron,BAT::Muon,BAT::Jet,BAT::MET> BatHitFit;

namespace BAT {

class HitFitAnalyser : public BasicAnalyser{
private:
//    BAT::TtbarHypothesis trueFourVectors;
    BAT::TtbarHypothesis truthMatchEvent;
    BAT::JetCollection jetsForFitting;

    std::string CMSSWBase_;
    std::string hitfitDefault_;
    std::string hitfitElectronResolution_;
    std::string hitfitMuonResolution_;
    std::string hitfitJetResolution_;
    std::string hitfitMETResolution_;

    double      hitfitLepWMass_;
    double      hitfitHadWMass_;
    double      hitfitTopMass_;
    double      lepton_charge;

    hitfit::LeptonTranslatorBase<BAT::Electron> electronTranslator_;
    hitfit::LeptonTranslatorBase<BAT::Muon>     muonTranslator_;
    hitfit::JetTranslatorBase<BAT::Jet>         jetTranslator_;
    hitfit::METTranslatorBase<BAT::MET>         metTranslator_;

    struct jetPtCompare {
      bool operator()(const BAT::ParticlePointer& i, const BAT::ParticlePointer& j) const {
        return i->pt() > j->pt();
      }
    };
    jetPtCompare jetPtComp;
    FourVector fourVectorFromHitFit(const hitfit::Fourvec& v);
    BAT::TtbarHypothesis BatEvent(const hitfit::Lepjets_Event& ev);

public:
    HitFitAnalyser(boost::shared_ptr<HistogramManager> histMan);
    virtual ~HitFitAnalyser();

    void analyse(const TopPairEventCandidate& ttbarEvent);
    void createHistograms();
    void printFile(const string filename);
};

}

#endif /* HITFITANALYSER_H_ */