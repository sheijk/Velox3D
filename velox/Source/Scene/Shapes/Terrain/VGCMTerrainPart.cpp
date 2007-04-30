/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Scene/Shapes/Terrain/VGCMTerrainPart.h>
//-----------------------------------------------------------------------------
#include <V3d/OpenGL.h>
#include <GL/glut.h>

#include "Terrain.h"

#include <V3d/Resource.h>

#include <V3d/Messaging/VMessageInterpreter.h>
#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace geomclip;

namespace {
	const std::string DEFAULT_VERTEX_SHADER_RES = "/system/mat/gcmterrain.vert";
	const std::string DEFAULT_FRAGMENT_SHADER_RES = "/system/mat/gcmterrain.frag";
}

/**
 * standard c'tor
 */
VGCMTerrainPart::VGCMTerrainPart() :
	m_pHeightmapSourcePart(entity::VPartDependency::Neighbour, RegisterTo()),
	m_pShooting(entity::VPartDependency::Ancestor, RegisterTo())
{
	m_bColoredRegions = false;
	m_bWireframe = false;
	m_bUpdateRegions = true;

	m_strVertexShaderRes = DEFAULT_VERTEX_SHADER_RES;
	m_strFragmentShaderRes = DEFAULT_FRAGMENT_SHADER_RES;
}

/**
 * d'tor
 */
VGCMTerrainPart::~VGCMTerrainPart()
{
}

void VGCMTerrainPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	//glutWireSphere( 4.0f, 10, 10 );
	if( m_pTerrain != NULL )
	{
		if( m_bUpdateRegions )
		{
			geomclip::Orientation orientation;
			math::VVector3f campos = m_pShooting->GetCamera()->GetPosition();
			orientation.pos.x = campos.GetX();
			orientation.pos.y = campos.GetY();
			orientation.pos.z = campos.GetZ();

			m_pTerrain->tellCamera( orientation );
			m_pTerrain->update( 0.0f );
		}

		m_pTerrain->setGeometryMode( m_bWireframe ? Terrain::RMLines : Terrain::RMDefault );
		m_pTerrain->setSurfaceMode( m_bColoredRegions ? Terrain::SMColored : Terrain::SMShaded );

		m_pTerrain->render();
	}
}

vuint VGCMTerrainPart::GetPassCount() const
{
	return 1;
}

void VGCMTerrainPart::ApplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const
{
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
}

void VGCMTerrainPart::UnapplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const
{
}

//new StretchedHeightmapSource( 100.0f,
//	"../nepal_6000_16.raw", 6000, 16, 150000.0f,
//	RawHeightmapSource::BigEndian );

void v3d::scene::VGCMTerrainPart::Activate()
{
	VMeshPartBase::Activate();

	HeightmapSource* heightmapSource = 
		m_pHeightmapSourcePart.IsConnected() 
		? m_pHeightmapSourcePart->GetHeightmapSource()
		: NULL;

	if( m_pTerrain == NULL && heightmapSource != NULL )
	{
		m_pTerrain.Assign( new Terrain() );

		using resource::VTextFile;
		using resource::GetResourceData;
		std::string vertexSource = GetResourceData<VTextFile>(m_strVertexShaderRes.c_str())->GetContent();
		std::string fragmentSource = GetResourceData<VTextFile>(m_strFragmentShaderRes.c_str())->GetContent();
		m_pTerrain->setShaderSource( vertexSource, fragmentSource );
		//m_pTerrain->init( m_pHeightmapSource.Get() );
		m_pTerrain->init( heightmapSource );
	}
}

void v3d::scene::VGCMTerrainPart::Deactivate() 
{
	VMeshPartBase::Deactivate();
}

void VGCMTerrainPart::Disconnect(
	entity::VPartDependency::Location in_Location, 
	const std::string& in_Id, 
	entity::IVPart& in_Part)
{
	if( &in_Part == m_pHeightmapSourcePart.Get() )
	{
		m_pTerrain.Release();
	}
}

void VGCMTerrainPart::OnMessage(
	const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	static messaging::VMessageInterpreter interpreter;

	if( ! interpreter.IsInitialized() )
	{
		interpreter.AddMemberOption("colored-regions", this, &m_bColoredRegions);
		interpreter.AddMemberOption("wireframe", this, &m_bWireframe);
		interpreter.AddMemberOption("update-regions", this, &m_bUpdateRegions);

		interpreter.AddMemberOption("vertex-shader-res", this, &m_strVertexShaderRes);
		interpreter.AddMemberOption("fragment-shader-res", this, &m_strFragmentShaderRes);

		interpreter.SetInitialized(true);
	}

	InterpreteMessage(interpreter, in_Message, in_pAnswer);
}

namespace {
	math::VRBTransform identityTransform;
}

const math::VRBTransform& VGCMTerrainPart::GetModelTransform() const
{
	return identityTransform;
}

V3D_REGISTER_PART_PARSER( VGCMTerrainPart );
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

