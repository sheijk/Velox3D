#ifndef V3D_VBOUNDINGMTERRAINVOLUMEPART_12_28_05
#define V3D_VBOUNDINGMTERRAINVOLUMEPART_12_28_05
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Entity/VUnconnectedPart.h>
#include <v3d/Entity.h>
#include "VBoundingMesh.h"
#include <V3d/Scene/Shapes/VTerrainPart.h>
#include "IVBoundingVolumePart.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Special creation method for the terrain part
 * @note only works at pos 0,0,0
 *
 * @author: ins
 */
class VBoundingTerrainVolumePart :public entity::VPartBaseAdapter<IVBoundingVolumePart>
{
public:
	VBoundingTerrainVolumePart();


	math::VBoundingBox* GetBoundingBox();
	math::VBoundingSphere* GetBoundingSphere();
	math::VBoundingMesh* GetBoundingMesh();
	vbool HasBoundingMesh();
	math::VPlane* GetBoundingPlane();
	
	virtual void Activate();
	virtual void Deactivate();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:

	virtual void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer);
	void Create();

	entity::VPartConnection<scene::VTerrainPart> m_pTerrainPart;

	math::VBoundingMesh m_BoundingMesh;
	vbool m_bActive;

	vint* m_pIndicesPointer; //delete

};

//-----------------------------------------------------------------------------
}
} // namespace v3d::
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::physics::VBoundingTerrainVolumePart, v3d::physics::IVBoundingVolumePart);
//-----------------------------------------------------------------------------
#endif // V3D_VBOUNDINGMTERRAINVOLUMEPART_12_28_05