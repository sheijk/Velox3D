// VSmartPointerTest.cpp: Implementierung der Klasse VSmartPointerTest.
//
//////////////////////////////////////////////////////////////////////

#include "VSmartPointerTest.h"

#include "VDestructTest.h"

#include <Utils/SmartPtr/VSmartPointer.h>
#include <Utils/SmartPtr/VNoCheckPol.h>
#include <Utils/SmartPtr/VPointerStorage.h>
#include <Utils/SmartPtr/VExclusiveOwnerPol.h>

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
	typedef VSmartPointer<
		VDestructTest, 
		VExclusiveOwnerPol< VPointerStorage<VDestructTest> >,
		VNoCheckPol<VDestructTest>,
		VNoCheckPol<VDestructTest>
		> OurPointer;

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

	// test reset functions

	// test release functions

	// test copy functions

	// try to access a member function
}
