//TODO: insert header file name
#include "VFileStreamTest.h"
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

VFileStreamTest::VFileStreamTest()
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

VFileStreamTest::~VFileStreamTest()
{
}

void VFileStreamTest::GetTestInfo(
	VString& out_TestName, 
	VString& out_SubjectName)
{
	// set the name
	out_TestName = "FileStream Test";

	// specifiy the subject of the whole thing
	out_SubjectName = "VFileStream";		
}

//TODO: implement test
void VFileStreamTest::ExecuteTest()
{
	IVStreamFactory* pStreamFac = 0;
	IVStreamFactory::OfflineStreamPtr pFileStream;

	// create a file stream
	try 
	{
		pStreamFac = QueryObject<IVStreamFactory>("vfs.strfact");

		//TODO: makro/fkt fuer einfacheres querien von objekten?

		pFileStream = pStreamFac->CreateFileStream(
			"temp/vfilestream_tst", 
			vfs::VCreateAlways, 
			vfs::VRWAccess);

		// test it
		TestStreamRW(this, pFileStream.Get());
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
