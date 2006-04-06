#ifndef V3D_VBOUNDINGBOXVOLUMEPART_12_28_05
#define V3D_VBOUNDINGBOXVOLUMEPART_12_28_05
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Math/VBoundingBox.h>
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
class VBoundingBoxVolumePart :  public entity::VUnconnectedPartAdapter<IVBoundingVolumePart>
{
public:

	//derived from IVBoundVolume

	
	math::VBoundingBox* GetBoundingBox();
	math::VBoundingSphere* GetBoundingSphere();
	VBoundingMesh* GetBoundingMesh();
	vbool HasBoundingMesh();


	//entity related methods
	virtual void Activate();
	virtual void Deactivate();
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:

	math::VBoundingBox m_BoundingBox;
};

//-----------------------------------------------------------------------------
} // namespace v3d::
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::VBoundingBoxVolumePart, v3d::IVBoundingVolumePart);
//-----------------------------------------------------------------------------
#endif // V3D_VBOUNDINGBOXVOLUMEPART_12_28_05
