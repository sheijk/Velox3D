#ifndef V3D_IVUNITTEST_H
#define V3D_IVUNITTEST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <string>

/**	a macro for defining tests */
#define V3D_REGISTER_UNIT_TEST(t) namespace vunittests { t g_test##t; };

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

/**
	IVUnitTest
	abstract interface for all unit tests
*/
class IVUnitTest  
{
public:
	//! result of a unit test
	enum VErrorType
	{
		// warning, minor problems which wont affect the functionality
		VWarning,
		//! error, a tested functionality did not work
		VError,
		/*! an error which would affect the stability of other system, 
		crashes, illegal memory operations etc. */
		VCriticalError
	};

	/*!
		returns the name of the test and the name of the subject to 
		be tested
	*/
	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName) = 0;

	/*!
		executes the test. must catch all exceptions
	*/
	virtual void ExecuteTest() = 0;

	//! make constructor virtual
	virtual ~IVUnitTest();
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVUNITTEST_H
