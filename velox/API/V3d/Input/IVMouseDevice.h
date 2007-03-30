/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVMOUSEDEVICE_2004_08_09_H
#define V3D_IVMOUSEDEVICE_2004_08_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Input/IVInputDevice.h>
#include <V3d/Input/IVButton.h>
#include <V3d/Input/IVRelativeAxis.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/**
 * Interface for an attached input controller
 * @author sheijk
 * @version 1.0
 */
class IVMouseDevice : public IVInputDevice
{
public:
	virtual	 ~IVMouseDevice() {};

	virtual vuint			GetButtonCount() = 0;
	virtual IVButton&		GetButton(const vuint in_Number)= 0;
	virtual IVButton&		GetLeftButton() = 0;
	virtual IVButton&		GetRightButton() = 0;

	virtual IVRelativeAxis& GetXAxis() = 0;
	virtual IVRelativeAxis& GetYAxis() = 0;
	virtual IVRelativeAxis& GetWheel() = 0;
};
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVMOUSEDEVICE_2004_08_09_H

