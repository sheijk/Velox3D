#include "VFileNameResType.h"
//-----------------------------------------------------------------------------

#include <V3d/VFS/IVFileSystem.h>

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
	m_ManagedTypes.push_back(VTypeId::Create<VFileName>());
}

/**
 * d'tor
 */
VFileNameResType::~VFileNameResType()
{
}

VRangeIterator<VTypeId> VFileNameResType::CreatedTypes()
{
	return CreateBeginIterator< std::vector<VTypeId> >(m_ManagedTypes);
}

vbool VFileNameResType::Generate(
	resource::VResource* in_pResource, 
	resource::VTypeId in_Type)
{
	V3D_ASSERT(VTypeId::Create<VFileName>() == in_Type);

	if( ! in_pResource->ContainsData<VFileName>() )
	{
		in_pResource->AddData(new VFileName(in_pResource->GetQualifiedName().c_str()));
	}

	//TODO:
	// get vfs
	// check if file exists
		// add vfilename

	return true;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
