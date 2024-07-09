#ifndef __STEPPINGACTION__
#define __STEPPINGACTION__


//Geant4 Libraries
#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "G4SteppingManager.hh"

//My Libraries
#include "RunAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include <G4VSteppingVerbose.hh>
#include <G4VProcess.hh>
#include <G4String.hh>
#include "G4AccumulableManager.hh"
#include "G4DynamicParticle.hh"
#include "G4VSolid.hh"
#include "G4AnalysisManager.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"
#include "G4EventManager.hh"

class SteppingAction : public G4UserSteppingAction{
  public:
    SteppingAction(EventAction* eventAction);
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*);

  private:
    EventAction*  fEventAction;

};

#endif
