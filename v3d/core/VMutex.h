//
// *** VMutex ***
//
// Synopsis:
//    - simple solution for solving multithreading inconsisitence
//
// Description:
//    -
//
// See also:
//    -
//


#ifndef V3D_VMUTEX_H
#define V3D_VMUTEX_H

#include <windows.h>
#include <Core/VTypes.h>

class VMutex
{
private :

	HANDLE m_hMutexHandle;

public :

	VMutex(void);
	virtual ~VMutex(void);

	vbool Initialize();
	void Enable() const;
	void Disable() const;
};


#endif