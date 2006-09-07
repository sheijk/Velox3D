/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VMeshResourceType.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVMesh.h>
#include <V3d/Graphics/VMeshDescription.h>
#include <../Source/Graphics/OpenGL/VStreamMesh.h>
#include <../Source/Graphics/DeviceBase/VMeshBase.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
* standard c'tor
*/
VMeshResourceType::VMeshResourceType()
{
	m_ManagedTypes.push_back(GetTypeInfo<IVMesh>());
}

/**
 * d'tor
 */
VMeshResourceType::~VMeshResourceType()
{
}

VRangeIterator<VTypeInfo> VMeshResourceType::CreatedTypes()
{
	return CreateBeginIterator< std::vector<VTypeInfo> >(m_ManagedTypes);
}

vbool VMeshResourceType::Generate(
	resource::VResource* in_pResource,
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<IVMesh>() == in_Type);
	
	resource::VResourceDataPtr<const VMeshDescription> in_pMeshDescription
		= in_pResource->GetData<VMeshDescription>();

	// create mesh
	VMeshDescription descr = *in_pMeshDescription;
	VMeshBase* pMesh = new graphics::VStreamMesh(*in_pMeshDescription);

	in_pResource->AddData<IVMesh>(pMesh);

	return true;
}

void VMeshResourceType::NotifyChange(
	const VTypeInfo& in_Type, resource::VResource* in_pResource)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

