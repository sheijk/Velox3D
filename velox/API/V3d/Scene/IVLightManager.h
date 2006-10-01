/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVLIGHTMANAGER_2006_01_21_H
#define V3D_IVLIGHTMANAGER_2006_01_21_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
	class IVDevice;
	class VLight;
}}

namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VLightPart;
class IVShapePart;

/**
 * A light manager stores all lights in the scene graph and applies it to the
 * device. Depending on the implementation, some lights may be omitted (if they
 * are too far away, if there are too many lights, etc.
 *
 * @author sheijk
 */
class IVLightManager : public entity::IVPart
{
public:
	virtual void Add(VLightPart* in_pLight) = 0;
	virtual void Remove(VLightPart* in_pLight) = 0;

	/** Apply all lights for the given shape */
	virtual void ApplyLights(graphics::IVDevice* in_pDevice, const IVShapePart* in_pShape) = 0;

	virtual VRangeIterator<graphics::VLight> Lights() = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::IVLightManager, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_IVLIGHTMANAGER_2006_01_21_H

