//
//  design.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/19.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef OpenAccessPODEM_design_h
#define OpenAccessPODEM_design_h
#include "library.h"

class DESIGN {
private:
    string Name;
    MODULE* TopModule;
public:
    DESIGN():TopModule(NULL){}
    ~DESIGN(){
        delete TopModule;
    }
    void CloneDesign(OA_DESIGN* oa_design_ptr,map<string, PIN*> &NameToPinMap,map<string, std_CELL*> &std_CELL_map);
    void SetupNonScanFF();
    void Levelize();
};

#endif
