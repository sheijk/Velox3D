/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Core/VAssert.h>
//-----------------------------------------------------------------------------
#ifdef V3D_WIN32
#include <windows.h>
#endif
//#include <Error/VDebugLogger.h>
#include <sstream>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

void _V3DAssert( bool bExp, const char* cFile, const vuint iLine, const vchar* cExp )
{

	if ( bExp == false ) //assertion failed
	{
		std::ostringstream Error;
		Error <<"ASSERTION FAILED: " << "(" << cExp << ")" << " File: " << cFile << ", Line: " << iLine << "\0";

#ifdef V3D_WIN32
	    int iResult;
		iResult = MessageBox(NULL, Error.str().c_str(), "Velox3D Assertion Error", MB_OKCANCEL | MB_ICONERROR );

		if (iResult == IDOK) return;
		if (iResult == IDCANCEL) abort();
#endif 
	}
}

//-----------------------------------------------------------------------------
} // namespace v3d

