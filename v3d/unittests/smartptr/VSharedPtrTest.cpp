// VSharedPtrTest.cpp: Implementierung der Klasse VSharedPtrTest.
//
//////////////////////////////////////////////////////////////////////

#include "VSharedPtrTest.h"

/*
#include <utils/smartptr/VRefCountPol.h>
#include <utils/smartptr/VRefCountSharedStorage.h>
#include <utils/smartptr/VPointerStorage.h>
#include <utils/smartptr/VSmartPointer.h>
#include <utils/smartptr/VNoCheckPol.h>
*/
#include <utils/smartptr/VGuards.h>

#include "VDestructTest.h"

#include <memory>
using std::auto_ptr;

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
V3D_REGISTER_UNIT_TEST(VSharedPtrTest);

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
	TestRefCountPol();
	TestSharedPtr();
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

void VSharedPtrTest::TestRefCountPol()
{
	typedef VRefCountPol< VPointerStorage<VDestructTest> > RefCountOwner;

	vbool bAlive;
	VDestructTest* pDestrTest = new VDestructTest(bAlive);

	if( ! bAlive ) 
	{ 
		V3D_THROW_UNITTEST_ERROR("internal error", VError); 
	}

	RefCountOwner theRefCountOwner;

	theRefCountOwner.Set(pDestrTest);

	if( theRefCountOwner.Get() != pDestrTest )
	{
		V3D_THROW_UNITTEST_ERROR(
			"RefCountPol<..>.Get() returned wrong value", VError);
	}

	theRefCountOwner.Release();

	if( bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"RefCountPol<..>.Release() did not delete the subject",
			VError);
	}

	vbool bAlive2;
	theRefCountOwner.Set(new VDestructTest(bAlive2));
	theRefCountOwner.Set(new VDestructTest(bAlive));

	if( bAlive2 )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VRefCountPol<..>.Set did not release previous subject",
			VError);
	}

	RefCountOwner theRefCountOwner2;

	vbool bAlive3, bAlive4;
	pDestrTest = new VDestructTest(bAlive3);

	theRefCountOwner.Set(pDestrTest);
	theRefCountOwner2.Set(new VDestructTest(bAlive4));
	theRefCountOwner2.Clone(theRefCountOwner);

	if( !bAlive3 )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VRefCountPol<..>.Clone deleted subject", VError);
	}

	if( bAlive4 )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VRefCountPol<..>.Clone old subject was not released",
			VError);
	}

	if( theRefCountOwner.Get() != pDestrTest )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VRefCountPol<..>.Clone source lost subject", VError);
	}

	if( theRefCountOwner2.Get() != pDestrTest )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VRefCountPol<..>.Clone target did not get subject", VError);
	}

	theRefCountOwner.Release();

	if( ! bAlive3 )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VRefCountPol<.,> released subject still referred to by other VRefCountPol",
			VError);
	}

	theRefCountOwner2.Release();

	if( bAlive3 )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VRefCountPol<..> did not released a subject after cloning",
			VError);
	}

}

void VSharedPtrTest::TestSharedPtr()
{
/*
	typedef VSmartPointer<
		VDestructTest, 
		VRefCountPol< VPointerStorage<VDestructTest> >,
		VNoCheckPol<VDestructTest*>,
		VNoCheckPol<VDestructTest*>
		> SharedTestPtr;
*/
	typedef VPointer<VDestructTest>::SharedPtr SharedTestPtr;

	vbool bAlive;
	VDestructTest* pDestrTest = new VDestructTest(bAlive);
	
	SharedTestPtr thePtr;
	const int cnPtrCount = 10;
	SharedTestPtr thePtrArray[cnPtrCount];
	int i;

	thePtr = pDestrTest;

	if( thePtr.Get() != pDestrTest )
	{
		V3D_THROW_UNITTEST_ERROR(
			"SharedPtr does not store it's subject", VError);
	}

	for(i = 0; i < cnPtrCount; ++i)
	{
		thePtrArray[i] = thePtr;
	}

	for(i = 0; i < cnPtrCount; ++i)
	{
		if( thePtrArray[i].Get() != pDestrTest )
		{
			V3D_THROW_UNITTEST_ERROR(
				"SharedPtr: could not share subject between pointers",
				VError);
		}
	}

	for(i = 0; i < cnPtrCount; ++i)
	{
		thePtrArray[i] = 0;
	}

	if( ! bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"SharedPtr: subject was destroyed while still in use",
			VError);
	}

	thePtr = 0;

	if( bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"SharedPtr did not release subject", VError);
	}

	// test if subjects will be released when last pointer is destructed
	vbool bAlive2;
	pDestrTest = new VDestructTest(bAlive2);

	{
		SharedTestPtr aTestPtr(pDestrTest);
	}

	if( bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"SharedPtr did not release subject on it's destruction",
			VError);
	}

	// more tests needed?
}
