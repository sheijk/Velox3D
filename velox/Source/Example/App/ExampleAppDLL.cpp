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

VExampleAppModule::VExampleAppModule() : VModuleBase("app")
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

//-----------------------------------------------------------------------------
namespace
{
	VExampleAppModule g_theApp;
}
//-----------------------------------------------------------------------------
