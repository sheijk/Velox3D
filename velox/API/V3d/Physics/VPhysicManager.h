/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VPHYSICMANAGER_2006_02_15_H
#define V3D_VPHYSICMANAGER_2006_02_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Physics/VPhysics.h>
#include <V3d/Entity.h>
#include <V3d/Updater.h>
#include <V3d/Physics/VBodyPart.h>
#include <v3d/Physics/Bounding/IVBoundingVolumePart.h>
#include <V3d/Math/VBoundingBox.h>
#include <V3d/Math/VBoundingSphere.h>
#include <V3d/Physics/VJointHinge2.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d;
class VGeometryPlane;

class VPhysicManager : updater::IVUpdateable
{
public:
	/**
	* creates the manager
	* @note do not forget to register this manager to the updater
	**/
	VPhysicManager();
    virtual ~VPhysicManager();

	//typedef VSharedPtr<VBodyPart> BodyPtr;
	typedef VSharedPtr<VBody> BodyPtr;
	typedef VSharedPtr<VJoint> JointPtr;
	typedef VSharedPtr<entity::VEntity> EntityPtr;
	typedef VSharedPtr<VGeometry> Geometry;
	typedef std::list<BodyPtr> BodyList;
	typedef std::list<VJointHinge2*> JointList;

	void Update();
	//void LinkBody(BodyPtr in_pBody1, BodyPtr in_pBody2, JointPtr in_LinkMode);
	
	/**
	 * Returns the currently registered count of objects
	 */
	vuint GetPhysicObjectCount();

	//EntityPtr CreateBox();
	
	/**
	* registers this type to the update manager
	*/
	void RegisterToUpdater();

	/**
	* unregisters this type to the update manager
	*/
	void UnregisterToUpdater();


	/**
	* Updates the world
	* @param in_fSeconds Seconds since last update
	*/
	virtual void Update(vfloat32 in_fSeconds);

	/**
	* Tells the object that the main loop has been entered
	* and it can expect calls to Update from now on.
	* Objects should register themselves to any external
	* managers
	*/
	virtual void Activate();
	virtual void Deactivate();

	/**
	 * Removes a collision mesh from the world. This does not destroy the body
	 * in_Geometry pointer will be deleted by this method
	 */
	void DeleteCollisionMesh(VGeometry* in_Geometry);

	

	// TODO: fix mass parameter to be a part
	BodyPtr Create(
		IVBoundingVolumePart* in_pBoundingPart, 
		vfloat32 in_fMass,
		std::string in_sIdentifierName);
	
	void Delete(BodyPtr in_Body);

	Geometry CreateGeom(IVBoundingVolumePart* in_pBoundingPart);
	/**
	 * Queries the manager if the in_Identifier name is available
	 * @return: returns in_Identifier if name is available else a generated name will be returned
	 */
	
	std::string QueryAvailableIdentifier(std::string in_sIdentifier);
	void RequestNameChange(std::string in_sName, VBody* in_pBody);
	VBody* QueryBodyByName(std::string in_sName);

	/**
	 * a plane cannot be attached to a body, thus we return only the object
	 */
	Geometry CreatePlane(math::VVector3f in_Normal,vfloat32 in_fDistance);
	VWorld* GetWorld();

	void RegisterJoint(VJointHinge2* in_pJoint);
	void UnregisterJoint(VJointHinge2* in_pJoint);
	void RefreshJoint(VBody* in_pBody);

private:
	vbool IsRegisteredName(std::string in_sName);
	void UpdateBodies();
	BodyPtr CreateBody(std::string in_sName);
	Geometry CreateMeshGeom(VBoundingMesh* in_pBoundingMesh);
	Geometry CreateSphereGeom(math::VBoundingSphere* in_pBoundingMesh);
	Geometry CreateBoxGeom(math::VBoundingBox* in_pBoundingMesh);
	BodyPtr CreateSphere(vfloat32 in_fMass, vfloat32 in_fRadius, std::string in_sName);
	BodyPtr CreateBox(vfloat32 in_fMass, math::VVector3f in_Expansion, std::string in_sName);
	BodyPtr CreateMesh(vfloat32 in_fMass, VBoundingMesh* in_BoundingMesh, std::string in_sName);
	
	VWorld m_World;
	//list of all created bodies for updating reasons
	BodyList m_BodyList;
	JointList m_JointList;
	const vfloat32 m_fTimeStep;
	vuint m_iAutoGeneratedCounter;
	vfloat32 m_fTimeDelta;
};

typedef VSharedPtr<VPhysicManager> VPhysicManagerPtr;

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICMANAGER_2006_02_15_H

