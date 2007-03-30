/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VBOUNDINGCCYLINDERVOLUMEPART_12_28_05
#define V3D_VBOUNDINGCCYLINDERVOLUMEPART_12_28_05
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Math/VCCylinder.h>
#include <V3d/Entity/VUnconnectedPart.h>
#include "IVBoundingVolumePart.h"
//-----------------------------------------------------------------------------
namespace v3d { 
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * represents a capped cylinder volume part
 * @author: ins
 */
class VBoundingCCylinderVolumePart : public entity::VUnconnectedPartAdapter<IVBoundingVolumePart>
{
public:
	math::VBoundingBox* GetBoundingBox();
	math::VBoundingSphere* GetBoundingSphere();
	VBoundingMesh* GetBoundingMesh();
	math::VCCylinder* GetBoundingCylinder();
	vbool HasBoundingMesh();
	math::VPlane* GetBoundingPlane();

	//entity related methods
	virtual void Activate();
	virtual void Deactivate();
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }


private:

	virtual void OnMessage(
		const messaging::VMessage& in_Message,
		messaging::VMessage* in_pAnswer);

	math::VCCylinder m_BoundingCCylinder;
};


//-----------------------------------------------------------------------------
} // namespace v3d::
} //
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::physics::VBoundingCCylinderVolumePart, v3d::physics::IVBoundingVolumePart);
//-----------------------------------------------------------------------------
#endif //V3D_VBOUNDINGCCYLINDERVOLUMEPART_12_28_05