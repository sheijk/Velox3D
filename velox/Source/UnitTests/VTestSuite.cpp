#include "VTestSuite.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/UnitTests/IVUnitTest.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <functional>

//TODO: write documentation for VTestSuite

//-----------------------------------------------------------------------------
using std::cout;
using std::endl;

namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/*
	implementation of class VTestSuite
*/

// constructor
VTestSuite::VTestSuite(VStringParam in_strName) :
	VNamedObject(in_strName, 0)
{

}

// destructor
VTestSuite::~VTestSuite()
{

}

void VTestSuite::GenerateTestList()
{
	// get all test from the test manager

	VUnitTestInfo info;
	IVTestManager* pTestManager = QueryObject<IVTestManager>("testmngr");

	IVTestManager::TestIterator testIt(pTestManager->CommonTestsBegin());

	for( ;
		testIt != pTestManager->CommonTestsEnd();
		++testIt )
	{
		// generate test info
		testIt->GetTestInfo(info.strName, info.strSubject);
		info.pUnitTest = &(*testIt);

		// add to list
		m_UnitTests.insert(info);

		info.Reset();
	}
}

void VTestSuite::PrintList() const
{
	UnitTestInfoList::const_iterator iter = m_UnitTests.begin();

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
			cout << "Error detected:" << endl
				<< "Test name:     " << iter->strName << endl
				<< "Error message: " << "\"" << exc.GetErrorString() 
				<< "\"" << endl
				<< "Line:          " << exc.GetErrorLine() << endl
				<< "File:          " << exc.GetErrorFile() << endl
				<< endl;

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
				<< "test may be corrupt." << endl
				<< "Test name:     " << iter->strName << endl
				<< "Error message: " << "\"" << exc.GetErrorString() 
				<< "\"" << endl
				<< "Line:          " << exc.GetErrorLine() << endl
				<< "File:          " << exc.GetErrorFile() << endl
				<< endl;

			bErrors = true;
		}
		catch(...)
		{
			cout << "Unknown error occured in test " << endl
				<< "<" << iter->strName << ">" << endl
				<< "Unit test might be corrupt or incomplete" << endl
				<< endl;

			bErrors = true;
		}
	}

	if( !bErrors )
	{
		cout << "no errors detected" << endl;
	}
}

int VTestSuite::Main()
{
	// generate test list and print it
	GenerateTestList();

	// print "header"
	cout << "-----------------------------------------------------------------------------"
		<< endl << "-- UnitTest Suite: starting tests" << endl;

	// print list of tests
	cout << "list of unit tests" << endl << endl;

	PrintList();

	cout << endl << endl << "executing tests" << endl << endl;

	// do tests
	ExecuteTests();

	return 0;
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
