#ifndef V3D_IVRESOURCETYPE_2004_11_06_H
#define V3D_IVRESOURCETYPE_2004_11_06_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource/VResourceData.h>
#include <V3d/Resource/VResourceId.h>

#include <V3d/Core/RangeIter/VRangeIterator.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A managed resource type. Provides functionality to create resource data
 * of a specific type on request and to decide when to unload it.
 *
 * @author sheijk
 */
class IVResourceType
{
public:
	virtual VRangeIterator<VTypeId> CreatedTypes() = 0;
    virtual vbool Generate(VResource* in_pResource, VTypeId in_Type) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_IVRESOURCETYPE_2004_11_06_H
