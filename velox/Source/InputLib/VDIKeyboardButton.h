/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDIKEYBOARDBUTTON_09_02_2004_H
#define V3D_VDIKEYBOARDBUTTON_09_02_2004_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Input/IVButton.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
//TODO: insert documentation here
*/
class VDIKeyboardButton : public IVButton
{
private:
	vchar* m_pButton;
	VString m_strName;

	public:
	VDIKeyboardButton() {;};
	VDIKeyboardButton( VStringParam in_strName, vchar* in_pPointer );
	virtual ~VDIKeyboardButton();

	virtual VStringRetVal GetName();
	virtual vbool IsDown();
	virtual void SetDown(vbool down);
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
#endif // V3D_VDIKEYBOARDBUTTON_09_02_2004_H
