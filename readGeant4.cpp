//g++ readGeant4.cpp `root-config --cflags --libs` -o readGeant4.exe
///mnt/c/Users/colto/Research/GradSchool/EJ315/build/out_1E9.root

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <utility>
#include <iomanip>
#include <omp.h>
#include <ctime>

#include "TApplication.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH2.h"
#include "TH1.h"
#include "TCutG.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TString.h"

using namespace std;

TH1F* readGeant4Data(string filename);

int main(int argc, char** argv){

    TH1F* simulationSpectrum = readGeant4Data(argv[1]);
    TApplication* app1 = new TApplication("app1",&argc,argv);

    TCanvas* c1 = new TCanvas();
    simulationSpectrum->Draw();

    app1->Run();

    return 0;

}

TH1F* readGeant4Data(string filename){

    TFile* data = new TFile((TString)filename);
    TTree* dataTree;
    data->GetObject("t1",dataTree);

    int eventID;
    int stepID;
    double eDep;
    double x;
    double y;
    double z;
    double KE;
    int parentID;
    int trackID;
    int pdg;
    int intVol;

    TH1F* simulationSpectrum = new TH1F("simulationSpectrum",";Energy Deposited [MeV];Flux",3000,0,12);

    dataTree->SetBranchAddress("eventID", &eventID);
    dataTree->SetBranchAddress("stepID", &stepID);
    dataTree->SetBranchAddress("edep", &eDep);
    dataTree->SetBranchAddress("x", &x);
    dataTree->SetBranchAddress("y", &y);
    dataTree->SetBranchAddress("z", &z);
    dataTree->SetBranchAddress("kE", &KE);
    dataTree->SetBranchAddress("parentID", &parentID);
    dataTree->SetBranchAddress("trackID", &trackID);
    dataTree->SetBranchAddress("pdgNum", &pdg);
    dataTree->SetBranchAddress("intVolName", &intVol);

    double totalEDep = 0;
    int previousEventID = 0;

    for(int i=0; i<dataTree->GetEntries(); i++){
        dataTree->GetEntry(i);

        if(eventID%1000000==0){
            cout<<eventID<<endl;
        }

        if(eventID!=previousEventID){
            if(totalEDep>0){
                simulationSpectrum->Fill(totalEDep);
            }


            totalEDep = 0;
            previousEventID = eventID;
        }

        if(pdg==11 && intVol==300){
            totalEDep+=eDep;
        }
    }

    TFile* geant4SimFile = new TFile((TString)"geant4Histo.root","recreate");
    simulationSpectrum->Write();
    geant4SimFile->Close();

    return simulationSpectrum;

}