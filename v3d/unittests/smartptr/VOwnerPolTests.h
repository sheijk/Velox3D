// VOwnerPolTests.h: Schnittstelle für die Klasse VOwnerPolTests.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOwnerPolTests_H__10819185_D06C_43A0_AFD5_B3C38627D7F5__INCLUDED_)
#define AFX_VOwnerPolTests_H__10819185_D06C_43A0_AFD5_B3C38627D7F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UNITTESTS\VCommonTestBase.h"

class VOwnerPolTests : public VCommonTestBase  
{
public:
	VOwnerPolTests();
	virtual ~VOwnerPolTests();

	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);
	virtual void ExecuteTest();
};

#endif // !defined(AFX_VOwnerPolTests_H__10819185_D06C_43A0_AFD5_B3C38627D7F5__INCLUDED_)
