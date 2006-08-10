#include <V3d/Utils/VTrackballPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Input/IVInputManager.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace entity;

/**
 * standard c'tor
 */
VTrackballPart::VTrackballPart() :
	m_pRigidBodyPart(VPartDependency::Neighbour, RegisterTo()),
	m_pUpdateManager(VPartDependency::Ancestor, RegisterTo()),
	m_pInputPart(VPartDependency::Ancestor, RegisterTo())
{
}

/**
 * d'tor
 */
VTrackballPart::~VTrackballPart()
{
}

void VTrackballPart::Activate()
{
	m_pUpdateManager->Register(this);

	using namespace input;

	IVInputManager* pInputManager = m_pInputPart->GetInputManager();
	if( pInputManager != 0 )
	{
		IVMouseDevice* pMouse = &pInputManager->GetStandardMouse();
		m_pTrackball.Assign(new VMouseTrackball(pMouse));
	}
}

void VTrackballPart::Deactivate()
{
	m_pUpdateManager->Unregister(this);
}

void VTrackballPart::Update(vfloat32 in_fSeconds)
{
	if( m_pTrackball.Get() != 0 && m_pRigidBodyPart.Get() != 0 )
	{
		m_pTrackball->Update(in_fSeconds);
		m_pRigidBodyPart->SetTransform(m_pTrackball->GetTransform());
	}
}

void VTrackballPart::SetTrackball(const VSharedPtr<VMouseTrackball>& in_Trackball)
{
	m_pTrackball = in_Trackball;
}

V3D_REGISTER_PART_PARSER(VTrackballPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
