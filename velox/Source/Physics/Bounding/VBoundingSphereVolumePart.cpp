#include <v3d/Physics/Bounding/VBoundingSphereVolumePart.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

math::VBoundingBox* VBoundingSphereVolumePart::GetBoundingBox()
{
	return 0;
}
math::VBoundingSphere* VBoundingSphereVolumePart::GetBoundingSphere()
{
	return &m_BoundingSphere;
}

VBoundingMesh* VBoundingSphereVolumePart::GetBoundingMesh()
{
	return 0;
}

vbool VBoundingSphereVolumePart::HasBoundingMesh()
{
	return false;
}

void VBoundingSphereVolumePart::Activate()
{
	;
}

void VBoundingSphereVolumePart::Deactivate()
{
	;
}



//-----------------------------------------------------------------------------
} // namespace v3d::
//-----------------------------------------------------------------------------
