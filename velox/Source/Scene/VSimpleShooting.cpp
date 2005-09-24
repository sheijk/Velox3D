#include <V3d/Scene/VSimpleShooting.h>
//-----------------------------------------------------------------------------

#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Scene/IVShapePart.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;
using namespace entity;

VSimpleShooting::VSimpleShooting() :
	m_pScene(VPartDependency::Neighbour, RegisterTo())
{
	m_pDevice = 0;
	m_pCamera = 0;
}

void VSimpleShooting::SetRenderTarget(graphics::IVDevice* in_pDevice)
{
	m_pDevice = in_pDevice;
}

graphics::IVDevice* VSimpleShooting::GetRenderTarget() const
{
	return m_pDevice;
}

void VSimpleShooting::SetCamera(graphics::IVCamera* in_pCamera)
{
	m_pCamera = in_pCamera;
}

graphics::IVCamera* VSimpleShooting::GetCamera() const
{
	return m_pCamera;
}

void VSimpleShooting::UpdateAndCull()
{
	if( m_pScene.IsConnected() )
		m_pScene->UpdateAndCull(*m_pCamera);
}

void VSimpleShooting::Render()
{
	if( ! m_pScene.IsConnected() )
		return;
	
	VRangeIterator<const IVShapePart> shape = m_pScene->GetVisibleMeshes();
	while( shape.HasNext() )
	{
		const IVMaterial& material = shape->GetMaterial();

		for(vuint pass = 0; pass < material.PassCount(); ++pass)
		{
			ApplyMaterial(*m_pDevice, &material.GetPass(pass));
			shape->SendGeometry(*m_pDevice);
		}

		++shape;
	}
}

void VSimpleShooting::Activate()
{
}

void VSimpleShooting::Deactivate()
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
