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

#include <Core/VThread.h>
			

static DWORD WINAPI ThreadProc(VThread *pThis)
{
  return pThis->m_ThreadProc();
}

VThread::VThread()
{
  m_dwThreadID = 0;
  m_hThreadHandle = NULL;
  m_bIsRunning = false;
}

VThread::~VThread()
{
	Stop();
}

vbool VThread::Start()
{

#if defined V3D_MULTITHREADING_SUPPORT
    if(m_hThreadHandle)
        Stop();

  m_hThreadHandle = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)ThreadProc,
                                this, 0, (LPDWORD)&m_dwThreadID);
  
  if(m_hThreadHandle == NULL)
	  return false;
  
  m_bIsRunning = true;
  return true;

#endif
}

void VThread::Stop()
{
#if defined V3D_MULTITHREADING_SUPPORT

	if(m_hThreadHandle != NULL)
	{
	    m_bIsRunning = false;
	    WaitForSingleObject(m_hThreadHandle, INFINITE);
		CloseHandle(m_hThreadHandle);
		m_hThreadHandle = NULL;
	}

#endif
}

DWORD VThread::m_ThreadProc()
{
  return 0;
}
