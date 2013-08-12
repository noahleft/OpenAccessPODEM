//
//  library.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/19.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef OpenAccessPODEM_library_h
#define OpenAccessPODEM_library_h
#include "module.h"
typedef PIN std_PIN;
typedef CELL std_CELL;

class LIBRARY {
private:
    vector<std_CELL*> CellList;
    
public:
    LIBRARY(){}
    ~LIBRARY(){
        for (unsigned i=0; i<CellList.size(); i++) {
            delete CellList[i];
            CellList[i]=NULL;
        }
    }
    
    std_CELL* CreateStdCell(string n){
        std_CELL* cell=NULL;
        cell=cell->CreateCell(n);
        CellList.push_back(cell);
        return cell;
    }
    
};

#endif
