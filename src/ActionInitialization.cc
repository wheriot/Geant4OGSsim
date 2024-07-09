#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization():G4VUserActionInitialization(){
}

ActionInitialization::~ActionInitialization(){
}

void ActionInitialization::BuildForMaster() const{
  SetUserAction(new RunAction);
}

void ActionInitialization::Build() const{
  SetUserAction(new PrimaryGeneratorAction);
  RunAction* myRunAction = new RunAction;
  SetUserAction(myRunAction);
  EventAction* myEventAction = new EventAction(myRunAction);
  SetUserAction(myEventAction);
  SetUserAction(new SteppingAction(myEventAction));
}
