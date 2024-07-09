#include "DetectorConstruction.hh"

void PrintSurfaceDetails(G4OpticalSurface* surface) {
    if (!surface) return;

    G4cout << "Surface Name: " << surface->GetName() << G4endl;
    G4cout << "Surface Type: " << surface->GetType() << G4endl;
    G4cout << "Surface Finish: " << surface->GetFinish() << G4endl;

    G4MaterialPropertiesTable* mpt = surface->GetMaterialPropertiesTable();
    if (mpt) {
        G4cout << "Surface Properties: " << G4endl;
        mpt->DumpTable();
    }
    G4cout << G4endl;
}

void PrintSurfaceInfo(const G4String& surfaceName = "") {
    const G4LogicalSkinSurfaceTable* skinSurfaces = G4LogicalSkinSurface::GetSurfaceTable();
    const G4LogicalBorderSurfaceTable* borderSurfaces = G4LogicalBorderSurface::GetSurfaceTable();

    G4cout << "\n===== Surface Information =====" << G4endl;

    // Check skin surfaces
    for (auto* skinSurface : *skinSurfaces) {
        auto* optSurface = dynamic_cast<G4OpticalSurface*>(skinSurface->GetSurfaceProperty());
        if (surfaceName.empty() || skinSurface->GetName() == surfaceName) {
            PrintSurfaceDetails(optSurface);
        }
    }

    // Check border surfaces
    for (auto& borderSurfaceEntry : *borderSurfaces) {
        auto* borderSurface = borderSurfaceEntry.second;
        auto* optSurface = dynamic_cast<G4OpticalSurface*>(borderSurface->GetSurfaceProperty());
        if (surfaceName.empty() || borderSurface->GetName() == surfaceName) {
            PrintSurfaceDetails(optSurface);
        }
    }
    G4cout << "====================================" << G4endl;
}


DetectorConstruction::DetectorConstruction(): G4VUserDetectorConstruction(),fVisAttributes(){
  std::cout << "detector constructor\n";
  matDef.defineMaterials();
}

