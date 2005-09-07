#include <V3d/Core/VAssert.h>
//-----------------------------------------------------------------------------
//#include <Error/VDebugLogger.h>
#include <sstream>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

#ifdef V3D_WIN32
#include <windows.h>
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
#else // V3D_WIN32
void _V3DAssert( bool bExp, const char* cFile, const vuint iLine, const vchar* cExp )
{
	if ( bExp == false ) //assertion failed
	{
		std::ostringstream Error;
		Error <<"ASSERTION FAILED: " << "(" << cExp << ")" << " File: " << cFile << ", Line: " << iLine << "\0";

		abort();
	}
}
#endif // V3D_WIN32

//-----------------------------------------------------------------------------
} // namespace v3d

