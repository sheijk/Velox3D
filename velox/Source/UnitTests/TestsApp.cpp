#include <V3d/Core.h>

#include "CoreLibTests/VStringTests.h"
#include "CoreLibTests/VSmartPointerTests.h"
#include "CoreLibTests/VIteratorTests.h"
#include "CoreLibTests/VContainerTests.h"

#include "VFSTests/VFileStreamTest.h"
#include "VFSTests/VMemoryStreamTest.h"
#include "VFSTests/VFileSysTest.h"

#include "XMLTests/VXMLTests.h"

#include "VTestManager.h"
#include "VTestSuite.h"
#include "VUnitTestExample.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//-----------------------------------------------------------------------------
using namespace v3d;
using namespace unittests;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// test system
VPointer<IVTestManager>::AutoPtr g_pTestManager;
VPointer<VTestSuite>::AutoPtr g_pTestSuite;

// add all tests here
VPointer<VUnitTestExample>::AutoPtr g_pExampleTest;

VPointer<VStringTests>::AutoPtr g_pStringTests;
VPointer<VSmartPointerTest>::AutoPtr g_pSmartPtrTest;
VPointer<VIteratorTests>::AutoPtr g_pIterTests;
VPointer<VContainerTests>::AutoPtr g_pContainerTests;

VPointer<VFileStreamTest>::AutoPtr g_pFileStreamTest;
VPointer<VMemoryStreamTest>::AutoPtr g_pMemStreamTest;
VPointer<VFileSysTest>::AutoPtr g_pFileSysTest;

VPointer<VXMLTest>::AutoPtr g_pXmlTest;

class VUnitTestApp : public VVeloxApp
{
public:
	void Initialize();
	void Shutdown();

	vint Main(std::vector<std::string>);
};

void VUnitTestApp::Initialize()
{
	VVeloxApp::Initialize();

	// create test manager
	g_pTestManager.Assign(new VTestManager("testmngr"));

	// create test suite
	g_pTestSuite.Assign(new VTestSuite());

	// create example test
	g_pExampleTest.Assign(new VUnitTestExample());

	// create tests and register them
	g_pStringTests.Assign(new VStringTests());
	g_pSmartPtrTest.Assign(new VSmartPointerTest());
	g_pContainerTests.Assign(new VContainerTests());
	g_pIterTests.Assign(new VIteratorTests());

	g_pFileStreamTest.Assign(new VFileStreamTest());
	g_pMemStreamTest.Assign(new VMemoryStreamTest());
	g_pFileSysTest.Assign(new VFileSysTest());

	g_pXmlTest.Assign(new VXMLTest());
}

void VUnitTestApp::Shutdown()
{
	g_pXmlTest.Release();

	g_pFileSysTest.Release();
	g_pMemStreamTest.Release();
	g_pFileStreamTest.Release();

	g_pContainerTests.Release();
	g_pIterTests.Release();
	g_pSmartPtrTest.Release();
	g_pStringTests.Release();

	g_pExampleTest.Release();

	g_pTestSuite.Release();
	g_pTestManager.Release();

	VVeloxApp::Shutdown();
}

vint VUnitTestApp::Main(std::vector<std::string>)
{
	// execute unit tests
	return g_pTestSuite->Main();
}

namespace {
	VUnitTestApp g_UnitTestApp;
}
//-----------------------------------------------------------------------------
