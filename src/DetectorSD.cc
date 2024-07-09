#include "DetectorSD.hh"
//#include "HistoManager.hh" //Old histo manager

DetectorSD::DetectorSD(G4String name):G4VSensitiveDetector(name){
  G4cout << "your sensitive detector's name is " << name << G4endl;
  G4SDManager::GetSDMpointer()-> AddNewDetector(this);
}

DetectorSD::~DetectorSD(){
}

G4bool DetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist){
  // const G4ParticleDefinition* pd = aStep->GetTrack()->GetDefinition();
  // G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  // G4int stepId    = aStep->GetTrack()->GetCurrentStepNumber();
  // G4double kE = preStepPoint->GetKineticEnergy();
  // G4double fixedKE = kE/keV;
  // G4double edepStep = aStep->GetTotalEnergyDeposit();
  // edepStep = edepStep/keV;

  // EventAction* myEventAction = (EventAction*)(G4EventManager::GetEventManager()->GetUserEventAction());

  // if (pd == G4Electron::Electron()){
  //   myEventAction->AddEnrg(edepStep);
  // }

//!!Old Particle Collection Code!!//
  // if (pd == G4Gamma::Gamma()) {
  //   (HistoManager::GetPointer())->Fill(0,fixedKE,1.0);
  // }
  // else if (pd == G4Electron::Electron()){
  //    if(stepId == 1){
  //         (HistoManager::GetPointer())->Fill(1,fixedKE,1.0);   
  //  }
  //   else {
  //     //G4cout << "Step ID is " << stepId << G4endl;
  //     (HistoManager::GetPointer())->Fill(2,fixedKE,1.0);
  // }
  // }
//!!Colton's Stuff!!//
  // const G4ParticleDefinition* pd = aStep->GetTrack()->GetDefinition();
  // if(pd == G4Gamma::Gamma()) {
  // G4int pdgNum = aStep->GetTrack()->GetDefinition()->GetPDGEncoding();
  // G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  // G4StepPoint* postStepPoint = aStep->GetPostStepPoint();  
  // G4double edep = aStep->GetTotalEnergyDeposit();
  // G4String strVolName = preStepPoint->GetTouchableHandle()->GetVolume()->GetName();
  // G4int intVolName = atoi(strVolName);
  // G4int stepID          = aStep->GetTrack()->GetCurrentStepNumber();
  // G4int trackID         = aStep->GetTrack()->GetTrackID();
  // G4double edepStep     = aStep->GetTotalEnergyDeposit();
  // G4ThreeVector inpos   = preStepPoint->GetPosition();
  // G4ThreeVector outpos  = postStepPoint->GetPosition();
  // G4int parentTrackID   = aStep->GetTrack()->GetParentID();
  
  // G4double kE          = preStepPoint->GetKineticEnergy();///CLHEP::keV;
  // G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // EventAction* myEventAction = (EventAction*)(G4EventManager::GetEventManager()->GetUserEventAction());
  // //analysisManager->FillH2(0,inpos.getZ(),inpos.getY(),edepStep);
  // //analysisManager->FillH2(1,inpos.getZ(),inpos.getY(),this->convertEnergyToSignal(edepStep));
  // if (!myEventAction->checkIfInTrack(trackID)){
  //   myEventAction->addToTrack(trackID);
  //   //analysisManager->FillH2(2,inpos.getZ(),inpos.getY(),this->convertEnergyToSignal(kE));
  // }
  // myEventAction->setEventID(eventID);
  // myEventAction->setStepID(stepID);
  // myEventAction->setEDep(edepStep/MeV);
  // myEventAction->setX(inpos.getX());
  // myEventAction->setY(inpos.getY());
  // myEventAction->setZ(inpos.getZ());

  // G4double fixedKE = kE/MeV;

  // //G4cout<<"IN SEVEN: "<<fixedKE<<G4endl;
  // //G4cout<<"IN ELEVEN: "<<intVolName<<G4endl;

  // myEventAction->setKE(fixedKE);
  // myEventAction->setParentID(parentTrackID);
  // myEventAction->setTrackID(trackID);
  // myEventAction->setPDG(pdgNum);
  // myEventAction->setIntVol(intVolName);
  // myEventAction->FillMyNtuple();
  // }
  return true;
}

double DetectorSD::convertEnergyToSignal(G4double E){
  if(E<2.11){
      return 0.22039*exp(-pow((E-1.5049),2.0)/(1.1842*1.1842));
  }
  else{
      return 0.33357*pow(E,(-0.91377));
    }
}

void DetectorSD::Initialize(){
}

void DetectorSD::EndOfEvent(){
}
