#include "VStreamMesh.h"
//-----------------------------------------------------------------------------
#include "VOpenGLUtils.h"

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
VStreamMesh::VStreamMesh(
	std::vector<IVMaterial*> in_Materials,
	const VMeshDescription& in_MeshDescription
	) :
	VMeshBase(in_Materials),
	m_nPrimitiveCount(in_MeshDescription.GetCoordinateFormat().GetCount()),
	m_PrimitiveType(GetGeometryMode(in_MeshDescription.GetGeometryType())),
	m_pIndexStream(0)
{
	//TODO: check if mesh descr format matches vertex buffer format

	// create data streams
	AddVertexBuffer(in_MeshDescription.GetCoordinateResource(), 
		IVVertexStream::Coordinates);
	AddVertexBuffer(in_MeshDescription.GetColorResource(),
		IVVertexStream::Colors);

	for(int texCoordId = 0; 
		texCoordId < in_MeshDescription.GetTexCoordCount();
		++texCoordId)
	{
		AddVertexBuffer(in_MeshDescription.GetTexCoordResource(texCoordId),
			IVVertexStream::TexCoords);
	}

	if( in_MeshDescription.GetIndexResource() != "" )
	{
		VResourceId pIndexResource = VResourceManagerPtr()->GetResourceByName(
			in_MeshDescription.GetIndexResource().c_str());
		m_pIndexStream.reset(new StreamRes(pIndexResource->GetData<VImmediateVertexStream>()));

		m_nPrimitiveCount = in_MeshDescription.GetIndexFormat().GetCount();

//#ifdef V3D_DEBUG
//		VImmediateVertexStream* pIndexStream = pIndexResource->GetData<VImmediateVertexStream>();
//		V3D_ASSERT(pIndexStream != 0);
//
//		const vuint* pIndexAddress = pIndexStream->GetIndexAddress();
//		V3D_ASSERT(pIndexAddress != 0);
//
//		// check for invalid indices
//		for(vuint index = 0; index < m_nPrimitiveCount; ++index)
//		{
//            V3D_ASSERT(pIndexAddress[index] < 
//		}
//#endif
	}
}

/**
 * d'tor
 */
VStreamMesh::~VStreamMesh()
{
}

void VStreamMesh::AddVertexBuffer(
	std::string in_strResourceName, 
	IVVertexStream::DataTypes in_Types)
{
	if( in_strResourceName != "" )
	{
		VResourceId pResource = VResourceManagerPtr()->GetResourceByName(
			in_strResourceName.c_str());
		StreamRes pVertexStream = pResource->GetData<VImmediateVertexStream>();

		BufferInfo info;
		info.pStream = pVertexStream;
		info.dataTypeFlag = in_Types;

		m_Streams.push_back(info);
	}
}

void VStreamMesh::Render()
{
	// bind all streams
	for(vuint i = 0; i < m_Streams.size(); ++i)
	{
		BufferInfo& current(m_Streams[i]);
		m_Streams[i].pStream->Bind(m_Streams[i].dataTypeFlag);
	}

	// send vertices
	//TODO: handle index meshes
	if( m_pIndexStream.get() != 0 )
	{
		const void* pIndexAddress = (*m_pIndexStream)->GetIndexAddress();

		glDrawElements(
			m_PrimitiveType, m_nPrimitiveCount, 
			GL_UNSIGNED_INT, 
			pIndexAddress);
	}
	else
	{
		glDrawArrays(m_PrimitiveType, 0, m_nPrimitiveCount);
	}

	// unbind all streams
	for(vuint i = 0; i < m_Streams.size(); ++i)
	{
		m_Streams[i].pStream->UnbindAll();
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
