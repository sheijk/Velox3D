#include "VMemoryStreamTest.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <v3d/VFS/IVStreamFactory.h>

#include "StreamTests.h"
//-----------------------------------------------------------------------------
using namespace v3d::vfs;

namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

VMemoryStreamTest::VMemoryStreamTest()
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

VMemoryStreamTest::~VMemoryStreamTest()
{
}

//TODO: add info
void VMemoryStreamTest::GetTestInfo(
	VString& out_TestName, 
	VString& out_SubjectName)
{
	// set the name
	out_TestName = "VMemoryStreamTest";

	// specifiy the subject of the whole thing
	out_SubjectName = "VMemoryStream";		
}

void VMemoryStreamTest::ExecuteTest()
{
	try
	{
		// create a memory stream
        IVStreamFactory* 
			pStreamFac = QueryObject<IVStreamFactory>("vfs.strfact");

		IVStreamFactory::OfflineStreamPtr pMemStream
			= pStreamFac->CreateMemoryStream();

		// test basic functionality
		TestStreamRW(this, pMemStream.Get());

		//TODO: do more tests
	}
	catch(VException e)
	{
		throw VUnitTestException(
			e.GetErrorString(), e.GetErrorFile(), e.GetErrorLine(),
			this, VUnitTestException::CriticalError);
	}
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
