/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSHADOWMAPSHOOTING_2006_09_24_H
#define V3D_VSHADOWMAPSHOOTING_2006_09_24_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Scene/VSimpleShooting.h>
#include <V3d/Entity/VPartDependency.h>
#include <V3d/Graphics/Parameters/VGenericValue.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
	class IVRenderContext;
	class VTextureValue;
	class IVDevice;
}}

namespace v3d { namespace scene {
	class IVLightManager;
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VShadowMapShooting : public VSimpleShooting
{
public:
	VShadowMapShooting();
	virtual ~VShadowMapShooting();

	virtual void Render();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	void AquireResources();
	vbool HasAquiredResources();
	void RenderDepthMap(const graphics::VLight& light);
	void CalculateTextureMatrix(
		math::VMatrix44f& out_TextureMatrix,
		const graphics::VLight& in_Light);

	//resource::VResourceDataPtr<graphics::IVRenderContext> m_pDepthMapContext;
	resource::VResourceDataPtr<graphics::IVDevice> m_pDevice;

	entity::VNodeConnection<IVLightManager> m_pLightManager;

	VSharedPtr<graphics::VTextureValue> m_pDepthMapValue;
	VSharedPtr<graphics::VFloat44ParamValue> m_pDepthMapMatrixValue;

	vuint m_nShadowMapSize;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VShadowMapShooting, v3d::scene::VSimpleShooting);
//-----------------------------------------------------------------------------
#endif // V3D_VSHADOWMAPSHOOTING_2006_09_24_H

