// UnitTestExample.cpp: Implementierung der Klasse CUnitTestExample.
//
//////////////////////////////////////////////////////////////////////

#include "VUnitTestExample.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

// this is important: create one static global instance of your UnitTest
// or the test will never be executed
VUnitTestExample g_theExampleUnitTest;

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

IVUnitTest::VTestResult VUnitTestExample::ExecuteTest()
{
	enum VWheather
	{
		VSun, VRain
	};

	// do test functions (remember to assure that no exception will "leave"
	// this function
	try
	{
		VWheather theWeather = VSun;
		
		// bad weather, return a warning ;)
		if( VSun != theWeather )
		{
			return IVUnitTest::VWarning;
		}

		// cpu is broken, return an error
		if( 1 + 1 != 2 ) 
		{
			return IVUnitTest::VError;
		}
	}
	catch(...)
	{
		// an unknown exception occured which might crash the whole system
		// indicate critical error
		return IVUnitTest::VCriticalError;
	}

	// indicates that no error occured
	return IVUnitTest::VOk;
}
