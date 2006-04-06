#include "VCameraPosPart.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace racer {
//-----------------------------------------------------------------------------
using namespace entity;
VCameraPosPart::VCameraPosPart(
	const graphics::IVCamera& in_Camera,
	VEntityUpdater<VUpdateablePart>* in_pUpdater
) : 
	VUpdateablePart(in_pUpdater),
	m_Camera(in_Camera)
{
	m_pRigidBody = 0;
}

void VCameraPosPart::TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part)
{
	if( in_Id.AsStdString() == "body" && in_Part.IsOfType<VRigidBodyPart>() )
	{
		m_pRigidBody = in_Part.Convert<VRigidBodyPart>();
	}
}

void VCameraPosPart::Update()
{
	if( m_pRigidBody != 0 )
	{
		m_pRigidBody->SetPosition(m_Camera.GetPosition());
	}
}

vbool VCameraPosPart::IsReady()
{
	return true;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::racer
//-----------------------------------------------------------------------------
