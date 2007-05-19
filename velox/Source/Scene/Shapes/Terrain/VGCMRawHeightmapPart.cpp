/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Scene/Shapes/Terrain/VGCMRawHeightmapPart.h>
//-----------------------------------------------------------------------------

#include "RawHeightmapSource.h"
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VGCMRawHeightmapPart::VGCMRawHeightmapPart()
{
	m_nFileBitDepth = 0;
	m_nFileWidth = 0;
	m_bFileBigEndian = false;
	m_fMaxHeight = 0.0f;
}

/**
 * d'tor
 */
VGCMRawHeightmapPart::~VGCMRawHeightmapPart()
{
}

geomclip::HeightmapSource* VGCMRawHeightmapPart::GetHeightmapSource()
{
	return m_pHeightmap.Get();
}

void VGCMRawHeightmapPart::OnActivate()
{
	if( m_pHeightmap == NULL )
	{
		LoadHeightmap();
	}
}

void VGCMRawHeightmapPart::OnDeactivate()
{
}

void VGCMRawHeightmapPart::LoadHeightmap()
{
	m_pHeightmap.Assign( new geomclip::RawHeightmapSource(
		m_strHeightmapFileName.c_str(), 
		m_nFileWidth, 
		m_nFileBitDepth, 
		m_fMaxHeight, 
		m_bFileBigEndian 
		? geomclip::RawHeightmapSource::BigEndian 
		: geomclip::RawHeightmapSource::LittleEndian) );
}

void VGCMRawHeightmapPart::SetReload(vbool in_bReload)
{
	if( in_bReload )
	{
		m_pHeightmap.Release();
		LoadHeightmap();
	}
}

vbool VGCMRawHeightmapPart::GetReload() const
{
	return false;
}

void VGCMRawHeightmapPart::OnMessage(
	const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	static messaging::VMessageInterpreter interpreter;

	if( ! interpreter.IsInitialized() )
	{
		interpreter.AddMemberOption("file-name", this, &m_strHeightmapFileName);
		interpreter.AddMemberOption("file-width", this, &m_nFileWidth);
		interpreter.AddMemberOption("file-bitdepth", this, &m_nFileBitDepth);
		interpreter.AddMemberOption("file-bigendian", this, &m_bFileBigEndian);
		interpreter.AddMemberOption("max-height", this, &m_fMaxHeight);

		interpreter.SetInitialized(true);
	}

	interpreter.HandleMessage(this, in_Message, in_pAnswer);
}


V3D_REGISTER_PART_PARSER(VGCMRawHeightmapPart);

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

