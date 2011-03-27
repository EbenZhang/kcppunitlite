#include "test.h"
#include "testregistry.h"
#include "testresult.h"

#ifdef _MSC_VER
#ifdef _DEBUG
#include "afx.h"
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#endif

Test::Test() :  bIsFailed(false)
{
    
}

void Test::run (TestResult& result) 
{
	runTest (result);
	result.testWasRun();
}

void Test::runTest( TestResult& result )
{
    setUp();
    bIsFailed = false;
    doTest(result);
    if (!bIsFailed)
    {
        Success success(getName());
        result.addSuccess(success);
    }
    tearDown();
}

Test::~Test()
{
    
}
TestCreator::TestCreator(bool bSlow)
{
    if(!bSlow)
    {
        TestRegistry::addFastTest (this);
    }
    else
    {
        TestRegistry::addSlowTest(this);
    }
}

void TestCreator::run( TestResult& result )
{
    Test& test = GetTestInstance();
    test.run(result);
}

TestCreator::~TestCreator()
{
    
}

TestCreatorForTestOnlyOneTest::TestCreatorForTestOnlyOneTest() : TestCreator(false)
{
    TestRegistry::addOnlyTest(this);
}


//end of file

