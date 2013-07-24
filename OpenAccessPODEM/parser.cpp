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
        if (num==4) {
            break;
        }
    }
    if (OA_DesignParameter.size()!=4) {
        cout<<"check config file format."<<endl;
        exit(-1);
    }
    return OA_DesignParameter;
}


void FirstCircuitParser(vector<string> OA_DesignParameter) {
    OA_openDesign oa_design=oa_design.getDesign(OA_DesignParameter[0], OA_DesignParameter[1], OA_DesignParameter[2], OA_DesignParameter[3]);
    OA_DESIGN* design=oa_design.getDesignStructure();
    
}