//
//  module.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/19.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef OpenAccessPODEM_module_h
#define OpenAccessPODEM_module_h
#include "cell.h"

class MODULE {
private:
    string Name;
    vector<CELL*> CellList; //this can be treat as std cell list
    vector<PIN*> PinList;
    
    vector<PIN*> PIlist;
    vector<PIN*> POlist;
    vector<PIN*> PPIlist;
    vector<PIN*> PPOlist;
    
    list<PIN*>* Queue;
    unsigned MaxLevel;
    
public:
    MODULE(string n):Name(n),MaxLevel(0){}
    ~MODULE(){
        for (unsigned i=0; i<PinList.size(); i++) {
            delete PinList[i];
            PinList[i]=NULL;
        }
        for (unsigned i=0; i<CellList.size(); i++) {
            delete CellList[i];
            CellList[i]=NULL;
        }
    }
    
    MODULE* CreateModule(OA_MODULE* oa_module_ptr){return new MODULE(oa_module_ptr->Name);}
    void CloneModule(OA_MODULE* oa_module_ptr,map<string, PIN*> &NameToPinMap,map<string, std_CELL*> &std_CELL_map);
    
    void CreatePin(map<string, PIN*> &NameToPinMap) {
        map<string, PIN*>::iterator it;
        for (it=NameToPinMap.begin(); it!=NameToPinMap.end(); it++) {
            it->second=it->second->CreatePin(it->first);
            PinList.push_back(it->second);
        }
    }
    
    void AddPI(PIN* ptr){PIlist.push_back(ptr);}
    void AddPO(PIN* ptr){POlist.push_back(ptr);}
    void AddPPI(PIN* ptr){PPIlist.push_back(ptr);}
    void AddPPO(PIN* ptr){PPOlist.push_back(ptr);}
    
    void Levelize();
    void Check_Levelization();
    
    unsigned No_Pin(){return (unsigned)PinList.size();}
    unsigned No_PI(){return (unsigned)PIlist.size();}
    unsigned No_PO(){return (unsigned)POlist.size();}
    unsigned No_PPI(){return (unsigned)PPIlist.size();}
    unsigned No_PPO(){return (unsigned)PPOlist.size();}
    
    PIN* PIPin(unsigned idx){return PIlist[idx];}
    PIN* POPin(unsigned idx){return POlist[idx];}
    PIN* Pin(unsigned idx){return PinList[idx];}
    
    void Schedule(PIN* gptr)
    {
        Queue[gptr->GetLevel()].push_back(gptr);
    }
    void InitializeQueue();
    void SetMaxLevel();
    //
    void LogicSimVectors();
    void LogicSim();
    void SchedulePI();
    void PrintIO();
    void ScheduleFanout(PIN*);
    VALUE Evaluate(PIN*);
    //
};

#endif
