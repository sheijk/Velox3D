// VStoragePolTests.h: Schnittstelle für die Klasse VStoragePolTests.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VSTORAGEPOLTESTS_H__C64A2A17_6B75_4F74_A5EA_5FEE3930A075__INCLUDED_)
#define AFX_VSTORAGEPOLTESTS_H__C64A2A17_6B75_4F74_A5EA_5FEE3930A075__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UNITTESTS\VCommonTestBase.h"

class VStoragePolTests : public VCommonTestBase  
{
public:
	VStoragePolTests();
	virtual ~VStoragePolTests();

	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);
	virtual void ExecuteTest();

};

#endif // !defined(AFX_VSTORAGEPOLTESTS_H__C64A2A17_6B75_4F74_A5EA_5FEE3930A075__INCLUDED_)
