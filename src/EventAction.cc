//
#include "EventAction.hh"
#include "Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4String.hh"
#include "G4SystemOfUnits.hh"
#include "TMath.h"
#include "G4WorkerThread.hh"
#include "G4AccumulableManager.hh"
#include "TRandom2.h"
#include "G4AnalysisManager.hh"
//#include "HistoManager.hh" //Old histo manager


EventAction::EventAction(RunAction* runAction): G4UserEventAction()
{
}

EventAction::~EventAction(){
    G4cout << "Deleting EventAction";
    G4cout<<"...done"<<G4endl;
}

void EventAction::BeginOfEventAction(const G4Event* event){
  EventAction* myEventAction = (EventAction*)(G4EventManager::GetEventManager()->GetUserEventAction());
}

void EventAction::AddEnrg(double val){
  totaleDep = totaleDep + val;
} 

void EventAction::StoreInitEnrg(double val){
  InitEnrg = InitEnrg + val;
}

void EventAction::CollectPhoton(int val){
  if (val==1){
    phocollect1 = phocollect1 + 1;
  }
  if (val==2){
    phocollect2 = phocollect2 + 1;
  }

}

void EventAction::RecordEnrg(){
  if (InitEnrg==0){
    return;
  }
  //G4cout<<InitEnrg<<G4endl;
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(0,totaleDep);
  analysisManager->FillH1(1,InitEnrg);
  
  if (std::ceil(InitEnrg)-std::ceil(totaleDep)!=0){
    analysisManager->FillH1(2,InitEnrg-totaleDep);
    }
  // (HistoManager::GetPointer())->Fill(0,totaleDep,1.0);
  // (HistoManager::GetPointer())->Fill(1,InitEnrg,1.0);
  //   if (std::ceil(InitEnrg)-std::ceil(totaleDep)!=0){
  //       //G4cout<< std::ceil(InitEnrg)-std::ceil(totaleDep) <<G4endl;
  //       (HistoManager::GetPointer())->Fill(2,InitEnrg-totaleDep,1.0);
  //   }
  // (HistoManager::GetPointer())->Fill(3,phocollect1,1.0);

  phocollect1=0;
  phocollect2=0;
  totaleDep=0;
  InitEnrg=0;
}

// void EventAction::FillMyNtuple(){

//   EventAction* myEventAction = (EventAction*)(G4EventManager::GetEventManager()->GetUserEventAction());
//   auto analysisManager = G4AnalysisManager::Instance();
    
//   analysisManager->FillNtupleIColumn(0, 0, eventID);
//   analysisManager->FillNtupleIColumn(0, 1, stepID);
//   analysisManager->FillNtupleDColumn(0, 2, eDep);
//   analysisManager->FillNtupleDColumn(0, 3, x);
//   analysisManager->FillNtupleDColumn(0, 4, y);
//   analysisManager->FillNtupleDColumn(0, 5, z);
//   analysisManager->FillNtupleDColumn(0, 6, KE);
//   analysisManager->FillNtupleIColumn(0, 7, parentID);
//   analysisManager->FillNtupleIColumn(0, 8, trackID);
//   analysisManager->FillNtupleIColumn(0, 9, pdg);
//   analysisManager->FillNtupleIColumn(0, 10, intVol);

//   analysisManager->AddNtupleRow(0);
// }

void EventAction::EndOfEventAction(const G4Event* event){
  trackIDList.clear();
  RecordEnrg();
  //G4cout<<"1"<<G4endl;
}

bool EventAction::checkIfInTrack(G4int trackId){
  for(int i = 0; i<trackIDList.size(); ++i){
    if(trackIDList[i]==trackId){
      return true;
    }
  }
  return false;
}
