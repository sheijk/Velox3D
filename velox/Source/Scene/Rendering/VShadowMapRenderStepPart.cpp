#include <V3d/Scene/Rendering/VShadowMapRenderStepPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/OpenGL.h>
#include <V3d/Graphics/Misc/MiscUtils.h>
#include <V3d/Graphics/IVGraphicsService.h>
#include <V3d/Scene/IVShapePart.h>
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

		graphics::IVRenderContext* pRenderContext =	graphics::VGraphicsServicePtr()
			->GetMainDevice()->CreateOffscreenContext(&displaySettings);

		resource->AddData(pRenderContext);
	}

	m_hShadowMapDevice = resource->GetMutableData<graphics::IVDevice>();
	m_hDepthTexture = resource->GetData<graphics::IVTexture>();
	m_hShadowMapShader = GetResourceData<graphics::IVMaterial>(g_ShaderResourceName.c_str());
}

void VShadowMapRenderStepPart::Activate()
{
	IVRenderStepPart::Activate();

	if( ! HasAquiredResources() )
		AquireResources();
}

void VShadowMapRenderStepPart::Render(IVGraphicsPart* in_pScene)
{
	V3D_ASSERT(HasAquiredResources());

	V3D_ASSERT(GetOutputDevice() != 0);
	graphics::IVDevice& device(*GetOutputDevice());

	//device.EndScene(graphics::IVDevice::NoFlip);

	//m_hShadowMapDevice->BeginScene();

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
}


V3D_REGISTER_PART_PARSER(VShadowMapRenderStepPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
