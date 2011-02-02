#include "tinyxml.h"
#include "testresultxml.h"

#ifdef _MSC_VER
#ifdef _DEBUG
#include "afx.h"
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#endif

using namespace CppUnitLite;

TestResultXml::TestResultXml( std::string szFilePath ) : m_szFilePath(szFilePath)
{
    
}

void TestResultXml::endTests()
{
    TestResult::endTests();
    
    TiXmlDocument doc;
    
    ////xml desc.
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );
    
    TiXmlElement* pRoot = new TiXmlElement( "TestRun" );
    doc.LinkEndChild(pRoot);
    
    GenerateFailures(pRoot);
    
    GenerateSuccess(pRoot);
    
    GenerateStatistics(pRoot);
    
    doc.SaveFile(m_szFilePath.c_str());
}

void TestResultXml::GenerateFailures( TiXmlElement* pParent )
{
    TiXmlElement* pAllFailedTests = new TiXmlElement( "FailedTests" );
    pParent->LinkEndChild(pAllFailedTests);
    
    std::vector<Failure>::iterator iter = failures.begin();
    std::vector<Failure>::iterator iterEnd = failures.end();
    for (int id = successes.size();iter != iterEnd; ++iter,++id)
    {
        const Failure& fail = *iter;
        
        TiXmlElement* pFailedTest = new TiXmlElement( "FailedTest" );
        pAllFailedTests->LinkEndChild(pFailedTest);
        pFailedTest->SetAttribute("id",id);
        pFailedTest->SetAttribute("Name",fail.testName.c_str());
        pFailedTest->SetAttribute("FailureType","fail");
        
        TiXmlElement* pLocationInfo = new TiXmlElement( "Location" );
        
        pFailedTest->LinkEndChild(pLocationInfo);
        pLocationInfo->SetAttribute("File",fail.fileName.c_str());
        pLocationInfo->SetAttribute("Line",fail.lineNumber);
        
        pFailedTest->SetAttribute("Message",fail.condition.c_str());
    }
}

void TestResultXml::GenerateSuccess( TiXmlElement* pParent )
{
    TiXmlElement* pAllOKTest = new TiXmlElement( "SuccessfulTests" );
    pParent->LinkEndChild(pAllOKTest);
    
    std::vector<Success>::iterator iter = successes.begin();
    std::vector<Success>::iterator iterEnd = successes.end();
    for (int id = 0;iter != iterEnd; ++iter,++id)
    {
        const Success& success = *iter;
        
        TiXmlElement* pTest = new TiXmlElement( "Test" );
        pAllOKTest->LinkEndChild(pTest);
        
        pTest->SetAttribute("id",id);//id
        pTest->SetAttribute("Name",success.getTestName().c_str());
    }
}

void TestResultXml::GenerateStatistics( TiXmlElement* pParent )
{
    TiXmlElement* pStatistics = new TiXmlElement( "Statistics" );
    pParent->LinkEndChild(pStatistics);
    
    pStatistics->SetAttribute("Tests",testCount);
    pStatistics->SetAttribute("FailuresTotal",failures.size());
}




//end of file

