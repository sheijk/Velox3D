#ifndef V3D_VTEXTURESTATE_H
#define V3D_VTEXTURESTATE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VTypeInfo.h>

#include "IVOpenGLRenderState.h"

#include <V3d/OpenGL.h>
#include <V3d/Graphics/IVTexture.h>
#include <V3d/Resource/VResourceDataPtr.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * @author sheijk
 */
class VTextureState : public IVOpenGLRenderState
{
public:
	VTextureState(IVTexture* in_pTexture);
	VTextureState(resource::VResourceDataPtr<const IVTexture> in_pTexture);

	virtual void Apply() const;
	virtual IVStateCategory* GetCategory() const;

	static void SetCategory(IVStateCategory* in_pStateCategory);

private: 
//TODO: removed for VCGFXMaterial, put back in once VTexture2D ist
//stored in the resource manager instead of VTextureState

	IVTexture*        m_pTexture;
	static IVTexture* m_pLastTexture;

	static IVStateCategory* m_pCategory;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d

//TODO: remove as soon as new material system stores IVTexture instead of
// VTextureState inside a resource
V3D_TYPEINFO(v3d::graphics::IVRenderState);
V3D_TYPEINFO_WITHPARENT(v3d::graphics::VTextureState, v3d::graphics::IVRenderState);

//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATE_H
