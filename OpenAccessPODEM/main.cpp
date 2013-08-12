//
//  main.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/7/19.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include <iostream>
#include "GetLongOpt.h"
#include "design.h"
#include "library.h"

GetLongOpt option;
LIBRARY Library;

int SetupOption(int argc, char * argv[])
{
    option.usage("[options] config_file");
    option.enroll("help", GetLongOpt::NoValue,
                  "print this help summary", 0);
    option.enroll("logicsim", GetLongOpt::NoValue,
                  "run logic simulation", 0);
    option.enroll("plogicsim", GetLongOpt::NoValue,
                  "run parallel logic simulation", 0);
    option.enroll("fsim", GetLongOpt::NoValue,
                  "run stuck-at fault simulation", 0);
    //    option.enroll("stfsim", GetLongOpt::NoValue,
    //                  "run single pattern single transition-fault simulation", 0);
    //    option.enroll("transition", GetLongOpt::NoValue,
    //                  "run transition-fault ATPG", 0);
    option.enroll("input", GetLongOpt::MandatoryValue,
                  "set the input pattern file", 0);
    option.enroll("output", GetLongOpt::MandatoryValue,
                  "set the output pattern file", 0);
    option.enroll("bt", GetLongOpt::OptionalValue,
                  "set the backtrack limit", 0);
//    option.enroll("pattern", GetLongOpt::NoValue,
//                  "Random Pattern Generation", 0);
    
    int optind = option.parse(argc, argv);
    if ( optind < 1 ) { exit(0); }
    if ( option.retrieve("help") ) {
        option.usage();
        exit(0);
    }
    return optind;
}
extern vector<string> ConfigFileParser(string FileName);
extern void FirstCircuitParser(vector<string> OA_DesignParameter);
extern void FirstLibraryParser(string LibraryPath);

int main(int argc, char * argv[])
{
    int optind = SetupOption(argc, argv);
    vector<string> OA_DesignParameter;
    string LibraryPath;
    //Setup File
    if (optind < argc) {
        if (fopen(argv[optind], "r")==NULL) {
            cout << "Can't open config file: " << argv[optind] << endl;
            exit(-1);
        }
        else {
            OA_DesignParameter=ConfigFileParser(argv[optind]);
        }
    }
    else {
        cout << "config file missing" << endl;
        option.usage();
        return -1;
    }
    cout<<"Start parsing input file"<<endl;
    LibraryPath=OA_DesignParameter[4];
    FirstCircuitParser(OA_DesignParameter);
    FirstLibraryParser(LibraryPath);
    
    return 0;
}

