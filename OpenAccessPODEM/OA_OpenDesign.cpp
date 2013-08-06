#include "OA_OpenDesign.h"
#include <iostream>
OA_openDesign OA_openDesign::getDesign(string libPath,string library,string cellName,string ViewName){
    OA_openDesign design;
    design.loadDesign(libPath,library,cellName,ViewName);
    return design;
}


oaNativeNS ns;

void OA_openDesign::loadDesign(string libPath,string library,string cellName,string ViewName){

//    try {
//      oaDesignInit(oacAPIMajorRevNumber, oacAPIMinorRevNumber, 4);
//
//      oaString oa_libPath(libPath.c_str());
//      oaString oa_library(library.c_str());
//      oaString oa_cell(cellName.c_str());
//      oaString oa_view(ViewName.c_str());
//
//      oaScalarName oa_libName (ns,oa_library);
//      oaScalarName oa_cellName(ns,oa_cell);
//      oaScalarName oa_viewName(ns,oa_view);
//
//      // Setup an instance of the oaTech conflict observer.
//      opnTechConflictObserver myTechConflictObserver(1);
//      // Setup an instance of the oaLibDefList observer.
//      opnLibDefListObserver   myLibDefListObserver(1);
//      // Read in the lib.defs file.
//      oaLibDefList::openLibs();
//      // Try to get a pointer to the library. If it does not exist yet,
//      // it will be created and added to the lib.defs file.
//      m_library = openLibrary(oa_libName, oa_libPath);
//      // Create the design with the specified viewType,
//      // Opening it for a 'write' operation.
//      cout << "The design "<<cellName<<" is created and opened in 'read' mode." << endl;
//      m_design = oaDesign::open(oa_libName, oa_cellName, oa_viewName, 'r');
//    }
//    catch (oaCompatibilityError &ex) {
//      handleFBCError(ex);
//      exit(1);
//    }
//    catch (oaException &excp) {
//      cout << "ERROR: "<< excp.getMsg() <<endl;
//      exit(1);
//    }
    constructDesign();
}

void OA_openDesign::dumpModule(){
/*    oaModule *module = m_design->getTopModule();
    oaString stringBuf;
    module->getName(ns,stringBuf);
    cout<<stringBuf<<endl;
    cout<<"Print sub module header"<<endl;
    oaIter<oaModModuleInstHeader> mHeaderIter(module->getModuleInstHeaders());
    while(oaModModuleInstHeader *mHeaderPtr = mHeaderIter.getNext()){
        mHeaderPtr->getName(ns,stringBuf);
        cout<<stringBuf<<endl;
    }
    cout<<"Print Module Instant"<<endl;
    oaIter<oaModInst> mInstIter(module->getInsts());
    while(oaModInst *mInstPtr = mInstIter.getNext()){
        mInstPtr->getName(ns,stringBuf);
        cout<<stringBuf<<endl;
        oaModule* tmpModule=mInstPtr->getMasterModule();
        tmpModule->getName(ns,stringBuf);
        cout<<stringBuf<<endl;
        cout<<"Print Module Instant terminal name"<<endl;
        oaIter<oaModInstTerm> mInstTermIter(mInstPtr->getInstTerms());
        while(oaModInstTerm *mInstTermPtr = mInstTermIter.getNext()){
            mInstTermPtr->getTermName(ns,stringBuf);
            cout<<"    "<<stringBuf;
            mInstTermPtr->getNet()->getName(ns,stringBuf);
            oaSigType mSigType=mInstTermPtr->getNet()->getSigType();
            cout<<"    Net: "<<stringBuf;
            cout<<"    Type: "<<mSigType;
            cout<<endl;
        }
        cout<<"#############################################"<<endl;
    }
    cout<<"_________________SUBMODULE_____________"<<endl;
    oaIter<oaModule> mModuleIter(m_design->getModules());
    while(module=mModuleIter.getNext()) {
        if(module== m_design->getTopModule())continue;
        module->getName(ns,stringBuf);
        cout<<stringBuf<<endl;
        cout<<"Print sub module header"<<endl;
        oaIter<oaModModuleInstHeader> mHeaderIter(module->getModuleInstHeaders());
        while(oaModModuleInstHeader *mHeaderPtr = mHeaderIter.getNext()){
            mHeaderPtr->getName(ns,stringBuf);
            cout<<stringBuf<<endl;
        }
        cout<<"Print Module Instant"<<endl;
        oaIter<oaModInst> mInstIter(module->getInsts());
        while(oaModInst *mInstPtr = mInstIter.getNext()){
            mInstPtr->getName(ns,stringBuf);
            cout<<stringBuf<<endl;
            oaModule* tmpModule=mInstPtr->getMasterModule();
            tmpModule->getName(ns,stringBuf);
            cout<<stringBuf<<endl;
            cout<<"Print Module Instant terminal name"<<endl;
            oaIter<oaModInstTerm> mInstTermIter(mInstPtr->getInstTerms());
            while(oaModInstTerm *mInstTermPtr = mInstTermIter.getNext()){
                mInstTermPtr->getTermName(ns,stringBuf);
                cout<<"    "<<stringBuf;
                mInstTermPtr->getNet()->getName(ns,stringBuf);
                cout<<"    Net: "<<stringBuf;
                cout<<endl;
            }
            cout<<"#############################################"<<endl;
        }
    }*/
}

