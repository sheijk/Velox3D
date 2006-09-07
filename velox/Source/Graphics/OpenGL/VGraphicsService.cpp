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

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

