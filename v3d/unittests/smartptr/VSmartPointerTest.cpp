// VSmartPointerTest.cpp: Implementierung der Klasse VSmartPointerTest.
//
//////////////////////////////////////////////////////////////////////

#include "VSmartPointerTest.h"

#include "VDestructTest.h"

/*
#include <Utils/SmartPtr/VSmartPointer.h>
#include <Utils/SmartPtr/VNoCheckPol.h>
#include <Utils/SmartPtr/VPointerStorage.h>
#include <Utils/SmartPtr/VExclusiveOwnerPol.h>
*/
#include <utils/smartptr/VGuards.h>

#include <strstream>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
V3D_REGISTER_UNIT_TEST(VSmartPointerTest);

VSmartPointerTest::VSmartPointerTest()
{

}

VSmartPointerTest::~VSmartPointerTest()
{

}

void VSmartPointerTest::GetTestInfo(std::string& out_TestName, std::string& out_SubjectName)
{
	out_TestName = "SmartPointer Test";
	out_SubjectName = "VSmartPointer";
}

void VSmartPointerTest::ExecuteTest()
{
	// create a simple smart pointer
	/*
	typedef VSmartPointer<
		VDestructTest, 
		VExclusiveOwnerPol< VPointerStorage<VDestructTest> >,
		VNoCheckPol<VDestructTest*>,
		VNoCheckPol<VDestructTest*>
		> OurPointer;
	*/
	typedef VPointer<VDestructTest>::AutoPtr OurPointer;

	vbool bAlive;
	VDestructTest* pDestructTest = new VDestructTest(bAlive);

	OurPointer ptr(pDestructTest);

	// test access functions
	if( pDestructTest != ptr.Get() )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSmartPointer<...>.Get(): returned wrong value",
			VError);
	}

	// test release functions
	ptr.Release();

	if( ptr.Get() != 0 ) 
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSmartPointer<..>.Release() did not free the subject",
			VError);
	}

	// test reset functions
	bAlive = true;
	ptr.Reset(new VDestructTest(bAlive));
	vbool bAlive2;
	ptr.Reset(new VDestructTest(bAlive2));

	if( true == bAlive )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSmartPointer<..>.Reset(..) did not delete the old subject",
			VError);
	}

	if( false == bAlive2 )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSmartPointer<..>.Reset(..) deleted the new subject",
			VError);
	}

	// test copy functions
	vbool bAlive3;

	VDestructTest* pDestrTest = new VDestructTest(bAlive3);

	ptr.Release();
	ptr.Reset(pDestrTest);
	OurPointer ptr2(0);

	ptr2 = ptr;

	if( ptr2.Get() != pDestrTest )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSmartPointer<..>.op=(..): destination does not own the pointer",
			VError);
	}

	if( ptr.Get() != 0 )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSmartPointer<..>.op=(..): source was not set to 0",
			VError);
	}

	// check size of smart pointer
	if( sizeof(ptr) != 8 ) 
	{
		std::strstream strm;
		strm << "sizeof(VSmartPointer<..>) is " << sizeof(ptr)
			<< " instead of 8 bytes";

		std::string str = strm.str();

		V3D_THROW_UNITTEST_ERROR(str.c_str(), VWarning);
	}

	// try to access a member function
}
