#include "OA_OpenDesign.h"

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

OA_openDesign::~OA_openDesign(){
    for(unsigned i=0;i<m_designStructure.size();i++){
        delete m_designStructure[i];
        m_designStructure[i]=NULL;
    }
}

void OA_openDesign::constructDesign(){
    OA_GATE* gate;
    gate=new OA_GATE("OA_test");
    m_designStructure.push_back(gate);
}

