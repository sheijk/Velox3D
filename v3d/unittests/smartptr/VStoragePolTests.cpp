// VStoragePolTests.cpp: Implementierung der Klasse VStoragePolTests.
//
//////////////////////////////////////////////////////////////////////

#include "VStoragePolTests.h"
#include <Core/VCoreLib.h>

#include <Utils/smartptr/VPointerStorage.h>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

// register test
VREGISTER_UNIT_TEST(VStoragePolTests);

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

// constructor sets flag to true, destructor to false
class VDestructTest 
{
private:
	vbool& m_bFlag;

public:
	VDestructTest(bool& io_bDestFlag) : m_bFlag(io_bDestFlag) 
	{
		m_bFlag = true;
	}
	
	~VDestructTest()
	{
		m_bFlag = false;
	}
};

VStoragePolTests::VTestResult VStoragePolTests::ExecuteTest()
{
	vbool bAlive;

	// test pointer storage policy
	VPointerStorage<VDestructTest> PointerStore;
	VDestructTest* pDestTest = new VDestructTest(bAlive);

	PointerStore.Set(pDestTest);

	if( PointerStore.Get() != pDestTest )
	{
		return VCriticalError;
	}

	if( !bAlive )
	{
		return VError;
	}

	PointerStore.Release();

	if( bAlive )
	{
		return VError;
	}

	// test array storage policy
	// TODO .. :)

	return VOk;
}
