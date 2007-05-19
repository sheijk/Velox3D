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
	return m_pDepthMapContext != 0;
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

		GLuint depthTex = 0;
		glGenTextures(1, &depthTex);
		glBindTexture(GL_TEXTURE_2D, depthTex);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_DEPTH_COMPONENT24,
			width, height,
			0,
			GL_DEPTH_COMPONENT,
			GL_FLOAT,
			0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		GLuint fbo = 0;
		glGenFramebuffersEXT(1, &fbo);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);

		glFramebufferTexture2DEXT(
			GL_FRAMEBUFFER_EXT,
			GL_DEPTH_ATTACHMENT_EXT,
			GL_TEXTURE_2D,
			depthTex,
			0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		if( GL_FRAMEBUFFER_COMPLETE_EXT != glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) )
		{
			V3D_THROW(VException, "Could not create FBO");
		}

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
};

void VShadowMapRenderStepPart::AquireResources()
{
	// create fbo context
	graphics::VDisplaySettings displaySettings;
	displaySettings.SetSize(m_nShadowMapSize, m_nShadowMapSize);
	displaySettings.SetBitsPerPixel(0);
	displaySettings.SetDepthBits(16);
 	
	graphics::IVRenderContext* pRenderContext = new VDepthMapFrameBufferObjectContext(
		displaySettings,
		graphics::VGraphicsServicePtr()->GetMainDevice()->GetRenderContext());

	resource::VResourceId res = VServicePtr<resource::IVResourceManager>()->CreateResource("/graphics/shadowX");
	res->AddData(pRenderContext);
	m_pDepthMapContext = res->GetMutableData<graphics::IVRenderContext>();

	//              graphics::IVRenderContext* pRenderContext =     graphics::VGraphicsServicePtr()
	//                      ->GetMainDevice()->CreateOffscreenContext(&displaySettings);
}

void VShadowMapRenderStepPart::OnActivate()
{
	if( ! HasAquiredResources() )
		AquireResources();
}

void VShadowMapRenderStepPart::OnDeactivate()
{
}

/*
TODO:
merke: shooting(klasse) registrieren, welche der lichtquelle aus (IVLightManager->Lights())
in depthmapfborendercontect rendert, dann szene 1x normal rendern und dann mit compare to
depth / schwarz drueber blenden rendern
*/
void VShadowMapRenderStepPart::Render(IVGraphicsPart* in_pScene)
{
	// make fbo current
	// render from each light's point of view
	// make previous 
}


V3D_REGISTER_PART_PARSER(VShadowMapRenderStepPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------


