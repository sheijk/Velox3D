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
	ErrorService = NULL;
	ErrorService = QueryObject<error::IVErrorService>("error.service");
	
	VConsoleWindow& app = wxGetApp();
	ErrorService->RegisterListener(&app, new util::VAllFilter());
}

/**
 * d'tor
 */
VConsoleService::~VConsoleService()
{
	VConsoleWindow& app = wxGetApp();
	ErrorService->UnregisterListener(&app);
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

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
