#ifndef V3D_VKERNEL_H
#define V3D_VKERNEL_H
//------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <V3d/XML/IVXMLService.h>
//------------------------------------------------------------------------
#include "VKernelException.h"
#include "VServiceProxy.h"
//------------------------------------------------------------------------
#include <string>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace kernel {
//-----------------------------------------------------------------------------

/**
 * The kernel
 * Initializes the program and loads all libraries
 */
class VKernel{
protected:
	virtual void CreateObjectRegistry();
	virtual void ParseFile(const std::string& in_strFileName);
	virtual void GenerateInitSequence();
	virtual void LoadServices();
	virtual void DelegateControl();
	virtual void Shutdown();
	virtual void LoadXMLService();

private:
	typedef VPointer<VServiceProxy>::SharedPtr ServicePointer;
	typedef std::list<ServicePointer> ServiceList;

	ServiceList m_Services;
	std::string m_strAppName;
	xml::IVXMLService* m_XmlService;

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
