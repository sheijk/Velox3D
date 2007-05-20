/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Shootings/VMirrorShooting.h>
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>

#include <V3d/OpenGL.h>
#include <V3d/Math.h>
#include <V3d/Math/TransformationOps.h>

#include <V3d/Scene/VDefaultRenderStepPart.h>
#include <V3d/Scene/IVLightManager.h>

#include <V3d/Graphics/IVGraphicsService.h>

#include <V3d/Entity/VGenericPartParser.h>

#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace resource;
using namespace graphics;
using namespace entity;
using namespace math;

namespace {
	const std::string g_strRenderTargetPropertyName = "render-target";
}

/**
 * standard c'tor
 */
VMirrorShooting::VMirrorShooting() :
	m_pMainShooting(RegisterTo()),
	m_pMirrorMesh(VNodeDependency::Optional, RegisterTo()),
	m_pRigidyBodyPart(RegisterTo())
{
	m_pTextureMatrixValue.Assign(new VFloat44ParamValue());
}

/**
 * d'tor
 */
VMirrorShooting::~VMirrorShooting()
{
}

namespace {
	using namespace math;
	VVector3f ReflectDir(const VVector3f& in_Dir, const VPlane& in_Plane)
	{
		vfloat32 planeDist = Dot(in_Dir, in_Plane.GetNormal());

		VVector3f reflectedDir = in_Dir - (2 * planeDist * in_Plane.GetNormal());
		return reflectedDir;
	}

	VVector3f Reflect(const VVector3f& in_Pos, const VPlane& in_Plane)
	{
		VVector3f pos2 = in_Pos - in_Plane.GetNormal() * in_Plane.GetDistance();
		vfloat32 planeDist = Dot(pos2, in_Plane.GetNormal());

		VVector3f reflectedPos = pos2 - (2 * in_Plane.GetNormal() * planeDist);
		return reflectedPos;
	}

	VRBTransform Reflect(const VRBTransform& in_Transform, const VPlane& in_Plane)
	{
		VVector3f newPos = Reflect(in_Transform.GetPosition(), in_Plane);
		VVector3f newx = ReflectDir(in_Transform.GetXAxis(), in_Plane);
		VVector3f newy = ReflectDir(in_Transform.GetYAxis(), in_Plane);
		VVector3f newz = ReflectDir(in_Transform.GetZAxis(), in_Plane);
		//VVector3f newViewDir = ReflectDir(-in_Transform.GetZAxis(), in_Plane);
		//VVector3f newUpDir = ReflectDir(in_Transform.GetYAxis(), in_Plane);

		VRBTransform reflected;
		reflected.SetPosition(newPos);
		//reflected.SetDirection(newViewDir, newUpDir);
		reflected.SetXAxis(newx);
		reflected.SetYAxis(newy);
		reflected.SetZAxis(newz);
		return reflected;
	}

	void MakeTextureProjectionMatrix2(
		VMatrix44f* out_pMatrix, const math::VRBTransform& in_Transform)
	{
		VVector3f f = - in_Transform.GetZAxis();
		Normalize(f);

		VVector3f up = in_Transform.GetYAxis();
		Normalize(up);

		VVector3f s;

		s = Cross(f,up);

		VVector3f u;

		u = Cross(s,f);

		VMatrix44f m;
		Identity(m);
		m.Set(0, 0, s.Get(0));
		m.Set(0, 1, s.Get(1));
		m.Set(0, 2, s.Get(2));

		m.Set(1, 0, u.Get(0));
		m.Set(1, 1, u.Get(1));
		m.Set(1, 2, u.Get(2));

		m.Set(2, 0, -f.Get(0));
		m.Set(2, 1, -f.Get(1));
		m.Set(2, 2, -f.Get(2));

		VMatrix44f t;
		Identity(t);
		VVector3f pos = in_Transform.GetPosition();
		t.SetTransform(-pos[0], -pos[1], -pos[2]);

		VMatrix44f r;
		Identity(r);
		Mult(r, m, t);

		*out_pMatrix = r;
	}
}

