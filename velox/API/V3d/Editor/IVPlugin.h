#ifndef V3D_IVPLUGIN_2004_05_05_H
#define V3D_IVPLUGIN_2004_05_05_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor/IVAction.h>
#include <V3d/Core/Wrappers/VIterator.h>

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

	virtual ActionIterator ActionsBegin() = 0;
	virtual ActionIterator ActionsEnd() = 0;

	virtual void Enable(wxWindow* in_pParent) = 0;

	virtual VStringRetVal GetName() = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_IVPLUGIN_2004_05_05_H
