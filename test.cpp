

#include "test.h"
#include "testregistry.h"
#include "testresult.h"

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
TestCreator::TestCreator()
{
    TestRegistry::addTest (this);
}

void TestCreator::run( TestResult& result )
{
    Test& test = GetTestInstance();
    test.run(result);
}

TestCreator::~TestCreator()
{
    
}