//TODO: add file creation date to file guard
#ifndef V3D_VFILENAMERESTYPE_2005_02_25_H
#define V3D_VFILENAMERESTYPE_2005_02_25_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource/IVResourceType.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Establishes a link between the virtual file system and the resource manager
 * If a file exists in the vfs with a name which is the same as the resource
 * a VFileName will be created for it
 *
 * @author sheijk
 */
class VFileNameResType : public IVResourceType
{
	std::vector<VTypeInfo> m_ManagedTypes;
public:
	VFileNameResType();
	virtual ~VFileNameResType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VFILENAMERESTYPE_2005_02_25_H
