#ifndef V3D_VIOSTREAMTEST_H
#define V3D_VIOSTREAMTEST_H

#include <UnitTests\VCommonTestBase.h>

class VIOStreamTest : public VCommonTestBase  
{
public:
	VIOStreamTest();
	virtual ~VIOStreamTest();

	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);

	virtual VTestResult ExecuteTest();
};

#endif // V3D_VIOSTREAMTEST_H
