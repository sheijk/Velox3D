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
VREGISTER_UNIT_TEST(VOwnerPolTests);

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

IVUnitTest::VTestResult VOwnerPolTests::ExecuteTest()
{
	VExclusiveOwnerPol< VPointerStorage<VDestructTest> > owner, owner2;

	static vbool bAlive;

	VDestructTest* pBlah = new VDestructTest(bAlive);

	// get und set testen
	owner.Set(pBlah);

	if( owner.Get() != pBlah ) 
	{
		return VError;
	}

	owner.Set(0);

	if( bAlive == true ) 
	{
		return VError;
	}

	owner.Set(new VDestructTest(bAlive));
	owner2.Clone(owner);

	if( ! bAlive )
	{
		return VError;
	}

	owner2.Release();

	if( bAlive )
	{
		return VError;
	}

	return VOk;
}
