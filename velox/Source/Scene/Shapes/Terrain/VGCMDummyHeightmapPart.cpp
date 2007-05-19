/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Scene/Shapes/Terrain/VGCMDummyHeightmapPart.h>
//-----------------------------------------------------------------------------

#include "HeightmapSource.h"
#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace geomclip;

namespace {
	class DummyHeightmapSource : public geomclip::HeightmapSource
	{
	public:
		virtual u32 colorAt( WorldCoord x, WorldCoord y ) const
		{
			return 0;
		}
	};
}

/**
 * standard c'tor
 */
VGCMDummyHeightmapPart::VGCMDummyHeightmapPart()
{
}

/**
 * d'tor
 */
VGCMDummyHeightmapPart::~VGCMDummyHeightmapPart()
{
}

HeightmapSource* VGCMDummyHeightmapPart::GetHeightmapSource()
{
	return m_pHeightmapSource.Get();
}

void VGCMDummyHeightmapPart::OnActivate()
{
	if( m_pHeightmapSource == 0 )
	{
		m_pHeightmapSource.Assign( new DummyHeightmapSource() );
	}
}

void VGCMDummyHeightmapPart::OnDeactivate()
{
}

V3D_REGISTER_PART_PARSER(VGCMDummyHeightmapPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

