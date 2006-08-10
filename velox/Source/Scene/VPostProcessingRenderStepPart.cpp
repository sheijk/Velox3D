#include <V3d/Scene/Rendering/VPostProcessingRenderStepPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Math.h>
#include <V3d/Resource.h>

#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Resource/VResource.h>

#include <string>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace resource;
using namespace graphics;
using std::string;

namespace {
	void SendTexturedQuad(vfloat32 halfSize = 1.0f, vfloat32 depth = .0f)
	{
		glBegin(GL_QUADS);
		//glColor3f(1, 1, 1);
		glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, depth);
		glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, depth);
		glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, depth);
		glTexCoord2f(0, 1); glVertex3f(-halfSize, halfSize, depth);
		glEnd();
	}
}

VPostProcesssingRenderStepPart::VPostProcesssingRenderStepPart()
{
}

void VPostProcesssingRenderStepPart::SetOutputDevice(
	graphics::IVDevice* in_OutputDevice)
{
	IVRenderStepPart::SetOutputDevice(in_OutputDevice);

	if( in_OutputDevice != 0 )
	{
		VResourceId offscreenDeviceRes = VResourceManagerPtr()->GetResourceByName(
			"/system/graphics")->AddRandomNamedSubResource("postproc");

		VDisplaySettings settings;
		settings.SetSize(1024, 1024);
		//settings.SetBitsPerPixel(32);
		offscreenDeviceRes->AddData(in_OutputDevice->CreateOffscreenContext(&settings));

		m_hOffscreenDevice = offscreenDeviceRes->GetMutableData<IVDevice>();
		m_hOffscreenTexture = offscreenDeviceRes->GetMutableData<IVTexture>();
	}
}

void VPostProcesssingRenderStepPart::SetPostProcessingShader(
	resource::VResourceDataPtr<graphics::IVMaterial> in_hShader)
{
	m_hPostProcessingShader = in_hShader;
}

graphics::IVDevice* VPostProcesssingRenderStepPart::GetPredecessorDevice() const 
{ 
	//return GetOutputDevice();
	return &*m_hOffscreenDevice; 
}

void VPostProcesssingRenderStepPart::Render(IVGraphicsPart* in_pScene)
{
	//if( &*m_hOffscreenTexture == 0 )
	//	return;
	if( GetOutputDevice() == 0 )
		return;

	//V3D_ASSERT(&*m_hOffscreenDevice != 0);
	//V3D_ASSERT(&*m_hOffscreenTexture != 0);
	//V3D_ASSERT(&*m_hPostProcessingShader != 0);
	// no multipass shaders supported atm
	//V3D_ASSERT(m_hPostProcessingShader->PassCount() == 1);
	//V3D_ASSERT(GetOutputDevice() != 0);

	GetOutputDevice()->SetMatrix(IVDevice::ProjectionMatrix, math::IdentityMatrix());
	GetOutputDevice()->SetMatrix(IVDevice::ModelMatrix, math::IdentityMatrix());
	GetOutputDevice()->SetMatrix(IVDevice::ViewMatrix, math::IdentityMatrix());

	if( &*m_hPostProcessingShader != 0 )
	{
		//TODO: seems not to work correctly with multipass materials
		// use two render targets for multiple passes
		//for(vuint passNum = 0; passNum < m_hPostProcessingShader->PassCount(); ++passNum)
		//{
		const vuint passNum = 0;
			ApplyMaterial(*GetOutputDevice(), &m_hPostProcessingShader->GetPass(passNum));
			m_MaterialSetup.Apply(*m_hPostProcessingShader);
			VRangeIterator<IVParameter> params = m_hPostProcessingShader->Parameters();
			while( params.HasNext() )
			{
				params->ApplyAutoValue(*GetOutputDevice());
				++params;
			}

			m_hOffscreenTexture->Bind();

			glColor3f(1, 1, 1);
			SendTexturedQuad(1.0f, -.5f);

			m_hOffscreenTexture->Unbind();
		//}
	}
	else
	{
		ApplyMaterial(*GetOutputDevice(), &IVDevice::GetDefaultMaterial()->GetPass(0));

		m_hOffscreenTexture->Bind();

		glColor3f(1, 1, 1);
		SendTexturedQuad(1.0f, -.5f);

		m_hOffscreenTexture->Unbind();
	}
}

void VPostProcesssingRenderStepPart::AddMaterialParameter(
	VStringParam in_strParamName, 
	VSharedPtr<graphics::IVParameterValue> in_Value)
{
	m_MaterialSetup.Add(in_strParamName, in_Value);
}

const VTypeInfo& VPostProcesssingRenderStepPart::GetTypeInfo() const
{
	return ::v3d::GetTypeInfo<VPostProcesssingRenderStepPart>();
}

void VPostProcesssingRenderStepPart::OnMessage(
	const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	if( ! in_Message.HasProperty("type") )
		return;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer != 0 )
		{
			string materialRes;
			if( &*m_hPostProcessingShader != 0 &&
				m_hPostProcessingShader.GetEnclosingResource() != 0 )
			{
				materialRes = m_hPostProcessingShader.GetEnclosingResource()->GetQualifiedName();
			}

			in_pAnswer->AddProperty("material", materialRes);
		}
	}
	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");

		if( name == "material" )
		{
			const string resource = in_Message.GetAs<string>("value");
			SetPostProcessingShader(
				GetMutableResourceData<IVMaterial>(resource.c_str()));
		}
	}
}

V3D_REGISTER_PART_PARSER(VPostProcesssingRenderStepPart);
V3D_REGISTER_PART_PARSER(VPostProcesssingRenderStepPart2);
V3D_REGISTER_PART_PARSER(VPostProcesssingRenderStepPart3);
V3D_REGISTER_PART_PARSER(VPostProcesssingRenderStepPart4);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
