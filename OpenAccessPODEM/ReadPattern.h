//
//  ReadPattern.h
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/8/23.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef __OpenAccessPODEM__ReadPattern__
#define __OpenAccessPODEM__ReadPattern__

#include "module.h"
#include <fstream>

struct ScanChain {
    string Name;
    vector<pair<PIN*, PIN*> > SeqPairlist;
    
    ScanChain(string n):Name(n){}
};

class PATTERN {
    private:
        ifstream patterninput;
        vector<pair<PIN*, PIN*> > SequentialList; //when clock trigger,load data from first to second (PPO,PPI)
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
    
        void Initialize(MODULE*);
    
        void AddSeqPair(pair<PIN*, PIN*> seq_pair){
            SequentialList.push_back(seq_pair);
        }
};

#endif /* defined(__OpenAccessPODEM__ReadPattern__) */
