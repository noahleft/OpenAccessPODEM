#include "oaDesignDB.h"
#include "OA_LibraryPath.h"
#include "gate.h"
//Design Pattern: Simple Factory
using namespace oa;

class OA_openDesign
{
  private:  typedef GATE OA_GATE;
  public:
    //the only way to touch constructor
    OA_openDesign getDesign(string libPath,string library,string cellName,string ViewName);
    //the only way to dump design
    void dumpModule();
    vector<OA_GATE*> getDesignStructure();
    
    ~OA_openDesign();
  private:
    OA_openDesign():m_design(NULL),m_library(NULL){}
    
    oaDesign*   m_design;
    oaLib*      m_library;
    vector<OA_GATE*> m_designStructure;
    
    void loadDesign(string,string,string,string);
    void constructDesign();
};

