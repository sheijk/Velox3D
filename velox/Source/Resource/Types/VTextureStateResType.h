#ifndef V3D_VTEXTURESTATERESTYPE_2004_11_06_H
#define V3D_VTEXTURESTATERESTYPE_2004_11_06_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Image/VImage.h>
#include <V3d/Resource.h>
#include "../../Graphics/OpenGL/VTextureState.h"

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
	typedef std::map<resource::VTypeId, GLenum> TextureTargetMap;

	std::vector<resource::VTypeId> m_ManagedTypes;
	TextureTargetMap m_TextureTargets;

	GLenum GetTextureTarget(resource::VTypeId in_Type) const;
public:
	VTextureStateResType();
	virtual ~VTextureStateResType();

	virtual VRangeIterator<resource::VTypeId> CreatedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		resource::VTypeId in_Type);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATERESTYPE_2004_11_06_H
