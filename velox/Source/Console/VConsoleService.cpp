#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Utils/VAllFilter.h>
//-----------------------------------------------------------------------------
#include "VConsoleService.h"
#include "VConsoleFrame.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------

VConsoleService::VConsoleService() : IVConsoleService("console.service", 0)
{
	//Do not delete wx will do that
	m_pFrame = new VConsoleFrame();
}

VConsoleService::~VConsoleService()
{
}

void VConsoleService::Write(VStringParam in_strString)
{
	m_pFrame->WriteText(in_strString);
}

error::IVErrorService& VConsoleService::GetErrorService()
{
	return * QueryObject<error::IVErrorService>("error.service");
}

IVConsoleService::CommandConnection 
VConsoleService::RegisterCommandListener(const CommandSlot& slot)
{
	// register to frame
	return m_pFrame->RegisterCommandListener(slot);
}

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
