/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VContainerTests.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <v3d/Core/Container/VList.h>

#include <v3d/Core/VIOStream.h>

#include <iostream>
#include <list>

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
	out_TestName = "zz VContainerTests";

	// specifiy the subject of the whole thing
	out_SubjectName = "VList";
}

template<typename ContainerType>
void TestContainer(const std::string& name)
{
	typedef ContainerType Container;

	// test empty container
	Container cont;

	if( cont.begin() != cont.end() )
	{
		V3D_UNITTEST_ERROR_STATIC(
			(name + " Empty Container " "'s begin and end "
			" iterators did not match").c_str()
			);
	}

	// add value to container
	int val = 3;
	cont.push_back(val);

	// test whether it was correctly added
	if( *cont.begin() != val )
	{
		V3D_UNITTEST_ERROR_STATIC(
			(name +
			" Container::push_back did not insert element"
			).c_str()
			);
	}

	// empty container
	cont.clear();

	if( cont.begin() != cont.end() )
	{
		V3D_UNITTEST_ERROR_STATIC(
			(name +
			" Container::clear did not clear container: "
			" begin() and end() mismatch"
			).c_str()
			);
	}

	if( cont.size() != 0 )
	{
		V3D_UNITTEST_ERROR_STATIC(
			(name +
			" Container::size() != 0 after clear()"
			).c_str()
			);
	}

	if( ! cont.empty() )
	{
		V3D_UNITTEST_ERROR_STATIC(
			(name + "::empty() does not return true after clearing the "
			"container.").c_str()
			);
	}

	// "complex" test:
	const int cnTestDataCount = 10;
	int naTestData[cnTestDataCount];

    for(int i = 0; i < cnTestDataCount; ++i)
	{
		naTestData[i] = i;
		cont.push_back(i);
	}

	// test data
	if( ! std::equal(cont.begin(), cont.end(), naTestData) )
	{
		V3D_UNITTEST_ERROR_STATIC(
			(name +
			" Filling with values and reading them back failed"
			).c_str()
			);
	}

	// test erasing: delete 3rd element
	typename Container::iterator it(cont.begin());

	advance(it, 2);

	it = cont.erase(it);

	if( *it != 3 )
	{
		V3D_UNITTEST_ERROR_STATIC(
			(name +
			"::erase did not return the correct iterator"
			).c_str()
			);
	}


	//cout << cont.size() << ": ";
	//for( Container::iterator iter = cont.begin(); iter != cont.end(); ++ iter)
	//	cout << *iter << ",";
	//cout << endl;

	// test insert
	it = cont.begin();
	advance(it, 2);

	it = cont.insert(it, 2);

	int t = *it;
	if( *it != 2 )
	{
		V3D_UNITTEST_ERROR_STATIC(
			(name+
			"::insert returned an invalid iterator"
			).c_str()
			);
	}

	//cout << cont.size() << ": ";
	//for( Container::iterator iter = cont.begin(); iter != cont.end(); ++ iter)
	//	cout << *iter << ",";
	//cout << endl;

	if( ! std::equal(cont.begin(), cont.end(), naTestData) )
	{
		V3D_UNITTEST_ERROR_STATIC(
			(name+ "::insert did not insert correctly").c_str()
			);
	}
}

void VContainerTests::ExecuteTest()
{
	// validate test correctness
	TestContainer< std::list<int> >("std::list");

	// test VList
	TestContainer< VList<int> >("v3d::VList");
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------

