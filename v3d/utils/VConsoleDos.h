//
// *** VConsoleDos ***
//
// Synopsis:
//    - Writes text to a dos like console
//
// Description:
//    - 
//
// See also:
//    - 
//

#ifndef V3D_VCONSOLEDOS_H
#define V3D_VCONSOLEDOS_H

#include <windows.h>

#include <Utils/IVConsole.h>
#include <Utils/VFormattedOutput.h>

class VConsoleDos : public IVConsole, VFormattedOutput
{

private:
	
	DWORD m_dwCount;
	HANDLE m_hOut;
	
public:

	VRESULT Initialize();
	VRESULT Shutdown();
	void Write(const vchar *pcText, ...);
};

#endif

