#include "VCommonTestBase.h"
//-----------------------------------------------------------------------------
#include "VTestManager.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
