#include <Core/VDialogBox.h>


VDialogBox::RET_VALUE VDialogBox::Show(const char* pszText, const char* pszTitle, 
											   ICON_STYLE eIconStyle, BUTTON_STYLE eButtonStyle)
{
	return ShowWin32(pszText, pszTitle, eIconStyle, eButtonStyle);
}

VDialogBox::RET_VALUE VDialogBox::ShowWin32(const char* pszText, const char* pszTitle, 
													ICON_STYLE eIconStyle, BUTTON_STYLE eButtonStyle)
{
	unsigned int uiStyle;

	switch (eIconStyle)
	{
	case IS_ICONSTOP:
		uiStyle = MB_ICONSTOP;
		break;

	case IS_ICONEXCLAMATION:
		uiStyle = MB_ICONEXCLAMATION;
		break;

	case IS_ICONINFORMATION:
		uiStyle = MB_ICONINFORMATION;
		break;

	default:
		//P3DASSERT(FALSE); // TODO
		break;
	}

	switch (eButtonStyle)
	{
	case BS_YESNO:
		uiStyle |= MB_YESNO;
		break;

	case BS_ABORTRETRYIGNORE:
		uiStyle |= MB_ABORTRETRYIGNORE;
		break;

	case BS_OK:
		uiStyle |= MB_OK;
		break;

	default:
		//P3DASSERT(FALSE); // TODO
		break;
	}

	int	iRetVal = ::MessageBox(NULL, pszText, pszTitle, uiStyle);

	RET_VALUE retVal;

	switch (iRetVal)
	{
	case IDABORT:
		retVal = RV_ABORT;
		break;

	case IDCANCEL:
		retVal = RV_CANCEL;
		break;

	case IDIGNORE:
		retVal = RV_IGNORE;
		break;

	case IDNO:
		retVal = RV_NO;
		break;

	case IDOK:
		retVal = RV_OK;
		break;

	case IDRETRY:
		retVal = RV_RETRY;
		break;

	case IDYES:
		retVal = RV_YES;
		break;

	default:
//		V3DASSERT(FALSE); // TODO
		retVal = RV_CANCEL;
		break;
	}
	
	return retVal;
}