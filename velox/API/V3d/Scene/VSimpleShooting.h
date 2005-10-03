#ifndef V3D_VSIMPLESHOOTING_2005_09_24_H
#define V3D_VSIMPLESHOOTING_2005_09_24_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVShooting.h>
#include <V3d/Scene/IVGraphicsPart.h>
#include <V3d/Entity/VPartBase.h>
#include <V3d/Graphics/IVDevice.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VSimpleShooting : public entity::VPartBaseAdapter<IVShooting>
{
public:
	VSimpleShooting();

	virtual void UpdateAndCull();
	virtual void Render();

	void SetRenderTarget(graphics::IVDevice* in_pDevice);
	graphics::IVDevice* GetRenderTarget() const;
	
	void SetCamera(graphics::IVCamera* in_pCamera);
	graphics::IVCamera* GetCamera() const;

	virtual void Activate();
	virtual void Deactivate();

	virtual vbool IsActive() const;

private:
	entity::VPartConnection<IVGraphicsPart> m_pScene;
	graphics::IVDevice* m_pDevice;
	graphics::IVCamera* m_pCamera;
	vbool m_bActive;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLESHOOTING_2005_09_24_H
