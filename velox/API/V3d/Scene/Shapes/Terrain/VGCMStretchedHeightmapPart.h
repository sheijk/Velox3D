/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VGCMSTRETCHEDHEIGHTMAPPART_2007_04_27_H
#define V3D_VGCMSTRETCHEDHEIGHTMAPPART_2007_04_27_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/Shapes/Terrain/VGCMRawHeightmapPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VGCMStretchedHeightmapPart : public VGCMRawHeightmapPart
{
public:
	VGCMStretchedHeightmapPart();
	virtual ~VGCMStretchedHeightmapPart();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:
	virtual void LoadHeightmap();
	vbool SettingsValid();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VGCMStretchedHeightmapPart, v3d::scene::IVGCMHeightmapSourcePart);
//-----------------------------------------------------------------------------
#endif // V3D_VGCMSTRETCHEDHEIGHTMAPPART_2007_04_27_H

