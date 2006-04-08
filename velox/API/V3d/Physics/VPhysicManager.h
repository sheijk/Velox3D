#ifndef V3D_VPHYSICMANAGER_2006_02_15_H
#define V3D_VPHYSICMANAGER_2006_02_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Physics/VPhysics.h>
#include <V3d/Entity.h>
#include <V3d/Updater.h>
#include <V3d/Physics/VBodyPart.h>

#include <v3d/Physics/Bounding/IVBoundingVolumePart.h>
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

	typedef VSharedPtr<VBodyPart> BodyPtr;
	typedef VSharedPtr<VJoint> JointPtr;
	typedef VSharedPtr<entity::VEntity> EntityPtr;
	typedef VSharedPtr<VGeometryPlane> Plane;
	typedef std::list<VBodyPart*> BodyPartList;

	void Update();
	void LinkBody(BodyPtr in_pBody1, BodyPtr in_pBody2, JointPtr in_LinkMode);

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
	* managers now
	*/
	virtual void Activate();
	virtual void Deactivate();

	/**
	 * Removes a collision mesh from the world. This does not destroy the body
	 * in_Geometry pointer will be deleted by this method
	 */
	void DeleteCollisionMesh(VGeometry* in_Geometry);

	

	// TODO: fix mass parameter to be a part
	BodyPtr Create(IVBoundingVolumePart* in_pBoundingPart, vfloat32 in_fMass);

	void CreateGeom(IVBoundingVolumePart* in_pBoundingPart);

	/**
	 * a plane cannot be attached to a body, thus we return only the object
	 */
	Plane CreatePlane(VVector3f in_Normal,vfloat32 in_fDistance);


private:

	BodyPtr CreateBody();
	void CreateMeshGeom(VBoundingMesh* in_pBoundingMesh);
	BodyPtr CreateSphere(vfloat32 in_fMass, vfloat32 in_fRadius);
	BodyPtr CreateBox(vfloat32 in_fMass, VVector3f in_Expansion);
	BodyPtr CreateMesh(vfloat32 in_fMass, VBoundingMesh* in_BoundingMesh);
	
	VWorld m_World;
	//list of all created bodies for updating reasons
	std::list<VBodyPart*> m_BodyList; 
};

typedef VSharedPtr<VPhysicManager> VPhysicManagerPtr;

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICMANAGER_2006_02_15_H