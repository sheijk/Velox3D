// VStoragePolTests.cpp: Implementierung der Klasse VStoragePolTests.
//
//////////////////////////////////////////////////////////////////////

#include "VStoragePolTests.h"
#include <Core/VCoreLib.h>

#include <Utils/smartptr/VPointerStorage.h>
#include "VDestructTest.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

// register test
V3D_REGISTER_UNIT_TEST(VStoragePolTests);

VStoragePolTests::VStoragePolTests()
{

}

VStoragePolTests::~VStoragePolTests()
{

}

void VStoragePolTests::GetTestInfo(std::string& out_TestName, std::string& out_SubjectName)
{
	out_TestName = "Storage Policy Test";
	out_SubjectName = "Storage Policies of SmartHandle/SmartPointers";
}

void VStoragePolTests::ExecuteTest()
{
	vbool bAlive;

	// test pointer storage policy
	VPointerStorage<VDestructTest> PointerStore;
	VDestructTest* pDestTest = new VDestructTest(bAlive);

	PointerStore.Set(pDestTest);

	if( PointerStore.Get() != pDestTest )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VPointerStorage.Get() returned wrong value",
			VError);
	}

	if( !bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VPointerStorage: Object was illegally deleted",
			VError);
	}

	PointerStore.Release();

	if( bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VPointerStorage.Release(): Object was not deleted",
			VError);
	}

	// test array storage policy
	// TODO .. :)
}
