//
//  ReadPattern.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/8/23.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef __OpenAccessPODEM__ReadPattern__
#define __OpenAccessPODEM__ReadPattern__

#include "pin.h"
#include <fstream>

struct ScanChain {
    string Name;
    vector<PIN*> pinlist;
};

class PATTERN {
    private:
        ifstream patterninput;
        vector<pair<PIN*, PIN*> > SequentialList; //when clock trigger,load data from first to second
        vector<PIN*> PIlist;
        vector<ScanChain*> ScanChainlist;
    public:
        PATTERN(){}
        ~PATTERN(){
            for (unsigned i=0; i<ScanChainlist.size(); i++) {
                delete ScanChainlist[i];
                ScanChainlist[i]=NULL;
            }
        }
    
};

#endif /* defined(__OpenAccessPODEM__ReadPattern__) */
