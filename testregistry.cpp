

#include "test.h"
#include "testresult.h"
#include "testregistry.h"


void TestRegistry::addTest (TestCreator *test) 
{
	instance ().add (test);
}


void TestRegistry::runAllTests (TestResult& result) 
{
	instance ().run (result);
}


TestRegistry& TestRegistry::instance () {
	static TestRegistry registry;
	return registry;
}


void TestRegistry::add (TestCreator *test) {
	tests.push_back (test);
}


void TestRegistry::run (TestResult& result) {
	result.startTests ();
	for (std::vector<TestCreator *>::iterator it = tests.begin (); it != tests.end (); ++it)
		(*it)->run (result);
	result.endTests ();
}



