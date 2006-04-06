#include <v3d/Physics/Bounding/VBoundingMeshVolumePart.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
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
//-----------------------------------------------------------------------------
} // namespace v3d::
//-----------------------------------------------------------------------------
