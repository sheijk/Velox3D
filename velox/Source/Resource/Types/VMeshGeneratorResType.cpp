/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VMeshGeneratorResType.h"
//-----------------------------------------------------------------------------

#include <V3d/Graphics/VVertexBuffer.h>
#include <V3d/Graphics/VMeshDescription.h>
#include <V3d/Graphics/Geometry/VGeometryUtil.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::resource;

/**
 * standard c'tor
 */
VMeshGeneratorResType::VMeshGeneratorResType()
{
	//m_ManagedTypes.push_back(GetTypeInfo<VVertexBuffer>());
	m_ManagedTypes.push_back(GetTypeInfo<VMeshDescription>());
}

/**
 * d'tor
 */
VMeshGeneratorResType::~VMeshGeneratorResType()
{
}

VRangeIterator<VTypeInfo> VMeshGeneratorResType::CreatedTypes()
{
	return CreateBeginIterator(m_ManagedTypes);
}

vbool VMeshGeneratorResType::Generate(
	resource::VResource* in_pResource, VTypeInfo in_Type)
{
	if( in_pResource->ContainsData<IVMeshGenerator>() )
	{
		//if( in_Type == GetTypeInfo<VVertexBuffer>() )
		//{
		//	return GenerateVertexBuffer(in_pResource);
		//}else 
		if( in_Type == GetTypeInfo<VMeshDescription>() )
		{
			return GenerateMeshDescription(in_pResource);
		}
		else
		{
			V3D_ASSERT(false /* internal error, unexpected resource type */);
			return false;
		}
	}
	else
	{
		return false;
	}
}

vbool VMeshGeneratorResType::GenerateVertexBuffer(resource::VResource* in_pResource)
{
	//VResourceDataPtr<const IVMeshGenerator> pMeshGenerator =
	//	in_pResource->GetData<IVMeshGenerator>();

	//VVertexBuffer* pVertexBuffer = pMeshGenerator->CreateVertexBuffer();
	//in_pResource->AddData(pVertexBuffer);

	//return true;
	return false;
}

vbool VMeshGeneratorResType::GenerateMeshDescription(resource::VResource* in_pResource)
{
	VResourceDataPtr<const IVMeshGenerator> pMeshGenerator =
		in_pResource->GetData<IVMeshGenerator>();

	VVertexBuffer* pVertexBuffer = pMeshGenerator->CreateVertexBuffer();
	in_pResource->AddData(pVertexBuffer);

	VMeshDescription* pMeshDescription = CreateMeshDescription(
		pMeshGenerator->GetGeometryType(),
		*pVertexBuffer,
		in_pResource->GetQualifiedName(),
		"this be dragons");

	VVertexBuffer* pIndexBuffer = pMeshGenerator->CreateIndexBuffer();
	
	if( pIndexBuffer != 0 )
	{
		VResourceId indexRes = in_pResource->AddSubResource("indices");
		indexRes->AddData(pIndexBuffer);
		pMeshDescription->SetIndexFormat(pIndexBuffer->GetFormat().GetIndexFormat());
		pMeshDescription->SetIndexResource(indexRes->GetQualifiedName());
	}

	in_pResource->AddData(pMeshDescription);

	return true;
}

void VMeshGeneratorResType::NotifyChange(
	const VTypeInfo& in_Type, resource::VResource* in_pResource)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