void VMirrorShooting::UpdateAndCull()
{
	VShootingBase::UpdateAndCull();

	if( m_pMainShooting.Get() != 0 && m_pMainShooting->GetCamera() != 0 )
	{
		// calculate plane from rigid body part
		m_Plane.SetNormal(m_pRigidyBodyPart->GetTransform().GetYAxis());
		m_Plane.SetDistance(0.);

		// calculate mirrored camera position
		IVCamera* pOriginalCam = m_pMainShooting->GetCamera();

		VRBTransform transform;
		transform = Reflect(pOriginalCam->Transform(), m_Plane);
		m_Camera.SetTransform(transform);

		//VMatrix44f mat = m_Camera.ViewMatrix();

		// calculate texture matrix
		VRBTransform camTransform;// = math::IdentityMatrix();
		camTransform = m_Camera.GetTransform();

		VMatrix44f textureMatrix;
		VMatrix44f proj;
		MakeProjectionMatrix(&proj, 45.0f, 1.0f, 1.0f, 900000.0f);
		VMatrix44f view;
		MakeTextureProjectionMatrix2(&view, camTransform);
		Mult(textureMatrix, proj, view);
		//Scale(textureMatrix, 4.0f/3.0f, 1, 1);
		m_pTextureMatrixValue->SetValue(textureMatrix);

		if( m_pMirrorMesh.IsConnected() )
		{
			static vbool initalized = false;
			static messaging::VMessage msg;
			if( ! initalized )
			{
				initalized = true;
				msg.AddProperty("type", "update");
				msg.AddProperty("name", "mat_cam");
				msg.AddProperty("value", "");
			}

			msg.Set("value", utils::VStringValue(textureMatrix));
			m_pMirrorMesh->Send(msg);
		}
	}
}

VSharedPtr<VFloat44ParamValue> VMirrorShooting::GetTextureMatrixValue() const
{
	return m_pTextureMatrixValue;
}

void VMirrorShooting::Render()
{
	IVDevice* activeDevice = GetRenderTarget();

	if( activeDevice == NULL )
	{
		V3D_LOGONCE(activeDeviceNull);
		return;
	}

	activeDevice->BeginScene();

	VMatrix44f viewMatrix = GetCamera()->ViewMatrix();
	activeDevice->SetMatrix(IVDevice::ViewMatrix, viewMatrix);
	
	VMatrix44f projMatrix;
	MakeProjectionMatrix(&projMatrix, 45.0f, 4.0f/3.0f, 1.0f, 1000.0f);
	activeDevice->SetMatrix(IVDevice::ProjectionMatrix, projMatrix);
	//if( GetCamera() != 0 )
	//	GetCamera()->ApplyTo(*activeDevice);

	if( m_pLightManager.IsConnected() )
		m_pLightManager->ApplyLights(activeDevice, NULL);

	static VDefaultRenderStepPart defaultRenderStep;
	defaultRenderStep.SetOutputDevice(activeDevice);

	VRangeIterator<IVRenderStepPart> renderStep = CreateSingleValueIterator<IVRenderStepPart>(&defaultRenderStep);

	//for(vuint stepNum = 0; stepNum < m_RenderSteps.size(); ++stepNum)
	while( renderStep.HasNext() )
	{
		//IVRenderStepPart* renderStep = m_RenderSteps[stepNum];

		if( activeDevice != renderStep->GetOutputDevice() )
		{
			activeDevice->EndScene();
			activeDevice = renderStep->GetOutputDevice();
			activeDevice->BeginScene();

			if( m_pLightManager.IsConnected() )
				m_pLightManager->ApplyLights(activeDevice, NULL);
		}

		renderStep->Render(GetScene());

		++renderStep;
	}

	activeDevice->EndScene();
	//glViewport(0, 0, 512, 384);
	//VShootingBase::Render();
}

