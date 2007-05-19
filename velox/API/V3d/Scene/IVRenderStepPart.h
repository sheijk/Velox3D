/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVRENDERSTEPPART_2005_10_19_H
#define V3D_IVRENDERSTEPPART_2005_10_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Scene/IVGraphicsPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VShootingBase;

/**
 */
class IVRenderStepPart : public entity::VPartBase
{
public:
	IVRenderStepPart();
	virtual ~IVRenderStepPart();

	virtual void Render(IVGraphicsPart* in_pScene) = 0;

	virtual graphics::IVDevice* GetPredecessorDevice() const;

	virtual graphics::IVDevice* GetOutputDevice() const;
	virtual void SetOutputDevice(graphics::IVDevice* in_OutputDevice);

private:
	virtual void OnActivate();
	virtual void OnDeactivate();

	/** The device this render step will render to */
	graphics::IVDevice* m_pOutputDevice;

	entity::VPartConnection<VShootingBase> m_pShooting;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::IVRenderStepPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_IVRENDERSTEPPART_2005_10_19_H

