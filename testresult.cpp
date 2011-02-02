
#include "testresult.h"
#include "failure.h"

#include <iostream>



void TestResult::testWasRun()
{
	testCount++;
}

void TestResult::startTests () 
{
}

void TestResult::addFailure (Failure failure) 
{
	using namespace std;
	cout << failure << endl;
    failures.push_back(failure);
}

void TestResult::endTests () 
{
	using namespace std;

	cout << testCount << " tests run" << endl;
    int failureCount = failures.size();
	if (failureCount > 0)
		cout << "There were " << failureCount << " failures" << endl;
	else
		cout << "There were no test failures" << endl;
}
bool TestResult::wasSucessful()const
{
    return failures.empty();
}

void TestResult::addSuccess( const Success& success )
{
    successes.push_back(success);
}