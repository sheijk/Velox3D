#include "VTestManager.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/Wrappers/VSTLDerefIteratorPol.h>

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

VTestManager::TestIterator VTestManager::CommonTestsBegin()
{
	typedef VSTLDerefIteratorPol<UnitTestList::iterator, IVUnitTest> IterPol;

	TestIterator theIter(new IterPol(m_CommonTests.begin()));

	return theIter;
}

VTestManager::TestIterator VTestManager::CommonTestsEnd()
{
	typedef VSTLDerefIteratorPol<UnitTestList::iterator, IVUnitTest> IterPol;

	TestIterator theIter(new IterPol(m_CommonTests.end()));

	return theIter;
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
