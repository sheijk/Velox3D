// VObjRegTest.h: Schnittstelle für die Klasse VObjRegTest.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOBJREGTEST_H__52EADA7C_C672_4E83_AD28_7F9D757EBA60__INCLUDED_)
#define AFX_VOBJREGTEST_H__52EADA7C_C672_4E83_AD28_7F9D757EBA60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UNITTESTS\VCommonTestBase.h"

class VObjRegTest : public VCommonTestBase  
{
private:
	void ObjRegTest();
	void NameGeneratorTest();
	
public:
	VObjRegTest();
	virtual ~VObjRegTest();

	virtual void GetTestInfo(std::string& out_TestName, std::string& out_SubjectName);
	virtual void ExecuteTest();
};

#endif // !defined(AFX_VOBJREGTEST_H__52EADA7C_C672_4E83_AD28_7F9D757EBA60__INCLUDED_)
