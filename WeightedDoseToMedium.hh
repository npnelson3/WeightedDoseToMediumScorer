//
// By: Nicholas P. Nelson
//

#ifndef WeightedDoseToMedium_hh
#define WeightedDoseToMedium_hh

#include "TsVBinnedScorer.hh"


class WeightedDoseToMedium : public TsVBinnedScorer
{
public:
	WeightedDoseToMedium(TsParameterManager* pM, TsMaterialManager* mM, TsGeometryManager* gM, TsScoringManager* scM, TsExtensionManager* eM,
					   G4String scorerName, G4String quantity, G4String outFileName, G4bool isSubScorer);

	virtual ~WeightedDoseToMedium();

	G4bool ProcessHits(G4Step*,G4TouchableHistory*);
	void UpdateForSpecificParameterChange(G4String parameter);


	private: 
	G4double fWeights;

};
#endif
