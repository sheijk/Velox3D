// VSmartPointerTest.h: Schnittstelle für die Klasse VSmartPointerTest.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VSMARTPOINTERTEST_H__165C983C_4CA8_487A_ADFB_26B312A7BA2A__INCLUDED_)
#define AFX_VSMARTPOINTERTEST_H__165C983C_4CA8_487A_ADFB_26B312A7BA2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <UnitTests\VCommonTestBase.h>

class VSmartPointerTest : public VCommonTestBase  
{
public:
	VSmartPointerTest();
	virtual ~VSmartPointerTest();

	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);
	virtual void ExecuteTest();

};

#endif // !defined(AFX_VSMARTPOINTERTEST_H__165C983C_4CA8_487A_ADFB_26B312A7BA2A__INCLUDED_)
