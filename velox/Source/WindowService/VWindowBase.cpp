/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VWindowBase.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------

