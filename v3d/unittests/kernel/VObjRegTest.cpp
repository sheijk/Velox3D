#include "VObjRegTest.h"
//-----------------------------------------------------------------------
#include <kernel/objreg/VObjectRegistry.h>
#include <iostream>

using std::cout;

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

void VObjRegTest::ObjRegTest()
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

	// check whether it's key can be retrieved
	if( VObjectRegistry::GetInstance()->GetKey(*pObj).ToString() 
		!= pObj->GetKey().ToString() )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VObjectRegistry::GetKey returned wrong key for object",
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

void VObjRegTest::NameGeneratorTest()
{
	// try to create a named object
	try 
	{
		VNamedObject theObj("testobj", 0);
	} 
	catch( VObjectRegistryException exc )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VNamedObject(string, ...) could not be created", VError);
	}

	const int cnObjCount = 12;
	VNamedObject* pObjects[cnObjCount];
	VObjectKey* pKeys[cnObjCount];
	int i = 0, n = 0;

	for(i = 0; i < cnObjCount; ++i)
	{
		pKeys[i] = new VObjectKey(VObjectRegistry::GetInstance()->GenerateKey());

		// check if key already exists
		for(n = 0; n < i; ++n)
		{
			if( pKeys[i]->ToString() == pKeys[n]->ToString() )
			{
				V3D_THROW_UNITTEST_ERROR(
					"VObjectRegistry.GenerateKey returned a key already in use",
					VError);
			}
		}

		cout << pKeys[i]->ToString() << std::endl;

		try
		{
			pObjects[i] = new VNamedObject(pKeys[i]->ToString(), 0);
		}
		catch( VObjectRegistryException e )
		{
		}
	}

	for(i = 0; i < cnObjCount; ++i)
	{
		delete pKeys[i];
		delete pObjects[i];
	}
}

void VObjRegTest::ExecuteTest()
{
	NameGeneratorTest();
	ObjRegTest();
}
