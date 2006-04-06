#ifndef V3D_VBODY_05_11_04_H
#define V3D_VBODY_05_11_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Entity.h>
#include <V3d/Physics/VOdeBody.h>
#include <V3d/Physics/VStateOrientation.h>
#include <V3d/Physics/VStatePosition.h>
#include <V3d/Physics/VGeometry.h>
#include <V3d/Physics/VStateListContainer.h>
#include <V3d/Math.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

class VBody
{
public:
		
	void Update();
	void SetCollisionMesh();

	VStateOrientation& GetOrientation();
	VStatePosition& GetPositionState();
	VBody(VOdeBody* in_pOdeBody);
	virtual ~VBody();
	VOdeBody* GetOdeBody();
	void Add(VState* in_pState);
	void Delete(VState* in_pState);
	void SetCollisionMesh(VGeometry* in_Geometry);

	void SetPosition(graphics::VVertex3f in_Position);
	void SetOrientation(math::VQuatf in_Orientation);
	
	/**
	 * returns 0 if no mesh is set
	 * use this to remove a collision mesh with the manager
	 */
	VGeometry* GetCollisionMesh();

			
protected: 

	VBody(const VBody&);
	VBody& operator=(const VBody&);
	
	VOdeBody* m_Body;
	VGeometry* m_CollisionMesh;

	/**
	 * States supported
	 */
	VStateOrientation m_OrientationState;
	VStatePosition m_PositionState;

	VStateListContainer m_StateListContainer;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBODY_05_11_04_H

