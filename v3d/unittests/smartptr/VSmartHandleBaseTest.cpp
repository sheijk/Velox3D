// VSmartHandleBaseTest.cpp: Implementierung der Klasse VSmartHandleBaseTest.
//
//////////////////////////////////////////////////////////////////////

#include "VSmartHandleBaseTest.h"

#include "VDestructTest.h"

#include <utils/smartptr/VSmartHandleBase.h>
#include <utils/smartptr/VNullCheckPol.h>
#include <utils/smartptr/VPointerStorage.h>
#include <utils/smartptr/VExclusiveOwnerPol.h>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
V3D_REGISTER_UNIT_TEST(VSmartHandleBaseTest);

VSmartHandleBaseTest::VSmartHandleBaseTest()
{
}

VSmartHandleBaseTest::~VSmartHandleBaseTest()
{
}

void VSmartHandleBaseTest::GetTestInfo(
									   std::string& out_TestName, 
									   std::string& out_SubjectName)
{
	out_TestName = "SmartHandleBase Test";
	out_SubjectName = "SmartHandleBase";
}

void VSmartHandleBaseTest::ExecuteTest()
{
	typedef VSmartHandleBase<	VDestructTest*, 
								VExclusiveOwnerPol<VPointerStorage<VDestructTest> >, 
								VNullCheckPol<VDestructTest*>, 
								VNullCheckPol<VDestructTest*> 
							> SmartHandleExclNoCheck;

	SmartHandleExclNoCheck handle;
	vbool bAlive;
	VDestructTest* pDestTest = new VDestructTest(bAlive);
	
	// test set and get methods
	handle.SetTarget(pDestTest);
	if( handle.GetTarget() != pDestTest ) 
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSmartHandleBase.Get(): returned wrong value",
			VError);
	}

	// test cloning
	SmartHandleExclNoCheck handle2;

	//todo: bei owner policies etc. immer referenzen zurueckgeben?

	// test releasing target


	// test auto target release


}
