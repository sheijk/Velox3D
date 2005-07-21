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

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