void VMirrorShooting::SetRenderTargetResource(const std::string& in_strResourceName)
{
	if( ! VResourceManagerPtr()->ExistsResource(in_strResourceName.c_str()) )
	{
		VResourceManagerPtr()->CreateResource(in_strResourceName.c_str());
	}

	VResourceId res(in_strResourceName.c_str());

	if( ! res->ContainsData<IVDevice>() )
	{
//TODO:
//plane aus rigid body part berechnen
//resource bei bedarf erzeugen (?)
		graphics::VGraphicsServicePtr pGfxService;

		graphics::VDisplaySettings settings;
		settings.SetSize(512, 512);

		graphics::IVRenderContext* pRenderContext =
			pGfxService->GetMainDevice()->CreateOffscreenContext(&settings);

		res->AddData(pRenderContext);

		//VAutoPtr<IVDevice> device = pGfxService->CreateOffscreenDevice(settings);
		//res->AddData(device.DropOwnership());
	}

	m_pRenderTarget = res->GetMutableData<IVDevice>();

	if( m_pMirrorMesh.IsConnected() )
	{
		static vbool initialized = false;
		static messaging::VMessage msg;
		if( ! initialized )
		{
			initialized = true;
			msg.AddProperty("type", "update");
			msg.AddProperty("name", "mat_mirrorTex");
			msg.AddProperty("value", "");
		}

		msg.Set("value", res->GetQualifiedName());

		m_pMirrorMesh->Send(msg);
	}
}

std::string VMirrorShooting::GetRenderTargetResource() const
{
	const VResource* res = m_pRenderTarget.GetEnclosingResource();

	if( res != 0 )
		return res->GetQualifiedName();
	else
		return "";
}

graphics::IVDevice* VMirrorShooting::GetRenderTarget()
{
	return &*m_pRenderTarget;
}

graphics::IVCamera* VMirrorShooting::GetCamera()
{
	return &m_Camera;
}

scene::IVGraphicsPart* VMirrorShooting::GetScene()
{
	if( m_pMainShooting.Get() != 0 )
	{
		return m_pMainShooting->GetScene();
	}
	else
	{
		return 0;
	}
}

void VMirrorShooting::OnActivate()
{
	VShootingBase::OnActivate();

	m_pMainShooting->AddPreShooting(this);
}

void VMirrorShooting::OnDeactivate()
{
	VShootingBase::OnDeactivate();

	m_pMainShooting->RemovePreShooting(this);
}

math::VPlane VMirrorShooting::GetPlane() const
{
	return m_Plane;
}

void VMirrorShooting::SetPlane(const math::VPlane& in_Plane)
{
	m_Plane = in_Plane;
}

messaging::VMessageInterpreter* VMirrorShooting::GetMessageInterpreterForClass()
{
	static messaging::VMessageInterpreter interpreter;

	return &interpreter;
}

void VMirrorShooting::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddAccessorOption<VMirrorShooting, std::string>(
		g_strRenderTargetPropertyName,
		&VMirrorShooting::GetRenderTargetResource,
		&VMirrorShooting::SetRenderTargetResource);

	VShootingBase::SetupProperties( interpreter );
}

//void VMirrorShooting::OnMessage(
//	const messaging::VMessage& in_Message, 
//	messaging::VMessage* in_pAnswer)
//{
//	using std::string;
//
//	if( ! in_Message.HasProperty("type") )
//		return;
//
//	string request = in_Message.Get("type").Get<string>();
//
//	if( request == "getSettings" )
//	{
//		if( in_pAnswer == 0 )
//			return;
//
//		std::string renderTargetResource = "";
//		if( m_pRenderTarget != 0 &&
//			m_pRenderTarget.GetEnclosingResource() != 0 )
//		{
//			renderTargetResource = m_pRenderTarget.GetEnclosingResource()->GetQualifiedName();
//		}
//
//		in_pAnswer->AddProperty(g_strRenderTargetPropertyName, renderTargetResource);
//	}
//	else if( request == "update" )
//	{
//		const string name = in_Message.Get("name").Get<string>();
//		const string value = in_Message.Get("value").Get<string>();
//
//		if( name == g_strRenderTargetPropertyName )
//		{
//			SetRenderTargetResource(value);
//		}
//	}
//}

//namespace {
//	using namespace v3d::entity;
//
//	class Parser : public VPartParser<VMirrorShooting>
//	{
//	public:
//		virtual VSharedPtr<IVPart> CreatePart()
//		{
//			return SharedPtr(new VMirrorShooting());
//		}
//	};
//
//	Parser g_Parser;
//	//v3d::entity::VPartParser<VMirrorShooting> g_parser;
//}

V3D_REGISTER_PART_PARSER(VMirrorShooting);

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

