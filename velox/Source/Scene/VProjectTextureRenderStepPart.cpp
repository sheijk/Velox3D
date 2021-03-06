/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Rendering/VProjectTextureRenderStepPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics.h>
#include <V3d/Graphics.h>
#include <V3d/Scene/IVShapePart.h>
#include <V3d/Entity/VGenericPartParser.h>

#include <V3d/Messaging/VMessageInterpreter.h>
#include <V3d/Resource.h>

#include <string>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

using namespace std;
using namespace math;
using namespace graphics;
using namespace resource;
using namespace math;


namespace {
	//TODO: should use it's own material..
	VResourceDataPtr<const IVMaterial> GetDefaultMaterial()
	{
		return GetResourceData<IVMaterial>("/system/graphics/defaultMaterial");
	}
}

/**
 * standard c'tor
 */
VProjectTextureRenderStepPart::VProjectTextureRenderStepPart()
{
	m_fTextureSize = 10.0f;
}

/**
 * d'tor
 */
VProjectTextureRenderStepPart::~VProjectTextureRenderStepPart()
{
}

void VProjectTextureRenderStepPart::Render(IVGraphicsPart* in_pScene)
{
	if( GetOutputDevice() == 0 )
		return;

	if( &*m_pTexture == 0 )
		return;

	ApplyMaterial(*GetOutputDevice(), &GetDefaultMaterial()->GetPass(0));

	IVTexture* pTex = const_cast<IVTexture*>(&*m_pTexture);
	pTex->Bind();

	const GLenum texGenMode = GL_EYE_LINEAR;
	//const GLenum texGenMode = GL_OBJECT_LINEAR;
	const GLenum texPlane = GL_EYE_PLANE;
	//const GLenum texPlane = GL_OBJECT_PLANE;

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_Q);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, texGenMode);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, texGenMode);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, texGenMode);
	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, texGenMode);

	float sfact[4] = { 1, 0, 0, 0 };
	float tfact[4] = { 0, 1, 0, 0 };
	float rfact[4] = { 0, 0, 1, 0 };
	float qfact[4] = { 0, 0, 0, 1 };
	glTexGenfv(GL_S, texPlane, sfact);
	glTexGenfv(GL_T, texPlane, tfact);
	glTexGenfv(GL_R, texPlane, rfact);
	glTexGenfv(GL_Q, texPlane, qfact);

	VMatrix44f textureMatrix = CalculateTextureMatrix();
	GetOutputDevice()->SetMatrix(IVDevice::TextureMatrix, textureMatrix);

	glPushAttrib(GL_DEPTH_FUNC);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VRangeIterator<const IVShapePart> shape = in_pScene->GetVisibleMeshes();
	while( shape.HasNext() )
	{
		GetOutputDevice()->SetMatrix(IVDevice::ModelMatrix, shape->GetModelTransform().AsMatrix());
		glColor4f(1, 0, 0, .5f);
		shape->SendGeometry(*GetOutputDevice());

		++shape;
	} 

	glPopAttrib();

	glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_Q);
	glDisable(GL_TEXTURE_GEN_R);

	GetOutputDevice()->SetMatrix(IVDevice::TextureMatrix, math::IdentityMatrix());
	pTex->Unbind();
}

VMatrix44f VProjectTextureRenderStepPart::CalculateTextureMatrix()
{
	VMatrix44f textureMatrix;
	Translate(textureMatrix, .5f, .5f, .5f);
	Scale(textureMatrix, -.5f * 1.0f/m_fTextureSize);
	VMatrix44f projMatrix;
	MakeTextureProjectionMatrix(&projMatrix, m_ProjectorOrientation);
	Mult(textureMatrix, textureMatrix, projMatrix);
	return textureMatrix;
}

math::VRBTransform VProjectTextureRenderStepPart::GetProjectorOrientation() const
{
	return m_ProjectorOrientation;
}

void VProjectTextureRenderStepPart::SetProjectorOrientation(const math::VRBTransform& in_ProjectorOrientation)
{
	m_ProjectorOrientation = in_ProjectorOrientation;
}

VResourceDataPtr<const IVTexture> VProjectTextureRenderStepPart::GetTexture() const
{
	return m_pTexture;
}

void VProjectTextureRenderStepPart::SetTexture(const VResourceDataPtr<const IVTexture>& in_Texture)
{
	m_pTexture = in_Texture;
}

vfloat32 VProjectTextureRenderStepPart::GetTextureSize() const
{
	return m_fTextureSize;
}

void VProjectTextureRenderStepPart::SetTextureSize(const vfloat32& in_TextureSize)
{
	m_fTextureSize = in_TextureSize;
}

messaging::VMessageInterpreter* VProjectTextureRenderStepPart::GetMessageInterpreterForClass()
{
	static messaging::VMessageInterpreter interpreter;

	return &interpreter;
}

void VProjectTextureRenderStepPart::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddAccessorOption<VProjectTextureRenderStepPart, std::string>("texture", 
		&VProjectTextureRenderStepPart::GetTextureResource, 
		&VProjectTextureRenderStepPart::SetTextureResource);
}

std::string VProjectTextureRenderStepPart::GetTextureResource() const
{
	return m_pTexture.GetResourceName();
}

void VProjectTextureRenderStepPart::SetTextureResource(const std::string& in_NewResource)
{
	SetTexture( resource::GetResourceData<IVTexture>(in_NewResource.c_str()) );
}

//void VProjectTextureRenderStepPart::OnMessage(const messaging::VMessage& in_Message, 
//				  messaging::VMessage* in_pAnswer)
//{
//	try
//	{
//		vout << "VProjectTextureRenderStepPart received messsage" << vendl;
//
//		if( ! in_Message.HasProperty("type") )
//			return;
//
//		string request = in_Message.Get("type").Get<string>();
//
//		vout << "\trequest=" << request << vendl;
//
//		if( request == "getSettings" )
//		{
//			if( in_pAnswer == 0 )
//				return;
//
//			string textureRes;
//
//			if( &*m_pTexture != 0 && m_pTexture.GetEnclosingResource() != 0 )
//				textureRes = m_pTexture.GetEnclosingResource()->GetQualifiedName();
//            
//			in_pAnswer->AddProperty("texture", textureRes);
//		}
//		else if( request == "update" )
//		{
//			const string name = in_Message.Get("name").Get<string>();
//			const string value = in_Message.Get("value").Get<string>();
//
//			if( name == "texture" )
//			{
//				try
//				{
//					m_pTexture = GetResourceData<IVTexture>(value.c_str());
//				}
//				catch(VDataNotFoundException&)
//				{}
//			}
//		}
//	}
//	catch(VException&)
//	{}
//}


//-----------------------------------------------------------------------------

V3D_REGISTER_PART_PARSER(VProjectTextureRenderStepPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

