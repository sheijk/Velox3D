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


#include <Core/VMutex.h>

VMutex::VMutex(void)
{
	m_hMutexHandle = NULL;
}

VMutex::~VMutex(void)
{
#if defined V3D_MULTITHREADING_SUPPORT

	if(m_hMutexHandle != NULL)
    {
      CloseHandle(m_hMutexHandle);
      m_hMutexHandle = NULL;
    }

#endif
}


vbool VMutex::Initialize()
{
#if defined V3D_MULTITHREADING_SUPPORT

	m_hMutexHandle = CreateMutex(NULL, false, NULL);
    if(m_hMutexHandle == NULL)
		return false;

#endif

	return true;
}

void VMutex::Enable() const
{
#if defined V3D_MULTITHREADING_SUPPORT

    WaitForSingleObject(m_hMutexHandle, INFINITE);

#endif
}


void VMutex::Disable() const
{
#if defined V3D_MULTITHREADING_SUPPORT

	ReleaseMutex(m_hMutexHandle);

#endif
}
