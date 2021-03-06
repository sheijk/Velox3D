/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/VSimpleShooting.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics.h>
#include <V3d/Graphics.h>
#include <V3d/Scene/IVShapePart.h>
#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;
using namespace entity;

VSimpleShooting::VSimpleShooting() :
	m_pScene(RegisterTo())
{
	m_pDevice = 0;
	m_pCamera = 0;
}

VSimpleShooting::VSimpleShooting(VNodeDependency::Condition in_SceneCondition)
				:
	m_pScene(in_SceneCondition, RegisterTo())
{
	m_pDevice = 0;
	m_pCamera = 0;
}

void VSimpleShooting::SetRenderTarget(graphics::IVDevice* in_pDevice)
{
	m_pDevice = in_pDevice;
	SetupRenderSteps();
}

graphics::IVDevice* VSimpleShooting::GetRenderTarget()
{
	return m_pDevice;
}

//void VSimpleShooting::SetCamera(graphics::IVCamera* in_pCamera)
//{
//	m_pCamera = in_pCamera;
//}

graphics::IVCamera* VSimpleShooting::GetCamera()
{
	return m_pCamera;
}

scene::IVGraphicsPart* VSimpleShooting::GetScene()
{
	return m_pScene.Get();
}

void VSimpleShooting::Register(graphics::IVCamera* in_pCamera)
{
	m_Cameras.push_back(in_pCamera);

	if( m_pCamera == 0 )
		SetActiveCamera(0);
}

void VSimpleShooting::Unregister(graphics::IVCamera* in_pCamera)
{
	std::remove(m_Cameras.begin(), m_Cameras.end(), in_pCamera);

	if( m_pCamera = in_pCamera )
	{
		m_pCamera = 0;
		SetActiveCamera(0);
	}
}

vuint VSimpleShooting::CameraCount() const
{
	return static_cast<vuint>(m_Cameras.size());
}

void VSimpleShooting::SetActiveCamera(vuint in_nNum)
{
	if( in_nNum < CameraCount() )
		m_pCamera = m_Cameras[in_nNum];
}

V3D_REGISTER_PART_PARSER(VSimpleShooting);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

