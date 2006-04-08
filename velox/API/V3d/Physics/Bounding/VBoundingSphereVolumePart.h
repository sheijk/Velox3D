#ifndef V3D_VBOUNDINGSPHEREVOLUMEPART_12_28_05
#define V3D_VBOUNDINGSPHEREVOLUMEPART_12_28_05
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Math/VBoundingSphere.h>
#include <v3d/Entity/VUnconnectedPart.h>

#include "IVBoundingVolumePart.h"
//-----------------------------------------------------------------------------
namespace v3d { 
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * represents a bounding box volume part
 * @author: ins
 */
class VBoundingSphereVolumePart : public entity::VUnconnectedPartAdapter<IVBoundingVolumePart>
{
public:
	math::VBoundingBox* GetBoundingBox();
	math::VBoundingSphere* GetBoundingSphere();
	VBoundingMesh* GetBoundingMesh();
	vbool HasBoundingMesh();


	//entity related methods
	virtual void Activate();
	virtual void Deactivate();
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }


private:

	math::VBoundingSphere m_BoundingSphere;
};

//-----------------------------------------------------------------------------
} // namespace v3d::
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::VBoundingSphereVolumePart, v3d::IVBoundingVolumePart);
//-----------------------------------------------------------------------------
#endif // V3D_VBOUNDINGSPHEREVOLUMEPART_12_28_05