#ifndef V3D_IVUNITTEST_H
#define V3D_IVUNITTEST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

/**
	IVUnitTest
	abstract interface for all unit tests
*/
class IVUnitTest
{
public:
	/*!
		returns the name of the test and the name of the subject to 
		be tested
	*/
	virtual void GetTestInfo(
		VStringParam out_TestName, 
		VStringParam out_SubjectName) = 0;

	/*!
		executes the test. must catch all exceptions
	*/
	virtual void ExecuteTest() = 0;

	//! make constructor virtual
	virtual ~IVUnitTest() {};
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVUNITTEST_H
