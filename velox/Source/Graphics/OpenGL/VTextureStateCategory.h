#ifndef V3D_VTEXTURESTATECATEGORY_H
#define V3D_VTEXTURESTATECATEGORY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "VTextureState.h"
#include <v3d/Graphics/IVStateCategory.h>

#include <map>

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

//-----------------------------------------------------------------------------
namespace v3d {
	// forward declaration of VImage for CreateImage function
	namespace image {
		class VImage;
	}
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * @author sheijk
 */
class VTextureStateCategory : public IVStateCategory
{
	typedef VMaterialDescription::TextureFilter TextureFilter;
	typedef VMaterialDescription::TextureWrapMode TextureWrapMode;

	typedef std::map<VMaterialDescription::ByteBufferHandle, VTextureState*> 
		TextureMap;

	VTextureState m_DefaultState;
	TextureMap m_Textures;

	VTextureState* CreateTextureState(const VMaterialDescription::TextureRef& in_Ref);
	VTextureState* GetTextureState(const VMaterialDescription::TextureRef& in_Ref);

	static vuint GetGLModeNum(const TextureWrapMode in_WrapMode);
	static vuint GetGLModeNum(const TextureFilter in_Filer);

public:
	VTextureStateCategory();

	virtual vfloat32 GetPriority() const;

	virtual const IVRenderState& GetDefault() const;

	virtual VTextureState* CreateState(const VMaterialDescription& in_Descr);
	virtual VTextureState* CreateState(const VRenderPass& in_Pass);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATECATEGORY_H
