#ifndef V3D_VStringTests_H
#define V3D_VStringTests_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/UnitTests/IVUnitTest.h>
#include <v3d/UnitTests/VUnitTestException.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

/**
//TODO: insert documentation here
*/
class VStringTests : public IVUnitTest
{
private:
	void AssignAndGetTest();
	void CopyTest();

public:
	VStringTests();
	virtual ~VStringTests();

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
#endif // V3D_VStringTests_H
