# WeightedDoseToMediumScorer
A beamlet-weighted Dose to Medium scoring extension for TOPAS. This scorer is intended to be used for a 4D simulation, where each beamlet is defined by one time point. And for each time point, the BeamletWeight parameter will be updated if it changes between time points. This BeamletWeight parameter is directly multiplied on a per-hit basis within the process hits method.

Please see http://www.topasmc.org/ for installation instructions.
