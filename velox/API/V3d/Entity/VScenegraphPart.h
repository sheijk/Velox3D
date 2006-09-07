/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSCENEGRAPHPART_2004_11_14_H
#define V3D_VSCENEGRAPHPART_2004_11_14_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Entity/VPartBase.h>
#include <V3d/Entity.h>
#include <V3d/Math/VRBTransform.h>
#include <V3d/Entity/VRigidBodyPart.h>
#include <V3d/Entity/VUpdateablePart.h>

#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
* The SceneGraph add RigidBodys in a List
*
* @author lars
*/
class VSceneGraphPart : public VPartBase
{
public:
		
	VSceneGraphPart();
	virtual ~VSceneGraphPart();

	/**
	 * Updates all children and the VRigidBodyParts named "body"
	 */
	virtual void Update();

	/**
	 * Set the rigid body transformation of this 
	 * VSceneGraphPart.
	 * @param in_Transform The new rigid body transformation
	 */
	virtual void SetTransform(const math::VRBTransform& in_Transform);


	/**
	* Set the relative rigid body transformation of this 
	* VSceneGraphPart.
	*
	* @param in_relTransform The new rigid body transformation
	*/
	virtual void SetRelativeTransform(const math::VRBTransform& in_relTransform);

	/**
	 * Gets the current relative rigid body transformation of this 
	 * VSceneGraphPart.
	 *
	 * @return The current transformation
 	 */
	virtual math::VRBTransform GetTransform() const;

	/**
	 * Returns the absolute rigid body transformation.
	 */
	virtual math::VRBTransform GetAbsoluteTransform();


	/**
	* Returns the relative rigid body transformation.
	*/
	virtual math::VRBTransform GetRelativeTransform();

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

	static std::string GetDefaultId();
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:

	vbool	                         m_bActive;
	VPartConnection<VSceneGraphPart> m_pParent;

protected:

	std::list<VSceneGraphPart*>      m_pChilds;
	VPartConnection<VRigidBodyPart>  m_pRigidBodyPart;
	math::VRBTransform               m_Transform;
	math::VRBTransform               m_relativeTransform;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity

V3D_TYPEINFO_WITHPARENT(v3d::entity::VSceneGraphPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VSCENEGRAPHPART_2004_11_14_H
