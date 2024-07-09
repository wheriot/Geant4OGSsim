#ifndef __RUNACTION__
#define __RUNACTION__

//Geant4 Libraries
#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Accumulable.hh"

//ROOT Libraries
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"

// c++ Libraries
#include <cstdlib>
#include <mutex>

//My Libraries
#include "Run.hh"

// namespace
using std::lock_guard;
using std::mutex;

class RunAction : public G4UserRunAction{
  public:
    RunAction();
    virtual ~RunAction();

    virtual G4Run* GenerateRun();
    virtual void   BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
    G4double fSourcePartEn;
    G4ThreeVector fSourcePartPos;
    Run* mainRun;

  public:
    inline void SetSourceParticleEnergy(G4double energy){fSourcePartEn=energy;}
    inline double GetSourceParticleEnergy(){return fSourcePartEn;}
    inline void SetSourceParticlePos(G4ThreeVector position){fSourcePartPos=position;}
    inline G4ThreeVector GetSourceParticlePos(){return fSourcePartPos;}

};

#endif
