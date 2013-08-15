//
//  design.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/8/16.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "design.h"

void DESIGN::CloneDesign(OA_DESIGN* oa_design_ptr) {
    Name=oa_design_ptr->Name;
    TopModule=TopModule->CreateModule(oa_design_ptr->TopModule);
    TopModule->CloneModule(oa_design_ptr->TopModule);
}
