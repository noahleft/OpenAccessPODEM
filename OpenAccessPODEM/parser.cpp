//
//  parser.c
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/19.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "design.h"
#include "OA_OpenDesign.h"
using namespace std;


vector<string> ConfigFileParser(string FileName) {
    vector<string> OA_DesignParameter;
    fstream infile(FileName.c_str(),ios::in);
    
    string str;
    unsigned num=0;
    while (!infile.eof()) {
        getline(infile, str);
        if (str[0]=='#') {
            continue;
        }
        OA_DesignParameter.push_back(str);
        num++;
        if (num==5) {
            break;
        }
    }
    if (OA_DesignParameter.size()!=5) {
        cout<<"check config file format."<<endl;
        exit(-1);
    }
    return OA_DesignParameter;
}

map<string, std_CELL*> std_CELL_Map;

void FirstCircuitParser(vector<string> OA_DesignParameter) {
    OA_openDesign oa_design=oa_design.getDesign(OA_DesignParameter[0], OA_DesignParameter[1], OA_DesignParameter[2], OA_DesignParameter[3]);
    OA_DESIGN* design=oa_design.getDesignStructure();
    OA_MODULE* top_module=design->TopModule;
    
    for (unsigned i=0; i<top_module->CellList.size(); i++) {
        std_CELL_Map[top_module->CellList[i]->Std_Name]=NULL;
    }
    
}

void GetNextLine(fstream &infile,string &str);
void CheckBracesLevel(string str,unsigned &level);
void FirstLibraryParser(string LibraryPath) {
    if (fopen(LibraryPath.c_str(), "r")==NULL) {
        cout << "Can't open library file: " << LibraryPath << endl;
        exit(-1);
    }
    fstream infile(LibraryPath.c_str(),ios::in);
    //programmer have to check std_CELL_Map defined
    string str;
    string::size_type pos;
    unsigned BracesLevel=1;
    while (!infile.eof()) {
        
        GetNextLine(infile, str);
        CheckBracesLevel(str, BracesLevel);
        
        if (BracesLevel==3 && (pos=str.find("cell("))!=string::npos) {
            str=str.substr(pos+5);
            pos=str.find(')');
            str=str.substr(0,pos);
            if (std_CELL_Map.find(str)!=std_CELL_Map.end()) {
                cout<<str<<endl;
                
                
                
            }
        }
        else if (BracesLevel==0) {
            cout<<"Mismatch on Braces. {}"<<endl;
            exit(-1);
        }
    }
    
    
    
    
    infile.close();
}

void GetNextLine(fstream &infile,string &next_line) {
    next_line.clear();
    
    string str;
    while (!infile.eof()) {
        getline(infile, str);
        next_line+=str;
        if (str.find(';')!=string::npos) {
            break;
        }
        if (str.find('{')!=string::npos) {
            break;
        }
        if (str.find('}')!=string::npos) {
            break;
        }
    }
    
}

void CheckBracesLevel(string str,unsigned &level) {
    if (str.find('{')!=string::npos) {
        level++;
    }
    if (str.find('}')!=string::npos) {
        level--;
    }
}