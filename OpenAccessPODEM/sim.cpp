//
//  sim.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/9/23.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "design.h"
#include <iostream>
extern PATTERN Pattern;
void MODULE::LogicSimVectors() {
    cout<<"Run logic simulation"<<endl;
    //read test pattern
    while (!Pattern.eof()) {
        Pattern.ReadNextPattern();
        SchedulePI();
        LogicSim();
        PrintIO();
        break;
    }
}

void PATTERN::ReadNextPattern() {
    for (unsigned i=0; i<PIlist.size(); i++) {
        PIlist[i]->SetValue(S0);
    }
}

void MODULE::LogicSim() {
    PIN* gptr;
    VALUE new_value;
    for (unsigned i=0; i<=MaxLevel; i++) {
        while (!Queue[i].empty()) {
            gptr=Queue[i].front();
            Queue[i].pop_front();
            new_value = Evaluate(gptr);
            gptr->SetValue(new_value);
            ScheduleFanout(gptr);
        }
    }
}

//Used only in the first pattern
void MODULE::SchedulePI()
{
    for (unsigned i = 0;i < No_PI();i++) {
        ScheduleFanout(PIPin(i));
    }
    return;
}

//schedule all fanouts of gate to Queue
void MODULE::ScheduleFanout(PIN* gptr)
{
    for (unsigned j = 0;j < gptr->No_Fanout();j++) {
        Schedule(gptr->Fanout(j));
    }
    return;
}

VALUE MODULE::Evaluate(PIN* gptr) {
    return S0;
}

void MODULE::PrintIO() {
    for (unsigned i=0; i<No_PI(); i++) {
        cout<<PIPin(i)->GetValue();
    }
    cout<<" ";
    for (unsigned i=0; i<No_PO(); i++) {
        cout<<POPin(i)->GetValue();
    }
    cout<<endl;
}
