//TODO: insert header file name
#include "VSmartPointerTests.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <v3d/Core/SmartPtr/VGuards.h>

#include "VDestructTest.h"

#include <list>
#include <string>
//-----------------------------------------------------------------------------
using std::string;
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

//-----------------------------------------------------------------------------
template<typename SmartPtr>
void testSmartPtrInterface(SmartPtr& in_SmarPtr, const VString& in_strPtrName)
{
	Value val, val2;

	// tests assign, get and release
	in_SmartPtr.Assign(&val);

	if( in_SmartPtr.Get() != &val || !( in_SmartPtr.Get() == &val) )
	{
		V3D_UNITTEST_ERROR_STATIC(in_strPtrName + ": Assign()/Get() failure");
	}

	in_SmarPtr.Release();

	if( in_SmartPtr.Get() != 0 || !( in_SmartPtr.Get() == 0) )
	{
		V3D_UNITTEST_ERROR_STATIC(in_strPtrName + ": Release() failure");
	}
}

template<typename SmartPtr>
void testZeroInit(const VString& strPtrName)
{
	SmartPtr ptr;
	typename SmartPtr::Pointer pVal = 0;

	string str("abc");
	str += "def";

	if( ptr.Get() != pVal )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName + 
			": default c'tor did not initialize with 0");
	}
}

template<typename SmartPtr>
void testAssignment(const VString& strPtrName)
{
	typedef typename SmartPtr::Value Value;
	typedef typename SmartPtr::Pointer Pointer;

	Pointer pVal = new Value();

	SmartPtr ptr;

	ptr.Assign(pVal);

	if( ptr.Get() != pVal )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName + ": op= / get failure");
	}
}

template<typename SmartPtr>
void testDeleteOnRelease(const VString& strPtrName)
{
	vbool bCheck;
	VDestructTest* pDestTst = new VDestructTest(bCheck);
	SmartPtr ptr(pDestTst);

	ptr.Release();

	if( ptr.Get() != 0 )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName + ": Release() did not release");
	}

	if( bCheck != false )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName + 
			": Release() did not delete subject");
	}
}

template<typename SmartPtr>
void testDeleteOnNewVal(const VString& strPtrName)
{
	vbool bCheck, bDummy;
	VDestructTest* pDestTest = new VDestructTest(bCheck);
	VDestructTest* pNewVal = new VDestructTest(bDummy);

	SmartPtr ptr(pDestTest);

	ptr.Assign(pNewVal);

	if( bCheck != false )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName + 
			": did not release old target when assigning new target");
	}
}

template<typename SmartPtr>
void testDeleteOnDestructor(const VString& strPtrName)
{
	vbool bCheck;
	VDestructTest* pDestrTest = new VDestructTest(bCheck);

	{
		SmartPtr ptr(pDestrTest);
	}

	if( bCheck != false )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName + 
			": d'tor did not delete subject");
	}
}

template<typename SmartPtr>
void testEqCmp(const VString& strPtrName)
{
	typedef typename SmartPtr::Pointer Pointer;
	typedef typename SmartPtr::Value Value;

	Pointer pVal = 0;

	SmartPtr a, b;

	// test for equal smart ptrs
	a.Assign(pVal);
	b.Assign(pVal);

	if( a != b )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName + 
			": op!= returned true for equal objects");
	}

	if( !(a == b) )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName +
			": op== returned false for equal objects");
	}

	if( a.Get() != pVal || pVal != a.Get() )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName +
			": op!=(T*) returned true for 'equal' smart pointer and pointer");
	}

	if( !(a.Get() == pVal) || !(pVal == a.Get()) )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName +
			": op==(T*) returned false for 'equal' smart ptr and pointer");
	}

	// test for different smart ptrs
	b.Assign(new Value());

	if( !(a != b) || !(b != a) )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName +
			": op!= returned false for distinct objects");
	}

	if( a == b || b == a )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName +
			": op== returned true for distinct objects");
	}

	if( !(b.Get() != pVal) || !(pVal != b.Get()) )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName +	": op!=(pointer) returned"
			" false for 'distinct' pointer and smart ptr ");
	}

	if( b.Get() == pVal || pVal == b.Get() )
	{
		V3D_UNITTEST_ERROR_STATIC(strPtrName + ": op==(pointer) returned"
			" true for 'distinct' pointer and smart pointer");
	}
}

//-----------------------------------------------------------------------------

