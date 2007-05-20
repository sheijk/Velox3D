/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VGCMTERRAINPART_2007_04_21_H
#define V3D_VGCMTERRAINPART_2007_04_21_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/VMeshPartBase.h>
#include <V3d/Scene/Shapes/Terrain/IVGCMHeightmapSourcePart.h>
#include <V3d/Scene/VSimpleShooting.h>
//-----------------------------------------------------------------------------
namespace geomclip {
	class Terrain;
	class HeightmapSource;
}

namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VGCMTerrainPart : public VMeshPartBase
{
public:
	VGCMTerrainPart();
	virtual ~VGCMTerrainPart();

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual vuint GetPassCount() const;
	virtual void ApplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const;
	virtual void UnapplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const;

	virtual const math::VRBTransform& GetModelTransform() const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

	virtual void Disconnect(
		entity::VPartDependency::Location in_Location,
		const std::string& in_Id,
		entity::IVPart& in_Part);

protected:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

	virtual void OnActivate();
	virtual void OnDeactivate();

private:
	entity::VNodeConnection<IVGCMHeightmapSourcePart> m_pHeightmapSourcePart;
	entity::VNodeConnection<VSimpleShooting> m_pShooting;

	VSharedPtr<geomclip::HeightmapSource> m_pHeightmapSource;
	VSharedPtr<geomclip::Terrain> m_pTerrain;

	vbool m_bColoredRegions;
	vbool m_bWireframe;
	vbool m_bUpdateRegions;

	std::string m_strVertexShaderRes;
	std::string m_strFragmentShaderRes;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT( v3d::scene::VGCMTerrainPart, v3d::scene::IVShapePart );
//-----------------------------------------------------------------------------
#endif // V3D_VGCMTERRAINPART_2007_04_21_H

