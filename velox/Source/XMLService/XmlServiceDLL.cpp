#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include <v3d/Core/Modules/VModuleBase.h>

#include "VXMLService.h"

//-----------------------------------------------------------------------------

class VXmlModule : public v3d::VModuleBase
{
	v3d::VPointer<v3d::xml::VXMLService>::AutoPtr m_pXMLService;

public:
	VXmlModule() : VModuleBase("xml") 
	{
	}

	virtual void Initialize();
	virtual void Shutdown();
};

namespace {
	VXmlModule g_XMLModule;
}
//-----------------------------------------------------------------------------

void VXmlModule::Initialize()
{
	m_pXMLService.Assign(new v3d::xml::VXMLService());
}

void VXmlModule::Shutdown()
{
	m_pXMLService.Release();
}