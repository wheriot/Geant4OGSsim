#include "Run.hh"

namespace { G4Mutex myRunMutex = G4MUTEX_INITIALIZER; }

Run::Run(): G4Run(){
  G4cout << "Creating Run in thread " << G4Threading::G4GetThreadId();
  G4cout << "...done." << G4endl;
}

Run::~Run(){
}

void Run::RecordEvent(const G4Event* evt){
  G4Run::RecordEvent(evt);
}

void Run::Merge(const G4Run* run){
  G4Run::Merge(run);
}