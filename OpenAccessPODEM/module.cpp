//
//  module.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/8/16.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "module.h"

void MODULE::CloneModule(OA_MODULE* oa_module_ptr,map<string, PIN*> &NameToPinMap,map<string, std_CELL*> &std_CELL_map) {
    for (unsigned i=0; i<oa_module_ptr->CellList.size(); i++) {
        CELL* cell=NULL;
        cell=cell->CreateCell(oa_module_ptr->CellList[i]->Name);
        CellList.push_back(cell);
        cell->CloneCell(oa_module_ptr->CellList[i],NameToPinMap,std_CELL_map[oa_module_ptr->CellList[i]->Std_Name]);
    }
}

void MODULE::SetupNonScanFF() {
    for (unsigned i=0; i<PinList.size(); i++) {
        PIN* pin=PinList[i];
        if (!pin->IsPrimaryInOut() &&pin->No_Fanin()==0) {
            AddPPI(pin);
            pin->SetFunc(G_PPI);
        }
        if (!pin->IsPrimaryInOut() && pin->No_Fanout()==0) {
            AddPPO(pin);
            pin->SetFunc(G_PPO);
        }
    }
}
