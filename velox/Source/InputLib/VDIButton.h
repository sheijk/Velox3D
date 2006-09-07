/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDIBUTTON_09_02_2004_H
#define V3D_VDIBUTTON_09_02_2004_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Input/IVButton.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
 * DirectInput implementation of a button
 * @author AcrylSword
 * @version 1.2
 */
class VDIButton : public IVButton
{
	VString m_strName;
	vbool m_bState;

public:
	VDIButton(VStringParam in_strName);
	virtual ~VDIButton();

	virtual VStringRetVal GetName();
	virtual vbool IsDown();
	void SetDown( vbool in_bState );
};
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIBUTTON_09_02_2004_H
