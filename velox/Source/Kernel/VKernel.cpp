#include "VKernel.h"
//-----------------------------------------------------------------------------
// workaround, weil GeObject in windows.h als GetObjectA redefiniert wird..
#undef GetObject 
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VGuards.h>
#include <V3d/Core/VException.h>
#include <V3d/Core/IVApplication.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/Core/Modules/VModuleBase.h>
#include "VKernelIniReader.h"

#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using std::string;

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
	Shutdown();
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

	// if there is a local module, initialize it
	try
	{
		v3d::VModuleBase::GetInstance()->Initialize();
	}
	catch(VModuleLoadFailure&)
	{}

	vout << "Dumping registered objects:" << vendl;
	vout << "-------------------------------------------------------" << vendl;
	vout << VObjectRegistry::GetInstance()->GetObjectDump();
	vout << "-------------------------------------------------------" << vendl;
	vout << "Dumping registered objects done" << vendl;
	vout << "-------------------------------------------------------" << vendl;

	// delegate control to app service
	DelegateControl();

	// deinitialize local instance if it exists
	try
	{
		v3d::VModuleBase::GetInstance()->Shutdown();
	}
	catch(VModuleLoadFailure&)
	{}
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
		ServicePointer(new VServiceProxy("XMLServiceDLL.dll")));
	ServicePointer XmlServiceProxy = m_Services.back();
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
	m_XmlService->Visit(IniReader, in_strFileName.c_str());

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
		VServiceProxy& service(**serviceIter);

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

		vout << "Return value of main service: " << ret << "\n";
	}
	else
	{
		vout << "Error: \"main\" service could not be found\n";
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
