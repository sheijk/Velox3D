// VOwnerPolTests.cpp: Implementierung der Klasse VOwnerPolTests.
//
//////////////////////////////////////////////////////////////////////

#include "VOwnerPolTests.h"

#include <utils/smartptr/VExclusiveOwnerPol.h>
#include <utils/smartptr/VPointerStorage.h>

#include "VDestructTest.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
V3D_REGISTER_UNIT_TEST(VOwnerPolTests);

VOwnerPolTests::VOwnerPolTests()
{

}

VOwnerPolTests::~VOwnerPolTests()
{

}

void VOwnerPolTests::GetTestInfo(
								std::string& out_TestName, 
								std::string& out_SubjectName)
{
	out_TestName = "VExclusiveStoragePol Test";
	out_SubjectName = "VExclusiveStoragePol";
}

void VOwnerPolTests::ExecuteTest()
{
	VExclusiveOwnerPol< VPointerStorage<VDestructTest> > owner, owner2;

	static vbool bAlive;

	VDestructTest* pBlah = new VDestructTest(bAlive);

	// get und set testen
	owner.Set(pBlah);

	if( owner.Get() != pBlah ) 
	{
		V3D_THROW_UNITTEST_ERROR(
			"VExclusiveOwnerPol.Get() returned wrong value",
			VError);
	}

	owner.Set(0);

	if( bAlive == true ) 
	{
		V3D_THROW_UNITTEST_ERROR(
			"VExclusiveOwnerPol: Object was not deleted when setting to 0",
			VError);
	}

	owner.Set(new VDestructTest(bAlive));
	owner2.Clone(owner);

	if( ! bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VExclusiveOwnerPol.Clone(): Object was deleted when copying",
			VError);
	}

	owner2.Release();

	if( bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VExclusiveOwnerPol.Release(): Object was not deleted",
			VError);
	}

}
