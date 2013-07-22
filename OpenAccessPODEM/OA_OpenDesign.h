#include "oaDesignDB.h"
#include "OA_LibraryPath.h"
#include <string>
#include <vector>
using namespace std;
//Design Pattern: Simple Factory
using namespace oa;

struct OA_GATE {
    string Name;
    OA_GATE(string n):Name(n){}
};

class OA_openDesign
{
  public:
    //the only way to touch constructor
    OA_openDesign getDesign(string libPath,string library,string cellName,string ViewName);
    //the only way to dump design
    void dumpModule();
    vector<OA_GATE*> getDesignStructure() {
        return m_designStructure;
    }
    
    ~OA_openDesign();
  private:
    OA_openDesign():m_design(NULL),m_library(NULL){}
    
    oaDesign*   m_design;
    oaLib*      m_library;
    vector<OA_GATE*> m_designStructure;
    
    void loadDesign(string,string,string,string);
    void constructDesign();
};

