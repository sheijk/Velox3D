// VSharedPtrTest.h: Schnittstelle für die Klasse VSharedPtrTest.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VSHAREDPTRTEST_H__7E6E3192_2D47_40DA_B8A9_1F7EE498C43F__INCLUDED_)
#define AFX_VSHAREDPTRTEST_H__7E6E3192_2D47_40DA_B8A9_1F7EE498C43F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UNITTESTS\VCommonTestBase.h"

class VSharedPtrTest : public VCommonTestBase  
{
private:
	void TestSharedPtr();
	void TestSharedStorage();
	void TestRefCountPol();

public:
	VSharedPtrTest();
	virtual ~VSharedPtrTest();

	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);
	virtual void ExecuteTest();
};

#endif // !defined(AFX_VSHAREDPTRTEST_H__7E6E3192_2D47_40DA_B8A9_1F7EE498C43F__INCLUDED_)
