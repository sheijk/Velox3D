#include <v3d/Physics/Bounding/VBoundingMeshVolumePart.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VBoundingMesh* VBoundingMeshVolumePart::GetBoundingMesh()
{
	return &m_BoundingMesh;
}

vbool VBoundingMeshVolumePart::HasBoundingMesh()
{
	if(m_BoundingMesh.GetVertices())
		return true;
	return false;
}

void VBoundingMeshVolumePart::SetBoundingMesh(VBoundingMesh in_BoundingMesh)
{
	m_BoundingMesh = in_BoundingMesh;
}

math::VPlane* VBoundingMeshVolumePart::GetBoundingPlane()
{
	return 0;
}

math::VBoundingBox* VBoundingMeshVolumePart::GetBoundingBox()
{
	return 0;
}

math::VBoundingSphere* VBoundingMeshVolumePart::GetBoundingSphere()
{
	return 0;
}

void VBoundingMeshVolumePart::Activate()
{
	;
}

void VBoundingMeshVolumePart::Deactivate()
{
	;
}

void VBoundingMeshVolumePart::OnMessage(
										const messaging::VMessage& in_Message,
										messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer != 0 )
		{
			in_pAnswer->AddProperty("VertexCount",  m_BoundingMesh.GetVertexCount());
			in_pAnswer->AddProperty("VertexStride",  m_BoundingMesh.GetVertexStride());
			in_pAnswer->AddProperty("IndexCount", m_BoundingMesh.GetIndexCount());
			in_pAnswer->AddProperty("IndexStride", m_BoundingMesh.GetIndexStride());
			in_pAnswer->AddProperty("NormalCount",  m_BoundingMesh.GetNormalCount());
			in_pAnswer->AddProperty("NormalStride",  m_BoundingMesh.GetNormalStride());
		}
	}
}

V3D_REGISTER_PART_PARSER(VBoundingMeshVolumePart);
//-----------------------------------------------------------------------------
} // namespace v3d::
}
//-----------------------------------------------------------------------------
