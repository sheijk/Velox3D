/**
 * Velox3D
 *
 * Disciption:	Dialog Box for Windows
 * Author:		Reinhold Früsmer
 * History:		Taken from p3d. Request Reinhold's permission to use!!
 * 
 */

#ifndef V3D_VDIALOGBOX_H
#define V3D_VDIALOGBOX_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h> 


class VDialogBox 
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


	RET_VALUE Show(const char* pszText, const char* pszTitle, ICON_STYLE eIconStyle, 
		BUTTON_STYLE eButtonStyle);

protected:

	RET_VALUE ShowWin32(const char* pszText, const char* pszTitle, ICON_STYLE eIconStyle, 
		BUTTON_STYLE eButtonStyle);
};



#endif // WINDIALOGBOX_H