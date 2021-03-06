/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
#include <V3d/Math/VVector.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

class VBody
{
public:
	typedef VSharedPtr<VOdeBody> SpOdeBody;
	typedef VSharedPtr<VGeometry> SpGeom;
    
	VBody(SpOdeBody in_pOdeBody, std::string in_sName);
	virtual ~VBody();

	void Update();
	void SetCollisionMesh();

	VStateOrientation& GetOrientation();
	VStatePosition& GetPositionState();
	SpOdeBody GetOdeBody();
	void Add(VState* in_pState);
	void Delete(VState* in_pState);
	void SetCollisionMesh(SpGeom in_Geometry);

	void SetPosition(math::VVector3f in_Position);
	void SetOrientation(math::VQuatf in_Orientation);
	void SetMass(vfloat32 in_fMass);
	void VBody::SetOrientation(math::VVector4f in_Orientation);

	void Destroy();
	bool IsValid();
	
	/**
	 * returns 0 if no mesh is set
	 * use this to remove a collision mesh with the manager
	 */
	SpGeom GetCollisionMesh();

	//returns true if the body is taking part in the simulation
	vbool IsEnabled();
	vfloat32 GetMass();
	std::string GetName();
	void SetName(std::string in_sName);
			
	void Activate();
	void Deactivate();
protected:
	VBody(const VBody&);
	VBody& operator=(const VBody&);
	
	VSharedPtr<VOdeBody> m_Body;
	VSharedPtr<VGeometry> m_CollisionMesh;

	/**
	 * States supported
	 */
	VStateOrientation m_OrientationState;
	VStatePosition m_PositionState;
	VStateListContainer m_StateListContainer;
	std::string m_sName;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBODY_05_11_04_H


