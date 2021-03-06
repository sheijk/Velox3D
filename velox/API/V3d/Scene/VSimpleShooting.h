/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSIMPLESHOOTING_2005_09_24_H
#define V3D_VSIMPLESHOOTING_2005_09_24_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVGraphicsPart.h>
#include <V3d/Graphics/IVDevice.h>

#include <V3d/Scene/Shootings/VShootingBase.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVRenderStepPart;

/**
 * Simply renders the whole scene "as it is". For every visible shape it's
 * material and transform are applied and it's geometry is rendered
 *
 * Also serves as a base class for special shootings like shadow mapping etc
 *
 * @author sheijk
 */
class VSimpleShooting : public VShootingBase
{
public:
	VSimpleShooting();

	void SetRenderTarget(graphics::IVDevice* in_pDevice);
	graphics::IVDevice* GetRenderTarget();

	void Register(graphics::IVCamera* in_pCamera);
	void Unregister(graphics::IVCamera* in_pCamera);

	vuint CameraCount() const;
	void SetActiveCamera(vuint in_nNum);

	//void SetCamera(graphics::IVCamera* in_pCamera);
	graphics::IVCamera* GetCamera();

	virtual scene::IVGraphicsPart* GetScene();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	VSimpleShooting(entity::VNodeDependency::Condition in_SceneCondition);
	
	entity::VNodeConnection<IVGraphicsPart> m_pScene;
	graphics::IVDevice* m_pDevice;
	graphics::IVCamera* m_pCamera;

	std::vector<graphics::IVCamera*> m_Cameras;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VSimpleShooting, v3d::scene::VShootingBase);
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLESHOOTING_2005_09_24_H

