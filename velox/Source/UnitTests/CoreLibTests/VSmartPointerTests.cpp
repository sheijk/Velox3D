//TODO: insert header file name
#include "VSmartPointerTests.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include "VDestructTest.h"

#include <v3d/Core/NewSmartPtr/VSmartPtr.h>
#include <v3d/Core/NewSmartPtr/VExclusiveOwnerPol.h>
#include <v3d/Core/NewSmartPtr/VPointerStorage.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

VSmartPointerTest::VSmartPointerTest()
{
	IVTestManager* pTestManager = 0;

	// register unit test
	pTestManager = QueryObject<IVTestManager>("testmngr");

	if( ! pTestManager ) 
	{
		V3D_THROW(VException, "test manager could not be found");
	}

	pTestManager->AddCommonTest(this);
}

VSmartPointerTest::~VSmartPointerTest()
{
}

//TODO: add info
void VSmartPointerTest::GetTestInfo(
	VString& out_TestName, 
	VString& out_SubjectName)
{
	// set the name
	out_TestName = "VSmartPointerTest";

	// specifiy the subject of the whole thing
	out_SubjectName = "SmartPtr";
}

//TODO: implement test
void VSmartPointerTest::ExecuteTest()
{
	TestAutoPtr();
	TestRefCountPtr();
}


void VSmartPointerTest::TestAutoPtr()
{
	typedef VDestructTest MySubject;

	typedef VPointer<MySubject>::AutoPtr MyAutoPtr;

	// create an auto ptr
	MyAutoPtr myPtr;
	MySubject* pSubject;

	// check if it is correcly initialized
	if( myPtr.Get() != 0 )
	{
		V3D_THROW_UNITTEST_ERROR("VSmartPtr, AutoPtr did not init with 0",
			VUnitTestException::Error);
	}

	// test release fct
	vbool bCheck1;
	pSubject = new MySubject(bCheck1);

	myPtr.Assign(pSubject);
	myPtr.Release();

	if( bCheck1 != false )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSmartPtr, AutoPtr did not delete object on Release()",
			VUnitTestException::Error);
	}

	// test release on new value
	vbool bCheck2;
	pSubject = new MySubject(bCheck2);
	
	myPtr = pSubject;
	myPtr = 0;

	if( bCheck1 != false )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSmartPtr, AutoPtr did not delete object when assigning new target",
			VUnitTestException::Error);
	}

	// test release on destruction
	vbool bCheck3;
	pSubject = new MySubject(bCheck3);

	{
		MyAutoPtr ptr;
		ptr = pSubject;
	}

	if( bCheck1 != false )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VSmartPtr, AutoPtr did not delete object on d'tor",
			VUnitTestException::Error);
	}

	//TODO: more to test
		
}

void VSmartPointerTest::TestRefCountPtr()
{
	typedef VDestructTest MySubject;
	typedef VPointer<MySubject>::SharedPtr MySharedPtr;

	// test basic functionality:
	vbool bAlive;
	MySubject* pSubject = new VDestructTest(bAlive);
	MySharedPtr myPtr;

	// assign, retrieve
	// release
	// cloning

	// test operators:
	
	// compare ==, !=
	// assignment

	// test c'tors and d'tor:
	// standard c'tor
	// copy c'tor
	// conversion c'tor from ptr
	// check scope / auto release / d'tor
}

void VSmartPointerTest::TestAutoArray()
{
	const int nArraySize = 5;

	vbool bAlive[nArraySize];
	VDestructTest* pSubjects[5];

	for(int i = 0; i < nArraySize; ++i)
	{
		pSubjects[i] = new VDestructTest(bAlive[i]);
	}

	{
		// create
		VArray<VDestructTest>::AutoPtr myAutoArrays;

		myAutoArrays = pSubjects[0];		

		// access element
		VDestructTest& tmp = myAutoArrays[2];
	}

	// check if all deleted
	if( bAlive[0] )
	{
		V3D_THROW_UNITTEST_ERROR(
			"VArray<T>::AutoPtr did not release it's targets",
			VUnitTestException::Error);		
	}

	for(int i = 1; i < nArraySize; ++i)
	{
		if( bAlive[i] )
		{
			V3D_THROW_UNITTEST_ERROR(
				"VArray<T>::AutoPtr did not release all it's elements",
				VUnitTestException::Error);
		}
	}

	//TODO: more tests, see TestAutoPtr
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
