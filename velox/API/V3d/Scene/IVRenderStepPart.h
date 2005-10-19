#ifndef V3D_IVRENDERSTEPPART_2005_10_19_H
#define V3D_IVRENDERSTEPPART_2005_10_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Scene/IVGraphicsPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VSimpleShooting;

/**
 */
class IVRenderStepPart : public entity::VPartBase
{
public:
	IVRenderStepPart();
	virtual ~IVRenderStepPart();

	virtual void Render(IVGraphicsPart* in_pScene) = 0;

	graphics::IVDevice* GetPredecessorDevice() const;

	graphics::IVDevice* GetOutputDevice() const;
	void SetOutputDevice(graphics::IVDevice* in_OutputDevice);

	virtual void Activate();
	virtual void Deactivate();

private:
	/** The device this render step will render to */
	graphics::IVDevice* m_pOutputDevice;

	entity::VPartConnection<VSimpleShooting> m_pShooting;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_IVRENDERSTEPPART_2005_10_19_H
