/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VOFFSCREENCONTEXTBASE_2005_11_04_H
#define V3D_VOFFSCREENCONTEXTBASE_2005_11_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/VDisplaySettings.h>
#include <V3d/Graphics/IVRenderContext.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VOffscreenContextBase : public IVRenderContext
{
public:
	VOffscreenContextBase(
		const VDisplaySettings& in_DisplaySettings,
		IVRenderContext* in_pParentContext);

	virtual ~VOffscreenContextBase();

	virtual void MakeCurrent() = 0;
	virtual void SwapBuffers() = 0;

	virtual void BindAsTexture(vuint in_nTextureUnit) = 0;
	virtual void UnbindTexture() = 0;

	virtual VDisplaySettings* GetDisplaySettings();
	virtual IVRenderContext* CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings);

protected:
	IVRenderContext* m_pParentContext;
	VDisplaySettings m_DisplaySettings;
};

//-----------------------------------------------------------------------------
}
} // namespace v3d::graphics
V3D_TYPEINFO_WITHPARENT(v3d::graphics::VOffscreenContextBase, v3d::graphics::IVRenderContext);
//-----------------------------------------------------------------------------
#endif // V3D_VOFFSCREENCONTEXTBASE_2005_11_04_H
