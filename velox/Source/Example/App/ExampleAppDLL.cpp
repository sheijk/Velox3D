/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

/**
 * Example Service DLL
 *
 * Makro um Import und Export in der gleichen Datei zu realisieren
 * wird nicht gebraucht, wg. dynamischen linken
 */
#define EXAMPLEAPP_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include "VExampleApp.h"
#include <v3d/Core/SmartPtr/VGuards.h>

#include <v3d/Core/Modules/VModuleBase.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::example;
//-----------------------------------------------------------------------------

class VExampleAppModule : public VModuleBase
{
	/** instance of the application service */
	VPointer<VExampleApp>::AutoPtr g_pService;

public:
	VExampleAppModule();

	virtual void Initialize();
	virtual void Shutdown();
};

VExampleAppModule::VExampleAppModule()
{
}

void VExampleAppModule::Initialize()
{
	// create the application service instance
	// (registers itself at the Object Registry)
	g_pService.Assign(new VExampleApp("main"));
}

void VExampleAppModule::Shutdown()
{
	// destroy the application instance
	g_pService.Release();
}

const char* v3d::GetModuleName()
{
	return "example_app";
}

//-----------------------------------------------------------------------------
namespace
{
	VExampleAppModule g_theApp;
}
//-----------------------------------------------------------------------------

