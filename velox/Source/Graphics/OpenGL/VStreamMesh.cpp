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
	m_PrimitiveType(GetGeometryMode(in_MeshDescription.GetGeometryType()))
{
	//TODO: check if mesh descr format matches vertex buffer format

	// create data streams
	AddVertexBuffer(in_MeshDescription.GetCoordinateResource(), 
		IVVertexStream::Coordinates);
	AddVertexBuffer(in_MeshDescription.GetColorResource(),
		IVVertexStream::Colors);
	AddVertexBuffer(in_MeshDescription.GetTexCoordResource(0),
		IVVertexStream::TexCoords);
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
		m_Streams[i].pStream->Bind(m_Streams[i].dataTypeFlag);
	}

	// send vertices
	//TODO: handle index meshes
	glDrawArrays(m_PrimitiveType, 0, m_nPrimitiveCount);

	// unbind all streams
	for(vuint i = 0; i < m_Streams.size(); ++i)
	{
		m_Streams[i].pStream->UnbindAll();
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
