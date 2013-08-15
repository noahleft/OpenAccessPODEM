#include "oaDesignDB.h"
#include "OA_LibraryPath.h"
#include <string>
#include <vector>
#include "OA_Design.h"
using namespace std;
//Design Pattern: Simple Factory
using namespace oa;

class OA_openDesign
{
  public:
    //the only way to touch constructor
    void getDesign(string libPath,string library,string cellName,string ViewName);
    //the only way to dump design
    void dumpModule();
    OA_DESIGN* getDesignStructure() {
        return m_designStructure;
    }
    
    ~OA_openDesign();
	OA_openDesign():m_design(NULL),m_library(NULL),m_designStructure(NULL){}
  private:
    
    
    oaDesign*   m_design;
    oaLib*      m_library;
    OA_DESIGN* m_designStructure;
    
    void loadDesign(string,string,string,string);
    void constructDesign();
    void unrollingDesign();
};

