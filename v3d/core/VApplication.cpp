
#include <Core/VApplication.h>


VApplication::VApplication()
{
	m_hInstance = NULL;
}

VApplication::VApplication(HINSTANCE hInstanceHandle)
{
	m_hInstance = hInstanceHandle;
}

VRESULT VApplication::Initialize(HINSTANCE hInstanceHandle)
{
	m_hInstance = hInstanceHandle;

	return VOK;
}

vint VApplication::Idle()
{
	return 0;
}

vint VApplication::Run()
{
	
	MSG msg;
	vint iResult;

	while (1)
	{
		if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return 0;
			}
			else
			{
				TranslateMessage (&msg);
				DispatchMessage (&msg);
			}
		}
		else
		{
			if ((iResult = Idle ()) != 0)
				return iResult;
		}
	}
}

VRESULT VApplication::Shutdown()
{
	m_hInstance = NULL;
	return VOK;
}
