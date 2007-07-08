/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Shootings/VShadowMapShooting.h>
//-----------------------------------------------------------------------------
#include "../../Graphics/OpenGL/Context/VFrameBufferObjectContext.h"
#include <V3d/Graphics/IVGraphicsService.h>
#include <V3d/Resource.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Scene/IVLightManager.h>
#include <V3d/Graphics/VLight.h>
#include <V3d/Scene/IVShapePart.h>
#include <V3d/Graphics/OpenGLUtils.h>
#include <V3d/Math/VVectorOps.h>
#include <V3d/Graphics/Misc/MiscUtils.h>
#include <V3d/Math.h>
#include <V3d/Graphics/IVGraphicsService.h>
#include <V3d/Graphics/Parameters/VTextureValue.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace entity;

namespace {
	const std::string g_ShadowMapResource = "/graphics/shadowX";
	const std::string g_DepthMapShaderParamName = "v3d_DepthMap";
	const std::string g_DepthMapMatrixParamName = "v3d_DepthMapMatrix";

	const vuint g_ShadowMapDefaultSize = 512;

	struct VProjection
	{
		vfloat32 fNearPlane;
		vfloat32 fFarPlane;
		vfloat32 fAspectRatio;
		vfloat32 fFOV;

		VProjection(vfloat32 fov, vfloat32 aspect, vfloat32 nearPlane, vfloat32 farPlane)
		{
			fNearPlane = nearPlane;
			fFarPlane = farPlane;
			fAspectRatio = aspect;
			fFOV = fov;
		}
	};

	VProjection lightProjection(45.0f, 1.0f, 10.0f, 400.0f);
}

namespace {
	math::VMatrix44f TranslationMatrix(const math::VVector3f& pos)
	{
		return math::TranslationMatrix(pos.GetX(), pos.GetY(), pos.GetZ());
	}

	void multGlMatrix(const math::VRBTransform& transform)
	{
		using namespace math;

		graphics::MultGLMatrix(transform.AsMatrix());

	}

	/**
	* Copies the given transformation into it's inverse
	* @author sheijk
	*/
	void MakeInverse(math::VRBTransform& io_Transform)
	{
		using namespace math;

		// invert translation part
		VRBTransform translation;
		translation.SetPosition(- io_Transform.GetPosition());

		// transpose orientation part
		const VVector3f x = io_Transform.GetXAxis();
		const VVector3f y = io_Transform.GetYAxis();
		const VVector3f z = io_Transform.GetZAxis();

		VRBTransform orientation;
		orientation.SetXAxis(VVector3f(x.GetX(), y.GetX(), z.GetX()));
		orientation.SetYAxis(VVector3f(x.GetY(), y.GetY(), z.GetY()));
		orientation.SetZAxis(VVector3f(x.GetZ(), y.GetZ(), z.GetZ()));

		// multiply the inversed transformations
		Concatenate(io_Transform, orientation, translation);
	}

	void MakeProjectionMatrix(
		math::VMatrix44f* out_pMatrix,
		const VProjection& in_Projection)
	{
		math::MakeProjectionMatrix(out_pMatrix,
			in_Projection.fFOV,
			in_Projection.fAspectRatio,
			in_Projection.fNearPlane,
			in_Projection.fFarPlane);
	}
}

/**
 * standard c'tor
 */
VShadowMapShooting::VShadowMapShooting()
: m_pLightManager(RegisterTo())
{
	m_nShadowMapSize = g_ShadowMapDefaultSize;
}

/**
 * d'tor
 */
VShadowMapShooting::~VShadowMapShooting()
{
}

class VDepthMapFrameBufferObjectContext : public graphics::VFrameBufferObjectContext
{
public:
	VDepthMapFrameBufferObjectContext(
		const graphics::VDisplaySettings& in_DisplaySettings,
		graphics::IVRenderContext* in_pParentContext)
		:
/*	
	VFrameBufferObjectContext(in_DisplaySettings, in_pParentContext)
	{
	}
/*/	VFrameBufferObjectContext(in_DisplaySettings, in_pParentContext)
	{
		in_pParentContext->MakeCurrent();

		const vuint width = in_DisplaySettings.GetWidth();
		const vuint height = in_DisplaySettings.GetHeight();

		glGenTextures(1, &m_TextureId);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);
		std::vector<vbyte> pixels;
		pixels.resize(width*height*4);

		for(vuint y = 0; y < height; ++y)
		for(vuint x = 0; x < width; ++x)
			pixels[y*width+height] = 128;

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_DEPTH_COMPONENT24,
			width, height,
			0,
			GL_DEPTH_COMPONENT,
			GL_UNSIGNED_BYTE,
			&pixels[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glGenFramebuffersEXT(1, &m_FBOId);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_FBOId);

		glFramebufferTexture2DEXT(
			GL_FRAMEBUFFER_EXT,
			GL_DEPTH_ATTACHMENT_EXT,
			GL_TEXTURE_2D,
			m_TextureId,
			0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		if( GL_FRAMEBUFFER_COMPLETE_EXT != glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) )
		{
			V3D_THROW(VException, "Could not create FBO");
		}

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

		V3D_GLCHECK("");
	}
/**/
};

