#ifndef __ACTIONINITIALIZATION__
#define __ACTIONINITIALIZATION__

//Geant 4 Libraries
#include "G4VUserActionInitialization.hh"

//My Libraries
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
