/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSGANIMATIONPART_H
#define V3D_VSGANIMATIONPART_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Math.h>
#include <V3d/Entity/VPartBase.h>
#include <V3d/Entity.h>
#include <V3d/Entity/VSceneGraphPart.h>
#include <V3d/Entity/VUpdateablePart.h>
#include <V3d/Math/VRBTransform.h>

#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
* Calculate the Animation from the Rigidbody from the 
* SceneGraphPart
*
* @author lars
*/
class VSGAnimationPart : public IVUpdateablePart
{
public:

	VSGAnimationPart();
	virtual ~VSGAnimationPart();

	/** Sets the Position for the Translate */
	void SetPosition(math::VVector3f in_Position);

	/** Sets the Rotate Axis for the Rotation */
	void SetRotateAxis(math::VVector3f in_Rotate);

	/** Sets the Speed for the Rotation */
	void SetRotateSpeed(vfloat32 in_Speed);

	/** Gets the Relative Transformation */
	math::VRBTransform GetRelativeTransform() const;
	
	/** Update the Animation Part */
	virtual void Update(vfloat32 in_Seconds);

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

	VPartConnection<VSceneGraphPart>    m_pSceneGraphPart;
	VPartConnection<VUpdateManagerPart> m_pParent;
	math::VRBTransform                  m_Transform;
	math::VVector3f                           m_Position;
	math::VVector3f                           m_Rotate;
	vfloat32                            m_fRotateSpeed;
	vfloat32                            m_fAngle;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity

V3D_TYPEINFO_WITHPARENT(v3d::entity::VSGAnimationPart, v3d::entity::IVUpdateablePart);
//-----------------------------------------------------------------------------
#endif // V3D_VSGANIMATIONPART_H