void VShadowMapShooting::AquireResources()
{
	// create fbo context
	graphics::VDisplaySettings displaySettings;
	displaySettings.SetSize(m_nShadowMapSize, m_nShadowMapSize);
	displaySettings.SetBitsPerPixel(32);
	displaySettings.SetDepthBits(0); // change this!
 	
	graphics::IVRenderContext* pRenderContext = new VDepthMapFrameBufferObjectContext(
		displaySettings,
		graphics::VGraphicsServicePtr()->GetMainDevice()->GetRenderContext());

	resource::VResourceId res = VServicePtr<resource::IVResourceManager>()->CreateResource(g_ShadowMapResource.c_str());
	res->AddData(pRenderContext);
	//m_pDepthMapContext = res->GetMutableData<graphics::IVRenderContext>();
	m_pDevice = res->GetMutableData<graphics::IVDevice>();

	m_pDepthMapValue.Assign(new graphics::VTextureValue());
	m_pDepthMapValue->SetTextureResource(g_ShadowMapResource);

	m_pDepthMapMatrixValue.Assign(new graphics::VFloat44ParamValue());
	m_pDepthMapMatrixValue->SetValue(math::IdentityMatrix());
}

vbool VShadowMapShooting::HasAquiredResources()
{
	return m_pDevice != 0;
	//return m_pDepthMapContext != 0;
}

void VShadowMapShooting::Render()
{
	if( ! HasAquiredResources() )
		AquireResources();

	// render depth map to offscreen device
	//m_pDepthMapContext->MakeCurrent();
	m_pDevice->BeginScene();
	glViewport(0, 0, m_nShadowMapSize, m_nShadowMapSize);

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//gluPerspective(45.0f, 4.0/3.0, 1.0, 1000.0);
	//glMatrixMode(GL_MODELVIEW);

	math::VMatrix44f depthMapMatrix;

	VRangeIterator<graphics::VLight> lights = m_pLightManager->Lights();
	while( lights.HasNext() )
	{
		RenderDepthMap(*lights);
		CalculateTextureMatrix(depthMapMatrix, *lights);
		break; // only one light supported, yet
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	m_pDevice->EndScene();
	//m_pDepthMapContext->SwapBuffers();

	using namespace graphics;

	static VGraphicsServicePtr pGfxService;
	pGfxService->SetSystemParam(g_DepthMapShaderParamName, m_pDepthMapValue);
	m_pDepthMapMatrixValue->SetValue(depthMapMatrix);
	pGfxService->SetSystemParam(g_DepthMapMatrixParamName, m_pDepthMapMatrixValue);

	// do normal rendering
	VSimpleShooting::Render();
}

void VShadowMapShooting::CalculateTextureMatrix(
	math::VMatrix44f& out_TextureMatrix, 
	const graphics::VLight& in_Light)
{
	using namespace math;

	Identity(out_TextureMatrix);
	Translate(out_TextureMatrix, .5f, .5f, .5f);
	Scale(out_TextureMatrix, .5f, .5f, .5f);
// perspective..
	VMatrix44f projectionMatrix;
	MakeProjectionMatrix(&projectionMatrix, lightProjection);
	//MakeProjectionMatrix(&projectionMatrix, 45.0f, 1.0f, 10.0f, 1000.0f);
	Mult(out_TextureMatrix, out_TextureMatrix, projectionMatrix);
// orientation
	VRBTransform lightT = in_Light.GetTransform();
	MakeInverse(lightT);
	Mult(out_TextureMatrix, out_TextureMatrix, lightT.AsMatrix());
// inverse view
	//VMatrix44f viewMat = GetRenderTarget()->GetMatrix(graphics::IVDevice::ViewMatrix);
	//VRBTransform viewTransform;
	//viewTransform.Set(viewMat);
	VRBTransform viewTransform = GetRenderTarget()->GetViewTransform();
	MakeInverse(viewTransform);
	//out_TextureMatrix = viewTransform.AsMatrix();
	Mult(out_TextureMatrix, out_TextureMatrix, viewTransform.AsMatrix());
}

void VShadowMapShooting::RenderDepthMap(const graphics::VLight& light)
{
	static resource::VResourceDataPtr<graphics::IVMaterial> pMat = 
		resource::GetMutableResourceData<graphics::IVMaterial>("/edit/mat/showNormals.v3dmat");

	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//gluPerspective(45.0f, 1.0f, 10.0f, 1000.0f);
	math::VMatrix44f projection;
	MakeProjectionMatrix(&projection, lightProjection);
	//math::MakeProjectionMatrix(&projection, 45.0f, 1.0f, 10.0f, 1000.0f);
	m_pDevice->SetMatrix(graphics::IVDevice::ProjectionMatrix, projection);

	math::VRBTransform lightT = light.GetTransform();
	MakeInverse(lightT);
	m_pDevice->SetViewTransform( lightT );
	//m_pDevice->SetMatrix(graphics::IVDevice::ViewMatrix, lightT.AsMatrix());

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//math::VRBTransform lightT = light.GetTransform();
	//MakeInverse(lightT);
	//multGlMatrix(lightT);

	graphics::ApplyMaterial(*GetRenderTarget(), &pMat->GetPass(0));

	VRangeIterator<const IVShapePart> shape = GetScene()->GetVisibleMeshes();
	while( shape.HasNext() )
	{
		const IVShapePart* pShape = &*shape;

		//glPushMatrix();
		//multGlMatrix(shape->GetModelTransform());
		m_pDevice->SetMatrix(graphics::IVDevice::ModelMatrix, shape->GetModelTransform().AsMatrix());

		//m_pLightManager->ApplyLights(GetRenderTarget(), pShape);

		//shape->ApplyPassStates(0, *GetRenderTarget());
		shape->SendGeometry(*GetRenderTarget());
		//shape->UnapplyPassStates(0, *GetRenderTarget());

		//glPopMatrix();

		++shape;
	}

	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
}

V3D_REGISTER_PART_PARSER(VShadowMapShooting);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

