/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VGRAPHICSSERVICE_2006_04_19_H
#define V3D_VGRAPHICSSERVICE_2006_04_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVGraphicsService.h>
#include <V3d/Graphics/Parameters/IVParameterValue.h>
#include <V3d/Graphics/IVMaterial.h>
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

	void SetSystemParam(
		const std::string& in_strName, 
		VSharedPtr<IVParameterValue> in_pNewSystemParam);
	void RemoveSystemParam(const std::string& in_strName);

	void ApplySystemParams(IVMaterial& in_Material);

private:
	IVDevice* m_pMainDevice;

	typedef std::map<std::string, VSharedPtr<IVParameterValue> > SystemParamMap;
	SystemParamMap m_SystemParams;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VGRAPHICSSERVICE_2006_04_19_H

