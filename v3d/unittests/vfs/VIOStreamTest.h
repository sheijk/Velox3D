#ifndef V3D_VIOSTREAMTEST_H
#define V3D_VIOSTREAMTEST_H

#include <UnitTests\VCommonTestBase.h>

class IVStream;

class VIOStreamTest : public VCommonTestBase  
{
public:
	VIOStreamTest();
	virtual ~VIOStreamTest();

	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);

	virtual void ExecuteTest();
protected:
	void TestIOStreamSetpos(IVStream* in_pStream);
	void TestIOStreamRW(IVStream* in_Stream);
	void TestStreamIO(IVStream* in_Stream);
};

#endif // V3D_VIOSTREAMTEST_H
