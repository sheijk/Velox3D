/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Rendering/VShadowMapRenderStepPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/OpenGL.h>
#include <V3d/Graphics/Misc/MiscUtils.h>
#include <V3d/Graphics/IVGraphicsService.h>
#include <V3d/Scene/IVShapePart.h>
#include "../../Graphics/OpenGL/Context/VFrameBufferObjectContext.h"
#include <V3d/Scene/IVLightManager.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

namespace {
	const std::string g_ShaderResourceName("/system/mat/shadowmap.v3dmat");
	const std::string g_TextureResourceNameBase("/system/graphics/shadowmap");

	std::string GetTextureResourceName(vuint size)
	{
		std::stringstream stream;
		stream << g_TextureResourceNameBase << size << "x" << size;
		return stream.str();
	}
}

/**
 * standard c'tor
 */
VShadowMapRenderStepPart::VShadowMapRenderStepPart()
	: m_pLightManager(entity::VPartDependency::Neighbour, RegisterTo())
{
	m_nShadowMapSize = 512;
}

/**
 * d'tor
 */
VShadowMapRenderStepPart::~VShadowMapRenderStepPart()
{
}

vbool VShadowMapRenderStepPart::HasAquiredResources() const
{
	return 
		m_hShadowMapShader != 0 &&
		m_hDepthTexture != 0 &&
		m_hShadowMapDevice != 0;
}

class VDepthMapFrameBufferObjectContext : public graphics::VFrameBufferObjectContext
{
public:
	VDepthMapFrameBufferObjectContext(
		const graphics::VDisplaySettings& in_DisplaySettings,
		graphics::IVRenderContext* in_pParentContext)
		:
	VFrameBufferObjectContext(in_DisplaySettings, in_pParentContext, NoInit)
	{
		in_pParentContext->MakeCurrent();

		const vuint width = in_DisplaySettings.GetWidth();
		const vuint height = in_DisplaySettings.GetHeight();

		// create texture
		glGenTextures(1, &m_TextureId);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
		//vbyte pixels[width*height];
		std::vector<vbyte> pixels;
		pixels.resize(width*height);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
		V3D_ASSERT(glGetError() == 0);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		glGenFramebuffersEXT(1, &m_FBOId);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_FBOId);

		glGenRenderbuffersEXT(1, &m_DepthBufferId);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_DepthBufferId);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT16, width, height);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_DepthBufferId);

		//glGenRenderbuffersEXT(1, &m_StencilBufferId);
		//glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_StencilBufferId);
		//glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_STENCIL_INDEX, width, height);
		//glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_StencilBufferId);

//		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_TextureId, 0);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, m_TextureId, 0);

		glDrawBuffer(GL_NONE);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
};

/*
class VDepthMapShooting : public VShootingBase
{
public:
	VDepthMapShooting(vuint in_nOffscreenTargetSize)
	{
	}

protected:
	virtual graphics::IVDevice* GetRenderTarget()
	{
		return &*m_hShadowMapDevice;
	}

	virtual graphics::IVCamera* GetCamera()
	{
	}

	virtual scene::IVGraphicsPart* GetScene()
	{
	}

private:
	graphics::VCamera m_Camera;
	resource::VResourceDataPtr<graphics::IVDevice> m_hShadowMapDevice;
};
*/

void VShadowMapRenderStepPart::AquireResources()
{
	using namespace resource;

	const std::string textureResourceName =
		GetTextureResourceName(m_nShadowMapSize).c_str();
	const char* textureResource = textureResourceName.c_str();

	if( ! VResourceManagerPtr()->ExistsResource(textureResource) )
	{
		VResourceManagerPtr()->CreateResource(textureResource);
	}

	VResourceId resource(textureResource);

	if( ! resource->ContainsData<graphics::IVDevice>() )
	{
		graphics::VDisplaySettings displaySettings;
		displaySettings.SetSize(m_nShadowMapSize, m_nShadowMapSize);
		displaySettings.SetBitsPerPixel(0);
		displaySettings.SetDepthBits(16);

		graphics::IVRenderContext* pRenderContext = new VDepthMapFrameBufferObjectContext(
			displaySettings, 
			graphics::VGraphicsServicePtr()->GetMainDevice()->GetRenderContext());
//		graphics::IVRenderContext* pRenderContext =	graphics::VGraphicsServicePtr()
//			->GetMainDevice()->CreateOffscreenContext(&displaySettings);

		resource->AddData(pRenderContext);
	}

	m_hShadowMapDevice = resource->GetMutableData<graphics::IVDevice>();
	m_hDepthTexture = resource->GetData<graphics::IVTexture>();
	m_hShadowMapShader = GetResourceData<graphics::IVMaterial>(g_ShaderResourceName.c_str());
}

//void VShadowMapRenderStepPart::Activate()
//{
//	IVRenderStepPart::Activate();
//
//	if( ! HasAquiredResources() )
//		AquireResources();
//}

/*
TODO:
merke: shooting(klasse) registrieren, welche der lichtquelle aus (IVLightManager->Lights())
in depthmapfborendercontect rendert, dann szene 1x normal rendern und dann mit compare to
depth / schwarz drueber blenden rendern
*/

void VShadowMapRenderStepPart::Render(IVGraphicsPart* in_pScene)
{
	//V3D_ASSERT(HasAquiredResources());

	V3D_ASSERT(GetOutputDevice() != 0);
	graphics::IVDevice& device(*GetOutputDevice());

	//glClearColor(1.0f, .0f, .0f, .0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	graphics::ApplyMaterial(device, &m_hShadowMapShader->GetPass(0));

	VRangeIterator<const IVShapePart> shape = in_pScene->GetVisibleMeshes();
	while( shape.HasNext() )
	{
		device.SetMatrix(
			graphics::IVDevice::ModelMatrix, 
			shape->GetModelTransform().AsMatrix());

		shape->SendGeometry(*GetOutputDevice());

		++shape;
	}

	//m_hShadowMapDevice->EndScene();

	//device.BeginScene();
*/
}


V3D_REGISTER_PART_PARSER(VShadowMapRenderStepPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------


