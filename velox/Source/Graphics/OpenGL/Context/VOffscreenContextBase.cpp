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
