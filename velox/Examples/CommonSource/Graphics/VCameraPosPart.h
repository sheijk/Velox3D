#ifndef V3D_VCAMERAPOSPART_2004_10_14_H
#define V3D_VCAMERAPOSPART_2004_10_14_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3dLib/EntityParts/VRigidBodyPart.h>
#include "../Shared/VUpdateablePart.h"
//#include "../Shared/VRigidBodyPart.h"
#include <V3dLib/Graphics/Misc/IVCamera.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace racer {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * Gets a VRigidBodyPart named "body" and sets it's position vector to the
 * camera's position vector
 */
class VCameraPosPart : public VUpdateablePart
{
	entity::VRigidBodyPart* m_pRigidBody;
	const graphics::IVCamera& m_Camera;

public:
	VCameraPosPart(
		const graphics::IVCamera& in_Camera, 
		VEntityUpdater<VUpdateablePart>* in_pUpdater
		);

	virtual void TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part);
	virtual void Update();
	virtual vbool IsReady() const;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::racer
//-----------------------------------------------------------------------------
#endif // V3D_VCAMERAPOSPART_2004_10_14_H
