#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Utils/VAllFilter.h>
//-----------------------------------------------------------------------------
#include "VConsoleService.h"
#include "VConsoleFrame.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------

VConsoleService::VConsoleService() : IVConsoleSerivce("console.service", 0)
{
}

VConsoleService::~VConsoleService()
{
}

void VConsoleService::Write(VStringParam in_strString)
{
	m_Frame.WriteText(in_strString);
}

error::IVErrorService& VConsoleService::GetErrorService()
{
	return * QueryObject<error::IVErrorService>("error.service");
}

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
