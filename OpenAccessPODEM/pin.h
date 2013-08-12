//
//  gate.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/19.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef OpenAccessPODEM_gate_h
#define OpenAccessPODEM_gate_h
#include "typemu.h"
using namespace std;
#include <vector>

class PIN {
private:
    string Name;
    VALUE Value;
    GATEFUNC Func;
    string LogicFunction;
    vector<PIN*> InputList;
    vector<PIN*> OutputList;
    
    PIN(string n):Name(n),Value(X),Func(G_UNKNOWN){}
public:
    
    PIN* CreatePin(string n){
        PIN* pin=new PIN(n);
        return pin;
    }
    
    void SetFunc(GATEFUNC f) {Func=f;}
    void SetLogicFunc(string str){LogicFunction=str;}
};

#endif
