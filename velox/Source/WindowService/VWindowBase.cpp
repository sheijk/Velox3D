//TODO: insert header file name
#include "VWindowBase.h"
//-----------------------------------------------------------------------------

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
	m_Device = NULL;
	m_pInputManager = NULL;
}
//-----------------------------------------------------------------------------

VWindowBase::~VWindowBase()
{
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
