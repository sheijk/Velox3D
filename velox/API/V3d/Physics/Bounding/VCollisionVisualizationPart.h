/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCOLLISIONVISUALIZATIONPART_08_09_H
#define V3D_VCOLLISIONVISUALIZATIONPART_08_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Entity/VUnconnectedPart.h>
#include <V3d/Entity.h>
#include "VBoundingMesh.h"
#include "IVBoundingVolumePart.h"
#include <V3d/Resource.h>
#include <V3d/Entity/VRigidBodyPart.h>
#include <V3d/Entity/VUpdateablePart.h>
#include <V3d/OpenGL.h>
#include <V3d/Graphics.h>
#include <V3d/Scene/VMeshPartBase.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Visualization part for collision meshes
 *
 * @author: ins
 */
class VCollisionVisualizationPart : public scene::VMeshPartBase
{
public:
	VCollisionVisualizationPart();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
	
	void Update(vfloat32 in_fSeconds);
	void SendGeometry(graphics::IVDevice& in_Device) const;

private:
	virtual void OnActivate();
	virtual void OnDeactivate();

	void Create();	
	virtual void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer);
	
	entity::VNodeConnection<physics::IVBoundingVolumePart> m_pVolumePart;
	//math::VBoundingMesh m_BoundingMesh;
	resource::VResourceDataPtr<graphics::VVertexBuffer> m_hVertexBuffer;
	resource::VResourceDataPtr<graphics::VVertexBuffer> m_hIndexBuffer;	
	resource::VResourceDataPtr<const graphics::IVMesh> m_hMesh;


	vbool m_bCreated;
};

//-----------------------------------------------------------------------------
}
} // namespace v3d::
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::physics::VCollisionVisualizationPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VCOLLISIONVISUALIZATIONPART_08_09_H

