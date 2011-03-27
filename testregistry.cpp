#include "test.h"
#include "testresult.h"
#include "testregistry.h"

#ifdef _MSC_VER
#ifdef _DEBUG
#include "afx.h"
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#endif


void TestRegistry::addFastTest (TestCreator *test) 
{
	instance ().DoAddFastTest (test);
}

void TestRegistry::addSlowTest( TestCreator* test )
{
    instance ().DoAddSlowTest(test);
}

void TestRegistry::addOnlyTest( TestCreator* pTest )
{
    instance ().DoAddOnlyTest(pTest);
}

void TestRegistry::runAllTests (TestResult& result) 
{
    result.startTests();
    if (instance().IsUsingTestOnly())
    {
        instance().DoRunTestOnly(result);
        result.endTests();
        return ;
    }
    instance ().DoRunFastTest (result);
    instance ().DoRunSlowTest(result);
    result.endTests();
}


void TestRegistry::runFastTests( TestResult& result )
{
    result.startTests();
    instance ().DoRunFastTest (result);
    result.endTests();
}


void TestRegistry::runSlowTests( TestResult& result )
{
    result.startTests();
    instance ().DoRunSlowTest(result);
    result.endTests();
}

TestRegistry& TestRegistry::instance () {
	static TestRegistry registry;
	return registry;
}


void TestRegistry::DoAddFastTest (TestCreator *test) {
	m_fastTests.push_back (test);
}

void TestRegistry::DoAddSlowTest (TestCreator *test) {
    m_slowTests.push_back (test);
}

void TestRegistry::DoAddOnlyTest( TestCreator* pTest )
{    
    m_pOnlyTest = pTest;
}


void TestRegistry::DoRunFastTest (TestResult& result) 
{
    if (m_pOnlyTest)
    {
        m_pOnlyTest->run(result);
        return;
    }
    if (m_fastTests.size() == 0)
    {
        return;
    }
	for (std::vector<TestCreator *>::iterator it = m_fastTests.begin (); it != m_fastTests.end (); ++it)
    {
        (*it)->run (result);
    }
}


void TestRegistry::DoRunSlowTest( TestResult& result )
{
    if (m_pOnlyTest)
    {
        m_pOnlyTest->run(result);
        return;
    }
    if (m_slowTests.size() == 0)
    {
        return;
    }
    for (std::vector<TestCreator *>::iterator it = m_slowTests.begin (); it != m_slowTests.end (); ++it)
    {
        (*it)->run (result);
    }
}

TestRegistry::TestRegistry() : m_pOnlyTest(0)
{
    
}

void TestRegistry::DoRunTestOnly(TestResult& result)
{
    if (m_pOnlyTest)
    {
        m_pOnlyTest->run(result);
        return;
    }
}

bool TestRegistry::IsUsingTestOnly()const
{
    return m_pOnlyTest != 0;
}

//end of file




