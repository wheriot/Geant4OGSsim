#ifndef __DETECTORCONSTRUCTION__
#define __DETECTORCONSTRUCTION__

//Geant4 Libraries
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4PVPlacement.hh"
#include "G4GenericMessenger.hh"
#include "G4LogicalVolume.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4SystemOfUnits.hh"

#include "G4Material.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4SurfaceProperty.hh"

//My Libraries
#include "MaterialDefinitions.hh"
#include "DetectorSD.hh"

//c++ Libraries
#include<vector>
#include <iostream>

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction();

  private:
    MaterialDefinitions matDef;
    DetectorSD* imagepPlateSensetive;

  public:
    G4VPhysicalVolume* Construct();
    void ConstructSDandField();

  protected:
    std::vector<G4VisAttributes*> fVisAttributes;
};

#endif
