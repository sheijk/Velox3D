/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVGRAPHICSSERVICE_2006_04_19_H
#define V3D_IVGRAPHICSSERVICE_2006_04_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/SmartPtr/VAutoPtr.h>
#include <V3d/Graphics/GraphicsExceptions.h>

#include <V3d/Core/VNamedObject.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
	class IVMaterial;
	class IVParameterValue;
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVDevice;
class VDisplaySettings;

V3D_DECLARE_EXCEPTION(VMultipleMainDeviceException, VGraphicException);
V3D_DECLARE_EXCEPTION(VNoMainDeviceException, VGraphicException);

/**
 * @author sheijk
 */
class IVGraphicsService : public VNamedObject
{
public:
	IVGraphicsService() : VNamedObject("graphics.service", NULL) {}

	virtual ~IVGraphicsService() {}

	virtual void SetMainDevice(IVDevice* in_pDevice) = 0;
	virtual IVDevice* GetMainDevice() const = 0;

    virtual VAutoPtr<IVDevice> CreateOffscreenDevice(
		const VDisplaySettings&) const = 0;

	virtual void SetSystemParam(
		const std::string& in_strName, 
		VSharedPtr<IVParameterValue> in_pNewSystemParam) = 0;
	virtual void RemoveSystemParam(const std::string& in_strName) = 0;

	virtual void ApplySystemParams(IVMaterial& in_Material) = 0;
};

typedef VServicePtr<IVGraphicsService> VGraphicsServicePtr;
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
template<>
inline v3d::graphics::IVGraphicsService* v3d::QueryService<v3d::graphics::IVGraphicsService>()
{
	return QueryObject<v3d::graphics::IVGraphicsService>("graphics.service");
}
//-----------------------------------------------------------------------------
#endif // V3D_IVGRAPHICSSERVICE_2006_04_19_H

