#ifndef V3D_VKERNEL_H
#define V3D_VKERNEL_H
//------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Core/SmartPtr/VGuards.h>

#include "VKernelException.h"
#include "VServiceProxy.h"

#include <string>
#include <list>

//-----------------------------------------------------------------------------
namespace v3d {
namespace kernel {
//-----------------------------------------------------------------------------

//TODO: ableiten von "Spezial Kerneln" ermoeglichen

/**
 * The kernel
 * Initializes the program and loads all libraries
 */
class VKernel
{
private:
	void CreateObjectRegistry();
	void ParseFile(const std::string& in_strFileName);
	void GenerateInitSequence();
	void LoadServices();
	void DelegateControl();
	void Shutdown();

	typedef VPointer<VServiceProxy>::SharedPtr ServicePointer;
	typedef std::list<ServicePointer> ServiceList;

	ServiceList m_Services;
	std::string m_strAppName;
//	ServicePointer m_App;
public:
	VKernel();
	virtual ~VKernel();

	/** loads ini file and interpretes it */
	void ProcessIniFile(std::string in_strFileName);
};

//-----------------------------------------------------------------------------
} // namespace kernel
} // namespace v3d
//------------------------------------------------------------------------
#endif // V3D_VKERNEL_H
