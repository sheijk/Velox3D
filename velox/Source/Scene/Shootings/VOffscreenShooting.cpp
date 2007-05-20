/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Shootings/VOffscreenShooting.h>
//-----------------------------------------------------------------------------

#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Resource/VResourceId.h>
#include <V3d/Resource/VResource.h>
#include <V3d/Resource/IVResourceManager.h>
#include <V3d/Graphics/IVGraphicsService.h>
#include <V3d/Messaging/VMessageInterpreter.h>
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
	m_pMainShooting(RegisterTo()),
	m_pRigidBodyPart(RegisterTo())
{
}

/**
 * d'tor
 */
VOffscreenShooting::~VOffscreenShooting()
{
}

void VOffscreenShooting::OnActivate()
{
	VShootingBase::OnActivate();
	m_pMainShooting->AddPreShooting(this);
}

void VOffscreenShooting::OnDeactivate()
{
	m_pMainShooting->RemovePreShooting(this);
	VShootingBase::OnDeactivate();
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
		settings.SetBitsPerPixel(32);

		graphics::IVRenderContext* pRenderContext =
			pGfxService->GetMainDevice()->CreateOffscreenContext(&settings);

		res->AddData(pRenderContext);
	}

	m_pRenderTarget = res->GetMutableData<IVDevice>();
}

std::string VOffscreenShooting::GetRenderTargetResource() const
{
	return m_pRenderTarget.GetResourceName();
}

messaging::VMessageInterpreter* VOffscreenShooting::GetMessageInterpreterForClass()
{
	static messaging::VMessageInterpreter interpreter;

	return &interpreter;
}

void VOffscreenShooting::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddAccessorOption<VOffscreenShooting, std::string>(
		"render-target",
		&VOffscreenShooting::GetRenderTargetResource,
		&VOffscreenShooting::SetRenderTargetResource);

	VShootingBase::SetupProperties( interpreter );
}

//void VOffscreenShooting::OnMessage(
//	const messaging::VMessage& in_Message, 
//	messaging::VMessage* in_pAnswer)
//{
//	using std::string;
//
//	const string request = in_Message.GetAs<string>("type");
//
//	if( request == "getSettings" )
//	{
//		if( in_pAnswer == 0 )
//			return;
//
//		in_pAnswer->AddProperty("render-target", m_pRenderTarget.GetResourceName());
//	}
//	else if( request == "update" )
//	{
//		const std::string name = in_Message.GetAs<string>("name");
//		const std::string value = in_Message.GetAs<string>("value");
//
//		if( name == "render-target" )
//		{
//			SetRenderTargetResource(value);
//		}
//	}
//}

V3D_REGISTER_PART_PARSER(VOffscreenShooting);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

