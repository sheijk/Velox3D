//TODO: add file creation date to file guard
#ifndef V3D_VIMAGERESOURCETYPE_H
#define V3D_VIMAGERESOURCETYPE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource/Types/VFileName.h>
#include <V3d/Resource.h>
#include <V3d/Image.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace image {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Automatically loads VImage's if a VFileName is present in the same resource
 *
 * @author sheijk
 */
class VImageResourceType : public resource::IVResourceType
{
public:
	VImageResourceType();
	virtual ~VImageResourceType();

	virtual resource::VResourceData::TypeId GetTypeId() const;
    virtual vbool Generate(resource::VResource* in_pResource);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::image
//-----------------------------------------------------------------------------
#endif // V3D_VIMAGERESOURCETYPE_H
