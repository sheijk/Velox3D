#include <V3d/Scene/Shootings/VOffscreenShooting.h>
//-----------------------------------------------------------------------------

#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Resource/VResourceId.h>
#include <V3d/Resource/VResource.h>
#include <V3d/Resource/IVResourceManager.h>
#include <V3d/Graphics/IVGraphicsService.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;
using namespace v3d::resource;
using namespace v3d::graphics;

/**
 * standard c'tor
 */
VOffscreenShooting::VOffscreenShooting() :
	m_pMainShooting(VPartDependency::Ancestor, RegisterTo()),
	m_pRigidBodyPart(VPartDependency::Neighbour, RegisterTo())
{
}

/**
 * d'tor
 */
VOffscreenShooting::~VOffscreenShooting()
{
}

void VOffscreenShooting::Activate()
{
	VShootingBase::Activate();
	m_pMainShooting->AddPreShooting(this);
}

void VOffscreenShooting::Deactivate()
{
	m_pMainShooting->RemovePreShooting(this);
	VShootingBase::Deactivate();
}

graphics::IVDevice* VOffscreenShooting::GetRenderTarget()
{
	return &*m_pRenderTarget;
}

graphics::IVCamera* VOffscreenShooting::GetCamera()
{
	return &m_Camera;
	//return m_pMainShooting->GetCamera();
}

scene::IVGraphicsPart* VOffscreenShooting::GetScene()
{
	return m_pMainShooting->GetScene();
}

void VOffscreenShooting::UpdateAndCull()
{
	VShootingBase::UpdateAndCull();
	m_Camera.SetTransform(m_pRigidBodyPart->GetTransform());
}

void VOffscreenShooting::SetRenderTargetResource(const std::string& in_strResource)
{
	if( ! VResourceManagerPtr()->ExistsResource(in_strResource.c_str()) )
		VResourceManagerPtr()->CreateResource(in_strResource.c_str());

	VResourceId res(in_strResource.c_str());

	if( ! res->ContainsData<IVDevice>() )
	{
		graphics::VGraphicsServicePtr pGfxService;

		graphics::VDisplaySettings settings;
		settings.SetSize(512, 512);

		graphics::IVRenderContext* pRenderContext =
			pGfxService->GetMainDevice()->CreateOffscreenContext(&settings);

		res->AddData(pRenderContext);
	}

	m_pRenderTarget = res->GetMutableData<IVDevice>();
}

void VOffscreenShooting::OnMessage(
	const messaging::VMessage& in_Message, 
	messaging::VMessage* in_pAnswer)
{
	using std::string;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer == 0 )
			return;

		in_pAnswer->AddProperty("render-target", m_pRenderTarget.GetResourceName());
	}
	else if( request == "update" )
	{
		const std::string name = in_Message.GetAs<string>("name");
		const std::string value = in_Message.GetAs<string>("value");

		if( name == "render-target" )
		{
			SetRenderTargetResource(value);
		}
	}
}

namespace {
	entity::VPartParser<VOffscreenShooting> g_Parser;
}
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------