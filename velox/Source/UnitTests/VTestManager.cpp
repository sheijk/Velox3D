#include "VTestManager.h"
//-----------------------------------------------------------------------------
//#include <V3d/Core/Wrappers/VSTLIterDerefAdaptor.h>
#include <V3d/Core/Wrappers/VSTLIteratorAdaptor.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------
using namespace std;


VTestManager::VTestManager(VStringParam in_strName) :
	IVTestManager(in_strName, 0)
{
}

VTestManager::~VTestManager()
{

}

void VTestManager::AddCommonTest(IVUnitTest* in_pTest)
{
	// check for 0 pointer
	if( in_pTest != 0 )
	{
		// add tests to list
		m_CommonTests.push_back((IVUnitTest*)in_pTest);
	}
}

//void VTestManager::OutputDebugMessage(VMessageLevel in_eLevel, const char* in_pszMessage)
//{
//	// check output level
//	// if output level is allowed for output
//		// output message
//}

VTestManager::TestIteratorPtr VTestManager::CommonTestsBegin()
{
	TestIteratorPtr theIter;
	theIter.Reset(new 
		VSTLIteratorAdaptor<UnitTestList::iterator>(
//		VSTLIterDerefAdaptor<IVUnitTest, UnitTestList::iterator>(
		m_CommonTests.begin()));

	return theIter;
}

VTestManager::TestIteratorPtr VTestManager::CommonTestsEnd()
{
	TestIteratorPtr theIter;
	theIter.Reset(new 
		VSTLIteratorAdaptor<UnitTestList::iterator>(
//		VSTLIterDerefAdaptor<IVUnitTest, UnitTestList::iterator>(
		m_CommonTests.end()));

	return theIter;
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
