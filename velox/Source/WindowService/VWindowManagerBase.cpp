/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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

