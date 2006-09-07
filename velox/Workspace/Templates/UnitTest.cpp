/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: insert header file name
#include "/*classname*/.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

//TODO: replace /*classname*/ by your class's name

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace unittests {
//-----------------------------------------------------------------------------

/*classname*/::/*classname*/()
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

/*classname*/::~/*classname*/()
{
}

//TODO: add info
void /*classname*/::GetTestInfo(
	VString& out_TestName, 
	VString& out_SubjectName)
{
	// set the name
	out_TestName = ;

	// specifiy the subject of the whole thing
	out_SubjectName = ;		
}

//TODO: implement test
void /*classname*/::ExecuteTest()
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::unittests
//-----------------------------------------------------------------------------

