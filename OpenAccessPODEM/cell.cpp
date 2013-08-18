//
//  cell.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/8/18.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "cell.h"
#include <iostream>

void AnalyizeLogicFunction(string &func);
void CELL::CloneCell(OA_CELL* oa_cell_ptr,map<string, PIN*> &NameToPinMap,CELL* std_cell_ptr) {
    Std_Name=oa_cell_ptr->Std_Name;
    for (unsigned i=0; i<oa_cell_ptr->NetList.size(); i++) {
        AddPin(NameToPinMap[oa_cell_ptr->NetList[i].second]);
        if (std_cell_ptr->IsPIPin(oa_cell_ptr->NetList[i].first)) {
            AddPIPin(NameToPinMap[oa_cell_ptr->NetList[i].second]);
        }
        else {
            AddPOPin(NameToPinMap[oa_cell_ptr->NetList[i].second]);
            PIN* pin=NameToPinMap[oa_cell_ptr->NetList[i].second];
            string LogicFunction=std_cell_ptr->GetPin(oa_cell_ptr->NetList[i].first)->GetLogicFunc();
            AnalyizeLogicFunction(LogicFunction);
            for (unsigned j=0; j<oa_cell_ptr->NetList.size(); j++) {
                string::size_type idx;
                if ((idx=LogicFunction.find('@'+oa_cell_ptr->NetList[j].first))!=string::npos) {
                    LogicFunction.replace(idx, oa_cell_ptr->NetList[j].first.size()+1, oa_cell_ptr->NetList[j].second);
                }
            }
            pin->SetLogicFunc(LogicFunction);
        }
    }
    for (unsigned i=0; i<OutputList.size(); i++) {
        PIN* pin=OutputList[i];
        string LogicFunction=pin->GetLogicFunc();
        AnalyizeLogicFunction(LogicFunction);
        for (unsigned j=0; j<InputList.size(); j++) {
            if (LogicFunction.find('@'+InputList[j]->GetName())!=string::npos) {
                pin->AddInput(InputList[j]);
                InputList[j]->AddOutput(pin);
            }
        }
    }
}

bool islogicchar(char c) {
    if (c=='(' || c==')' || c=='&' || c=='|' || c=='^') {
        return true;
    }
    return false;
}

void AnalyizeLogicFunction(string &func) {
    unsigned i=0;
    bool AddPrefix=true;
    while (i!=func.size()) {
        if (AddPrefix) {
            if (isalpha(func[i])) {
                func.insert(func.begin()+i, '@');
                AddPrefix=false;
            }
        }
        else {
            if (islogicchar(func[i])) {
                AddPrefix=true;
            }
        }
        i++;
    }
}

