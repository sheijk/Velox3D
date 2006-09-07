/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VStringTests.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>
#include <V3d/Core/Wrappers/VString.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

//TODO: test ==, !=

VStringTests::VStringTests()
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

VStringTests::~VStringTests()
{
}

void VStringTests::GetTestInfo(
	VString& out_TestName, 
	VString& out_SubjectName)
{
	// set the name
	out_TestName = "VStringTests";

	// specifiy the subject of the whole thing
	out_SubjectName = "VString";
}

vbool StringsAreEqual(const char* p1, const char* p2)
{
	return (strcmp(p1, p2) == 0);
}

/**
 * Simplest test: assigns a string, and checks if it is stored correctly
 */
void VStringTests::AssignAndGetTest()
{
	VString subj;
	char* pTestString = "this is a teststring";

	subj.Set(pTestString);

	if( ! StringsAreEqual(subj.AsCString(), pTestString) )
	{
		V3D_UNITTEST_FAILURE(
			"VString did not store string correctly",
			VUnitTestException::CriticalError);
	}
}

/**
 * checks if copying a string works correctly
 */
void VStringTests::CopyTest()
{
	VString subj, subj2;
	char* pTestString = "another stoopid test thingy";

	subj.Set(pTestString);

	// test copy operator
	subj2 = subj;

	if( ! StringsAreEqual(pTestString, subj2.AsCString()) )
	{
		V3D_UNITTEST_FAILURE(
			"VString.op= failed", VUnitTestException::CriticalError);
	}

	// test copy c'tor
	VString subj3(subj);

	if( ! StringsAreEqual(pTestString, subj3.AsCString()) )
	{
		V3D_UNITTEST_FAILURE(
			"VString.op= failed", VUnitTestException::CriticalError);
	}

	// check if original string is still valid
	if( ! StringsAreEqual(pTestString, subj.AsCString()) )
	{
		V3D_UNITTEST_FAILURE(
			"VString.op= failed", VUnitTestException::CriticalError);
	}
}

//TODO: implement test
void VStringTests::ExecuteTest()
{
	AssignAndGetTest();
	CopyTest();
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------

