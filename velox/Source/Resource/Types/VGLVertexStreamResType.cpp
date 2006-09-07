/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VGLVertexStreamResType.h"
//-----------------------------------------------------------------------------
#include "../../Graphics/OpenGL/VImmediateVertexStream.h"

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::resource;

/**
 * standard c'tor
 */
VGLVertexStreamResType::VGLVertexStreamResType()
{
	m_ManagedTypes.push_back(GetTypeInfo<IVVertexStream>());
}

/**
 * d'tor
 */
VGLVertexStreamResType::~VGLVertexStreamResType()
{
}

VRangeIterator<VTypeInfo> VGLVertexStreamResType::CreatedTypes()
{
	return CreateBeginIterator(m_ManagedTypes);
}

vbool VGLVertexStreamResType::Generate(
	resource::VResource* in_pResource,
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<IVVertexStream>() == in_Type);

	vbool success = false;

	try
	{
		// get vertex buffer
		VResourceDataPtr<const VVertexBuffer> pVB = 
			in_pResource->GetData<VVertexBuffer>();

		// create stream
		VImmediateVertexStream* pStream = new VImmediateVertexStream(pVB);

		in_pResource->AddData(pStream);

		success = true;
	}
	catch(VResourceException&)
	{}

	return success;
}

void VGLVertexStreamResType::NotifyChange(
	const VTypeInfo& in_Type, resource::VResource* in_pResource)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

