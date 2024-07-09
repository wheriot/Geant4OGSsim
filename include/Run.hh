#ifndef __RUN__
#define __RUN__

//Geant4 Libraries
#include "G4Run.hh"
#include "globals.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

//Root Libraries
#include "TFile.h"
#include "TTree.h"

class G4Event;

class Run : public G4Run
{
  public:
    Run();
    virtual ~Run();
    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);

  private:
};


#endif
