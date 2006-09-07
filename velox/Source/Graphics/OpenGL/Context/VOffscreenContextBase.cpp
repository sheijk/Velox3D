/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VOffscreenContextBase.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/GraphicsExceptions.h>

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
* standard c'tor
*/
VOffscreenContextBase::VOffscreenContextBase(
	const VDisplaySettings& in_DisplaySettings,
	IVRenderContext* in_pParentContext)
{
	m_pParentContext = in_pParentContext;
	m_DisplaySettings = in_DisplaySettings;
}

/**
* d'tor
*/
VOffscreenContextBase::~VOffscreenContextBase()
{
}

VDisplaySettings* VOffscreenContextBase::GetDisplaySettings()
{
	return &m_DisplaySettings;
}

IVRenderContext* VOffscreenContextBase::CreateOffscreenContext(
	const VDisplaySettings* in_pDisplaySettings)
{
	return m_pParentContext->CreateOffscreenContext(in_pDisplaySettings);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

