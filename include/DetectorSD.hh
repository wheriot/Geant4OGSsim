#ifndef __DETECTORSD__
#define __DETECTORSD__

//Geant4 Libraries
#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4AccumulableManager.hh"
#include "G4ParticleTypes.hh"
#include "G4HadronicProcess.hh"
#include "G4SDManager.hh"

//My Libraries
#include "Run.hh"
#include "RunAction.hh"
#include "EventAction.hh"

//c++ Libraries
#include <cmath>

class DetectorSD : public G4VSensitiveDetector
{
  public:
    DetectorSD(G4String name);
    virtual ~DetectorSD();

    virtual void Initialize();
    virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory* ROhist);
	  virtual void EndOfEvent();

    double convertEnergyToSignal(G4double E);

};

#endif
