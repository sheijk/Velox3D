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

/*
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
*/

void VTestSuite::GenerateTestList()
{
	// get all test from the test manager

	VTestManager::TestIterator iter;
	iter = VTestManager::GetInstance().CommonTestsBegin();

	VUnitTestInfo info;

	for( ; iter != VTestManager::GetInstance().CommonTestsEnd(); ++iter)
	{
		// generate test info
		(*iter)->GetTestInfo(info.strName, info.strSubject);
		info.pUnitTest = *iter;

		// add to list
		m_UnitTests.insert(info);

		info.Reset();
	}
}

void VTestSuite::PrintList() const
{
	UnitTestInfoList::iterator iter = m_UnitTests.begin();

	for( ; iter != m_UnitTests.end(); ++iter)
	{
		cout << "\"" << iter->strName<< "\" tests \"" 
			<< iter->strSubject << "\"" << endl;
	}
}

void VTestSuite::ExecuteTests()
{
	UnitTestInfoList::iterator iter = m_UnitTests.begin();
	vbool bErrors = false;

	for( ; iter != m_UnitTests.end(); ++iter)
	{
		try
		{
			iter->pUnitTest->ExecuteTest();
		}
		catch(VUnitTestException exc)
		{
			cout << "Test \"" << iter->strName << "\" detected an error "
				<< "(Subject: \"" << iter->strSubject << "\") : \""
				<< exc.GetExtendedErrorString() << "\"" << endl;

			bErrors = true;
//			cout << "Test \"" + iter->strName + "\" detected an error in"
//				+ iter->strSubject << "Line nr. " << exc.GetErrorLine()
//				<< " File \"" << exc.GetErrorFile() << endl;
//			cout << "  Error message: \"" + exc.GetExtendedErrorString()
//				+ "\"";
		}
		catch(VException exc)
		{
			cout << "A Velox non UnitTest Exception occured while testing "
				<< "test may be corrupt. Error message:"
				<< "\"" << exc.GetErrorString() << "\""
				<< " in line " << exc.GetErrorLine()
				<< " in file " << exc.GetErrorFile()
				<< endl;

			bErrors = true;
		}
		catch(...)
		{
			cout << "\nunknown error occured in test" << iter->strName << endl
				<< "unit test might be corrupt or incomplete" << endl;

			bErrors = true;
		}
	}

	if( !bErrors )
	{
		cout << "no errors detected" << endl;
	}
}

void main(int argc, char* args[])
{
	VTestSuite suite;

	// generate test list and print it
	suite.GenerateTestList();

	cout << "list of unit tests" << endl << endl;
	
	suite.PrintList();

	cout << endl << endl << "executing tests" << endl << endl;

	// do tests
	suite.ExecuteTests();
}

