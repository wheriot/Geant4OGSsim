#include "PrimaryGeneratorAction.hh"

namespace { G4Mutex myHEPPrimGenMutex = G4MUTEX_INITIALIZER; }

PrimaryGeneratorAction::PrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(),fParticleGun(0)
{
  G4int numberParticle = 1;
  fParticleGun  = new G4ParticleGun(numberParticle);
  fParticleGun2 = new G4ParticleGun(numberParticle);
  fParticleGun3 = new G4ParticleGun(numberParticle);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
  delete fParticleGun;
  delete fParticleGun2;
  delete fParticleGun3;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  
  G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particleDefinition);    
  //fParticleGun2->SetParticleDefinition(particleDefinition);    
  //fParticleGun3->SetParticleDefinition(particleDefinition);    

  //std::vector<double> energy = {53.161,79.6139,80.9971,276.398,302.853,356.017,383.851};
  //std::vector<double> probability = {2.199,2.62,34.06,7.164,18.33,62.05,8.94};
  
  /*std::vector<double> energy = {1173.0,1332.5};
  std::vector<double> probability = {1.0,1.0};*/

  /*double sumProb = 0.0;

  std::vector<double> cumProb = {};

  double en = 0.0;

  for(int i = 0; i<probability.size(); ++i){
    double subCum = 0.0;
    for(int j = 0; j<=i; ++j){
      subCum+=probability[i];
    }
    cumProb.push_back(subCum);
    sumProb+=probability[i];
  }

  double selectProb = sumProb*G4UniformRand();

  for(int i = 0; i<cumProb.size(); ++i){
    if(selectProb<=cumProb[i]){
      en  = energy[i];
      break;
    }
    
  }
  //double en = 2.45;
  

  /*G4double partX = 0.0*cm;
  G4double partY = (-3.0+6.0*G4UniformRand())*cm;
  G4double partZ = (-3.0+6.0*G4UniformRand())*cm;
  fParticleGun->SetParticlePosition(G4ThreeVector(partX,partY,partZ));*/
  //fParticleGun->SetParticlePosition(G4ThreeVector(4.5*2.54*cm,0,(1.25+3.0/32.0)*2.54*cm));
  //fParticleGun->SetParticlePosition(G4ThreeVector(4.75*2.54*cm,0,(1.25+0.25)*2.54*cm));
  //fParticleGun2->SetParticlePosition(G4ThreeVector(4.75*2.54*cm,0,(1.25+0.25)*2.54*cm));
  //fParticleGun3->SetParticlePosition(G4ThreeVector(4.75*2.54*cm,0,(1.25+0.25)*2.54*cm));
  //fParticleGun->SetParticlePosition(G4ThreeVector(4.5*2.54*cm,0,(1.25+3.0/32.0)*2.54*cm));

  //fParticleGun->SetParticlePosition(G4ThreeVector((15-5.75)*2.54*cm,0.28*cm,4.98*cm)); //Corner Shot positioning ( assumes fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1,0,0));)
  fParticleGun->SetParticlePosition(G4ThreeVector(10*cm,0*cm,2.5*cm)); 
  //fParticleGun2->SetParticlePosition(G4ThreeVector((15-5.75)*2.54*cm,0,2.5*2.54*cm));
  //fParticleGun3->SetParticlePosition(G4ThreeVector((15-5.75)*2.54*cm,0,2.5*2.54*cm));

  //fParticleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
  //fParticleGun->SetParticleMomentumDirection(this->SampleFromPlusZ(2.54,2.54));
  G4ThreeVector iso = this->SampleIsotropic();
  //G4ThreeVector isoBack(-iso.x(),-iso.y(),-iso.z());

//Shoot particle at detector
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1,0,0));

  //fParticleGun->SetParticleMomentumDirection(iso);
  //fParticleGun2->SetParticleMomentumDirection(isoBack);
  //fParticleGun2->SetParticleMomentumDirection(this->SampleIsotropic());
  //fParticleGun3->SetParticleMomentumDirection(this->SampleIsotropic());

  G4double startEnergy = 11.25;
  G4double finalEnergy = 11.3;

  //G4double energy

  //G4double simulationEnergy = 0.662;

  //G4double simulationEnergy = startEnergy+(finalEnergy-startEnergy)*G4UniformRand();
  G4double simulationEnergy = 1333;

  fParticleGun->SetParticleEnergy(simulationEnergy*keV);
  //fParticleGun->SetParticleEnergy(Ba133EnSelector()*keV);

  //fParticleGun->SetParticleEnergy(1.1732*MeV);
  //fParticleGun2->SetParticleEnergy(1.3325*MeV);
  //fParticleGun3->SetParticleEnergy(1.274*MeV);

  //fParticleGun->SetParticleMomentumDirection(this->SampleFromPlusX());
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1,0,0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
  //fParticleGun2->GeneratePrimaryVertex(anEvent);
  //fParticleGun3->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector PrimaryGeneratorAction::SampleIsotropic(){
  G4double cosTheta = 2*G4UniformRand() - 1.0;
  G4double phi = 2*CLHEP::pi*G4UniformRand();
  G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  G4double ux = sinTheta*std::cos(phi),
           uy = sinTheta*std::sin(phi),
           uz = cosTheta;
  G4ThreeVector v(ux,uy,uz);
  return v;
}

G4double PrimaryGeneratorAction::Ba133EnSelector(){
  G4double MCseed = G4UniformRand();
  G4double v = 0;
  if (MCseed<0.4791875821){
    v = 356;
  }
  else if (MCseed<0.6208201406){
    v = 302;
  }
  else if (MCseed<0.6898602209){
    v = 383;
  }
  else if (MCseed<0.745154066){
    v = 276;
  }
  else{
    v = 81;
  }

  return v;
}

G4ThreeVector PrimaryGeneratorAction::SampleFromPlusX(){
  //G4double cosTheta = 2*G4UniformRand() - 1.0;
  //G4double phi = 2*3.14*G4UniformRand();
  G4double cosTheta = 0.242535625-2.0*0.242535625*G4UniformRand();
  G4double phi = 0.2449786631-2.0*0.2449786631*G4UniformRand();
  G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  G4double ux = sinTheta*std::cos(phi),
           uy = sinTheta*std::sin(phi),
           uz = cosTheta;
  G4ThreeVector v(ux,uy,uz);
  return v;
}

G4ThreeVector PrimaryGeneratorAction::SampleFromPlusZ(const double & distance, const double & radius){

  G4double phi = 2.0*CLHEP::pi*G4UniformRand();
  G4double cosTheta = 1.0-(1.0-distance/(sqrt(distance*distance+radius*radius)))*G4UniformRand();
  G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  G4double ux = sinTheta*std::cos(phi),
           uy = sinTheta*std::sin(phi),
           uz = cosTheta;
  G4ThreeVector v(ux,uy,uz);
  return v;

}