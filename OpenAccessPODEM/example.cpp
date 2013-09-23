//
//  example.cpp
//  OpenAccessPODEM
//
//  Created by lin shih-feng on 13/9/21.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include <iostream>
#include "GetLongOpt.h"
#include "design.h"
#include "library.h"
#include "ReadPattern.h"
extern GetLongOpt option;
extern LIBRARY Library;
extern DESIGN Design;
extern PATTERN Pattern;

extern vector<string> ConfigFileParser(string FileName);
extern void FirstCircuitParser(vector<string> OA_DesignParameter);
extern void FirstLibraryParser(vector<string> LibraryPathVector);
extern void CreateConfigFile();
extern void SecondCircuitParser(LIBRARY &lib);
extern void FirstLibraryParser();  //example:s27 use

int Example_main_s27()
{
    vector<string> OA_DesignParameter;
    
    OA_DesignParameter={"./designLib","designLib","s27","layout","./l90sprvt_typ.lib"};
    FirstCircuitParser(OA_DesignParameter);
    FirstLibraryParser();
    SecondCircuitParser(Library);
    
    Design.Levelize();
    Design.Check_Levelization();
    Design.InitializeQueue();
    
    if (option.retrieve("logicsim")) {
        Design.InitPattern("");
        Design.LogicSimVectors();
    }
    cout<<"end of program"<<endl;
    return 0;
}