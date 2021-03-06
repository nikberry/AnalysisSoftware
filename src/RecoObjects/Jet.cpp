/*
 * Jet.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Jet.h"
#include "../../interface/GlobalVariables.h"

namespace BAT {

Jet::Jet() :
		Particle(), //
		usedAlgorithm(JetAlgorithm::Calo_AntiKT_Cone05), //
		electromagneticFraction(0.), //
		numberOfRecHitsContaining90PercentOfTheJetEnergy(0.), //
		fractionOfEnergyIntheHottestHPDReadout(0.), //
		btag_discriminators(BtagAlgorithm::NUMBER_OF_BTAGALGORITHMS), //
		numberOfDaughters(0), //
		chargedEmEnergyFraction(1), //
		neutralHadronEnergyFraction(1), //
		neutralEmEnergyFraction(1), //
		chargedHadronEnergyFraction(1), //
		chargedMultiplicity(0), //
		pxRaw(-9999), //
		pyRaw(-9999), //
		pzRaw(-9999), //
		JECUncertainty(-9999), //
		l1OffJEC(0), //
		l2l3ResJEC(0), //
		l2RelJEC(0), //
		l3AbsJEC(0), //
		partonFlavour_(0) //
{
	for (unsigned int btag = 0; btag < btag_discriminators.size(); ++btag) {
		btag_discriminators[btag] = -9999;
	}
}

Jet::Jet(double energy, double px, double py, double pz) :
		Particle(energy, px, py, pz), //
		usedAlgorithm(JetAlgorithm::Calo_AntiKT_Cone05), //
		electromagneticFraction(0.), //
		numberOfRecHitsContaining90PercentOfTheJetEnergy(0.), //
		fractionOfEnergyIntheHottestHPDReadout(0.), //
		btag_discriminators(BtagAlgorithm::NUMBER_OF_BTAGALGORITHMS), //
		numberOfDaughters(0), //
		chargedEmEnergyFraction(1), //
		neutralHadronEnergyFraction(1), //
		neutralEmEnergyFraction(1), //
		chargedHadronEnergyFraction(1), //
		chargedMultiplicity(0), //
		pxRaw(-9999), //
		pyRaw(-9999), //
		pzRaw(-9999), //
		JECUncertainty(-9999), //
		l1OffJEC(0), //
		l2l3ResJEC(0), //
		l2RelJEC(0), //
		l3AbsJEC(0), //
		partonFlavour_(0) //
{
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

double Jet::PxRaw() const {
	return pxRaw;
}

double Jet::PyRaw() const {
	return pyRaw;
}

double Jet::PzRaw() const {
	return pzRaw;
}

double Jet::JECUnc() const {
	return JECUncertainty;
}

double Jet::L1OffJEC() const {
	return l1OffJEC;
}

double Jet::L2L3ResJEC() const {
	return l2l3ResJEC;
}

double Jet::L2RelJEC() const {
	return l2RelJEC;
}

double Jet::L3AbsJEC() const {
	return l3AbsJEC;
}

void Jet::setPxRaw(double px) {
	pxRaw = px;
}

void Jet::setPyRaw(double py) {
	pyRaw = py;
}

void Jet::setPzRaw(double pz) {
	pzRaw = pz;
}

void Jet::setJECUnc(double JECUnc) {
	JECUncertainty = JECUnc;
}

void Jet::setL1OffJEC(double JEC) {
	l1OffJEC = JEC;
}

void Jet::setL2L3ResJEC(double JEC) {
	l2l3ResJEC = JEC;
}

void Jet::setL2RelJEC(double JEC) {
	l2RelJEC = JEC;
}

void Jet::setL3AbsJEC(double JEC) {
	l3AbsJEC = JEC;
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

void Jet::setPartonFlavour(int flavour) {
	partonFlavour_ = flavour;
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
 * The b-tag POG has defined working points "Loose " (L), "Medium" (M) and "Tight" (T) for 10%, 1% and 0.1% light mis tag :
 * more details on these working points can be found on https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP
 */
