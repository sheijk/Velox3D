/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VTextFileResType.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter.h>
#include <V3d/Resource/VResource.h>
#include <V3d/Resource/Types/VFileName.h>
#include <V3d/Vfs.h>
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace vfs;

namespace {
	std::string LoadFile(const std::string& in_strVFSFileName)
	{
		IVFileSystem::FileStreamPtr pFileStream = VFileSystemPtr()->OpenFile(
			in_strVFSFileName.c_str(), VReadAccess);

		std::vector<vchar> pContent;
		pContent.resize(pFileStream->GetSize()+1);
		pFileStream->Read(&pContent[0], pFileStream->GetSize());
		pContent.back() = '\0';

		return std::string(pContent.begin(), pContent.end());
	}
}

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
	return CreatedTypes();
}

vbool VTextFileResType::Generate(VResource* in_pResource, VTypeInfo in_Type)
{
	try
	{
		VResourceDataPtr<const VFileName> fileName = in_pResource->GetData<VFileName>();
		std::string fileContent = LoadFile(fileName->AsString());

		//IVFileSystem::FileStreamPtr pFileStream = 
		//	VFileSystemPtr()->OpenFile(fileName->AsString().c_str(), VReadAccess);

		//std::auto_ptr<char> pContent(new char[pFileStream->GetSize()]);
		//pFileStream->Read(pContent.get(), pFileStream->GetSize());
		
		VTextFile* pTextFile = new VTextFile(fileContent);
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

void VTextFileResType::NotifyChange(
	const VTypeInfo& in_Type, VResource* in_pResource) 
{
	if( in_Type == GetTypeInfo<VTextFile>() &&
		in_pResource->ContainsData<VTextFile>() )
	{
		VResourceDataPtr<const VFileName> fileName = in_pResource->GetData<VFileName>();
        std::string fileContent = LoadFile(fileName->AsString());

		vout << "Updating VTextFile in " << in_pResource->GetQualifiedName()
			<< " file content: " << fileContent << vendl;

		VResourceDataPtr<VTextFile> pTextFile = in_pResource->GetMutableData<VTextFile>();
		pTextFile->SetContent(fileContent);
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------

