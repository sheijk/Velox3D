//TODO: correct file guard
#ifndef V3D_/*classname*/_H
#define V3D_/*classname*/_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/UnitTests/IVUnitTest.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

//TODO: replace /*classname*/ by your class's name

/**
//TODO: insert documentation here
 */
class /*classname*/ : public IVUnitTest
{
public:
	/*classname*/();
	virtual ~/*classname*/();

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
#endif // V3D_/*classname*/_H