void VSmartPointerTest::TestAutoPtr()
{
	typedef VDestructTest MySubject;
	typedef VPointer<MySubject>::AutoPtr MyAutoPtr;

	const VString& ptrName("AutoPtr");

	// check if it is correcly initialized
	testZeroInit<MyAutoPtr>(ptrName);

	// test assigment op and get
	testAssignment<MyAutoPtr>(ptrName);

	// test release fct
	testDeleteOnRelease<MyAutoPtr>(ptrName);

	// test release on new value
	testDeleteOnNewVal<MyAutoPtr>(ptrName);

	// test release on destruction
	testDeleteOnDestructor<MyAutoPtr>(ptrName);

	// test eq compare (==/!=)
	testEqCmp<MyAutoPtr>(ptrName);

	// test rel compare (</>/<=/>=) - not yet implemented for smart pointers

	// test copy semantic (a = b -> b.Get() == 0)

	//TODO: more to test
}

void VSmartPointerTest::TestRefCountPtr()
{
	typedef VPointer<VDestructTest>::SharedPtr TestPtr;

	const VString& ptrName("SharedPtr");

	// check if it is correcly initialized
	testZeroInit<TestPtr>(ptrName);

	// test assigment op and get
	testAssignment<TestPtr>(ptrName);

	// test release fct
	testDeleteOnRelease<TestPtr>(ptrName);

	// test release on new value
	testDeleteOnNewVal<TestPtr>(ptrName);

	// test release on destruction
	testDeleteOnDestructor<TestPtr>(ptrName);

	// test eq compare (==/!=)
	testEqCmp<TestPtr>(ptrName);

	// test rel compare (</>/<=/>=) - not yet implemented for smart pointers

	//TODO: more to test

	// test copying

	// test ref counting
}

///**
//* Tests IVIterator and IVSTLIteratorAdaptor
//*/
//void VSmartPointerTest::TestIterator()
//{
//	int vals[] = { 1, 2, 3, 4, 5 };
//	std::list<int> intList(vals, vals + 5);
//	int i = 0;
//
//	VSTLIteratorAdaptor<std::list<int>::iterator> adaptIter(intList.begin());
//	VSTLIteratorAdaptor<std::list<int>::iterator> endIter(intList.end());
//
//	// test dereferencing, and ++ operator
//	while( adaptIter != endIter )
//	{
//		if( vals[i] != *adaptIter )
//		{
//			V3D_UNITTEST_ERROR("VSTLIteratorAdaptor returned wrong argument");
//		}
//		++i;
//		++adaptIter;
//	}
//}
//
//void VSmartPointerTest::TestAutoArray()
//{
//	const int nArraySize = 5;
//
//	vbool bAlive[nArraySize];
//	VDestructTest* pSubjects[5];
//
//	for(int i = 0; i < nArraySize; ++i)
//	{
//		pSubjects[i] = new VDestructTest(bAlive[i]);
//	}
//
//	{
//		// create
//		VArrayPtr<VDestructTest>::AutoPtr myAutoArrays;
//
//		myAutoArrays = pSubjects[0];		
//
//		// access element
//		VDestructTest& tmp = myAutoArrays[2];
//	}
//
//	// check if all deleted
//	if( bAlive[0] )
//	{
//		V3D_UNITTEST_FAILURE(
//			"VArray<T>::AutoPtr did not release it's targets",
//			VUnitTestException::Error);		
//	}
//
//	for(int i = 1; i < nArraySize; ++i)
//	{
//		if( bAlive[i] )
//		{
//			V3D_UNITTEST_FAILURE(
//				"VArrayPtr<T>::AutoPtr did not release all it's elements",
//				VUnitTestException::Error);
//		}
//	}
//
//	//TODO: more tests for AutoArray, see TestAutoPtr
//}
//
///**
// * tests the iterator storage policy
// */
//void VSmartPointerTest::TestIteratorPtr()
//{
//	typedef std::list<int> IntList;
//	typedef VSTLIteratorAdaptor<IntList::iterator> IterType;
//
//	// test policy
//	VIteratorStorage<int, IVIterator<int> > theStorage;
//	int vals[] = { 0, 3, 6, 9 };
//	IntList theList(vals, vals + 4);
//
//	theStorage.Assign(new IterType(theList.begin()));
//
//	for(int i = 0; i < 4; ++i)
//	{
//		if( *(theStorage.Get()) != vals[i] )
//		{
//			V3D_UNITTEST_ERROR("IteratorStorage malfunction");
//		}
//
//		theStorage++;
//	}
//
//	// test ptr with policy
//}

//TODO: iteratoren test schreiben
//TODO: eigenen unit test fuer iteratoren
//TODO: IVIterator als StoragePolicy von VSmartPtr?
//TODO: iteratoren an STL konzepte anpassen
//TODO: iteratoren op++, op--, Proceed, MoveBack anpassen

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
