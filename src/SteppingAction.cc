#include "SteppingAction.hh"
//#include "HistoManager.hh" //Old histo manager


using namespace std;

SteppingAction::SteppingAction(EventAction* eventAction) : G4UserSteppingAction(){
	fEventAction = eventAction;
}

SteppingAction::~SteppingAction(){
}

void SteppingAction::UserSteppingAction(const G4Step* aStep){
	G4int prestepVolume = atoi(aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName());

	if(prestepVolume==600){
		aStep->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
	}
	

	const G4ParticleDefinition* pd = aStep->GetTrack()->GetDefinition();
  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4int stepId    = aStep->GetTrack()->GetCurrentStepNumber();
  G4double kE = preStepPoint->GetKineticEnergy();
  G4double fixedKE = kE/keV;
  G4double postkE = aStep->GetPostStepPoint()->GetKineticEnergy();
  G4double postfixedKE = postkE/keV;
  G4double edepStep = aStep->GetTotalEnergyDeposit();
  edepStep = edepStep/keV;
  EventAction* myEventAction = (EventAction*)(G4EventManager::GetEventManager()->GetUserEventAction());
  G4double delke = fixedKE - postfixedKE;
  double rando = G4UniformRand();
  bool phocheckedstatus = 0;

  	if ((stepId==1) && (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()=="400")) {
  		if (pd == G4Electron::Electron()){
  			myEventAction->StoreInitEnrg(fixedKE);
  		}
  	}

	if ((aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()=="400") && (aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName()=="400")){
  		if (pd == G4Electron::Electron()){
    		myEventAction->AddEnrg(delke);
    		//(HistoManager::GetPointer())->Fill(0,delke,1.0);
  		}
  	}

  	if ((aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()=="401")|| (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()=="402")){
  		if (pd == G4OpticalPhoton::OpticalPhoton()){
  			if((rando < 0.80) && (phocheckedstatus==0)){
  			  myEventAction->CollectPhoton(1);
  			  aStep->GetTrack()->SetTrackStatus(fStopAndKill);
  		    }
  		    else{
  		      phocheckedstatus = 1;
  		    }
  		}
  	}
	//G4cout<<rando<<G4endl;
}