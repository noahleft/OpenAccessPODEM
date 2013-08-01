//
//  OA_Design.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/23.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef OpenAccessPODEM_OA_Design_h
#define OpenAccessPODEM_OA_Design_h
#include <string>
using namespace std;

struct OA_CELL {
    string Name;
    string Std_Name;
    bool IsModule;
    vector<pair<string, string> > NetList;
    
    OA_CELL(string n,string std_n):Name(n),Std_Name(std_n),IsModule(false){}
    ~OA_CELL(){NetList.clear();}
};

struct OA_MODULE {
    string Name;
    vector<OA_MODULE*> SubModuleList;
    vector<OA_CELL*> CellList;
    
    OA_MODULE(string n):Name(n){}
    ~OA_MODULE(){
        for (unsigned i=0; i<CellList.size(); i++) {
            delete CellList[i];
            CellList[i]=NULL;
        }
    }
};

struct OA_DESIGN {
    string Name;
    vector<OA_MODULE*> ModuleList;
    OA_MODULE* TopModule;
    
    OA_DESIGN(string n):Name(n){}
    ~OA_DESIGN(){
        for (unsigned i=0; i<ModuleList.size(); i++) {
            delete ModuleList[i];
            ModuleList[i]=NULL;
        }
    }
};

#endif
