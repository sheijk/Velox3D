#include "VContainerTests.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <v3d/Core/Container/VList.h>

#include <iostream>
//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------
using namespace std;

VContainerTests::VContainerTests()
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

VContainerTests::~VContainerTests()
{
}

void VContainerTests::GetTestInfo(
	VString& out_TestName, 
	VString& out_SubjectName)
{
	// set the name
	out_TestName = "VContainerTests";

	// specifiy the subject of the whole thing
	out_SubjectName = "VList";
}

template<typename ContainerType>
void TestContainer()
{
	typedef ContainerType Container;

	// test empty container
	Container cont;

	if( cont.begin() != cont.end() )
	{
		V3D_UNITTEST_ERROR_STATIC(
			"Empty Container " "'s begin and end "
			" iterators did not match"
			);
	}
}

void VContainerTests::ExecuteTest()
{
	TestContainer< VList<int> >();

	cout << "---------------------------------------"
			"---------------------------------------"
			<< endl;
	cout << "Executing Container Tests" << endl << endl;
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
