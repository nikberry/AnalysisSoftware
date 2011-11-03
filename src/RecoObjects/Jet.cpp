/*
 * Jet.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Jet.h"

namespace BAT {

Jet::Jet() :
    Particle(),
    usedAlgorithm(JetAlgorithm::Calo_AntiKT_Cone05),
    electromagneticFraction(0.),
    numberOfRecHitsContaining90PercentOfTheJetEnergy(0.),
    fractionOfEnergyIntheHottestHPDReadout(0.),
    btag_discriminators(BtagAlgorithm::NUMBER_OF_BTAGALGORITHMS),
    numberOfDaughters(0),
    chargedEmEnergyFraction(1),
    neutralHadronEnergyFraction(1),
    neutralEmEnergyFraction(1),
    chargedHadronEnergyFraction(1),
    chargedMultiplicity(0),
    partonFlavour(0) {
    for (unsigned int btag = 0; btag < btag_discriminators.size(); ++btag) {
        btag_discriminators[btag] = -9999;
    }
}

Jet::Jet(double energy, double px, double py, double pz) :
    Particle(energy, px, py, pz),
    usedAlgorithm(JetAlgorithm::Calo_AntiKT_Cone05),
    electromagneticFraction(0.),
    btag_discriminators(BtagAlgorithm::NUMBER_OF_BTAGALGORITHMS),
    numberOfDaughters(0),
    chargedEmEnergyFraction(1),
    neutralHadronEnergyFraction(1),
    neutralEmEnergyFraction(1),
    chargedHadronEnergyFraction(1),
    chargedMultiplicity(0),
    partonFlavour(0) {
    for (unsigned int btag = 0; btag < btag_discriminators.size(); ++btag) {
        btag_discriminators[btag] = -9999;
    }

}

Jet::~Jet() {
}

JetAlgorithm::value Jet::getUsedAlgorithm() const {
    return usedAlgorithm;
}

double Jet::emf() const {
    return electromagneticFraction;
}

double Jet::n90Hits() const {
    return numberOfRecHitsContaining90PercentOfTheJetEnergy;
}

double Jet::fHPD() const {
    return fractionOfEnergyIntheHottestHPDReadout;
}

double Jet::NOD() const {
    return numberOfDaughters;
}

double Jet::CEF() const {
    return chargedEmEnergyFraction;
}

double Jet::NHF() const {
    return neutralHadronEnergyFraction;
}

double Jet::NEF() const {
    return neutralEmEnergyFraction;
}

double Jet::CHF() const {
    return chargedHadronEnergyFraction;
}

double Jet::NCH() const {
    return chargedMultiplicity;
}

void Jet::setUsedAlgorithm(JetAlgorithm::value algo) {
    usedAlgorithm = algo;
}
void Jet::setEMF(double emf) {
    electromagneticFraction = emf;
}

void Jet::setN90Hits(int n90Hits) {
    numberOfRecHitsContaining90PercentOfTheJetEnergy = n90Hits;
}

void Jet::setFHPD(double fHPD) {
    fractionOfEnergyIntheHottestHPDReadout = fHPD;
}

void Jet::setDiscriminatorForBtagType(double discriminator, BtagAlgorithm::value type) {
    btag_discriminators[type] = discriminator;
}

void Jet::setNOD(int nod) {
    numberOfDaughters = nod;
}
void Jet::setCEF(double cef) {
    chargedEmEnergyFraction = cef;
}
void Jet::setNHF(double nhf) {
    neutralHadronEnergyFraction = nhf;
}
void Jet::setNEF(double nef) {
    neutralEmEnergyFraction = nef;
}
void Jet::setCHF(double chf) {
    chargedHadronEnergyFraction = chf;
}
void Jet::setNCH(double nch) {
    chargedMultiplicity = nch;
}

bool Jet::isGood() const {
    bool passesPt = pt() > 30;
    bool passesEta = fabs(eta()) < 2.4;
    bool jetID = false;
    if (usedAlgorithm == JetAlgorithm::CA08PF || usedAlgorithm == JetAlgorithm::PF2PAT)
        jetID = FirstDataLoosePFJetID();
    else
        jetID = FirstDataLooseCaloJetID();

    return passesPt && passesEta && jetID;
}

bool Jet::FirstDataLoosePFJetID() const {
	bool passNOD = NOD() > 1;
	bool passCEF = CEF() < 0.99;
	bool passNHF = NHF() < 0.99;
	bool passNEF = NEF() < 0.99;
	bool passCHF = true;
	bool passNCH = true;
	if (fabs(eta()) < 2.4) {
		passCHF = CHF() > 0;
		passNCH = NCH() > 0;
	}
	return passNOD && passCEF && passNHF && passNEF && passCHF && passNCH;;
}

bool Jet::FirstDataLooseCaloJetID() const {
	bool passesEMF = emf() > 0.01;
	bool passesN90Hits = n90Hits() > 1;
	bool passesFHPD = fHPD() < 0.98;
	return passesEMF && passesN90Hits && passesFHPD;
}

/*
 * Values taken from
 * https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideBTagPerformance
 */
bool Jet::isBJet(BtagAlgorithm::value type, BtagAlgorithm::workingPoint wp) const {
    double cut(9998);
    switch (type) {
    case BtagAlgorithm::GenPartonFlavour:
        return abs(partonFlavour) == 5;

    case BtagAlgorithm::SimpleSecondaryVertexHighEffBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 9998;//no input found
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 1.74;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 3.05;
        break;

    case BtagAlgorithm::SimpleSecondaryVertexHighPurBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 9998;//no input found
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 9998;//no input found
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 2.;
        break;

    case BtagAlgorithm::TrackCountingHighEffBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 1.7;
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 3.3;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 10.2;
        break;

    case BtagAlgorithm::TrackCountingHighPurBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 1.19;
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 1.93;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 3.41;
        break;

    case BtagAlgorithm::JetProbabilityBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 0.215;
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 0.459;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 0.669;
        break;

    case BtagAlgorithm::JetBProbabilityBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 0.988;
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 1.83;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 1.95;
        break;
    default:
        return false;

    }
    return btag_discriminators[type] > cut;
}

double Jet::btagSSVHE() const {
	return btag_discriminators[BtagAlgorithm::SimpleSecondaryVertexHighEffBTag];
}

}

