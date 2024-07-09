#include "RunAction.hh"

#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "Run.hh"
//#include "HistoManager.hh" //Old histo manager

// Geant
#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4AccumulableManager.hh"
#include "G4AnalysisManager.hh"



RunAction::RunAction() : G4UserRunAction(){
  //  (HistoManager::GetPointer())->BeginOfRun();
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
 
  analysisManager->SetNtupleMerging(true);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("MTout.root");
  //analysisManager->SetFileType("root"); // Setting file type explicitly (if needed)
  analysisManager->OpenFile();


  // h2 number 0
  analysisManager->CreateH1("eDep","Energy Deposition",1500,0,1500); 
  analysisManager->SetH1YAxisTitle(0,"Counts");
  analysisManager->SetH1XAxisTitle(0,"Energy Deposition [MeV]");  
  
  // h2 number 1
  analysisManager->CreateH1("InitE","Energy Deposition",1500,0,1500); 
  analysisManager->SetH1YAxisTitle(0,"Counts");
  analysisManager->SetH1XAxisTitle(0,"Energy Deposition [MeV]");  
  // h2 number 2
  analysisManager->CreateH1("Diff","Energy Deposition",1500,0,1500); 
  analysisManager->SetH1YAxisTitle(0,"Counts");
  analysisManager->SetH1XAxisTitle(0,"Energy Deposition [MeV]");  
  // analysisManager->CreateH1("eDep","Energy Deposition",1000,0,1); 
  // analysisManager->SetH1XAxisTitle(0,"Energy Deposition [MeV]");
  // analysisManager->SetH1YAxisTitle(0,"Counts");

  // Creating ntuple
  // analysisManager->CreateNtuple("t1", "data");
  // analysisManager->CreateNtupleIColumn("eventID");
  // analysisManager->CreateNtupleIColumn("stepID");
  // analysisManager->CreateNtupleDColumn("edep");
  // analysisManager->CreateNtupleDColumn("x");
  // analysisManager->CreateNtupleDColumn("y");
  // analysisManager->CreateNtupleDColumn("z");
  // analysisManager->CreateNtupleDColumn("kE");
  // analysisManager->CreateNtupleIColumn("parentID");
  // analysisManager->CreateNtupleIColumn("trackID");
  // analysisManager->CreateNtupleIColumn("pdgNum");
  // analysisManager->CreateNtupleIColumn("intVolName");
  // analysisManager->FinishNtuple();

}

RunAction::~RunAction(){

}

G4Run* RunAction::GenerateRun(){
  mainRun = new Run;
  return mainRun;
}

void RunAction::BeginOfRunAction(const G4Run* aRun){
   auto analysisManager = G4AnalysisManager::Instance();
   analysisManager->OpenFile();

}

void RunAction::EndOfRunAction(const G4Run* aRun){
  auto analysisManager = G4AnalysisManager::Instance();
  if (IsMaster())
  { 
    G4cout << "-------Master-------\n"
    << "\n------- End of Global Run -------\n"
    <<G4endl;
  }
  else
  {
    G4cout << "\n------- End of Local Run -------\n";
  }
  G4cout << "You are going to write the root file" << G4endl;
  // (HistoManager::GetPointer())->EndOfRun();
  analysisManager->Write();
  analysisManager->CloseFile();  
}
