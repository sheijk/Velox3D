/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VNAIVELIGHTMANAGER_2006_01_21_H
#define V3D_VNAIVELIGHTMANAGER_2006_01_21_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVLightManager.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
	class VLight;
}

namespace scene {
//-----------------------------------------------------------------------------
class VLightPart;
class IVShapePart;

/**
 * A simple light manager. Will always try to activate all registered lights
 *
 * @author sheijk
 */
class VNaiveLightManager : public IVLightManager
{
public:
	virtual void Add(VLightPart* in_pLight);
	virtual void Remove(VLightPart* in_pLight);

	void ApplyLights(graphics::IVDevice* in_pDevice, const IVShapePart* in_pShape);

	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

	virtual VRangeIterator<graphics::VLight> Lights();

private:
	typedef std::set<VLightPart*> LightSet;
	LightSet m_Lights;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VNaiveLightManager, v3d::scene::IVLightManager);
//-----------------------------------------------------------------------------
#endif // V3D_VNAIVELIGHTMANAGER_2006_01_21_H

