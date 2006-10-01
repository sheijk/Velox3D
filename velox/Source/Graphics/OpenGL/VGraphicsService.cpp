/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VGraphicsService.h"
//-----------------------------------------------------------------------------

#include "VOpenGLDevice.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VGraphicsService::VGraphicsService()
{
	m_pMainDevice = NULL;
}

/**
 * d'tor
 */
VGraphicsService::~VGraphicsService()
{
}

void VGraphicsService::SetMainDevice(IVDevice* in_pDevice)
{
	if( m_pMainDevice == 0 )
	{
		m_pMainDevice = in_pDevice;
	}
	else
	{
		V3D_THROW(VMultipleMainDeviceException, "only one main device possible");
	}
}

IVDevice* VGraphicsService::GetMainDevice() const
{
	return m_pMainDevice;
}

VAutoPtr<IVDevice> VGraphicsService::CreateOffscreenDevice(
	const VDisplaySettings& in_Settings) const
{
	if( m_pMainDevice != NULL )
	{
		IVRenderContext* pContext = m_pMainDevice->CreateOffscreenContext(&in_Settings);

		return AutoPtr(new VOpenGLDevice(in_Settings, pContext));
	}
	else
	{
		V3D_THROW(VNoMainDeviceException, 
			"main device required to create offscreen context");
	}
}

void VGraphicsService::SetSystemParam(
	const std::string& in_strName, 
	VSharedPtr<IVParameterValue> in_pNewSystemParam)
{
	m_SystemParams.erase(in_strName);
	m_SystemParams.insert(SystemParamMap::value_type(in_strName, in_pNewSystemParam));
}

void VGraphicsService::RemoveSystemParam(const std::string& in_strName)
{
	m_SystemParams.erase(in_strName);
}

void VGraphicsService::ApplySystemParams(IVMaterial& in_Material)
{
	for(SystemParamMap::iterator value = m_SystemParams.begin();
		value != m_SystemParams.end();
		++value)
	{
		IVParameter* pParam = in_Material.GetParameterByName(value->first);

		if( pParam != 0 )
		{
			value->second->Apply(*pParam);
		}
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

