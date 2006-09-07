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
#define INPUTEXAMPLE_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include "Input/VInputExample.h"
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/Core/Modules/VModuleBase.h>
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------

class VExamplesModule : public VModuleBase
{
	/** instance of the application service */
	VPointer<v3d::input::example::VInputExample>::AutoPtr g_pService;

public:
	VExamplesModule();

	virtual void Initialize();
	virtual void Shutdown();
};

VExamplesModule::VExamplesModule()
{
}

void VExamplesModule::Initialize()
{
	// create the application service instance
	// (registers itself at the Object Registry)
	g_pService.Assign(new v3d::input::example::VInputExample("main"));
}

void VExamplesModule::Shutdown()
{
	// destroy the application instance
	g_pService.Release();
}

const char* v3d::GetModuleName()
{
	return "input_example";
}

//-----------------------------------------------------------------------------
namespace
{
	VExamplesModule g_theApp;
}
//-----------------------------------------------------------------------------

