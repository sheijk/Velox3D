#ifndef V3D_VMathTest_H
#define V3D_VMathTest_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/UnitTests/IVUnitTest.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

/**
 * Tests the math library
 */
class VMathTest : public IVUnitTest
{
public:
	VMathTest();
	virtual ~VMathTest();

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
#endif // V3D_VMathTest_H
