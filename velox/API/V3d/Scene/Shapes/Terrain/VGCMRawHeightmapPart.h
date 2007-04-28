/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VGCMRAWHEIGHTMAPPART_2007_04_27_H
#define V3D_VGCMRAWHEIGHTMAPPART_2007_04_27_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/Shapes/Terrain/VGCMDummyHeightmapPart.h>
//-----------------------------------------------------------------------------
namespace geomclip {
	class RawHeightmapSource;
}

namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VGCMRawHeightmapPart : public entity::VUnconnectedPartAdapter<IVGCMHeightmapSourcePart>
{
public:
	VGCMRawHeightmapPart();
	virtual ~VGCMRawHeightmapPart();

	virtual geomclip::HeightmapSource* GetHeightmapSource();

	virtual void Activate();
	virtual void Deactivate();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer);

	virtual void LoadHeightmap();

	void SetReload(vbool in_bReload);
	vbool GetReload() const;

protected:
	std::string m_strHeightmapFileName;
	vuint m_nFileBitDepth;
	vuint m_nFileWidth;
	vbool m_bFileBigEndian;
	vfloat32 m_fMaxHeight;

	VSharedPtr<geomclip::RawHeightmapSource> m_pHeightmap;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VGCMRawHeightmapPart, v3d::scene::IVGCMHeightmapSourcePart);
//-----------------------------------------------------------------------------
#endif // V3D_VGCMRAWHEIGHTMAPPART_2007_04_27_H

