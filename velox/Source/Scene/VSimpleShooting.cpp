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
	m_bActive = false;
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
	V3D_ASSERT(m_bActive);

	if( m_pScene.IsConnected() )
		m_pScene->UpdateAndCull(*m_pCamera);
}

void VSimpleShooting::Render()
{
	V3D_ASSERT(m_bActive);

	if( ! m_pScene.IsConnected() )
		return;

	static vuint counter = 0;
	counter = (counter + 1) % 100;

	if( counter == 0 )
		vout << "rendering: " << vendl;

	VRangeIterator<const IVShapePart> shape = m_pScene->GetVisibleMeshes();
	while( shape.HasNext() )
	{
		const IVMaterial& material = shape->GetMaterial();

		for(vuint pass = 0; pass < material.PassCount(); ++pass)
		{
			math::VRBTransform transform = shape->GetModelTransform();

			m_pDevice->SetMatrix(IVDevice::ModelMatrix, transform.AsMatrix());

			//VMatrix44f matrix = math::TranslationMatrix(
			//	transform.GetXAxis().GetX(),
			//	transform.GetXAxis().GetY(),
			//	transform.GetXAxis().GetZ());

			//if( counter == 0 ) {
   //             vout << "\tobj at " << transform.GetXAxis() << vendl;
			//}

			//m_pDevice->SetMatrix(IVDevice::ModelMatrix, matrix);

			ApplyMaterial(*m_pDevice, &material.GetPass(pass));
			shape->SendGeometry(*m_pDevice);
		}

		++shape;
	}
}

void VSimpleShooting::Activate()
{
	m_bActive = true;
}

void VSimpleShooting::Deactivate()
{
	m_bActive = false;
}

vbool VSimpleShooting::IsActive() const
{
	return m_bActive;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
