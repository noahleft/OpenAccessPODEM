//
//  module.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/8/16.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "module.h"

void MODULE::CloneModule(OA_MODULE* oa_module_ptr) {
    for (unsigned i=0; i<oa_module_ptr->CellList.size(); i++) {
        CELL* cell=NULL;
        cell=cell->CreateCell(oa_module_ptr->CellList[i]->Name);
        CellList.push_back(cell);
        cell->CloneCell(oa_module_ptr->CellList[i]);
    }
}