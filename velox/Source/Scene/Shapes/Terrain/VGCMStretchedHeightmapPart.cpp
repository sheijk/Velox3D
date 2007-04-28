/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Scene/Shapes/Terrain/VGCMStretchedHeightmapPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Entity/VGenericPartParser.h>
#include "StretchedHeightmapSource.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VGCMStretchedHeightmapPart::VGCMStretchedHeightmapPart()
{
}

/**
 * d'tor
 */
VGCMStretchedHeightmapPart::~VGCMStretchedHeightmapPart()
{
}

vbool VGCMStretchedHeightmapPart::SettingsValid()
{
	return m_strHeightmapFileName != ""
		&& m_nFileWidth != 0
		&& m_nFileBitDepth != 0
		&& m_fMaxHeight > 0.0f;
}

void VGCMStretchedHeightmapPart::LoadHeightmap()
{
	if( SettingsValid() )
	{
		m_pHeightmap.Assign( new geomclip::StretchedHeightmapSource(
			100.0f,
			m_strHeightmapFileName.c_str(),
			m_nFileWidth,
			m_nFileBitDepth,
			m_fMaxHeight,
			m_bFileBigEndian
			? geomclip::RawHeightmapSource::BigEndian
			: geomclip::RawHeightmapSource::LittleEndian ) );
	}
}

V3D_REGISTER_PART_PARSER(VGCMStretchedHeightmapPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

