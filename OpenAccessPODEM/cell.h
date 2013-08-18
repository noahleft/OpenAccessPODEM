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
//CELL has many GATE
class CELL {
private:
    string Name;
    string Std_Name;
    vector<PIN*> InputList;
    vector<PIN*> OutputList;
    vector<PIN*> GateList;
    
    CELL(string n):Name(n){}
public:
    
    ~CELL() {}
    
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
    
    void AddPin(PIN* ptr) {
        GateList.push_back(ptr);
    }
    void AddPIPin(PIN* ptr) {
        InputList.push_back(ptr);
    }
    void AddPOPin(PIN* ptr) {
        OutputList.push_back(ptr);
    }
    void CloneCell(OA_CELL* oa_cell_ptr,map<string, PIN*> &NameToPinMap,CELL* std_cell_ptr);
    
    
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
    
};
typedef CELL std_CELL;

#endif
