#ifndef V3D_IVPLUGIN_2004_05_05_H
#define V3D_IVPLUGIN_2004_05_05_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Core/Wrappers/VIterator.h>

#include <v3d/Editor/IVAction.h>
#include <v3d/Editor/IVMessage.h>

class wxWindow;
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * A plugin for the editor
 *
 * @author sheijk
 */
class IVPlugin
{
public:
	typedef VForwardIterator<IVAction> ActionIterator;

	/** Iterator to the first action */
	virtual ActionIterator ActionsBegin() = 0;

	/** Iterator pointing beyond the last action */
	virtual ActionIterator ActionsEnd() = 0;

	/**
	 * Enables the plugin. Plugin should load it's data and display it's
	 * windows now
	 */
	virtual void Enable() = 0;

	/** Returns the plugins name which will be used for menues etc */
	virtual VStringRetVal GetName() const = 0;

	/** Delivers a message to the plugin */
	virtual VMessageTreatment DeliverMessage(IVMessage& in_Message) = 0;
};

class IVTool : public IVPlugin
{
};

//class IVEditor : public IVPlugin
//{
//};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_IVPLUGIN_2004_05_05_H
