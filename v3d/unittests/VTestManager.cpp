#include "VTestManager.h"

using namespace std;


auto_ptr<VTestManager> VTestManager::s_pTestManager;


VTestManager::VTestManager()
{
}

VTestManager::~VTestManager()
{

}

VTestManager& VTestManager::GetInstance()
{
	// if no instance exists yet
	if(s_pTestManager.get() == 0)
	{
		// create one
		s_pTestManager.reset(new VTestManager());
	}

	// return the test manager
	return *s_pTestManager.get();
}

void VTestManager::AddCommonTest(VCommonTestBase *in_pTest)
{
	// check for 0 pointer
	if( in_pTest != 0 )
	{
		// add tests to list
		m_CommonTests.push_back((IVUnitTest*)in_pTest);
	}
}

void VTestManager::OutputDebugMessage(VMessageLevel in_eLevel, const char* in_pszMessage)
{
	// check output level
	// if output level is allowed for output
		// output message
}

VTestManager::TestIterator VTestManager::CommonTestsBegin()
{
	return m_CommonTests.begin();
}

VTestManager::TestIterator VTestManager::CommonTestsEnd()
{
	return m_CommonTests.end();
}
