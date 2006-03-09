#include "VFileNameResType.h"
//-----------------------------------------------------------------------------

#include <V3d/VFS/IVFileSystem.h>

#include <V3d/Vfs.h>
#include <V3d/Resource/Types/VFileName.h>
#include <V3d/Resource/VResource.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::vfs;

/**
 * standard c'tor
 */
VFileNameResType::VFileNameResType()
{
	m_ManagedTypes.push_back(GetTypeInfo<VFileName>());
}

/**
 * d'tor
 */
VFileNameResType::~VFileNameResType()
{
}

VRangeIterator<VTypeInfo> VFileNameResType::CreatedTypes()
{
	return CreateBeginIterator< std::vector<VTypeInfo> >(m_ManagedTypes);
}

vbool VFileNameResType::Generate(
	resource::VResource* in_pResource, 
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<VFileName>() == in_Type);

	if( ! in_pResource->ContainsData<VFileName>() )
	{
		VServicePtr<IVFileSystem> pFS;
		std::string fileName = in_pResource->GetQualifiedName();

		if( pFS->Exists(fileName.c_str()) )
		{
			in_pResource->AddData(new VFileName(fileName.c_str()));

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

void VFileNameResType::NotifyChange(
	const VTypeInfo& in_Type, resource::VResource* in_pResource)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
