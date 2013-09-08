//
//  ReadPattern.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/8/23.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "ReadPattern.h"
#include "design.h"

void PATTERN::Initialize(MODULE* module) { //s27 use default order as pattern order
    for (unsigned i=0; i<module->No_PI(); i++) {
        PIlist.push_back(module->PIPin(i));
    }
    {
        ScanChain* s27_chain1=NULL;
        s27_chain1=new ScanChain("s27_chain");
        s27_chain1->SeqPairlist.push_back(SequentialList[0]);
        s27_chain1->SeqPairlist.push_back(SequentialList[1]);
        //assume seqlist[2] as non-scan ff
        ScanChainlist.push_back(s27_chain1);
    }
}