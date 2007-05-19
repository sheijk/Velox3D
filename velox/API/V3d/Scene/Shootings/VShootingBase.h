/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSHOOTINGBASE_2005_12_10_H
#define V3D_VSHOOTINGBASE_2005_12_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVShooting.h>
#include <V3d/Entity/VPartBase.h>
#include <V3d/Scene/IVRenderStepPart.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVLightManager;

/**
 */
class VShootingBase : public entity::VPartBaseAdapter<IVShooting>
{
public:
	VShootingBase();
	virtual ~VShootingBase();

	void Add(IVRenderStepPart* in_pRenderStep);
	void Remove(IVRenderStepPart* in_pRenderStep);

	void AddPreShooting(IVShooting* in_pPreShooting);
	void RemovePreShooting(IVShooting* in_pPreShooting);

	virtual void UpdateAndCull();
	virtual void Render();

	virtual vbool IsActive() const;

protected:
	virtual void OnActivate();
	virtual void OnDeactivate();

	virtual graphics::IVDevice* GetRenderTarget() = 0;
	virtual graphics::IVCamera* GetCamera() = 0;
	virtual scene::IVGraphicsPart* GetScene() = 0;

	void UpdateAndCullPreShootings();
	void RenderPreShootings();

	void SetupRenderSteps();

	typedef std::vector<IVRenderStepPart*> RenderStepArray;
	RenderStepArray m_RenderSteps;

	typedef std::vector<IVShooting*> ShootingArray;
	ShootingArray m_PreShootings;

	entity::VPartConnection<IVLightManager> m_pLightManager;

	entity::VPartConnection<VShootingBase> m_pParentShooting;
private:
	vbool m_bActive;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VShootingBase, v3d::scene::IVShooting);
//-----------------------------------------------------------------------------
#endif // V3D_VSHOOTINGBASE_2005_12_10_H

