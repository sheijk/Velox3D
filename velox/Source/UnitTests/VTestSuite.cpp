#include "VTestSuite.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/UnitTests/IVUnitTest.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>
#include <v3d/Core/VIOStream.h>

#include <string>
#include <list>
#include <algorithm>
#include <functional>

//TODO: write documentation for VTestSuite

//-----------------------------------------------------------------------------
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
		vout << "\"" << iter->strName<< "\" tests \"" 
			<< iter->strSubject << "\"" << vendl;
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
			vout << "----------------------------------------"
				 << "---------------------------------------"
				 << vendl;

			vout << "Starting test " << iter->strName 
				 << " testing " << iter->strSubject
				 << vendl;

			vout << "----------------------------------------"
				<< "----------------------------------------"
				<< vendl;

			iter->pUnitTest->ExecuteTest();
		}
		catch(VUnitTestException exc)
		{
			vout << "Error detected:" << vendl
				<< "Test name:     " << iter->strName << vendl
				<< "Error message: " << "\"" << exc.GetErrorString() 
				<< "\"" << vendl
				<< "Line:          " << exc.GetErrorLine() << vendl
				<< "File:          " << exc.GetErrorFile() << vendl
				<< vendl;

			bErrors = true;
//			vout << "Test \"" + iter->strName + "\" detected an error in"
//				+ iter->strSubject << "Line nr. " << exc.GetErrorLine()
//				<< " File \"" << exc.GetErrorFile() << vendl;
//			vout << "  Error message: \"" + exc.GetExtendedErrorString()
//				+ "\"";
		}
		catch(VException exc)
		{
			vout << "A Velox non UnitTest Exception occured while testing "
				<< "test may be corrupt." << vendl
				<< "Test name:     " << iter->strName << vendl
				<< "Error message: " << "\"" << exc.GetErrorString() 
				<< "\"" << vendl
				<< "Line:          " << exc.GetErrorLine() << vendl
				<< "File:          " << exc.GetErrorFile() << vendl
				<< vendl;

			bErrors = true;
		}
		//catch(...)
		//{
		//	vout << "Unknown error occured in test " << vendl
		//		<< "<" << iter->strName << ">" << vendl
		//		<< "Unit test might be corrupt or incomplete" << vendl
		//		<< vendl;

		//	bErrors = true;
		//}
	}

	if( !bErrors )
	{
		vout << "no errors detected" << vendl;
	}
}

int VTestSuite::Main()
{
	// generate test list and print it
	GenerateTestList();

	// print "header"
	vout << "-----------------------------------------------------------------------------"
		<< vendl << "-- UnitTest Suite: starting tests" << vendl;

	// print list of tests
	vout << "list of unit tests" << vendl << vendl;

	PrintList();

	vout << vendl << vendl << "executing tests" << vendl << vendl;

	// do tests
	ExecuteTests();

	return 0;
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
