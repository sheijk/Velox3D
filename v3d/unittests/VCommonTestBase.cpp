#include "VCommonTestBase.h"

#include "VTestManager.h"

/*!
	registers the test instance to the test manager
*/
VCommonTestBase::VCommonTestBase()
{
	// register instance at test manager
	VTestManager::GetInstance().AddCommonTest(this);
}

VCommonTestBase::~VCommonTestBase()
{
	/* do not unregister... might cause crash if test manager has already
	been deconstructed.. references will simply be forgotten */
}

/* 
	returns information about the test

	to be removed from VCommonTestBase (?)
*/
void VCommonTestBase::GetTestInfo(std::string& out_TestName, std::string& out_SubjectName)
{
	// output an error message if function hasnt been overridden
	VTestManager::GetInstance().OutputDebugMessage(VTestManager::VError,
		"VCommonTestBase::GetTestInfo not overridden");
}

// to be removed from VCommonTestBase (?)
IVUnitTest::VTestResult VCommonTestBase::ExecuteTest()
{
	// output error
	VTestManager::GetInstance().OutputDebugMessage(VTestManager::VError,
		"VCommonTestBase::ExecuteTest must be overridden");

	/* return a critical error by default, ExecuteTest must be
	overridden by all test classes */
	return IVUnitTest::VCriticalError;
}
