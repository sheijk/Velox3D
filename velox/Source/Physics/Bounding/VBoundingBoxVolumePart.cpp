#include <v3d/Physics/Bounding/VBoundingBoxVolumePart.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

//VBoundingBoxVolumePart::VBoundingBoxVolumePart()
//{
//	;
//}

math::VBoundingBox* VBoundingBoxVolumePart::GetBoundingBox()
{
	return &m_BoundingBox;
}
math::VBoundingSphere* VBoundingBoxVolumePart::GetBoundingSphere()
{
	return 0;
}

VBoundingMesh* VBoundingBoxVolumePart::GetBoundingMesh()
{
	return 0;
}

vbool VBoundingBoxVolumePart::HasBoundingMesh()
{
	return false;
}

void VBoundingBoxVolumePart::Activate()
{
	;
}

void VBoundingBoxVolumePart::Deactivate()
{
	;
}

//-----------------------------------------------------------------------------
} // namespace v3d::
//-----------------------------------------------------------------------------
