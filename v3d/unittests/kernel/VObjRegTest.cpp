#include "VObjRegTest.h"
//-----------------------------------------------------------------------
#include <kernel/objreg/VObjectRegistry.h>

V3D_REGISTER_UNIT_TEST(VObjRegTest);

VObjRegTest::VObjRegTest()
{
}

VObjRegTest::~VObjRegTest()
{
}

void VObjRegTest::GetTestInfo(
	std::string& out_TestName, 
	std::string& out_SubjectName)
{
	out_TestName = "ObjRegistry Test";
	out_SubjectName = "VObjectRegistry";
}

class VDerivedNamedObject : public VNamedObject
{
public:
	VDerivedNamedObject() : VNamedObject(0)
	{
	}
};

void VObjRegTest::ExecuteTest()
{
	// create an object
	VNamedObject* pObj = new VNamedObject(0);

	// check whether it's registered
	if( & VObjectRegistry::GetInstance()->GetObject(pObj->GetKey()) != pObj )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VObjectRegistry::GetObject returned wrong value", 
			VError);
	}

	// delete it
	delete pObj;

	// check whether it's unregistered
	try
	{
		VObjectRegistry::GetInstance()->GetObject(pObj->GetKey());

		// when it comes here, no exception was thrown
		V3D_THROW_UNITTEST_ERROR(
			"VObjectRegistry::Unregister did not unregister object",
			VError);
	}
	catch(VObjectRegistryException e)
	{
	}

	VDerivedNamedObject theDerivedObj;

	// try to get the object
	if( & VObjectRegistry::GetInstance()->GetObject(theDerivedObj.GetKey())
		!= & theDerivedObj )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VObjectRegistry.GetObject failed", VError);
	}

	// try to get a pointer of the right type
	if( QueryObject<VDerivedNamedObject>(theDerivedObj.GetKey()) 
		!= & theDerivedObj )
	{
		V3D_THROW_UNITTEST_ERROR("QueryObject failed", VError);
	}

	// try to get the wrong type
	if( QueryObject<VObjRegTest>(theDerivedObj.GetKey()) != 0 )
	{
		V3D_THROW_UNITTEST_ERROR(
			"QueryObject returned illegal object", VError);
	}
}
