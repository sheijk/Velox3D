// VCheckPolTest.cpp: Implementierung der Klasse VCheckPolTest.
//
//////////////////////////////////////////////////////////////////////

#include <cmath>

#include "VCheckPolTest.h"

#include <Core/VCoreLib.h>
#include <Utils/smartptr/VNoCheckPol.h>
#include <Utils/smartptr/VNullCheckPol.h>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

VREGISTER_UNIT_TEST(VCheckPolTest);

VCheckPolTest::VCheckPolTest()
{

}

VCheckPolTest::~VCheckPolTest()
{

}

void VCheckPolTest::GetTestInfo(std::string& out_TestName, std::string& out_SubjectName)
{
	out_TestName = "CheckPolicy Test";
	out_SubjectName = "SmartHandle/Pointer CheckPolicies";
}

VCheckPolTest::VTestResult VCheckPolTest::ExecuteTest()
{
	// check no check policy
	VNoCheckPol<int*> pol;
	int* nullInt = NULL;
	int blub;
	int* einsInt = &blub;

	if( pol.IsValid(nullInt) != true || pol.IsValid(einsInt) != true ) 
	{
		return VError;
	}

	try
	{
		pol.Check(nullInt);
		pol.Check(einsInt);
	} 
	catch(...)
	{
		return VCriticalError;
	}

	// check NULL check policy
	VNullCheckPol<int*> pol0;

	if( pol0.IsValid(nullInt) == true || pol0.IsValid(einsInt) == false )
	{
		return VError;
	}

	try
	{
		pol0.Check(einsInt);
	}
	catch(...)
	{
		return VCriticalError;
	}

	try
	{
		pol0.Check(nullInt);

		return VError;
	}
	catch(...)
	{
	}

	return VOk;
}
