#include "VTestSuite.h"

#include <UnitTests/VTestManager.h>
#include <UnitTests/VCommonTestBase.h>

#include <iostream>
#include <string>
#include <list>

using std::cout;
using std::endl;

/*
	implementation of class VTestSuite
*/

// constructor
VTestSuite::VTestSuite()
{

}

// destructor
VTestSuite::~VTestSuite()
{

}

// no comment :)
void main(int argc, char* args[])
{
	// list all registered tests
	VTestManager::TestIterator theIter = VTestManager::GetInstance().CommonTestsBegin();

	std::string strTestName;
	std::string strTestInfo;

	cout << "Listing all registered tests:" << std::endl;

	// print out a list of all tests
	for( ; VTestManager::GetInstance().CommonTestsEnd() != theIter; ++theIter) 
	{
		strTestName = "not specified";
		strTestInfo = "please implement GetTestInfo properly";

		// get test info
		(*theIter)->GetTestInfo(strTestName, strTestInfo);

		// display test info
		std::cout << "\"" << strTestName << "\" tests \"" << strTestInfo << "\"" << std::endl;		
	}

	// FIXME: evtl. ein gui interface machen?
	// get list of tests to be executed
	typedef std::list<IVUnitTest*> TestList;
	
	TestList theTestList;

	// create a list of all unit tests
	for(theIter = VTestManager::GetInstance().CommonTestsBegin();
		VTestManager::GetInstance().CommonTestsEnd() != theIter;
		++theIter)
	{
			theTestList.push_back(*theIter);
	}
	
	// execute them
	TestList::iterator theTestIter = theTestList.begin();
	IVUnitTest::VTestResult theResult;

	cout << endl << endl;
	
	// execute all tests and display results
	for( ; theTestList.end() != theTestIter; ++theTestIter )
	{
		strTestName = "not specified";
		strTestInfo = "please implement GetTestInfo properly";

		(*theTestIter)->GetTestInfo(strTestName, strTestInfo);

		cout << "executing test " << strTestName << " : "; 

		theResult = (*theTestIter)->ExecuteTest();

		switch(theResult)
		{
		case IVUnitTest::VOk:
			{
				cout << "Ok" << endl;
			} break;
		case IVUnitTest::VWarning:
			{
				cout << "Warning" << endl;
			} break;
		case IVUnitTest::VError:
			{
				cout << "Error" << endl;
			} break;
		case IVUnitTest::VCriticalError:
			{
				cout << "Critical Error" << endl;
			} break;
		default:
			{
				cout << "daboo?" << endl;
			}
		}
	}
}
