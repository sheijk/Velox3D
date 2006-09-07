/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
