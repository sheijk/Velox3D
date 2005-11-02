#include "VTextFileResType.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VTextFileResType::VTextFileResType()
{
}

/**
 * d'tor
 */
VTextFileResType::~VTextFileResType()
{
}

VRangeIterator<VTypeInfo> VTextFileResType::CreatedTypes()
{
	static VTypeInfo textFileType = GetTypeInfo<VTextFile>();
	return CreateSingleValueIterator(&textFileType, 1);
}

VRangeIterator<VTypeInfo> VTextFileResType::ManagedTypes()
{
	return CreateEmptyIterator<VTypeInfo>();
}

vbool VTextFileResType::Generate(VResource* in_pResource, VTypeInfo in_Type)
{
	return false;
}

vbool VTextFileResType::AllowMutableAccess(const VTypeInfo& in_TypeInfo, 
	const VResource* in_Resource) const
{
	return in_TypeInfo == GetTypeInfo<VTextFile>();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
