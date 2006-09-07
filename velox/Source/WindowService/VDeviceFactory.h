/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDEVICEFACTORY_08_30_04_H
#define V3D_VDEVICEFACTORY_08_30_04_H
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVDevice.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace window{
//-----------------------------------------------------------------------------

/**
 * Factory for device creation
 * @author: ins
 */

class VDeviceFactory
{
public:

	/* Creates a device */
	virtual graphics::IVDevice* CreateDevice() = 0;
	
};
//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VDEVICEFACTORY_08_30_04_H

