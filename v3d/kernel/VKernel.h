#ifndef V3D_VKERNEL_H
#define V3D_VKERNEL_H
//------------------------------------------------------------------------
#include <Core/VCoreLib.h>

//#include "VServiceProxy.h"

#include <string>

/**
 * The kernel
 * Initializes the program and loads all libraries
 */
class VKernel
{
private:
	void LoadDLLs();
	void ParseFile(const std::string& in_strFileName);
	void GenerateInitSequence();
	void LoadServices();
	void DelegateControl();
	void Shutdown();

public:
	VKernel();
	virtual ~VKernel();

	/** loads ini file and interpretes it */
	void ProcessIniFile(std::string in_strFileName);
};

//------------------------------------------------------------------------
#endif // V3D_VKERNEL_H
