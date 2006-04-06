#ifndef V3D_VBOUNDINGMESHVOLUMEPART_12_28_05
#define V3D_VBOUNDINGMESHVOLUMEPART_12_28_05
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Entity/VUnconnectedPart.h>

#include "VBoundingMesh.h"
#include "IVBoundingVolumePart.h"
//-----------------------------------------------------------------------------
namespace v3d { 
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * represents a bounding box volume part
 * @author: ins
 */
class VBoundingMeshVolumePart :public entity::VUnconnectedPartAdapter<IVBoundingVolumePart>
{
public:
	math::VBoundingBox* GetBoundingBox();
	math::VBoundingSphere* GetBoundingSphere();
	math::VBoundingMesh* GetBoundingMesh();
	vbool HasBoundingMesh();
	
	virtual void SetBoundingMesh(VBoundingMesh in_BoundingMesh);

	virtual void Activate();
	virtual void Deactivate();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:

	math::VBoundingMesh m_BoundingMesh;
};

//-----------------------------------------------------------------------------
} // namespace v3d::
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::VBoundingMeshVolumePart, v3d::IVBoundingVolumePart);
//-----------------------------------------------------------------------------
#endif // V3D_VBOUNDINGSPHEREVOLUMEPART_12_28_05
