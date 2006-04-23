#ifndef V3D_IVBOUNDINGVOLUMEPART_12_28_05
#define V3D_IVBOUNDINGVOLUMEPART_12_28_05
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Math/VBoundingSphere.h>
#include <V3d/Math/VBoundingBox.h>

#include "VBoundingMesh.h"
//-----------------------------------------------------------------------------
namespace v3d { 
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * interface for volume parts
 * @author: ins
 */
class IVBoundingVolumePart :  public entity::IVPart
{
public:

	virtual math::VBoundingSphere* GetBoundingSphere() = 0;
	virtual math::VBoundingBox* GetBoundingBox() = 0;
	virtual VBoundingMesh* GetBoundingMesh() = 0;
	virtual vbool HasBoundingMesh() = 0;
	virtual math::VPlane* GetBoundingPlane() = 0;

};

//-----------------------------------------------------------------------------
} // namespace v3d::
}
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::physics::IVBoundingVolumePart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VBOUNDINGVOLUMEPART_12_28_05
