#include "VUnitTestExample.h"
//-----------------------------------------------------------------------------

//TODO: write documentation for VUnitTestExample

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

// this is important: create one static global instance of your UnitTest
// or the test will never be executed
V3D_REGISTER_UNIT_TEST(VUnitTestExample);

VUnitTestExample::VUnitTestExample()
{
}

VUnitTestExample::~VUnitTestExample()
{
}

void VUnitTestExample::GetTestInfo(std::string& out_TestName, std::string& out_SubjectName)
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
		VSun, VRain
	};

	VWheather theWeather = VSun;
	
	// bad weather, return a warning ;)
	if( VSun != theWeather )
	{
		V3D_THROW_UNITTEST_ERROR("bad weather detected", IVUnitTest::VWarning);
	}

	// cpu is broken, return an error
	if( 1 + 1 != 2 ) 
	{
		V3D_THROW_UNITTEST_ERROR("cpu broken", IVUnitTest::VCriticalError);
	}
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
