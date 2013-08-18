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
#include <string>
#include <vector>
#include "OA_Design.h"
using namespace std;
#include <vector>
class LIBRARY;

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
    string GetName(){return Name;}
    string GetLogicFunc(){return LogicFunction;}
    
    void AddInput(PIN* ptr){InputList.push_back(ptr);}
    void AddOutput(PIN* ptr){OutputList.push_back(ptr);}
    
    unsigned No_Fanin(){return (unsigned)InputList.size();}
    unsigned No_Fanout(){return (unsigned)OutputList.size();}
    
    bool IsPrimaryInOut(){return Func==G_PI||Func==G_PO;}
};
typedef PIN std_PIN;

#endif
