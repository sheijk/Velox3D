#ifndef V3D_VLIGHTPART_2006_01_21_H
#define V3D_VLIGHTPART_2006_01_21_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Scene/IVLightManager.h>
#include <V3d/Graphics/VLight.h>
#include <V3dLib/EntityParts/VUpdateablePart.h>
#include <V3dLib/EntityParts/VRigidBodyPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * An entity part which holds a light. Will register itself to it's ancestor
 * IVLightManager.
 *
 * ATTENTION: currently ignores it's entity's position
 * TODO: implement this once entity event notification is active
 * @author sheijk
 */
class VLightPart : public entity::VPartBaseAdapter<entity::IVUpdateablePart>
{
public:
	VLightPart();

	graphics::VLight& Light();

	virtual void Activate();

	virtual void Deactivate();

	virtual void Update(vfloat32 in_Seconds);

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	graphics::VLight m_Light;
	entity::VPartConnection<IVLightManager> m_LightManager;
	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBody;
	entity::VPartConnection<entity::VUpdateManagerPart> m_pUpdateManager;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VLightPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VLIGHTPART_2006_01_21_H
