#ifndef V3D_VAPPLICATION_H
#define V3D_VAPPLICATION_H

#include <windows.h>
#include <Core/VCoreLib.h>

class VApplication
{
    
public:
	

	VApplication();
	VApplication(HINSTANCE hInstanceHandle);

    virtual VRESULT Initialize(HINSTANCE hInstanceHandle);
	virtual VRESULT Shutdown();
    virtual vint Run();
	virtual vint Idle();
    
protected:
	
	HINSTANCE m_hInstance;
};



#endif