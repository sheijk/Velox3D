#include "VToolBase.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

VToolBase::VToolBase(VStringParam in_strName) : m_strName(in_strName)
{
}

IVTool::ActionIterator VToolBase::ActionsBegin() 
{
	return ActionIterator(new ActionIterPol(m_Actions.begin()));
}

IVTool::ActionIterator VToolBase::ActionsEnd() 
{
	return ActionIterator(new ActionIterPol(m_Actions.end()));
}

VStringRetVal VToolBase::GetName() const
{
	return m_strName.AsCString();
}

void VToolBase::AddAction(ActionPtr in_pAction)
{
	m_Actions.push_back(in_pAction);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
