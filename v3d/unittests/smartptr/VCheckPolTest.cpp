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

V3D_REGISTER_UNIT_TEST(VCheckPolTest);

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

void VCheckPolTest::ExecuteTest()
{
	// check no check policy
	VNoCheckPol<int*> pol;
	int* nullInt = NULL;
	int blub;
	int* einsInt = &blub;

	if( pol.IsValid(nullInt) != true || pol.IsValid(einsInt) != true ) 
	{
		V3D_THROW_UNITTEST_ERROR("VNoCheckPol rejected a pointer",	
			VError);
	}

	try
	{
		pol.Check(nullInt);
		pol.Check(einsInt);
	} 
	catch(VException e)
	{
		V3D_THROW_UNITTEST_ERROR(
			"VNoCheckPol. raised exception while checking",
			VError);
	}

	// check NULL check policy
	VNullCheckPol<int*> pol0;

	if( pol0.IsValid(nullInt) == true )
	{
		V3D_THROW_UNITTEST_ERROR("VNullCheckPol accepted null ptr", 
			VError);
	}

	if( pol0.IsValid(einsInt) == false )
	{
		V3D_THROW_UNITTEST_ERROR("VNullCheckPol rejected non null ptr", 
			VError);
	}

	try
	{
		pol0.Check(einsInt);
	}
	catch(VException e)
	{
		V3D_THROW_UNITTEST_ERROR(
			"VNullCheckPol raised exception while checking a non null ptr",
			VError);
	}

	try
	{
		pol0.Check(nullInt);

		V3D_THROW_UNITTEST_ERROR(
			"VNullCheckPol did not throw exception while checking null ptr",
			VError);
	}
	catch(VException e)
	{
	}

}
