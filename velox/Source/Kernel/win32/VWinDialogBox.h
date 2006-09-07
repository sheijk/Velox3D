/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VWINDIALOGBOX_H
#define V3D_VWINDIALOGBOX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
//-----------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace win32{
//-----------------------------------------------------------------------------

class VWinDialogBox 
{
public:

	enum BUTTON_STYLE
	{
		BS_YESNO,
		BS_OK,
		BS_ABORTRETRYIGNORE,
	};

	enum ICON_STYLE
	{
		IS_ICONSTOP,
		IS_ICONEXCLAMATION,
		IS_ICONINFORMATION
	};

	enum RET_VALUE
	{
		RV_ABORT,
		RV_CANCEL,
		RV_IGNORE,
		RV_NO,
		RV_OK,
		RV_RETRY,
		RV_YES
	};


	RET_VALUE Show(const vchar* pszText, const vchar* pszTitle,
				   ICON_STYLE eIconStyle, BUTTON_STYLE eButtonStyle);

protected:

	RET_VALUE ShowWin32(const vchar* pszText, const vchar* pszTitle,
						ICON_STYLE eIconStyle, BUTTON_STYLE eButtonStyle);
};

//-----------------------------------------------------------------------------
} //namespace v3d;
} // namespace win32;
//-----------------------------------------------------------------------------

#endif // WINDIALOGBOX_H
