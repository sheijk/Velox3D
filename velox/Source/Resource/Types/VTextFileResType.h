#ifndef V3D_VTEXTFILERESTYPE_2005_10_31_H
#define V3D_VTEXTFILERESTYPE_2005_10_31_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Resource/Types/VTextFile.h>
#include <V3d/Resource/IVResourceType.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VTextFileResType : public IVResourceType
{
public:
	VTextFileResType();
	virtual ~VTextFileResType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();
	virtual VRangeIterator<VTypeInfo> ManagedTypes();

	virtual vbool Generate(VResource* in_pResource, VTypeInfo in_Type);

	virtual vbool AllowMutableAccess(
		const VTypeInfo& in_TypeInfo, const VResource* in_Resource) const;

	virtual void NotifyChange(const VTypeInfo& in_Type, VResource* in_pResource);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTFILERESTYPE_2005_10_31_H
