#include "VKernel.h"
//-----------------------------------------------------------------------------
// workaround, weil GeObject in windows.h als GetObjectA redefiniert wird..
#undef GetObject 
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/smartptr/VGuards.h>
#include <v3d/Core/VException.h>
#include <v3d/Core/IVApplication.h>
//#include <v3d/ExampleService/IVExampleService.h>
#include "VKernelIniReader.h"

#include <iostream>

//-----------------------------------------------------------------------------
using std::string;
using std::cout;
using std::endl;

//using v3d::example::IVExampleService;

using namespace v3d::xml;

namespace v3d {
namespace kernel {
//-----------------------------------------------------------------------------

VKernel::VKernel()
{
	m_XmlService = NULL;
}

VKernel::~VKernel()
{
}

/**
 * loads the ini file and parses it's content. services will
 * be loaded and control will be given to the app service
 */
void VKernel::ProcessIniFile(std::string in_strFileName)
{
	// create the object registry
	CreateObjectRegistry();

	// parse file
	ParseFile(in_strFileName);

	// generate init sequence
	GenerateInitSequence();

	// load and init services
	LoadServices();

	cout << endl << endl << VObjectRegistry::GetInstance()->GetObjectDump() << endl;

	// delegate control to app service
	DelegateControl();
}

struct VServiceInfo
{
	string strId;
	string strDesc;
	string strFileName;
};

/**
* Push the xml service into the list an immedeatly  load it
*/
void VKernel::LoadXMLService()
{
	m_Services.push_back(
		ServicePointer(new VServiceProxy("XMLService.dll")));
	ServicePointer XmlServiceProxy = m_Services.front();
	XmlServiceProxy->Initialize(VObjectRegistry::GetInstance());

	m_XmlService = QueryObject<IVXMLService>("xml.service");

}

/**
 * Creates the single instance of the object registry
 */
void VKernel::CreateObjectRegistry()
{
	VObjectRegistry::SetInstance(VObjectRegistry::CreateInstance());
}

/**
 * Parses the xml file and creates a list of service info entries
 */
void VKernel::ParseFile(const string &in_strFileName)
{
	m_Services.clear();

	LoadXMLService();

	VKernelIniReader IniReader(&m_Services);
	m_XmlService->ParseXMLFile(in_strFileName.c_str(), &IniReader);

	m_strAppName = IniReader.GetAppName();
}

/**
 * Does nothing so far
 */
void VKernel::GenerateInitSequence()
{
	// get dependencies for all DLLs
	// sort
}

void VKernel::LoadServices()
{
	// intialize services
	ServiceList::iterator serviceIter = m_Services.begin();

	// load all services
	for( ; serviceIter != m_Services.end(); ++serviceIter )
	{
		(*serviceIter)->Initialize(VObjectRegistry::GetInstance());
	}

	// load the application
	//m_App->Initialize(VObjectRegistry::GetInstance());
}

void VKernel::DelegateControl()
{
	// get application service
	VObjectKey key(m_strAppName.c_str());
	IVApplication* pApp = QueryObject<IVApplication>(key);

	// start it
	if( 0 != pApp )
	{
		int ret = pApp->Main();

		cout << "Return value of main service: " << ret << endl;
	}
	else
	{
		cout << "Error: \"main\" service could not be found" << endl;
	}
}

void VKernel::Shutdown()
{
	// deinitialize app
	//m_App->Shutdown();	

	// deinitialize all services
	ServiceList::iterator serviceIter = m_Services.begin();

	for( ; serviceIter != m_Services.end(); ++serviceIter )
	{
		(*serviceIter)->Shutdown();
	}
}

//-----------------------------------------------------------------------------
} // namespace kernel
} // namespace v3d
//-----------------------------------------------------------------------------