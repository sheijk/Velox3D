#include <windows.h>
#include "VAssert.h"
#include <Error/VDebugLogger.h>
#include <sstream>


void _V3DAssert( bool bExp, const char* cFile, const vuint iLine, const vchar* cExp )
{
	int iResult;

	if ( bExp == false ) //assertion failed
	{
		std::ostringstream Error;
		Error <<"ASSERTION FAILED: " << "(" << cExp << ")" << " File: " << cFile << ", Line: " << iLine << "\0";

		VDebugLogger::CreateInstance()->Message( Error.str(), VDebugLogger::V3D_ERROR );
		iResult = MessageBox(NULL, Error.str().c_str(), "Velox3D Assertion Error", MB_OKCANCEL | MB_ICONERROR );

		if (iResult == IDOK) return;
		if (iResult == IDCANCEL) abort();
	}
}
