#include "VWindowManagerBase.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

VWindowManagerBase::VWindowManagerBase() : VNamedObject("window.manager", 0)
{
	m_iNumWindows = 0;
}
//-----------------------------------------------------------------------------

VWindowManagerBase::~VWindowManagerBase()
{
}
//-----------------------------------------------------------------------------

vuint VWindowManagerBase::GetNumberOfWindows()
{
	return m_iNumWindows;
	
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
