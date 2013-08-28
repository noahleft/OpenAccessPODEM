//
//  cell.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/19.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef OpenAccessPODEM_cell_h
#define OpenAccessPODEM_cell_h
#include "pin.h"
//CELL has many PIN
class CELL {
private:
    string Name;
    string Std_Name;
    vector<PIN*> InputList;
    vector<PIN*> OutputList;
    vector<PIN*> FFList;
    vector<PIN*> GateList;
    
    CELL(string n):Name(n){}
public:
    ~CELL(){}
    
    CELL* CreateCell(string n){
        CELL* cell=new CELL(n);
        return cell;
    }
    PIN* CreatePin(string n){
        PIN* pin=NULL;
        pin=pin->CreatePin(n);
        AddPin(pin);
        return pin;
    }
    
    void AddPin(PIN* ptr)   {GateList.push_back(ptr);}
    void AddPIPin(PIN* ptr) {InputList.push_back(ptr);}
    void AddPOPin(PIN* ptr) {OutputList.push_back(ptr);}
    void AddFFPin(PIN* ptr) {FFList.push_back(ptr);}

    void CloneCell(OA_CELL* oa_cell_ptr,map<string, PIN*> &NameToPinMap,CELL* std_cell_ptr,vector<PIN*> &FFlist);
    
    bool IsPIPin(string n){
        for (unsigned i=0; i<InputList.size(); i++) {
            if (n.compare(InputList[i]->GetName())==0) {
                return true;
            }
        }
        return false;
    }
    
    PIN* GetPin(string str){
        for (unsigned i=0; i<GateList.size(); i++) {
            if (str.compare(GateList[i]->GetName())==0) {
                return GateList[i];
            }
        }
        return NULL;
    }

    unsigned No_Internal(){return (unsigned)FFList.size();}
    unsigned No_Input(){return (unsigned)InputList.size();}
    unsigned No_Output(){return (unsigned)OutputList.size();}
    PIN* InputPin(unsigned idx){return InputList[idx];}
    PIN* OutputPin(unsigned idx){return OutputList[idx];}
    PIN* InternalPin(unsigned idx){return FFList[idx];}
    
};
typedef CELL std_CELL;

#endif
