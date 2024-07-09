#ifndef __PRIMARYGENERATORACTION__
#define __PRIMARYGENERATORACTION__

//Geant4 Libraries
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include <vector>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();
    void GeneratePrimaries(G4Event* anEvent);
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
    G4ThreeVector SampleIsotropic();
    G4ThreeVector SampleFromPlusX();
    G4ThreeVector SampleFromPlusZ(const double & distance, const double & radius);
    G4double Ba133EnSelector();

  private:
    G4ParticleGun*  fParticleGun;
    G4ParticleGun*  fParticleGun2;
    G4ParticleGun*  fParticleGun3;



};

#endif
