#include "VTestSuite.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/UnitTests/IVUnitTest.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <iostream>
#include <string>
#include <list>

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
	IVTestManager::TestIteratorPtr iter;
	IVTestManager* pTestManager = QueryObject<IVTestManager>("testmngr");
	iter = pTestManager->CommonTestsBegin();
	VUnitTestInfo info;

	//(*(iter.Get())).Get()->ExecuteTest();

	for( ; 
		*iter != *(pTestManager->CommonTestsEnd());
		iter->Proceed())
	{
		// generate test info
		(*iter)->GetTestInfo(info.strName, info.strSubject);
		info.pUnitTest = iter->Get();

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

int VTestSuite::Main()
{
	// generate test list and print it
	GenerateTestList();

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
