// VSharedPtrTest.cpp: Implementierung der Klasse VSharedPtrTest.
//
//////////////////////////////////////////////////////////////////////

#include "VSharedPtrTest.h"

#include <utils/smartptr/VRefCountPol.h>
#include <utils/smartptr/VRefCountSharedStorage.h>
#include <utils/smartptr/VPointerStorage.h>
#include "VDestructTest.h"

#include <memory>
using std::auto_ptr;

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

VSharedPtrTest::VSharedPtrTest()
{

}

VSharedPtrTest::~VSharedPtrTest()
{

}

void VSharedPtrTest::GetTestInfo(std::string& out_TestName, std::string& out_SubjectName)
{
	out_TestName = "VSharedPtrTest";
	out_SubjectName = "VSharedPtr, VRefCountPol, VRefCountSharedStorage";
}

void VSharedPtrTest::ExecuteTest()
{
	TestSharedStorage();
}

void VSharedPtrTest::TestSharedStorage()
{
	// test VRefCountSharedStorage
	typedef VRefCountSharedStorage< VPointerStorage<VDestructTest> > 
		SharedPtrStorage;

	vbool bAlive;
	VDestructTest* pDestrTest = new VDestructTest(bAlive);
	// will create mem leak on error (should be ok for unit tests)
	SharedPtrStorage* pSharePtrStore =
		SharedPtrStorage::CreateNew(pDestrTest);

	// test subject access
	if( pSharePtrStore->Get() != pDestrTest )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSharedPtrStorage did not return the right subject",
			VError);
	}

	// test the bookkeeping
	pSharePtrStore->AddRef();
	pSharePtrStore->AddRef();
	pSharePtrStore->Release();
	pSharePtrStore->Release();

	if( !bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"SharedPtrStorage released subject to early",
			VError);
	}

	pSharePtrStore->Release();

	if( bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSharedPtrStorage did not release subject properly",
			VError);
	}
}
