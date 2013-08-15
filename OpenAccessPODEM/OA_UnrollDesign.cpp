//
//  OA_UnrollDesign.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/8/6.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "OA_OpenDesign.h"
#include <iostream>

void OA_openDesign::getDesign(string libPath,string library,string cellName,string ViewName){
    loadDesign(libPath,library,cellName,ViewName);
    constructDesign();
    unrollingDesign();
}


OA_openDesign::~OA_openDesign(){
    delete m_designStructure;
    m_designStructure=NULL;
}


vector<OA_CELL*> unrollModule(OA_CELL* mapping_cell,OA_MODULE* mapped_module);

OA_MODULE* NameToModule(string Name,vector<OA_MODULE*> ModuleList) {
    for (unsigned i=0; i<ModuleList.size(); i++) {
        if (ModuleList[i]->Name.compare(Name)==0) {
            return ModuleList[i];
        }
    }
    cout<<"NameToModule fail"<<endl;
    exit(-1);
}

string MappingName(string Name,OA_CELL* cell) {
    for (unsigned i=0; i<cell->NetList.size(); i++) {
        if (Name.compare(cell->NetList[i].first)==0) {
            return cell->NetList[i].second;
        }
    }
    return cell->Name+"."+Name;
}

void OA_openDesign::unrollingDesign() {
    OA_MODULE *TopModule=m_designStructure->TopModule;
    unsigned idx=0;
    while (idx < TopModule->CellList.size()) {
        OA_CELL* cell=TopModule->CellList[idx];
        if (cell->IsModule) {  //unrolling needed
            OA_MODULE* mapped_module=NameToModule(cell->Std_Name,TopModule->SubModuleList);
            vector<OA_CELL*> unrollCellList=unrollModule(cell, mapped_module);
            {
                OA_CELL* delete_cell=TopModule->CellList[idx];
                delete delete_cell;
                TopModule->CellList[idx]=NULL;
                TopModule->CellList.erase(TopModule->CellList.begin()+idx);
            }
            TopModule->CellList.insert(TopModule->CellList.begin()+idx, unrollCellList.begin(), unrollCellList.end());
        }
        else {
            idx++;
        }
    }
}

vector<OA_CELL*> unrollModule(OA_CELL* cell,OA_MODULE* module) {
    vector<OA_CELL*> unrollCellList;
    for (unsigned i=0; i<module->CellList.size(); i++) {
        OA_CELL* template_cell=module->CellList[i];
        OA_CELL* clone_cell=new OA_CELL(cell->Name+"."+template_cell->Name,"LSDFQM2N");
        clone_cell->IsModule=template_cell->IsModule;
        unrollCellList.push_back(clone_cell);
        for (unsigned j=0; j<template_cell->NetList.size(); j++) {
            string Std_Pin_Name=template_cell->NetList[j].first;
            string Mapping_Name=template_cell->NetList[j].second;
            string Mapped_Name=MappingName(Mapping_Name, cell);
            clone_cell->NetList.push_back(pair<string,string>(Std_Pin_Name,Mapped_Name));
        }
    }
    return unrollCellList;
}