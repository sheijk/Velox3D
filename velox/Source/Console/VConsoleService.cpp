//TODO: insert header file name
#include <v3d/Core/VObjectRegistry.h>
#include "VConsoleService.h"
#include "VConsoleWindow.h"
#include <wx/app.h>
#include <v3d/Utils/VAllFilter.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------
VConsoleWindow& wxGetApp();
/**
 * standard c'tor
 */
VConsoleService::VConsoleService() : IVConsoleSerivce("console.service", 0)
{
	VConsoleWindow& app = wxGetApp();
	GetErrorService().RegisterListener(&app, new util::VAllFilter());

	// register at the update manager
	this->Register();
}

/**
 * d'tor
 */
VConsoleService::~VConsoleService()
{
	VConsoleWindow& app = wxGetApp();
	try
	{
		GetErrorService().UnregisterListener(&app);
	}
	catch(VObjectRegistryException&)
	{
	}
}


void VConsoleService::Update()
{
	wxTheApp->MainLoop();
//	wxTheApp->ExitMainLoop();
}

void VConsoleService::Write(VStringParam in_strString)
{
	VConsoleWindow& app = wxGetApp();
	app.Write(in_strString);
}

void VConsoleService::Update(float in_fSeconds)
{
	Update();
}

void VConsoleService::Activate()
{
}

void VConsoleService::Deactivate()
{
}

error::IVErrorService& VConsoleService::GetErrorService()
{
	return * QueryObject<error::IVErrorService>("error.service");
}

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
