#include "VWindowBase.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
using namespace graphics;
//-----------------------------------------------------------------------------
VStringParam VWindowBase::GetWindowName()
{
	return m_Name.c_str();
}
//-----------------------------------------------------------------------------

void VWindowBase::SetName(VStringParam in_pName)
{
	m_Name = in_pName;
}
//-----------------------------------------------------------------------------

VDisplaySettings VWindowBase::GetDisplaySettings()
{
	return m_DisplaySettings;
}

//-----------------------------------------------------------------------------

void VWindowBase::Activate()
{
}
//-----------------------------------------------------------------------------

void VWindowBase::Deactivate()
{
}
//-----------------------------------------------------------------------------

VWindowBase::VWindowBase()
{
	m_Device = 0;
	m_pInputManager = 0;
}
//-----------------------------------------------------------------------------

VWindowBase::~VWindowBase()
{
	delete m_pInputManager;
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
