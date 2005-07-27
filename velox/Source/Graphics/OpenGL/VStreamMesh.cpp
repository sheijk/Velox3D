#include "VStreamMesh.h"
//-----------------------------------------------------------------------------
#include "VOpenGLUtils.h"

#include <V3dLib/Graphics/Geometry.h>

// to display normals
#ifdef V3D_DEBUG
#include <V3dLib/Property/VPropertyManager.h>
namespace {
	const VStringParam NORMAL_PROPERTY_FLAG = "v3d.graphics.showNormals";
}
#endif
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
	//std::vector<IVMaterial*> in_Materials,
	const VMeshDescription& in_MeshDescription
	) :
	//VMeshBase(in_Materials),
	m_nPrimitiveCount(in_MeshDescription.GetCoordinateFormat().GetCount()),
	m_PrimitiveType(GetGeometryMode(in_MeshDescription.GetGeometryType())),
	m_pIndexStream(0), m_nIndexOffset(0)
{
	//TODO: check if mesh descr format matches vertex buffer format

	// create data streams
	AddVertexBuffer(in_MeshDescription.GetCoordinateResource(), 
		VVertexFormat::Coordinates);
	AddVertexBuffer(in_MeshDescription.GetNormalResource(),
		VVertexFormat::Normals);
	AddVertexBuffer(in_MeshDescription.GetColorResource(),
		VVertexFormat::Colors);

	for(vuint texCoordId = 0; 
		texCoordId < in_MeshDescription.GetTexCoordCount();
		++texCoordId)
	{
		AddVertexBuffer(in_MeshDescription.GetTexCoordResource(texCoordId),
			VVertexFormat::TexCoords);
	}

	if( in_MeshDescription.GetIndexResource() != "" )
	{
		VResourceId pIndexResource = VResourceManagerPtr()->GetResourceByName(
			in_MeshDescription.GetIndexResource().c_str());
		m_pIndexStream.reset(new StreamRes(pIndexResource->GetData<IVVertexStream>()));

		m_nPrimitiveCount = in_MeshDescription.GetIndexFormat().GetCount();

		//TODO: hacked in indexoffset --ins
		m_nIndexOffset = in_MeshDescription.GetIndexFormat().GetFirstIndex();


	}

	if( in_MeshDescription.GetCoordinateResource() != "" )
	{
		m_CoordBuffer = VResourceManagerPtr()->GetResourceByName(
			in_MeshDescription.GetCoordinateResource().c_str())->GetData<VVertexBuffer>();
	}
	if( in_MeshDescription.GetNormalResource() != "" )
	{
		m_NormalBuffer = VResourceManagerPtr()->GetResourceByName(
			in_MeshDescription.GetNormalResource().c_str())->GetData<VVertexBuffer>();

		m_bShowNormal = true;
	}
	else
		m_bShowNormal = false;

#ifdef V3D_DEBUG
	// access property one time to assure it exists
	try
	{
		property::GetProperty<vbool>(NORMAL_PROPERTY_FLAG);
	}
	catch(property::VPropertyNotFoundException&)
	{
		property::SetProperty(NORMAL_PROPERTY_FLAG, false);
	}
#endif
}

/**
 * d'tor
 */
VStreamMesh::~VStreamMesh()
{
}

void VStreamMesh::AddVertexBuffer(
	std::string in_strResourceName, 
	VVertexFormat::DataTypes in_Types)
{
	if( in_strResourceName != "" )
	{
		VResourceId pResource = VResourceManagerPtr()->GetResourceByName(
			in_strResourceName.c_str());
		StreamRes pVertexStream = pResource->GetData<IVVertexStream>();

		BufferInfo info;
		info.pStream = pVertexStream;
		info.dataTypeFlag = in_Types;

		m_Streams.push_back(info);
	}
}

void VStreamMesh::Render() const
{
	// bind all streams
	for(vuint i = 0; i < m_Streams.size(); ++i)
	{
		const BufferInfo& current(m_Streams[i]);
		m_Streams[i].pStream->Bind(m_Streams[i].dataTypeFlag);
	}

	// send vertices
	//TODO: handle index meshes
	if( m_pIndexStream.get() != 0 )
	{
		//TODO: hacked in indexoffset --ins
		const void* pIndexAddress = (*m_pIndexStream)->GetIndexAddress();
			//+ sizeof(vuint) * m_nIndexOffset;

		const vuint* pNewIndexAddress = reinterpret_cast<const vuint*>(pIndexAddress)
			+ m_nIndexOffset;
		
		
		glDrawElements(
			m_PrimitiveType, m_nPrimitiveCount, 
			GL_UNSIGNED_INT, 
			pNewIndexAddress);
	}
	else
	{
		glDrawArrays(m_PrimitiveType, 0, m_nPrimitiveCount);
	}

#ifdef V3D_DEBUG
	// show normals
	if( m_bShowNormal && property::GetProperty<vbool>(NORMAL_PROPERTY_FLAG) )
	{
		glBegin(GL_LINES);
		const vuint vertexCount = m_CoordBuffer->GetFormat().GetCoordinateFormat().GetCount();
		for(vuint v = 0; v < vertexCount; ++v)
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			VVertex3f pos = m_CoordBuffer->GetCoordinate(v);
			VNormal3f normal = m_NormalBuffer->GetNormal(v);
			glVertex3d(pos.x, pos.y, pos.z);
			//glVertex3d(pos.x + pos.x, pos.y + pos.y, pos.z + pos.z);
			glVertex3d(pos.x + normal.x, pos.y + normal.y, pos.z + normal.z);
		}
		glEnd();
	}
#endif

	// unbind all streams
	for(vuint i = 0; i < m_Streams.size(); ++i)
	{
		m_Streams[i].pStream->UnbindAll();
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
