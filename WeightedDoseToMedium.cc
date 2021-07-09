// Scorer for WeightedDoseToMedium
//
// By: Nicholas P. Nelson
//

#include "WeightedDoseToMedium.hh"
#include "TsParameterManager.hh"
WeightedDoseToMedium::WeightedDoseToMedium(TsParameterManager* pM, TsMaterialManager* mM, TsGeometryManager* gM, TsScoringManager* scM, TsExtensionManager* eM,
								 G4String scorerName, G4String quantity, G4String outFileName, G4bool isSubScorer)
: TsVBinnedScorer(pM, mM, gM, scM, eM, scorerName, quantity, outFileName, isSubScorer)
{
	SetUnit("Gy");
	fWeights = fPm->GetUnitlessParameter(GetFullParmName("BeamletWeight"));
//G4cout << "Current Beamlet Weight in Constructor: " << fWeights << G4endl;	
}


WeightedDoseToMedium::~WeightedDoseToMedium(){;}

void WeightedDoseToMedium::UpdateForSpecificParameterChange(G4String parameter)
{                                   
	if (parameter == GetFullParmName("BeamletWeight")){
		fWeights = fPm->GetUnitlessParameter(GetFullParmName("BeamletWeight"));
	//G4cout << "Current Beamlet Weight in UpdateForSpecificParameterChange: " << fWeights << G4endl;
} else {
	TsVBinnedScorer::UpdateForSpecificParameterChange(parameter);}                                      
}

G4bool WeightedDoseToMedium::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
	if (!fIsActive) {
		fSkippedWhileInactive++;
		return false;
	}
	G4double edep = aStep->GetTotalEnergyDeposit();
	if ( edep > 0. ) {
		G4double density = aStep->GetPreStepPoint()->GetMaterial()->GetDensity();
		ResolveSolid(aStep);
		G4double dose = edep / ( density * fSolid->GetCubicVolume() );
		dose *= aStep->GetPreStepPoint()->GetWeight();
		//WeightedDoseToMedium::UpdateForSpecificParameterChange(GetFullParmName("BeamletWeight"));
		//UpdateForSpecificParameterChange(GetFullParmName("BeamletWeight"));
		//G4double fWeights = fPm->GetUnitlessParameter(GetFullParmName("BeamletWeight"));
		//G4cout << "Current Beamlet Weight in ProcessHits: " << fWeights << G4endl;

		AccumulateHit(aStep, fWeights*dose);

		return true;
	}
	return false;
}
