#ifndef V3D_VTEXTURESTATERESTYPE_2004_11_06_H
#define V3D_VTEXTURESTATERESTYPE_2004_11_06_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Image/VImage.h>
#include <V3d/Resource.h>
#include <V3d/Graphics/IVRenderContext.h>
#include "../../Graphics/OpenGL/VTextureState.h"
#include "../../Graphics/OpenGL/VBaseTexture.h"
#include "../../Graphics/OpenGL/VTexture2D.h"

#include <vector>
#include <map>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VTextureStateResType : public resource::IVResourceType
{
	typedef std::map<VTypeInfo, GLenum> TextureTargetMap;

	std::vector<VTypeInfo> m_ManagedTypes;
	TextureTargetMap m_TextureTargets;

	GLenum GetTextureTarget(VTypeInfo in_Type) const;
public:
	VTextureStateResType();
	virtual ~VTextureStateResType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATERESTYPE_2004_11_06_H
