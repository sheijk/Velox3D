//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Modules/VModuleBase.h>

#include "VEditorApp.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Module for the velox editor app
 */
class VEditorModule : public VModuleBase
{
public:
	VEditorModule();

	virtual void Initialize();
	virtual void Shutdown();

private:
	VPointer<VEditorApp>::SharedPtr m_pEditorApp;
};

VEditorModule::VEditorModule() : VModuleBase("editor")
{
}

void VEditorModule::Initialize()
{
	m_pEditorApp.Assign(new VEditorApp());
}

void VEditorModule::Shutdown()
{
	m_pEditorApp.Release();
}

namespace
{
	VEditorModule g_theEditorModule;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------