//
// *** VThread ***
//
// Synopsis:
//    - Implements multithreading support for the win platform
//
// Description:
//    - 
//
// See also:
//    - 
//

#ifndef V3D_VTHREAD_H
#define V3D_VTHREAD_H

#include <windows.h>
#include <Core/VTypes.h>
#include <Core/VMutex.h>

class VThread : public VMutex
{

protected:
  HANDLE  m_hThreadHandle;
  DWORD   m_dwThreadID;
  vbool   m_bIsRunning;

public:
  VThread();
  virtual ~VThread();

  vbool Start();
  void Stop();
  vbool IsRunning();

  virtual DWORD m_ThreadProc();
};

#endif