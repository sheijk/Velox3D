// VCheckPolTest.h: Schnittstelle für die Klasse VCheckPolTest.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VCHECKPOLTEST_H__74D24B09_2FDB_468A_8E60_32EC2C874988__INCLUDED_)
#define AFX_VCHECKPOLTEST_H__74D24B09_2FDB_468A_8E60_32EC2C874988__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UNITTESTS\VCommonTestBase.h"

class VCheckPolTest : public VCommonTestBase  
{
public:
	VCheckPolTest();
	virtual ~VCheckPolTest();

	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);
	virtual void ExecuteTest();
};

#endif // !defined(AFX_VCHECKPOLTEST_H__74D24B09_2FDB_468A_8E60_32EC2C874988__INCLUDED_)
