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
#include "GetLongOpt.h"
#include "design.h"
#include "OA_OpenDesign.h"
using namespace std;
extern LIBRARY Library;
extern DESIGN Design;
extern GetLongOpt option;

void CreateConfigFile() {
	fstream outfile;
	if (option.retrieve("output"))
	{
		outfile.open(option.retrieve("output"),ios::out);
	}
	else {
		outfile.open("config",ios::out);
	}
	outfile<<"#open s27 at designLib"<<endl;
	outfile<<"./designLib"<<endl;
	outfile<<"designLib"<<endl;
	outfile<<"s27"<<endl;
	outfile<<"layout"<<endl;
	outfile<<"#foundry library path"<<endl;
	outfile<<"./l90sprvt_typ.lib"<<endl;
}

vector<string> ConfigFileParser(string FileName) {
    vector<string> OA_DesignParameter;
    fstream infile(FileName.c_str(),ios::in);
    
    string str;
    unsigned num=0;
    while (!infile.eof()) {
        getline(infile, str);

		if (str.length()==0)
		{
			continue;
		}

        if (str[0]=='#') {
            continue;
        }
        OA_DesignParameter.push_back(str);
        num++;
    }
    return OA_DesignParameter;
}

map<string, std_CELL*> std_CELL_Map;
OA_openDesign oa_design;
void FirstCircuitParser(vector<string> OA_DesignParameter) {
    oa_design.getDesign(OA_DesignParameter[0], OA_DesignParameter[1], OA_DesignParameter[2], OA_DesignParameter[3]);
    OA_DESIGN* design=oa_design.getDesignStructure();
    OA_MODULE* top_module=design->TopModule;
    
    for (unsigned i=0; i<top_module->CellList.size(); i++) {
        std_CELL_Map[top_module->CellList[i]->Std_Name]=NULL;
    }
}

void GetNextLine(fstream &infile,string &str,unsigned &BracesLevel);
void LibraryParser(string LibraryPath);
void FirstLibraryParser(vector<string> LibraryPathVector) {
    for (unsigned i=0; i<LibraryPathVector.size(); i++) {
        LibraryParser(LibraryPathVector[i]);
    }
}

void LibraryParser(string LibraryPath) {
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
        
        GetNextLine(infile, str, BracesLevel);
        
        if (BracesLevel==3 && (pos=str.find("cell("))!=string::npos) { //"cell" define detected
            str=str.substr(pos+5);
            pos=str.find(')');
            str=str.substr(0,pos);
            if (std_CELL_Map.find(str)!=std_CELL_Map.end() && std_CELL_Map[str]==NULL) { //this cell is used in design
                //cout<<str<<endl;
                std_CELL* cell=Library.CreateStdCell(str);
                std_CELL_Map[str]=cell;
                
                while (!infile.eof()) {
                    GetNextLine(infile, str,BracesLevel);
                    
                    if (BracesLevel==4 && (pos=str.find("pin("))!=string::npos) { //"pin" define detected
                        str=str.substr(pos+4);
                        pos=str.find(')');
                        str=str.substr(0,pos);
                        //cout<<str<<endl;
                        std_PIN* pin=NULL;
                        pin=cell->CreatePin(str);
                        Library.AddPin(pin);
                        
                        while (!infile.eof()) {
                            
                            GetNextLine(infile, str, BracesLevel);
                            
                            if ((pos=str.find("direction"))!=string::npos) {
                                str=str.substr(pos+9);
                                pos=str.find(';');
                                str=str.substr(0,pos);
                                pos=str.find(':');
                                str=str.substr(pos+1);
                                //cout<<str<<endl;
                                
                                if (str.find("input")!=string::npos) {
                                    pin->SetFunc(G_PI);
                                    cell->AddPIPin(pin);
                                }
                                else if (str.find("output")!=string::npos) {
                                    pin->SetFunc(G_PO);
                                    cell->AddPOPin(pin);
                                }
                                else {
                                    cout<<str<<endl;
                                }
                            }
                            else if ((pos=str.find("function"))!=string::npos) {
                                str=str.substr(pos+9);
                                pos=str.find(';');
                                str=str.substr(0,pos);
                                pos=str.find(':');
                                str=str.substr(pos+1);
                                //cout<<str<<endl;
                                
                                pos=str.find('"');
                                str=str.substr(pos+1);
                                pos=str.find('"');
                                str=str.substr(0,pos);
                                pin->SetLogicFunc(str);
                            }
                            else if (BracesLevel<4) break;
                            
                        }
                    }
                    else if (BracesLevel<3) break; //break "cell" define
                }
                
            }
        }
        else if (BracesLevel==0) {
            cout<<"Mismatch on Braces. {}"<<endl;
            exit(-1);
        }
    }
    
    infile.close();
}

void CheckBracesLevel(string str,unsigned &level);
void GetNextLine(fstream &infile,string &next_line,unsigned &BracesLevel) {
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
    
    CheckBracesLevel(str, BracesLevel);
}

void CheckBracesLevel(string str,unsigned &level) {
    if (str.find('{')!=string::npos) {
        level++;
    }
    if (str.find('}')!=string::npos) {
        level--;
    }

}


void SecondCircuitParser(LIBRARY &lib) {
	OA_DESIGN* design=oa_design.getDesignStructure();
    OA_MODULE* top_module=design->TopModule;
    map<string, PIN*> NameToPinMap;
    for (unsigned i=0; i<top_module->CellList.size(); i++) {
        OA_CELL* oa_cell=top_module->CellList[i];
        for (unsigned j=0; j<oa_cell->NetList.size(); j++) {
            NameToPinMap[oa_cell->NetList[j].second]=NULL;
        }
    }
    
    //clone
    Design.CloneDesign(design,NameToPinMap,std_CELL_Map);
    Design.SetupNonScanFF();
    
    
    
}