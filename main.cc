#include <fstream>
#include <math.h>
#include "G4ios.hh"

// package includes
//
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "ActionInitialization.hh"
// geant4 includes
#include "G4ios.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
// Physics lists
#include "FTFP_BERT.hh"
#include "QGSP_BIC_HP.hh"
#include "QGSP_INCLXX_HP.hh"
#include "QGSP_BIC_HP.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_INCLXX_HP.hh"
#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"

#include <TROOT.h>
// run ./main -help to see input commands
// (0) executable
// (1) macro
void help();
//------------------------------------------------------------------------------
int main(int argc,char** argv)
{

  gROOT->GetInterpreter();
  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  // Construct the default run manager
  // for single processor
  //G4RunManager* runManager = new G4RunManager;
  //G4int nThreads = 3;

  long seeds[2];
  time_t systime = time(NULL);
  seeds[0] = (long) systime;
  seeds[1] = (long) (systime*G4UniformRand());
  G4Random::setTheSeeds(seeds);


  // #ifdef G4MULTITHREADED
  // auto runManager = new G4MTRunManager;
  // if ( nThreads > 0 ) runManager->SetNumberOfThreads(nThreads);
  // #else
  auto runManager = new G4RunManager;
    // auto runManager = new G4MTRunManager;
    // runManager->SetNumberOfThreads(32);
  // #endif

  DetectorConstruction* dc = new DetectorConstruction();
  runManager->SetUserInitialization(dc);
  G4VModularPhysicsList* physicsList = new QGSP_BIC_HP; //Default Colton List
  //G4VModularPhysicsList* physicsList = new FTFP_BERT; //AWilhelm List for scint sim
  //physicsList->SetVerboseLevel(1);


  physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  auto opticalParams               = G4OpticalParameters::Instance();
  opticalParams->SetWLSTimeProfile("exponential");

  physicsList->RegisterPhysics(opticalPhysics);

  runManager->SetUserInitialization(physicsList);
  runManager->SetUserInitialization(new ActionInitialization());

  G4UIExecutive* ui = 0;
  if ( argc == 1 ){
    ui = new G4UIExecutive(argc, argv);
  }
  
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc == 2)  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    std::cout << "starting UI session...\n";
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  delete runManager;
}

void help(){
 std:: cout<<"-h for help"<<std::endl;
}
