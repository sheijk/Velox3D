/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VCUBEMAPSHOOTING_2007_06_23_H
#define V3D_VCUBEMAPSHOOTING_2007_06_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVShooting.h>
#include <V3d/Scene/Shootings/VShootingBase.h>
#include <V3d/Resource/VResourceDataPtr.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
	class VCubeMapTexture;
	class VCubeMapContext;
}}

namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVSceneManagerPart;

/**
 * Will render to an (axis aligned) cube map
 *
 * @author sheijk
 */
class VCubemapShooting : public IVShooting
{
public:
	VCubemapShooting();
	virtual ~VCubemapShooting();

	virtual void UpdateAndCull();
	virtual void Render();
	virtual vbool IsActive() const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual void OnActivate();
	virtual void OnDeactivate();

	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);
private:
	void SetCubeMapResource(const std::string& resourceName);
	std::string GetCubeMapResource() const;

	entity::VNodeConnection<IVSceneManagerPart> m_pScene;
	entity::VNodeConnection<VShootingBase> m_pParentShooting;

	resource::VResourceDataPtr<graphics::VCubeMapTexture> m_pCubeMapTexture;
	resource::VResourceDataPtr<graphics::IVDevice> m_pDevice;
	resource::VResourceDataPtr<graphics::VCubeMapContext> m_pContext;
	//graphics::VCubeMapContext* m_pContext;
	//graphics::IVDevice* m_pDevice;

	vuint m_nCubemapSize;

	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VCubemapShooting, v3d::scene::IVShooting);
//-----------------------------------------------------------------------------
#endif // V3D_VCUBEMAPSHOOTING_2007_06_23_H

