#ifndef V3D_VTOOLBASE_2004_06_18_H
#define V3D_VTOOLBASE_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <V3d/Core/Wrappers/VIterator.h>
#include <v3d/Core/Wrappers/VSTLDerefIteratorPol.h>

#include <V3d/Editor/IVAction.h>
#include <V3d/Editor/IVPlugin.h>

#include <vector>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VToolBase : public IVTool
{
protected:
	typedef VPointer<IVAction>::SharedPtr ActionPtr;
	typedef std::vector<ActionPtr> ActionList;
	typedef VSTLDerefIteratorPol<ActionList::iterator, IVAction> ActionIterPol;

public:
	typedef IVTool::ActionIterator ActionIterator;

	VToolBase(VStringParam in_strName);

	ActionIterator ActionsBegin();
	ActionIterator ActionsEnd();
	VStringRetVal GetName() const;

protected:
	void AddAction(ActionPtr in_pAction);

private:
	ActionList m_Actions;
	VString m_strName;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VTOOLBASE_2004_06_18_H
