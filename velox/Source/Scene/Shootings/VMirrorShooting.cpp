#include <V3d/Scene/Shootings/VMirrorShooting.h>
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>

#include <V3d/OpenGL.h>
#include <V3d/Math.h>
#include <V3d/Math/TransformationOps.h>

#include <V3d/Scene/VDefaultRenderStepPart.h>
#include <V3d/Scene/IVLightManager.h>
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

/**
 * standard c'tor
 */
VMirrorShooting::VMirrorShooting() :
	m_pMainShooting(VPartDependency::Ancestor, RegisterTo())
{
	m_pTextureMatrixValue.Assign(new VMatrix44fParamValue());
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
}

namespace {
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
		// calculate mirrored camera position
		IVCamera* pOriginalCam = m_pMainShooting->GetCamera();

		//VVector3f newPos = Reflect(pOriginalCam->GetPosition(), m_Plane);

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
	}
}

VSharedPtr<VMatrix44fParamValue> VMirrorShooting::GetTextureMatrixValue() const
{
	return m_pTextureMatrixValue;
}

void VMirrorShooting::Render()
{
	IVDevice* activeDevice = GetRenderTarget();

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
	VResourceId res(in_strResourceName.c_str());

	m_pRenderTarget = res->GetMutableData<IVDevice>();
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

void VMirrorShooting::Activate()
{
	VShootingBase::Activate();

	m_pMainShooting->AddPreShooting(this);
}

void VMirrorShooting::Deactivate()
{
	VShootingBase::Deactivate();

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

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
