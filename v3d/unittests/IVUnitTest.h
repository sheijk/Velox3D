#ifndef IVUnitTest_h
#define IVUnitTest_h

#include <string>

/**	a macro for defining tests */
#define V3D_REGISTER_UNIT_TEST(t) namespace vunittests { t g_test##t; };

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

#endif // !defined(AFX_IVUNITTEST_H__25BA89C7_92CC_454C_AC5F_29FE6B253238__INCLUDED_)
