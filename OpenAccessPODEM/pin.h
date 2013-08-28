//
//  pin.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/19.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef OpenAccessPODEM_pin_h
#define OpenAccessPODEM_pin_h
#include "typemu.h"
#include "OA_Design.h"
using namespace std;
class LIBRARY;

class PIN {
private:
    string Name;
    VALUE Value;
    GATEFUNC Func;
    string LogicFunction;
    vector<PIN*> InputList;
    vector<PIN*> OutputList;
    int Level;
    unsigned Count;
    
    PIN(string n):Name(n),Value(X),Func(G_UNKNOWN),Level(-1),Count(0){}
public:
    
    PIN* CreatePin(string n){
        PIN* pin=new PIN(n);
        return pin;
    }
    
    void SetFunc(GATEFUNC f) {Func=f;}
    GATEFUNC GetFunc(){return Func;}
    void SetLogicFunc(string str){LogicFunction=str;}
    string GetName(){return Name;}
    string GetLogicFunc(){return LogicFunction;}
    
    void AddInput(PIN* ptr){InputList.push_back(ptr);}
    void AddOutput(PIN* ptr){OutputList.push_back(ptr);}
    
    unsigned No_Fanin(){return (unsigned)InputList.size();}
    unsigned No_Fanout(){return (unsigned)OutputList.size();}
    PIN* Fanin(unsigned n){return InputList[n];}
    PIN* Fanout(unsigned n){return OutputList[n];}
    
    bool IsPrimaryInOut(){return Func==G_PI||Func==G_PO;}
    
    int GetLevel(){return Level;}
    void SetLevel(int n){Level=n;}
    
    void IncCount(){Count++;}
    void DecCount(){Count--;}
    void ResetCount(){Count=0;}
    unsigned GetCount(){return Count;}
    
};
typedef PIN std_PIN;

#endif
