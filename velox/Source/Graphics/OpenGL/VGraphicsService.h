#ifndef V3D_VGRAPHICSSERVICE_2006_04_19_H
#define V3D_VGRAPHICSSERVICE_2006_04_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVGraphicsService.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VGraphicsService : public IVGraphicsService
{
public:
	VGraphicsService();
	virtual ~VGraphicsService();

	virtual void SetMainDevice(IVDevice* in_pDevice);
	virtual IVDevice* GetMainDevice() const;

	virtual VAutoPtr<IVDevice> CreateOffscreenDevice(const VDisplaySettings&) const;

private:
	IVDevice* m_pMainDevice;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VGRAPHICSSERVICE_2006_04_19_H