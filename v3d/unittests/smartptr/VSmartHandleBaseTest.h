// VSmartHandleBaseTest.h: Schnittstelle für die Klasse VSmartHandleBaseTest.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VSMARTHANDLEBASETEST_H__8742C298_C8FC_46A8_85BF_0862C309ADAC__INCLUDED_)
#define AFX_VSMARTHANDLEBASETEST_H__8742C298_C8FC_46A8_85BF_0862C309ADAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UNITTESTS\VCommonTestBase.h"

class VSmartHandleBaseTest : public VCommonTestBase  
{
public:
	VSmartHandleBaseTest();
	virtual ~VSmartHandleBaseTest();

	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);
	virtual void ExecuteTest();
};

#endif // !defined(AFX_VSMARTHANDLEBASETEST_H__8742C298_C8FC_46A8_85BF_0862C309ADAC__INCLUDED_)
