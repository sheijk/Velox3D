//
// *** IVConsole ***
//
// Synopsis:
//    - Console interface
//


#ifndef V3D_IVCONSOLE_H
#define V3D_IVCONSOLE_H

#include <Core/VTypes.h>


class IVConsole
{
public:

	virtual VRESULT Initialize() = 0;
	virtual VRESULT Shutdown() = 0;
	virtual void Write(const vchar *pcText, ...) = 0;
		
};

#endif