void OA_openDesign::constructDesign(){
    OA_DESIGN* design=new OA_DESIGN("s27");
    m_designStructure=design;
    {
        OA_MODULE* module=new OA_MODULE("s27");
        design->TopModule=module;
        design->ModuleList.push_back(module);
        {
            OA_CELL* cell=new OA_CELL("U17","NR2M0N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("A","G1"));
            cell->NetList.push_back(pair<string,string>("B","G7"));
            cell->NetList.push_back(pair<string,string>("Z","n9"));
        }
        {
            OA_CELL* cell=new OA_CELL("U16","CKINVM1N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("A","G0"));
            cell->NetList.push_back(pair<string,string>("Z","n10"));
        }
        {
            OA_CELL* cell=new OA_CELL("U15","NR2M0N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("A","n1"));
            cell->NetList.push_back(pair<string,string>("B","n10"));
            cell->NetList.push_back(pair<string,string>("Z","G10"));
        }
        {
            OA_CELL* cell=new OA_CELL("U14","NR2M0N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("A","G2"));
            cell->NetList.push_back(pair<string,string>("B","n9"));
            cell->NetList.push_back(pair<string,string>("Z","G13"));
        }
        {
            OA_CELL* cell=new OA_CELL("U13","CKINVM1N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("A","n1"));
            cell->NetList.push_back(pair<string,string>("Z","G17"));
        }
        {
            OA_CELL* cell=new OA_CELL("U12","AOI22M2N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("A1","G3"));
            cell->NetList.push_back(pair<string,string>("A2","n9"));
            cell->NetList.push_back(pair<string,string>("B1","G6"));
            cell->NetList.push_back(pair<string,string>("B2","n10"));
            cell->NetList.push_back(pair<string,string>("Z","n11"));
        }
        {
            OA_CELL* cell=new OA_CELL("U11","NR2M2N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("A","n11"));
            cell->NetList.push_back(pair<string,string>("B","G5"));
            cell->NetList.push_back(pair<string,string>("Z","n1"));
        }
        {
            OA_CELL* cell=new OA_CELL("DFF_2","dff_test_1");
            module->CellList.push_back(cell);
            cell->IsModule=true;
            cell->NetList.push_back(pair<string,string>("test_se","test_se"));
            cell->NetList.push_back(pair<string,string>("test_si","G6"));
            cell->NetList.push_back(pair<string,string>("D","G13"));
            cell->NetList.push_back(pair<string,string>("Q","G7"));
            cell->NetList.push_back(pair<string,string>("CK","CK__L2_N0"));
        }
        {
            OA_CELL* cell=new OA_CELL("DFF_1","dff_test_0");
            module->CellList.push_back(cell);
            cell->IsModule=true;
            cell->NetList.push_back(pair<string,string>("test_se","test_se"));
            cell->NetList.push_back(pair<string,string>("test_si","G5"));
            cell->NetList.push_back(pair<string,string>("D","n1"));
            cell->NetList.push_back(pair<string,string>("Q","G6"));
            cell->NetList.push_back(pair<string,string>("CK","CK__L2_N0"));
        }
        {
            OA_CELL* cell=new OA_CELL("DFF_0","dff_test_2");
            module->CellList.push_back(cell);
            cell->IsModule=true;
            cell->NetList.push_back(pair<string,string>("test_se","test_se"));
            cell->NetList.push_back(pair<string,string>("test_si","test_si"));
            cell->NetList.push_back(pair<string,string>("D","G10"));
            cell->NetList.push_back(pair<string,string>("Q","G5"));
            cell->NetList.push_back(pair<string,string>("CK","CK__L2_N0"));
        }
        {
            OA_CELL* cell=new OA_CELL("CK__L1_I0","CKINVM32N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("A","CK"));
            cell->NetList.push_back(pair<string,string>("Z","CK__L1_N0"));
        }
        {
            OA_CELL* cell=new OA_CELL("CK__L2_I0","CKINVM12N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("A","CK__L1_N0"));
            cell->NetList.push_back(pair<string,string>("Z","CK__L2_N0"));
        }
    }
    {
        OA_MODULE* module=new OA_MODULE("dff_test_2");
        design->TopModule->SubModuleList.push_back(module);
        design->ModuleList.push_back(module);
        {
            OA_CELL* cell=new OA_CELL("Q_reg","LSDFQM2N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("CK","CK"));
            cell->NetList.push_back(pair<string,string>("D","D"));
            cell->NetList.push_back(pair<string,string>("Q","Q"));
            cell->NetList.push_back(pair<string,string>("SD","test_si"));
            cell->NetList.push_back(pair<string,string>("SE","test_se"));
        }
    }
    {
        OA_MODULE* module=new OA_MODULE("dff_test_0");
        design->TopModule->SubModuleList.push_back(module);
        design->ModuleList.push_back(module);
        {
            OA_CELL* cell=new OA_CELL("Q_reg","LSDFQM2N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("CK","CK"));
            cell->NetList.push_back(pair<string,string>("D","D"));
            cell->NetList.push_back(pair<string,string>("Q","Q"));
            cell->NetList.push_back(pair<string,string>("SD","test_si"));
            cell->NetList.push_back(pair<string,string>("SE","test_se"));
        }
    }
    {
        OA_MODULE* module=new OA_MODULE("dff_test_1");
        design->TopModule->SubModuleList.push_back(module);
        design->ModuleList.push_back(module);
        {
            OA_CELL* cell=new OA_CELL("Q_reg","LSDFQM2N");
            module->CellList.push_back(cell);
            cell->NetList.push_back(pair<string,string>("CK","CK"));
            cell->NetList.push_back(pair<string,string>("D","D"));
            cell->NetList.push_back(pair<string,string>("Q","Q"));
            cell->NetList.push_back(pair<string,string>("SD","test_si"));
            cell->NetList.push_back(pair<string,string>("SE","test_se"));
        }
    }
    unrollingDesign();
}


