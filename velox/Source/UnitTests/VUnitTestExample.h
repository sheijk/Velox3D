#ifndef V3D_VUNITTESTEXAMPLE_H
#define V3D_VUNITTESTEXAMPLE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "VCommonTestBase.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

/*!
	This is an example for a unit test class
*/
class VUnitTestExample : public VCommonTestBase
{
public:
	VUnitTestExample();
	virtual ~VUnitTestExample();

	/*! @see IVUnitTest#GetTestInfo(std::string&, std::string&) */
	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);

	/*! @see IVUnitTest#Execute() */
	virtual void ExecuteTest();
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VUNITTESTEXAMPLE_H