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
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * @author sheijk
 */
class VTextureStateCategory : public IVStateCategory
{
	typedef std::map<VMaterialDescription::ByteBufferHandle, VTextureState*> 
		TextureMap;

	VTextureState m_DefaultState;
	TextureMap m_Textures;

	VTextureState* CreateTextureState(const VMaterialDescription::TextureRef& in_Ref);
	VTextureState* GetTextureState(const VMaterialDescription::TextureRef& in_Ref);

public:
	VTextureStateCategory();

	virtual vfloat32 GetPriority() const;

	virtual const IVRenderState& GetDefault() const;

	VTextureState* CreateState(const VMaterialDescription& in_Descr);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATECATEGORY_H
