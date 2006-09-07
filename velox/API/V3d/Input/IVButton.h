/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVBUTTON_09_02_2004_H
#define V3D_IVBUTTON_09_02_2004_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/**
 * Interface for any input controller button
 * @author sheijk
 * @version 1.0
 */
class IVButton
{
public:
	virtual ~IVButton() {};
	
	virtual VStringRetVal GetName() = 0;
	virtual vbool IsDown() = 0;
	virtual void SetDown(vbool down) = 0;
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVBUTTON_09_02_2004_H
