#ifndef V3D_VKERNEL_H
#define V3D_VKERNEL_H
//------------------------------------------------------------------------
#include <Core/VCoreLib.h>

#include <Utils/SmartPtr/VGuards.h>

#include "VKernelException.h"
#include "VServiceProxy.h"

#include <string>
#include <list>

/**
 * The kernel
 * Initializes the program and loads all libraries
 */
class VKernel
{
private:
	void ParseFile(const std::string& in_strFileName);
	void GenerateInitSequence();
	void LoadServices();
	void DelegateControl();
	void Shutdown();

	typedef VPointer<VServiceProxy>::SharedPtr ServicePointer;
	typedef std::list<ServicePointer> ServiceList;

	ServiceList m_Services;
public:
	VKernel();
	virtual ~VKernel();

	/** loads ini file and interpretes it */
	void ProcessIniFile(std::string in_strFileName);
};

//------------------------------------------------------------------------
#endif // V3D_VKERNEL_H
