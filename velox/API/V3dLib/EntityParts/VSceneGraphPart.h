#ifndef V3D_VSCENEGRAPHPART_2004_11_14_H
#define V3D_VSCENEGRAPHPART_2004_11_14_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Entity.h>
#include <V3dlib/Math/VRBTransform.h>
#include <V3dlib/EntityParts/VRigidBodyPart.h>

#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VSceneGraphPart
{
private:
	//no copiing
	void operator=(const VSceneGraphPart&);
	VSceneGraphPart(const VSceneGraphPart&);

public:
		
	VSceneGraphPart();
	VSceneGraphPart(VSceneGraphPart* in_pParent);

	virtual ~VSceneGraphPart();

	/**
	 * Updates all children and the VRigidBodyParts named "body"
	 */
	virtual void Update();

	/**
	 * Sets the parent of this VSceneGraphPart. This includes
	 * unregistration to the old parent and registration to 
	 * the new parent.
	 * The parent can not be 0;
	 *
	 * @param in_pParent Pointer to the new parent != 0
	 */
	virtual void SetParent(VSceneGraphPart* in_pParent);

	/**
	 * Set the relative rigid body transformation of this 
	 * VSceneGraphPart.
	 * TODO: Auch die Transformation des VRigidBodyParts 
	 *       neu setzen?
	 *
	 * @param in_Transform The new rigid body transformation
	 */
	virtual void SetTransform(const VRBTransform& in_Transform);

	/**
	 * Gets the current relative rigid body transformation of this 
	 * VSceneGraphPart.
	 *
	 * @return The current transformation
 	 */
	virtual VRBTransform GetTransform() const;

	/**
	 * Returns the absolute rigid body transformation.
	 */
	virtual VRBTransform GetAbsoluteTransform();

	/**
	 * Adds a new child and sets the new parent for this child.
	 * AddChild does not allow duplicate children. 
	 *
	 */
	virtual void AddChild(VSceneGraphPart* in_pChild);

	/**
	 * Removes and deactivates a child.
	 */
	virtual void RemoveChild(VSceneGraphPart* in_pChild);

	/** 
	 * When called, the part registers itself to it's parent and
	 * activates its children
	 */
	virtual void Activate();

    /**
	 * When called, the part unregisters itself from it's parent and
	 * deactivates its children
	 */
	virtual void Deactivate();

	/**
	 * 
	 */
	virtual void TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part);

private:

	vbool	                    m_bActive;
	VSceneGraphPart*	        m_pParent;

protected:

	std::list<VSceneGraphPart*> m_pChilds;
	VRigidBodyPart*             m_pRigidBodyPart;
	VRBTransform                m_Transform;
};
//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VSCENEGRAPHPART_2004_11_14_H