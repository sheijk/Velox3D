#include <v3d/Physics/Bounding/VCollisionVisualizationPart.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3dLib/Graphics/Importer/Base/VImportedBufferDescription.h>
#include <V3dLib/Graphics/Geometry.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::entity;
using namespace v3d::utils;
using namespace resource;
using namespace v3d::graphics;

VCollisionVisualizationPart::VCollisionVisualizationPart() :
	VMeshPartBase(IVDevice::GetDefaultMaterial()),
	m_pVolumePart(entity::VPartDependency::Neighbour, RegisterTo())
{
	m_bCreated = false;
}

//VBoundingMesh* VCollisionVisualizationPart::GetBoundingMesh()
//{
//	return &m_BoundingMesh;
//}

void VCollisionVisualizationPart::Activate()
{
	VMeshPartBase::Activate();

	if( m_pVolumePart.Get() == 0 )
		V3D_THROW(entity::VMissingPartException, "missing terrain volume part 'data'");
	if( !m_bCreated )
		Create();

}

void VCollisionVisualizationPart::Deactivate()
{
	VMeshPartBase::Deactivate();
}

void VCollisionVisualizationPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	glColor3f(0,0,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	in_Device.RenderMesh(&*m_hMesh);
}

void VCollisionVisualizationPart::Create()
{
	if( m_pVolumePart->HasBoundingMesh() )
	{
		VBoundingMesh mesh = * m_pVolumePart->GetBoundingMesh();
		VImportedBufferDescription description(
			mesh.GetVertexCount(),
			mesh.GetIndexCount());
		description.SetVertexArray(mesh.GetVertices());
		description.SetIndexArray(mesh.GetIndices());
		description.CreateBuffer();

		VResourceId res = VResourceManagerPtr()->CreateRandomNamedResource("terrain");

		VVertexFormat format(
			VVertexFormat::Coordinates , mesh.GetVertexCount(), 0);

		VVertexBuffer* pVertexBuffer = new VVertexBuffer(format);
		res->AddData(pVertexBuffer);
		m_hVertexBuffer = res->GetMutableData<VVertexBuffer>();
		for(vuint i = 0 ; i<mesh.GetVertexCount(); i++)
		{
			VVector3f vec(mesh.GetVertices()[i*3], mesh.GetVertices()[i*3+1],
				mesh.GetVertices()[i*3+2]);
			m_hVertexBuffer->SetCoordinate(vec, i);
		}


		VVertexFormat indexFormat(VVertexFormat::Indices, 0, mesh.GetIndexCount());
		VVertexBuffer* pIndexBuffer = new VVertexBuffer(indexFormat);
		VResourceId indexRes = res->AddSubResource("indices");
		indexRes->AddData(pIndexBuffer);
		m_hIndexBuffer = indexRes->GetMutableData<VVertexBuffer>();
		for(vuint i = 0 ; i<mesh.GetIndexCount(); i++)
		{
			m_hIndexBuffer->SetIndex(mesh.GetIndices()[i], i);
		}

		VMeshDescription* pMeshDescription = new VMeshDescription(VVertexFormat(
			VVertexFormat::Coordinates | VVertexFormat::Indices, 
			mesh.GetVertexCount(), 
			mesh.GetIndexCount()));

		pMeshDescription->SetGeometryType(VMeshDescription::Triangles);
		pMeshDescription->SetCoordinateResource(res->GetQualifiedName());
		pMeshDescription->SetCoordinateFormat(format.GetCoordinateFormat());
		//pMeshDescription->SetTexCoordFormat(0, format.GetTexCoordFormat(0));
		//pMeshDescription->SetTexCoordResource(0, res->GetQualifiedName());
		pMeshDescription->SetIndexResource(indexRes->GetQualifiedName());
		pMeshDescription->SetIndexFormat(indexFormat.GetIndexFormat());
//		pMeshDescription->SetNormalFormat(format.GetNormalFormat());
//		pMeshDescription->SetNormalResource(res->GetQualifiedName());
		res->AddData(pMeshDescription);
		m_hMesh = res->GetData<IVMesh>();

		m_bCreated = true;

	}
	else
	{
		V3D_THROW(VException, "no bounding volume mesh");
	}
}

void VCollisionVisualizationPart::OnMessage(
										const messaging::VMessage& in_Message,
										messaging::VMessage* in_pAnswer)
{
	//using std::string;

	//if( ! in_Message.HasProperty("type") )
	//	return;

	//const string request = in_Message.GetAs<string>("type");

	//if( request == "getSettings" )
	//{
	//	if( in_pAnswer != 0 )
	//	{
	//		in_pAnswer->AddProperty("VertexCount",  m_BoundingMesh.GetVertexCount());
	//		in_pAnswer->AddProperty("VertexStride",  m_BoundingMesh.GetVertexStride());
	//		in_pAnswer->AddProperty("IndexCount", m_BoundingMesh.GetIndexCount());
	//		in_pAnswer->AddProperty("IndexStride", m_BoundingMesh.GetIndexStride());
	//		in_pAnswer->AddProperty("NormalCount",  m_BoundingMesh.GetNormalCount());
	//		in_pAnswer->AddProperty("NormalStride",  m_BoundingMesh.GetNormalStride());
	//	}
	//}
}

void VCollisionVisualizationPart::Update(vfloat32 in_fSeconds)
{
	;
}

V3D_REGISTER_PART_PARSER(VCollisionVisualizationPart);
//-----------------------------------------------------------------------------
} // namespace v3d::
}
//-----------------------------------------------------------------------------
