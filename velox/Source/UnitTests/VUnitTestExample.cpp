#include "VUnitTestExample.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

//TODO: write documentation for VUnitTestExample

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

VUnitTestExample::VUnitTestExample()
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

VUnitTestExample::~VUnitTestExample()
{
}

void VUnitTestExample::GetTestInfo(
	VString& out_TestName, 
	VString& out_SubjectName)
{
	// set the name
	out_TestName = "UnitTest Example";

	// specifiy the subject of the whole thing
	out_SubjectName = "CPU, the weather and the whole shit";		
}

void VUnitTestExample::ExecuteTest()
{
	enum VWheather
	{
		Sun, Rain
	};

	VWheather theWeather = Sun;
	
	// bad weather, return a warning ;)
	if( Sun != theWeather )
	{
		V3D_UNITTEST_FAILURE("bad weather detected", VUnitTestException::Warning);
	}

	// cpu is broken, return an error
	if( 1 + 1 != 2 ) 
	{
		V3D_UNITTEST_FAILURE("cpu broken", VUnitTestException::CriticalError);
	}
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
