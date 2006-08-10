#ifndef V3D_VCOLLISIONVISUALIZATIONPART_08_09_H
#define V3D_VCOLLISIONVISUALIZATIONPART_08_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Entity/VUnconnectedPart.h>
#include <v3d/Entity.h>
#include "VBoundingMesh.h"
#include "IVBoundingVolumePart.h"
#include <V3d/Resource.h>
#include <V3dLib/EntityParts/VRigidBodyPart.h>
#include <V3dLib/EntityParts/VUpdateablePart.h> //move away
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

	virtual void Activate();
	virtual void Deactivate();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
	
	void Update(vfloat32 in_fSeconds);
	void SendGeometry(graphics::IVDevice& in_Device) const;

private:

	void Create();	
	virtual void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer);
	
	entity::VPartConnection<physics::IVBoundingVolumePart> m_pVolumePart;
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
