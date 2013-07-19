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
public:
    MODULE(){}
    ~MODULE(){
        for (unsigned i=0; i<CellList.size(); i++) {
            delete CellList[i];
            CellList[i]=NULL;
        }
    }
};

#endif
