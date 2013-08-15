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
    void CloneCell(OA_CELL* oa_cell_ptr) {
        Std_Name=oa_cell_ptr->Std_Name;
        //not finish yet   u should create pin data here
    }
};

#endif
