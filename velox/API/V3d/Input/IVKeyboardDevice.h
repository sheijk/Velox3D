/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVKEYBOARDDEVICE_2004_08_09_H
#define V3D_IVKEYBOARDDEVICE_2004_08_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Input/IVInputDevice.h>
#include <v3d/Input/VKeyCode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
 * Interface for an attached keyboard
 * @author sheijk
 * @version 1.0
 */
class IVKeyboardDevice : public IVInputDevice
{
public:
	virtual				~IVKeyboardDevice() {};

	virtual IVButton&	GetKey(const VKeyCode in_Key) = 0;
};
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVKEYBOARDDEVICE_2004_08_09_H

