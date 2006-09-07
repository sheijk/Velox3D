/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVEDITORSUITE_2004_05_05_H
#define V3D_IVEDITORSUITE_2004_05_05_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor/IVPlugin.h>
#include <v3d/Editor/IVMessage.h>
#include <v3d/Core/VNamedObject.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VServicePtr.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * The editor suite is the containing instance for all editors and tools. All
 * plugins will have to register here.
 *
 * Plugins may be either editors or tools. An editor is something containing
 * some set of data which may be created, opened, altered and saved. Only one
 * editor may be active at a time.
 * A tool is some utility like a texture selector etc which may be used to
 * enhance or control an editor. On user interaction or other events it sends
 * messages to the active editor which will process them and send back messages
 *
 * @author sheijk
 */
class IVEditorSuite : public VNamedObject
{
public:
	IVEditorSuite(VStringParam in_strName) : VNamedObject(in_strName, 0) 
	{}

	/** 
	 * Registers a plugin to the editor suite. The plugins actions will be
	 * added to the suite's menu
	 */
	//virtual void RegisterPlugin(IVPlugin& in_Plugin) = 0;

	/**
	 * Sends a message to the active editor. Use this to send messages of tool
	 * plugins so they will always reach the right editor
	 *
	 * @return Processed iff message has been handled
	 */
	virtual VMessageTreatment SendToActiveDocument(IVMessage& in_Message) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
template<>
inline v3d::editor::IVEditorSuite* v3d::QueryService<v3d::editor::IVEditorSuite>()
{
	return QueryObject<v3d::editor::IVEditorSuite>("editor.suite");
}
//-----------------------------------------------------------------------------
#endif // V3D_IVEDITORSUITE_2004_05_05_H

