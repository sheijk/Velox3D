/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VOPENGLDEVICEFACTORY_08_30_04_H_H
#define V3D_VOPENGLDEVICEFACTORY_08_30_04_H_H
//-----------------------------------------------------------------------------
#include "VDeviceFactory.h"
#include <v3d/Graphics/VDisplaySettings.h>
#include "../Graphics/OpenGL/Context/VWin32WindowContext.h"

#include <windows.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------
 using namespace graphics;
/**
  * concrete device factory for an opengl device
  * @author: ins
 */

class VOpenGLDeviceFactory : public VDeviceFactory
{
public:

	VOpenGLDeviceFactory(
		const graphics::VDisplaySettings* in_pDisplaySettings,
		const HWND hWnd);
	
	virtual ~VOpenGLDeviceFactory();

	virtual graphics::IVDevice* CreateDevice();

private:

	HWND m_hWnd;
	const graphics::VDisplaySettings* m_pDisplaySettings;
	VWin32WindowContext* m_pContext;
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VOPENGLDEVICEFACTORY_08_30_04_H_H

