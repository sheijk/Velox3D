/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
namespace v3d { namespace graphics {
	class IVRenderContext;
}}

namespace v3d { namespace scene {
	class IVLightManager;
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

	//virtual void Activate();
	virtual void Render(IVGraphicsPart* in_pScene);

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

	virtual void Activate();
	virtual void Deactivate();
private:
	void AquireResources();
	vbool HasAquiredResources() const;

	entity::VPartConnection<IVLightManager> m_pLightManager;

	vuint m_nShadowMapSize;
	resource::VResourceDataPtr<graphics::IVRenderContext> m_pDepthMapContext;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(
	v3d::scene::VShadowMapRenderStepPart, 
	v3d::scene::IVRenderStepPart);
//-----------------------------------------------------------------------------
#endif // V3D_VSHADOWMAPRENDERSTEPPART_2006_07_23_H

