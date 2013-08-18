//
//  design.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/8/16.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "design.h"

void DESIGN::CloneDesign(OA_DESIGN* oa_design_ptr,map<string, PIN*> &NameToPinMap,map<string, std_CELL*> &std_CELL_Map) {
    Name=oa_design_ptr->Name;
    TopModule=TopModule->CreateModule(oa_design_ptr->TopModule);
    TopModule->CreatePin(NameToPinMap);
    TopModule->CloneModule(oa_design_ptr->TopModule,NameToPinMap,std_CELL_Map);
    for (unsigned i=0; i<oa_design_ptr->TopModule->InputList.size(); i++) {
        if (NameToPinMap.find(oa_design_ptr->TopModule->InputList[i])!=NameToPinMap.end()) {
            TopModule->AddPI(NameToPinMap[oa_design_ptr->TopModule->InputList[i]]);
            NameToPinMap[oa_design_ptr->TopModule->InputList[i]]->SetFunc(G_PI);
        }
    }
    for (unsigned i=0; i<oa_design_ptr->TopModule->OutputList.size(); i++) {
        if (NameToPinMap.find(oa_design_ptr->TopModule->OutputList[i])!=NameToPinMap.end()) {
            TopModule->AddPO(NameToPinMap[oa_design_ptr->TopModule->OutputList[i]]);
            NameToPinMap[oa_design_ptr->TopModule->OutputList[i]]->SetFunc(G_PO);
        }
    }
}

void DESIGN::SetupNonScanFF() {
    TopModule->SetupNonScanFF();
}
