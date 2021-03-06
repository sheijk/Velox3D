/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/SmartPtr/VGuards.h>

#include <V3d/Core/Modules/VModuleBase.h>

#include "VXMLService.h"
#include <V3d/Core/MemManager.h>

//-----------------------------------------------------------------------------

class VXmlModule : public v3d::VModuleBase
{
	v3d::VSharedPtr<v3d::xml::VXMLService> m_pXMLService;

public:
	VXmlModule() // : VModuleBase("xml") 
	{
	}

	virtual void Initialize();
	virtual void Shutdown();
};

const char* v3d::GetModuleName()
{
	return "xml";
}

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
