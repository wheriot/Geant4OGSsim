#include "MaterialDefinitions.hh"

MaterialDefinitions::MaterialDefinitions(){

    manager = G4NistManager::Instance();

}

MaterialDefinitions::~MaterialDefinitions(){

}

void MaterialDefinitions::defineMaterials(){

  //Default materials from Geant4
  vacuumMat = manager->FindOrBuildMaterial("G4_Galactic");
  airMat = manager->FindOrBuildMaterial("G4_AIR");
  graphiteMat = manager->FindOrBuildMaterial("G4_GRAPHITE");
  alMetalMat = manager->FindOrBuildMaterial("G4_Al");
  feMetalMat = manager->FindOrBuildMaterial("G4_Fe");


  
  //Elements building for geant4 
  G4Element*  H = manager->FindOrBuildElement("H");
  G4Element*  B = manager->FindOrBuildElement("B");
  G4Element*  C = manager->FindOrBuildElement("C");
  G4Element*  N = manager->FindOrBuildElement("N");
  G4Element*  O = manager->FindOrBuildElement("O");
  G4Element*  F = manager->FindOrBuildElement("F");
  G4Element* Na = manager->FindOrBuildElement("Na");
  G4Element* Al = manager->FindOrBuildElement("Al");
  G4Element* Si = manager->FindOrBuildElement("Si");
  G4Element* P = manager->FindOrBuildElement("P");
  G4Element* S = manager->FindOrBuildElement("S");
  G4Element* Ca = manager->FindOrBuildElement("Ca");
  G4Element* Cr = manager->FindOrBuildElement("Cr"); 
  G4Element* Mn = manager->FindOrBuildElement("Mn"); 
  G4Element* Fe = manager->FindOrBuildElement("Fe"); 
  G4Element* Ni = manager->FindOrBuildElement("Ni"); 
  G4Element* Zn = manager->FindOrBuildElement("Zn"); 
  G4Element* Br = manager->FindOrBuildElement("Br"); 
  G4Element*  I = manager->FindOrBuildElement("I"); 
  G4Element* Ba = manager->FindOrBuildElement("Ba"); 

  //Custom element building for geant4
  G4Isotope* H2 = new G4Isotope("H2", 1, 2, 2.014101*g/mole);
  G4Isotope* H1 = new G4Isotope("H1", 1, 1, 1.007825*g/mole);
  G4Element* deuteratedH = new G4Element("Deuterated Hydrogen","D",2);
  deuteratedH->AddIsotope(H2,0.999929);
  deuteratedH->AddIsotope(H1,0.000071);

  //ABS 3D Printing Resin
  G4double ABSDensity = 0.77*g/cm3;
  ABSMat = new G4Material("ABS",ABSDensity,3);
  ABSMat->AddElement(H, 17);
  ABSMat->AddElement(C, 15);
  ABSMat->AddElement(N, 1);

  //Image Plate Phosphor
  G4double imagePlatePhosphorDensity = 2.85*g/cm3;
  imagePlatePhosphorMat = new G4Material("imagePlatePhosphor",imagePlatePhosphorDensity,4);
  imagePlatePhosphorMat->AddElement(F,17);
  imagePlatePhosphorMat->AddElement(Br,15);
  imagePlatePhosphorMat->AddElement(I,1);
  imagePlatePhosphorMat->AddElement(Ba,17);

  //Image Plate Plastic Backing
  G4double imagePlatePlasticDensity = 1.66*g/cm3;
  imagePlatePlasticMat = new G4Material("imagePlatePlastic",imagePlatePlasticDensity,3);
  imagePlatePlasticMat->AddElement(H,2);
  imagePlatePlasticMat->AddElement(C,2);
  imagePlatePlasticMat->AddElement(O,1);

  //Image Plate Magnetic Backing
  G4double imagePlateMagneticDensity = 2.77*g/cm3;
  imagePlateMagneticMat = new G4Material("imagePlateMagnetic",imagePlateMagneticDensity,7);
  imagePlateMagneticMat->AddElement(H,15);
  imagePlateMagneticMat->AddElement(C,10);
  imagePlateMagneticMat->AddElement(N,1);
  imagePlateMagneticMat->AddElement(O,40);
  imagePlateMagneticMat->AddElement(Mn,2);
  imagePlateMagneticMat->AddElement(Fe,5);
  imagePlateMagneticMat->AddElement(Zn,1);

  //Polythylene
  G4double poltethyleneDensity = 0.96*g/cm3;
  polyMat = new G4Material("polethylene",poltethyleneDensity,2);
  polyMat->AddElement(H,2);
  polyMat->AddElement(C,1);

  //EJ300B5
  G4double EJ309B5Density = 0.96*g/cm3;
  EJ309B5 = new G4Material("EJ309B5",EJ309B5Density,3);
  EJ309B5->AddElement(H,0.09387043351);
  EJ309B5->AddElement(B,0.05066160306);
  EJ309B5->AddElement(C,0.8554679634);

  //EJ315
  G4double EJ315Density = 0.951*g/cm3;
  EJ315 = new G4Material("EJ315",EJ315Density,2);
  EJ315->AddElement(deuteratedH,0.1424);
  EJ315->AddElement(C,0.8576);

  //EJ309
  G4double EJ309Density = 0.956123*g/cm3;
  EJ309 = new G4Material("EJ309",EJ309Density,2);
  EJ309->AddElement(H,0.09482532355);
  EJ309->AddElement(C,0.9051746764);

  //Stainless Steel
  G4double SS304MatDensity = 8.03*g/cm3;
  SS304Mat = new G4Material("SS304",SS304MatDensity,8);
  SS304Mat->AddElement(C,0.000800);
  SS304Mat->AddElement(Mn,0.020000);
  SS304Mat->AddElement(P,0.000450);
  SS304Mat->AddElement(S,0.000300);
  SS304Mat->AddElement(Si,0.010000);
  SS304Mat->AddElement(Cr,0.190000);
  SS304Mat->AddElement(Ni,0.095000);
  SS304Mat->AddElement(Fe,0.683450);

  //Acrylic 
  G4double acrylicMatDensity = 1.18*g/cm3;
  acrylicMat = new G4Material("Acrylic",acrylicMatDensity,3);
  acrylicMat->AddElement(H,0.080545);
  acrylicMat->AddElement(O,0.319619);
  acrylicMat->AddElement(C,0.599836);

  //Acrylic 
  G4double concreteDensity = 2.25*g/cm3;
  concreteMat = new G4Material("Conrete",concreteDensity,7);
  concreteMat->AddElement(H,0.004530);
  concreteMat->AddElement(O,0.512600);
  concreteMat->AddElement(Si,0.360360);
  concreteMat->AddElement(Al,0.035550);
  concreteMat->AddElement(Na,0.015270);
  concreteMat->AddElement(Ca,0.057910);
  concreteMat->AddElement(Fe,0.013780);

  //Organic Glass
  G4double OGlassDensity = 1.07*g/cm3; //real density is 1.07
  OGlassMat = new G4Material("OGS",OGlassDensity,3);

  OGlassMat->AddElement(H,0.0637149);
  OGlassMat->AddElement(C,0.891306);
  OGlassMat->AddElement(Si,0.0449787); 
  //Above is below values converted to mass weight, Note to confirm these (Confirmation is done)

  //Scintillation stuff begins, start will Lxe values since its the example
  OGSenergy = {2.80*eV, 2.85*eV, 2.90*eV};
  OGSrindex = {1.59, 1.57, 1.54};
  OGSabsorption = {100.*cm, 100.*cm, 100.*cm};
  OGSscint = {0.1, 1.0, 0.1};
  OGSScatLength = {100.*mm,100.*mm, 100.*mm};  // placeholder from Awilhelm NoWash

  OGS_MPT = new G4MaterialPropertiesTable();
  OGS_MPT->AddConstProperty("SCINTILLATIONYIELD", 5000./MeV);
  //OGS_MPT->AddConstProperty("SCINTILLATIONYIELD", 15800./MeV); //Table 6: https://www.sciencedirect.com/science/article/pii/S0168900221007634
  OGS_MPT->AddProperty("SCINTILLATIONCOMPONENT1", OGSenergy, OGSscint);
  OGS_MPT->AddProperty("SCINTILLATIONCOMPONENT2", OGSenergy, OGSscint);
  OGS_MPT->AddProperty("RINDEX", OGSenergy, OGSrindex);
  OGS_MPT->AddProperty("ABSLENGTH", OGSenergy, OGSabsorption);
  OGS_MPT->AddProperty("RAYLEIGH",OGSenergy,OGSScatLength);
  OGS_MPT->AddConstProperty("RESOLUTIONSCALE", 1.0);
  OGS_MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 20.*ns);
  OGS_MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 45.*ns);
  OGS_MPT->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
  OGS_MPT->AddConstProperty("SCINTILLATIONYIELD2", 0.0);
  //OGlassMat->SetMaterialPropertiesTable(OGS_MPT);


//Make Optical photons travel in air test

  AlwaysScatLength = {0.001*mm,0.001*mm, 0.001*mm};

  AIR_MPT = new G4MaterialPropertiesTable();
  AIR_MPT->AddProperty("RINDEX", OGSenergy, {1.59, 1.57, 1.54});
  //AIR_MPT->AddProperty("RAYLEIGH",OGSenergy,AlwaysScatLength);
  airMat->SetMaterialPropertiesTable(AIR_MPT);


  // OGlassMat->AddElement(H,0.456004428);
  // OGlassMat->AddElement(C,0.531586318);
  // OGlassMat->AddElement(Si,0.011496792); 
  //These are wrong! in atom weights! needs to be in mass weights! Fixed, this is here as a legacy
}