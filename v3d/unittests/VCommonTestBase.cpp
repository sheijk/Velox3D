#include "VCommonTestBase.h"

#include "VTestManager.h"

/**
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