DetectorConstruction::~DetectorConstruction()
{
  for (G4int i=0; i<G4int(fVisAttributes.size()); ++i){
    delete fVisAttributes[i];
  }
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  G4bool  checkOverlaps = true;
  G4Color red(1,0,0);
  G4Color red2(1,0,0.3);
  G4Color red3(1,0,0.5);
  G4Color green(0,1,0);
  G4Color yellow(1,1,0);
  G4Color lightGrey(0.6,0.6,0.6,0.5);
  G4Color darkGrey(0.2,0.2,0.2,1.0);
  G4Color white(0.9,0.9,0.9);
  G4Color orange(1.0,0.34,0.2);

  G4RotationMatrix* turnSide = new G4RotationMatrix();
  turnSide->rotateY(90.0*deg);

  G4VSolid* worldVolumePhys = new G4Box("100",2.0*m, 2.0*m, 2.0*m);
  G4LogicalVolume* worldLog = new G4LogicalVolume(worldVolumePhys,matDef.airMat,"100");
  G4VPhysicalVolume* worldPos = new G4PVPlacement(0,G4ThreeVector(0,0,0),worldLog,"100",nullptr,false,0);
  worldLog->SetVisAttributes(G4VisAttributes::GetInvisible());

  /*G4VSolid* sourcePlastic = new G4Tubs("200",0.0,2.54/2.0*cm,3.0/32.0*2.54*cm,0.0,2.0*CLHEP::pi);
  G4LogicalVolume* sourcePlasticLog = new G4LogicalVolume(sourcePlastic,matDef.acrylicMat,"200");
  G4PVPlacement* sourcePlasticPos = new G4PVPlacement(0,G4ThreeVector((15-5.75)*2.54*cm,0,2.5*2.54*cm),sourcePlasticLog,"200",worldLog,false,0);
  G4VisAttributes* sourcePlasticVisAttributes = new G4VisAttributes(orange);
  sourcePlasticLog->SetVisAttributes(sourcePlasticVisAttributes);
  fVisAttributes.push_back(sourcePlasticVisAttributes);*/

  /*G4VSolid* sourcePlastic = new G4Tubs("200",0.0,2.54/2.0*cm,3.0/32.0*2.54*cm,0.0,2.0*CLHEP::pi);
  G4LogicalVolume* sourcePlasticLog = new G4LogicalVolume(sourcePlastic,matDef.feMetalMat,"200");
  G4PVPlacement* sourcePlasticPos = new G4PVPlacement(0,G4ThreeVector((15-5.75)*2.54*cm,0,2.5*2.54*cm),sourcePlasticLog,"200",worldLog,false,0);
  G4VisAttributes* sourcePlasticVisAttributes = new G4VisAttributes(orange);
  sourcePlasticLog->SetVisAttributes(sourcePlasticVisAttributes);
  fVisAttributes.push_back(sourcePlasticVisAttributes);*/


  /*G4VSolid* sourcePlastic = new G4Tubs("200",0.0,0.5/2.0*2.54*cm,2.5*2.54*cm,0.0,2.0*CLHEP::pi);
  G4LogicalVolume* sourcePlasticLog = new G4LogicalVolume(sourcePlastic,matDef.acrylicMat,"200");
  G4PVPlacement* sourcePlasticPos = new G4PVPlacement(turnSide,G4ThreeVector((2.5*2.54+(15-5.75)*2.54-0.25*2.54)*cm,0,2.5*2.54*cm),sourcePlasticLog,"200",worldLog,false,0);
  G4VisAttributes* sourcePlasticVisAttributes = new G4VisAttributes(orange);
  sourcePlasticLog->SetVisAttributes(sourcePlasticVisAttributes);
  fVisAttributes.push_back(sourcePlasticVisAttributes);*/

  G4RotationMatrix* turnX = new G4RotationMatrix();
  turnX->rotateX(90.0*deg);

  G4RotationMatrix* turnZ = new G4RotationMatrix();
  turnZ->rotateZ(90.0*deg);


  // G4VSolid* sourcePlastic = new G4Box("200",1.0*cm,0.25*cm,0.05*cm);
  // G4LogicalVolume* sourcePlasticLog = new G4LogicalVolume(sourcePlastic,matDef.acrylicMat,"200");
  // G4PVPlacement* sourcePlasticPos = new G4PVPlacement(turnZ,G4ThreeVector((15-5.75)*2.54*cm,0,2.5*2.54*cm),sourcePlasticLog,"200",worldLog,false,0);
  // G4VisAttributes* sourcePlasticVisAttributes = new G4VisAttributes(orange);
  // sourcePlasticLog->SetVisAttributes(sourcePlasticVisAttributes);
  // fVisAttributes.push_back(sourcePlasticVisAttributes);


  // G4VSolid* cartSurface1 = new G4Box("201",15.0*2.54*cm,10.0*2.54*cm,0.05*2.54*cm);
  // G4LogicalVolume* cartSurface1Log = new G4LogicalVolume(cartSurface1,matDef.SS304Mat,"201");
  // G4PVPlacement* cartSurface1Pos = new G4PVPlacement(0,G4ThreeVector(0,0,-0.05*2.54*cm),cartSurface1Log,"201",worldLog,false,0);
  // G4VisAttributes* cartSurfaceVisAttributes = new G4VisAttributes(darkGrey);
  // cartSurface1Log->SetVisAttributes(cartSurfaceVisAttributes);
  // fVisAttributes.push_back(cartSurfaceVisAttributes);

  // G4VSolid* cartSurface2 = new G4Box("202",15.0*2.54*cm,10.0*2.54*cm,0.05*2.54*cm);
  // G4LogicalVolume* cartSurface2Log = new G4LogicalVolume(cartSurface2,matDef.SS304Mat,"202");
  // G4PVPlacement* cartSurface2Pos = new G4PVPlacement(0,G4ThreeVector(0,0,-17.05*2.54*cm),cartSurface2Log,"202",worldLog,false,0);
  // cartSurface2Log->SetVisAttributes(cartSurfaceVisAttributes);

  // G4VSolid* cartSurface3 = new G4Box("203",15.0*2.54*cm,10.0*2.54*cm,0.05*2.54*cm);
  // G4LogicalVolume* cartSurface3Log = new G4LogicalVolume(cartSurface3,matDef.SS304Mat,"203");
  // G4PVPlacement* cartSurface3Pos = new G4PVPlacement(0,G4ThreeVector(0,0,-34.05*2.54*cm),cartSurface3Log,"203",worldLog,false,0);
  // cartSurface3Log->SetVisAttributes(cartSurfaceVisAttributes);

  // G4VSolid* floor = new G4Box("204",100.0*cm,100.0*cm,50.0*cm);
  // G4LogicalVolume* floorLog = new G4LogicalVolume(floor,matDef.concreteMat,"204");
  // G4PVPlacement* floorPos = new G4PVPlacement(0,G4ThreeVector(0,0,(-37.0*2.54-50.0)*cm),floorLog,"204",worldLog,false,0);
  // G4VisAttributes* floorVisAttributes = new G4VisAttributes(white);
  // floorLog->SetVisAttributes(floorVisAttributes);
  // fVisAttributes.push_back(floorVisAttributes);

  // G4VSolid* EJ315Plastic = new G4Tubs("300",0.0,2*2.54*cm,3*2.54*cm,0.0,2.0*CLHEP::pi);
  // G4LogicalVolume* EJ315PlasticLog = new G4LogicalVolume(EJ315Plastic,matDef.EJ309,"300");
  // G4PVPlacement* EJ315PlasticPos = new G4PVPlacement(turnSide,G4ThreeVector(-0.11*cm,0,2.5*2.54*cm),EJ315PlasticLog,"300",worldLog,false,0);
  // G4VisAttributes* EJ315PlasticVisAttributes = new G4VisAttributes(red);
  // EJ315PlasticLog->SetVisAttributes(EJ315PlasticVisAttributes);
  // fVisAttributes.push_back(EJ315PlasticVisAttributes);  

  // G4VSolid* alShieldEJ315Plastic = new G4Tubs("301",2*2.54*cm,(2*2.54+0.11)*cm,4.5*2.54*cm,0.0,2.0*CLHEP::pi);
  // G4LogicalVolume* alShieldEJ315PlasticLog = new G4LogicalVolume(alShieldEJ315Plastic,matDef.alMetalMat,"301");
  // G4PVPlacement* alShieldEJ315PlasticPos = new G4PVPlacement(turnSide,G4ThreeVector((-1.5*2.54-0.11)*cm,0,2.5*2.54*cm),alShieldEJ315PlasticLog,"301",worldLog,false,0);
  // G4VisAttributes* alShieldEJ315PlasticVisAttributes = new G4VisAttributes(lightGrey);
  // alShieldEJ315PlasticLog->SetVisAttributes(alShieldEJ315PlasticVisAttributes);
  // fVisAttributes.push_back(alShieldEJ315PlasticVisAttributes);  

  // G4VSolid* alCapEJ315Plastic = new G4Tubs("302",0.0,(2*2.54+0.11)*cm,0.11*cm,0.0,2.0*CLHEP::pi);
  // G4LogicalVolume* alCapEJ315PlasticLog = new G4LogicalVolume(alCapEJ315Plastic,matDef.alMetalMat,"302");
  // G4PVPlacement* alCapEJ315PlasticPos = new G4PVPlacement(turnSide,G4ThreeVector((-0.11/2.0+3.0*2.54)*cm,0,2.5*2.54*cm),alCapEJ315PlasticLog,"302",worldLog,false,0);
  // alCapEJ315PlasticLog->SetVisAttributes(alShieldEJ315PlasticVisAttributes);

  // G4VSolid* alCap2EJ315Plastic = new G4Tubs("303",0.0,(2*2.54+0.11)*cm,0.11*cm,0.0,2.0*CLHEP::pi);
  // G4LogicalVolume* alCap2EJ315PlasticLog = new G4LogicalVolume(alCap2EJ315Plastic,matDef.alMetalMat,"303");
  // G4PVPlacement* alCap2EJ315PlasticPos = new G4PVPlacement(turnSide,G4ThreeVector(-(0.11+6.0*2.54)*cm,0,2.5*2.54*cm),alCap2EJ315PlasticLog,"303",worldLog,false,0);
  // alCap2EJ315PlasticLog->SetVisAttributes(alShieldEJ315PlasticVisAttributes);


  // G4VSolid* EJ309Plastic = new G4Tubs("400",0.0,2.54*cm,2.54*cm,0.0,2.0*CLHEP::pi);
  // // G4VSolid* EJ309Plastic = new G4Tubs("400",0.0,2.54*cm,25*cm,0.0,2.0*CLHEP::pi);
  // G4LogicalVolume* EJ309PlasticLog = new G4LogicalVolume(EJ309Plastic,matDef.EJ309,"400");
  // G4PVPlacement* EJ309PlasticPos = new G4PVPlacement(turnSide,G4ThreeVector(-(3*2.54+2*0.11+2.54)*cm,0,1.5*2.54*cm),EJ309PlasticLog,"400",worldLog,false,0);
  // G4VisAttributes* EJ309PlasticVisAttributes = new G4VisAttributes(green);
  // EJ309PlasticLog->SetVisAttributes(EJ309PlasticVisAttributes);
  // fVisAttributes.push_back(EJ309PlasticVisAttributes);  

  // G4VSolid* alShieldEJ309Plastic = new G4Tubs("401",2.54*cm,(2.54+0.11)*cm,2.54*cm,0.0,2.0*CLHEP::pi);
  // G4LogicalVolume* alShieldEJ309PlasticLog = new G4LogicalVolume(alShieldEJ309Plastic,matDef.alMetalMat,"401");
  // G4PVPlacement* alShieldEJ309PlasticPos = new G4PVPlacement(turnSide,G4ThreeVector(-(3*2.54+2*0.11+2.54)*cm,0,1.5*2.54*cm),alShieldEJ309PlasticLog,"401",worldLog,false,0);
  // G4VisAttributes* alShieldEJ309PlasticVisAttributes = new G4VisAttributes(lightGrey);
  // alShieldEJ309PlasticLog->SetVisAttributes(alShieldEJ309PlasticVisAttributes);
  // fVisAttributes.push_back(alShieldEJ309PlasticVisAttributes);  

  // G4VSolid* alCapEJ309Plastic = new G4Tubs("402",0.0,(2.54+0.11)*cm,0.11*cm,0.0,2.0*CLHEP::pi);
  // G4LogicalVolume* alCapEJ309PlasticLog = new G4LogicalVolume(alCapEJ309Plastic,matDef.alMetalMat,"402");
  // G4PVPlacement* alCapEJ309PlasticPos = new G4PVPlacement(turnSide,G4ThreeVector(-(3*2.54+0.11)*cm,0,1.5*2.54*cm),alCapEJ309PlasticLog,"402",worldLog,false,0);
  // G4VisAttributes* alCapEJ309PlasticVisAttributes = new G4VisAttributes(lightGrey);
  // alCapEJ309PlasticLog->SetVisAttributes(alCapEJ309PlasticVisAttributes);
  // fVisAttributes.push_back(alCapEJ309PlasticVisAttributes);

  G4VSolid* OGSbox = new G4Box("400",0.3*cm,0.3*cm,2.5*cm);
  G4LogicalVolume* OGSboxLog = new G4LogicalVolume(OGSbox,matDef.OGlassMat,"400");
  G4VPhysicalVolume* OGSboxPos = new G4PVPlacement(0,G4ThreeVector(0,0,2.5*cm),OGSboxLog,"400",worldLog,false,0);
  G4VisAttributes* OGSboxVisAttributes = new G4VisAttributes(white);
  OGSboxLog->SetVisAttributes(OGSboxVisAttributes);
  fVisAttributes.push_back(OGSboxVisAttributes);

  G4VSolid* OpitPad1 = new G4Box("401",0.3*cm,0.3*cm,0.05*cm);
  G4LogicalVolume* OpitPadLog1 = new G4LogicalVolume(OpitPad1,matDef.airMat,"401");  
  G4VPhysicalVolume* OpitPadPos1 = new G4PVPlacement(0,G4ThreeVector(0,0,5.05*cm),OpitPadLog1,"401",worldLog,false,0);
  G4VisAttributes* OpitPadVisAttributes1 = new G4VisAttributes(white);
  OpitPadLog1->SetVisAttributes(OpitPadVisAttributes1);
  fVisAttributes.push_back(OpitPadVisAttributes1);

  G4VSolid* OpitPad2 = new G4Box("402",0.3*cm,0.3*cm,0.05*cm);
  G4LogicalVolume* OpitPadLog2 = new G4LogicalVolume(OpitPad2,matDef.airMat,"402");  
  G4VPhysicalVolume* OpitPadPos2 = new G4PVPlacement(0,G4ThreeVector(0,0,-0.05*cm),OpitPadLog2,"402",worldLog,false,0);
  G4VisAttributes* OpitPadVisAttributes2 = new G4VisAttributes(white);
  OpitPadLog2->SetVisAttributes(OpitPadVisAttributes2);
  fVisAttributes.push_back(OpitPadVisAttributes2);

  //PerfectReflectorSkinSuit for OGSbox

  std::vector<G4double> OGSphoE = {2.0*eV, 3.0*eV}; // Photon energies
  std::vector<G4double> Alwaysrefl = {1, 1};  

  G4OpticalSurface* ReflectiveSurface = new G4OpticalSurface("ReflectiveSurface");

  ReflectiveSurface->SetType(dielectric_metal); // adjust this type as suitable for your needs
  ReflectiveSurface->SetFinish(polished); // or ground, depending on your specific requirements
  ReflectiveSurface->SetModel(glisur); // again, unified might be more appropriate in newer versions

  G4MaterialPropertiesTable* ReflectiveSurfaceProperty = new G4MaterialPropertiesTable();
  ReflectiveSurfaceProperty->AddProperty("REFLECTIVITY", OGSphoE, Alwaysrefl);
  ReflectiveSurface->SetMaterialPropertiesTable(ReflectiveSurfaceProperty);

  // Now apply the optical surface to just one interface between the two volumes
  G4LogicalBorderSurface* surface = new G4LogicalBorderSurface("ReflectiveBorder", OGSboxPos, worldPos, ReflectiveSurface);

  //PrintSurfaceInfo();

  return worldPos;
}

void DetectorConstruction::ConstructSDandField(){
  //G4String sdName1 = "EJ315";
  G4String sdName2 = "OGS";
  //DetectorSD* sd1 = new DetectorSD(sdName1);
  DetectorSD* sd2 = new DetectorSD(sdName2);
  //G4SDManager::GetSDMpointer()->AddNewDetector(sd1);
  G4SDManager::GetSDMpointer()->AddNewDetector(sd2);
  //SetSensitiveDetector("300",sd1);
  SetSensitiveDetector("400",sd2);
}

