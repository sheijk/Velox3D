//TODO: correct file guard
#ifndef V3D_VFileStreamTest_H
#define V3D_VFileStreamTest_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/UnitTests/IVUnitTest.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

//TODO: replace VFileStreamTest by your class's name

/**
//TODO: insert documentation here
*/
class VFileStreamTest : public IVUnitTest
{
public:
	VFileStreamTest();
	virtual ~VFileStreamTest();

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
#endif // V3D_VFileStreamTest_H
