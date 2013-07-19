//
//  cell.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/19.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef OpenAccessPODEM_cell_h
#define OpenAccessPODEM_cell_h
#include "gate.h"
//CELL has many GATE
class CELL {
private:
    string Name;
    vector<PIN*> InputList;
    vector<PIN*> OutputList;
    vector<GATE*> GateList;
    
public:
    
};

#endif
