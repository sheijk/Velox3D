#ifndef V3D_VEDITORAPP_2004_05_05_H
#define V3D_VEDITORAPP_2004_05_05_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Core/IVApplication.h>
#include <v3d/Core/VNamedObject.h>

#include <v3d/Editor/IVEditorSuite.h>

#include "VEditorFrame.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * The velox editor application. Initializes the editor main frame and plugin
 * registry
 */
class VEditorApp : public IVApplication, VNamedObject
{
public:
	VEditorApp();

	/** the main function */
	virtual vint Main();

	/** register a tool */
	virtual void RegisterTool(IVTool& in_Tool);

private:
	typedef VEditorFrame::PluginList PluginList;

	vbool m_bAllowNewPlugins;
	PluginList m_Plugins;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VEDITORAPP_2004_05_05_H
