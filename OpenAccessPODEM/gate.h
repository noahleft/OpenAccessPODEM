//
//  gate.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/19.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef OpenAccessPODEM_gate_h
#define OpenAccessPODEM_gate_h
#include "pin.h"
#include <vector>
//GATE has a PIN. (GATE is not a PIN.)
class GATE {
private:
    PIN* Pin;
    GATEFUNC Func;
    vector<GATE*> InputList;
    vector<GATE*> OutputList;
    
public:
    
};

#endif
