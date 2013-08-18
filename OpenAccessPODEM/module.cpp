//
//  module.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/8/16.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "module.h"
#include <list>
#include <iostream>
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

void MODULE::Levelize() {
    list<PIN*> Queue;
    PIN* gptr;
    PIN* out;
    for (unsigned i=0; i<PIlist.size(); i++) {
        gptr=PIlist[i];
        gptr->SetLevel(0);
        for (unsigned j=0; j<gptr->No_Fanout(); j++) {
            out=gptr->Fanout(j);
            out->IncCount();
            if (out->GetCount()==out->No_Fanin()) {
                out->SetLevel(1);
                Queue.push_back(out);
            }
        }
    }
    for (unsigned i=0; i<PPIlist.size(); i++) {
        gptr=PPIlist[i];
        gptr->SetLevel(0);
        for (unsigned j=0; j<gptr->No_Fanout(); j++) {
            out=gptr->Fanout(j);
            out->IncCount();
            if (out->GetCount()==out->No_Fanin()) {
                out->SetLevel(1);
                Queue.push_back(out);
            }
        }
    }
    int l1,l2;
    while (!Queue.empty()) {
        gptr = Queue.front();
        Queue.pop_front();
        l1=gptr->GetLevel();
        for (unsigned j=0; j<gptr->No_Fanout(); j++) {
            out=gptr->Fanout(j);
            l2=out->GetLevel();
            if (l2<=l1) {
                out->SetLevel(l1+1);
            }
            out->IncCount();
            if (out->GetCount()==out->No_Fanin()) {
                Queue.push_back(out);
            }
        }
    }
    for (unsigned i=0; i<PinList.size(); i++) {
        PinList[i]->ResetCount();
    }
}

void MODULE::Check_Levelization() {
    PIN* gptr;
    PIN* in;
    for (unsigned i=0; i<PinList.size(); i++) {
        gptr=PinList[i];
        if (gptr->GetFunc()==G_PI) {
            if (gptr->GetLevel()!=0) {
                cout<<"Wrong level at PI:"<<gptr->GetName()<<endl;
                exit(-1);
            }
        }
        else if (gptr->GetFunc()==G_PPI) {
            if (gptr->GetLevel()!=0) {
                cout<<"Wrong level at PPI:"<<gptr->GetName()<<endl;
                exit(-1);
            }
        }
        else {
            for (unsigned j=0; j<gptr->No_Fanin(); j++) {
                in=gptr->Fanin(j);
                if (in==NULL) {
                    continue;
                }
                if (in->GetLevel() >= gptr->GetLevel()) {
                    cout<<"Wrong level at:"<<gptr->GetName()<<'\t'<<gptr->GetLevel()<<
                    " with its fanin "<<in->GetName()<<'\t'<<in->GetLevel()<<endl;
                }
            }
        }
    }
}

