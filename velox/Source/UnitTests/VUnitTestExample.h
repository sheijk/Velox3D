#ifndef V3D_VUNITTESTEXAMPLE_H
#define V3D_VUNITTESTEXAMPLE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/UnitTests/IVUnitTest.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

/*!
	This is an example for a unit test class
*/
class VUnitTestExample : public IVUnitTest
{
public:
	VUnitTestExample();
	virtual ~VUnitTestExample();

	/*! @see IVUnitTest#GetTestInfo(VStringParam, VStringParam) */
	virtual void GetTestInfo(
		VString& out_TestName, 
		VString& out_SubjectName);

	/*! @see IVUnitTest#Execute() */
	virtual void ExecuteTest();
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VUNITTESTEXAMPLE_H
