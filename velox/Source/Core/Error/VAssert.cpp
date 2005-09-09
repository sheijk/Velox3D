#include <V3D/Core/VAssert.h>
//-----------------------------------------------------------------------------
#include <windows.h>
//#include <Error/VDebugLogger.h>
#include <sstream>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

void _V3DAssert( bool bExp, const char* cFile, const vuint iLine, const vchar* cExp )
{
	int iResult;

	if ( bExp == false ) //assertion failed
	{
		std::ostringstream Error;
		Error <<"ASSERTION FAILED: " << "(" << cExp << ")" << " File: " << cFile << ", Line: " << iLine << "\0";

		iResult = MessageBox(NULL, Error.str().c_str(), "Velox3D Assertion Error", MB_OKCANCEL | MB_ICONERROR );

		if (iResult == IDOK) return;
		if (iResult == IDCANCEL) abort();
	}
}

//-----------------------------------------------------------------------------
} // namespace v3d
