#ifndef V3D_VTEXTURESTATECATEGORY_H
#define V3D_VTEXTURESTATECATEGORY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "VTextureState.h"
#include <v3d/Graphics/IVStateCategory.h>

#include <map>

#include <V3d/OpenGL.h>

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
	//typedef VMaterialDescription::TextureFilter TextureFilter;
	//typedef VMaterialDescription::TextureWrapMode TextureWrapMode;

	//typedef std::map<VMaterialDescription::ByteBufferHandle, VTextureState2D*> 
		//TextureMap;

	VTextureStateUntextured m_DefaultState;
	//TextureMap m_Textures;

	VTextureState2D* Create2DState(const VState* in_pTextureState);
	IVRenderState* CreateCubeMapState(const VState* in_pTextureState);

public:
	VTextureStateCategory();

	virtual vfloat32 GetPriority() const;

	virtual const IVRenderState& GetDefault() const;

	virtual IVRenderState* CreateState(const VRenderPass& in_Pass);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATECATEGORY_H