bool Jet::isBJet(BtagAlgorithm::value type, BtagAlgorithm::workingPoint wp) const {
	double cut(9998);
	switch (type) {

	case BtagAlgorithm::CombinedSecondaryVertex:
		if (wp == BtagAlgorithm::LOOSE)
			cut = 0.244;
		else if (wp == BtagAlgorithm::MEDIUM)
			cut = 0.679;
		else if (wp == BtagAlgorithm::TIGHT)
			cut = 0.898;
		break;

	case BtagAlgorithm::CombinedSecondaryVertexMVA:
		//same as without MVA? No hints found
		//according to
		//https://cms-btag-validation.web.cern.ch/cms-btag-validation/validation/index_RecoB_CMSSW_4_2_1_TTbar_421_vs_420_Startup.html
		//these cuts should be lower
		if (wp == BtagAlgorithm::LOOSE)
			cut = 0.244;
		else if (wp == BtagAlgorithm::MEDIUM)
			cut = 0.679;
		else if (wp == BtagAlgorithm::TIGHT)
			cut = 0.898;
		break;

	case BtagAlgorithm::JetBProbability:
		if (wp == BtagAlgorithm::LOOSE)
			cut = 1.33;
		else if (wp == BtagAlgorithm::MEDIUM)
			cut = 2.55;
		else if (wp == BtagAlgorithm::TIGHT)
			cut = 3.74;
		break;

	case BtagAlgorithm::JetProbability:
		if (wp == BtagAlgorithm::LOOSE)
			cut = 0.275;
		else if (wp == BtagAlgorithm::MEDIUM)
			cut = 0.545;
		else if (wp == BtagAlgorithm::TIGHT)
			cut = 0.790;
		break;

	case BtagAlgorithm::SimpleSecondaryVertexHighEfficiency:
		if (wp == BtagAlgorithm::LOOSE)
			cut = 9998; //no input found
		else if (wp == BtagAlgorithm::MEDIUM)
			cut = 1.74;
		else if (wp == BtagAlgorithm::TIGHT) //not supported
			cut = 3.05;
		break;

	case BtagAlgorithm::SimpleSecondaryVertexHighPurity:
		if (wp == BtagAlgorithm::LOOSE)
			cut = 9998; //no input found
		else if (wp == BtagAlgorithm::MEDIUM)
			cut = 9998; //no input found
		else if (wp == BtagAlgorithm::TIGHT)
			cut = 2.;
		break;

	case BtagAlgorithm::TrackCountingHighEfficiency:
		if (wp == BtagAlgorithm::LOOSE)
			cut = 1.7;
		else if (wp == BtagAlgorithm::MEDIUM)
			cut = 3.3;
		else if (wp == BtagAlgorithm::TIGHT) //not supported
			cut = 10.2;
		break;

	case BtagAlgorithm::TrackCountingHighPurity:
		if (wp == BtagAlgorithm::LOOSE) //not supported
			cut = 1.19;
		else if (wp == BtagAlgorithm::MEDIUM)
			cut = 1.93;
		else if (wp == BtagAlgorithm::TIGHT)
			cut = 3.41;
		break;

	default:
		return false;

	}
	return btag_discriminators[type] > cut;
}

double Jet::btagSSVHE() const {
	return btag_discriminators[BtagAlgorithm::SimpleSecondaryVertexHighEfficiency];
}

double Jet::getBJetL7EtCorrection() const {
	Float_t towerBinning[] = { 0.0, 0.174, 0.348, 0.522, 0.696, 0.87, 1.044, 1.218, 1.392, 1.566, 1.74, 2.5 };
	unsigned int nEtaBins_ = 11;
	double res = -1;
	for (unsigned int iEta = 0; iEta < nEtaBins_; ++iEta)
		if (fabs(eta()) >= towerBinning[iEta] && fabs(eta()) < towerBinning[iEta + 1])
			res = Globals::bL7Corrections[iEta]->Eval(pt());
	return res;
}

double Jet::getLightJetL7EtCorrection() const {
	Float_t towerBinning[] = { 0.0, 0.174, 0.348, 0.522, 0.696, 0.87, 1.044, 1.218, 1.392, 1.566, 1.74, 2.5 };
	unsigned int nEtaBins_ = 11;
	double res = -1;
	for (unsigned int iEta = 0; iEta < nEtaBins_; ++iEta)
		if (fabs(eta()) >= towerBinning[iEta] && fabs(eta()) < towerBinning[iEta + 1])
			res = Globals::lightL7Corrections[iEta]->Eval(pt());
	return res;
}

int Jet::partonFlavour() const {
	return partonFlavour_;
}

double Jet::getBTagDiscriminator(BtagAlgorithm::value type) const {
	return btag_discriminators.at((unsigned int) type);
}

}

