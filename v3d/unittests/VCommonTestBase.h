#ifndef VCommonTestBase_h
#define VCommonTestBase_h

#include "IVUnitTest.h"

/*!
	the base class for common unit tests.
	common unit tests are tests that are regularely processed
	to ensure the correctness of all existing code
*/
class VCommonTestBase : public IVUnitTest  
{
private:
	VCommonTestBase(const VCommonTestBase&);
	void operator=(const VCommonTestBase&);

protected:
	/*!
		registers the test to the test manager
	*/
	VCommonTestBase();

	virtual ~VCommonTestBase();
public:
	/*!
		@see IVUnitTest::GetTestInfo
	*/
	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);

	/*!
		@see IVUnitTest::ExecuteTest
	*/
	virtual VTestResult ExecuteTest();
};

#endif // eof