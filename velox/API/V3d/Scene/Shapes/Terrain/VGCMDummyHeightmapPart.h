/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VGCMDUMMYHEIGHTMAPPART_2007_04_27_H
#define V3D_VGCMDUMMYHEIGHTMAPPART_2007_04_27_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/Shapes/Terrain/IVGCMHeightmapSourcePart.h>
#include <V3d/Entity/VUnconnectedPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VGCMDummyHeightmapPart : public entity::VUnconnectedPartAdapter<IVGCMHeightmapSourcePart>
{
public:
	VGCMDummyHeightmapPart();
	virtual ~VGCMDummyHeightmapPart();

	virtual geomclip::HeightmapSource* GetHeightmapSource();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual void OnActivate();
	virtual void OnDeactivate();

private:
	VSharedPtr<geomclip::HeightmapSource> m_pHeightmapSource;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VGCMDummyHeightmapPart, v3d::scene::IVGCMHeightmapSourcePart);
//-----------------------------------------------------------------------------
#endif // V3D_VGCMDUMMYHEIGHTMAPPART_2007_04_27_H

