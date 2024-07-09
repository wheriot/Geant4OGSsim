#ifndef __EVENTACTION__
#define __EVENTACTION__

//My Libraries
#include "RunAction.hh"

//Geant4 Libraries
#include "globals.hh"
#include "G4UserEventAction.hh"

// c++ Libraries
#include <vector>

class EventAction : public G4UserEventAction{
  private:

    int eventID, stepID, trackID, pdg, parentID, intVol;
    double eDep, x, y, z, time, KE;
    double totaleDep, InitEnrg, phocollect1, phocollect2;

    std::vector<int> trackIDList = {};

  public:
    EventAction(RunAction* runAction);
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
    inline void ClearTrackSet(){trackIDList.clear();}
    inline void addToTrack(G4int trackId){trackIDList.push_back(trackId);}
    bool checkIfInTrack(G4int trackId);
    void FillMyNtuple();
    void RecordEnrg();
    void AddEnrg(double val);
    void StoreInitEnrg(double val);
    void CollectPhoton(int val);

    inline void setEventID(int val)  {eventID = val;}
    inline void setStepID(int val)   {stepID = val;}
    inline void setTrackID(int val)  {trackID = val;}
    inline void setParentID(int val) {parentID = val;}
    inline void setEDep(double val)  {eDep = val;}
    inline void setKE(double val)    {KE = val;}
    inline void setX(double val)     {x = val;}
    inline void setY(double val)     {y = val;}
    inline void setZ(double val)     {z = val;}
    inline void setPDG(int val)      {pdg = val;}
    inline void setIntVol(int val)   {intVol = val;}

};


#endif
