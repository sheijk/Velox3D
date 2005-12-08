#include "VTextFileResType.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter.h>
#include <V3d/Resource/VResource.h>
#include <V3d/Resource/Types/VFileName.h>
#include <V3d/Vfs.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace vfs;

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
	try
	{
		VResourceDataPtr<const VFileName> fileName = in_pResource->GetData<VFileName>();
		IVFileSystem::FileStreamPtr pFileStream = 
			VFileSystemPtr()->OpenFile(fileName->AsString().c_str(), VReadAccess);

		std::auto_ptr<char> pContent(new char[pFileStream->GetSize()]);
		pFileStream->Read(pContent.get(), pFileStream->GetSize());
		
		VTextFile* pTextFile = new VTextFile(pContent.get());
		in_pResource->AddData(pTextFile);

		return true;
	}
	catch(VException& e)
	{
		return false;
	}
}

vbool VTextFileResType::AllowMutableAccess(const VTypeInfo& in_TypeInfo, 
	const VResource* in_Resource) const
{
	return in_TypeInfo == GetTypeInfo<VTextFile>();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
