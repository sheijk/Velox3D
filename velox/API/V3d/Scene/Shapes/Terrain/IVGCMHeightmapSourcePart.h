/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVGCMHEIGHTMAPSOURCEPART_2007_04_27_H
#define V3D_IVGCMHEIGHTMAPSOURCEPART_2007_04_27_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
//-----------------------------------------------------------------------------
namespace geomclip {
	class HeightmapSource;
}

namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Provides terrain data for the terrain renderer
 * @author sheijk
 */
class IVGCMHeightmapSourcePart : public entity::IVPart
{
public:
	virtual ~IVGCMHeightmapSourcePart() {};

	virtual geomclip::HeightmapSource* GetHeightmapSource() = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::IVGCMHeightmapSourcePart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_IVGCMHEIGHTMAPSOURCEPART_2007_04_27_H

