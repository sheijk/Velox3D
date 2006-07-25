#ifndef V3D_VSHADOWMAPRENDERSTEPPART_2006_07_23_H
#define V3D_VSHADOWMAPRENDERSTEPPART_2006_07_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Resource.h>

#include <V3d/Graphics/IVTexture.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics/IVMaterial.h>

#include <V3d/Scene/IVRenderStepPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VShadowMapRenderStepPart : public IVRenderStepPart
{
public:
	VShadowMapRenderStepPart();
	virtual ~VShadowMapRenderStepPart();

	virtual void Activate();
	virtual void Render(IVGraphicsPart* in_pScene);

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	void AquireResources();
	vbool HasAquiredResources() const;

	resource::VResourceDataPtr<graphics::IVDevice> m_hShadowMapDevice;
	resource::VResourceDataPtr<const graphics::IVTexture> m_hDepthTexture;
	resource::VResourceDataPtr<const graphics::IVMaterial> m_hShadowMapShader;

	vuint m_nShadowMapSize;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(
	v3d::scene::VShadowMapRenderStepPart, 
	v3d::scene::IVRenderStepPart);
//-----------------------------------------------------------------------------
#endif // V3D_VSHADOWMAPRENDERSTEPPART_2006_07_23_H
