#ifndef V3D_XMLTEST_H
#define V3D_XMLTEST_H
//-----------------------------------------------------------------------------
#include <v3d/UnitTests/IVUnitTest.h>
#include <V3d/XML/IVXMLWriter.h>
#include <V3d/Core/Wrappers/VString.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace unittests{
//-----------------------------------------------------------------------------
class VXMLTest : public IVUnitTest
{
	public:
		
		VXMLTest();
			
		void VXMLTest::GetTestInfo(VString& out_TestName, 
									  VString& out_SubjectName);
	
		//TODO: implement test
		void VXMLTest::ExecuteTest();


};
//-----------------------------------------------------------------------------
} // v3d
} // unittests


#endif V3D_XMLTEST_H