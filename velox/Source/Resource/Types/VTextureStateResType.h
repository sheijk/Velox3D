#ifndef V3D_VTEXTURESTATERESTYPE_2004_11_06_H
#define V3D_VTEXTURESTATERESTYPE_2004_11_06_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Image/VImage.h>
#include <V3d/Resource.h>
#include "../../Graphics/OpenGL/VTextureState.h"
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VTextureStateResType : public resource::IVResourceType
{
public:
	VTextureStateResType();
	virtual ~VTextureStateResType();

	virtual resource::VResourceData::TypeId GetTypeId() const;
    virtual vbool Generate(resource::VResource* in_pResource);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATERESTYPE_2004_11_06_H
