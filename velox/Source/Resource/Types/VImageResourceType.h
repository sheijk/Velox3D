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
	std::vector<resource::VTypeId> m_ManagedTypes;
public:
	VImageResourceType();
	virtual ~VImageResourceType();

	virtual VRangeIterator<resource::VTypeId> CreatedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		resource::VTypeId in_Type);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::image
//-----------------------------------------------------------------------------
#endif // V3D_VIMAGERESOURCETYPE_H
