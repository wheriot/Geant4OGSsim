#ifndef __MATERIALDEFINITIONS__
#define __MATERIALDEFINITIONS__

//General Geant4 Libraries
#include "globals.hh"
#include "G4NistManager.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"

class MaterialDefinitions{

    public:
        
      MaterialDefinitions();
      ~MaterialDefinitions();
      void defineMaterials();

      std::vector<G4double> OGSenergy, OGSrindex, OGSabsorption, OGSscint, OGSScatLength, AlwaysScatLength;

      G4MaterialPropertiesTable* OGS_MPT;
      G4MaterialPropertiesTable* AIR_MPT;

      G4NistManager *manager;

      G4Material* vacuumMat;
      G4Material* airMat;
      G4Material* graphiteMat;
      G4Material* alMetalMat;
      G4Material* feMetalMat;
      G4Material* ABSMat;
      G4Material* imagePlatePhosphorMat;
      G4Material* imagePlatePlasticMat;
      G4Material* imagePlateMagneticMat;
      G4Material* polyMat;
      G4Material* EJ309B5;
      G4Material* EJ315;
      G4Material* EJ309;
      G4Material* SS304Mat;
      G4Material* acrylicMat;
      G4Material* concreteMat;
      G4Material* OGlassMat;


};

#endif
