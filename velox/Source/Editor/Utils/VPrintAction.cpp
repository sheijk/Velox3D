#include "VPrintAction.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VIOStream.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

VPrintAction::VPrintAction(VStringParam in_strMessage)
{
	m_strMessage = in_strMessage;
	m_strCaption = in_strMessage;
}

VPrintAction::VPrintAction(
	VStringParam in_strMessage, 
	VStringParam in_strCaption)
{
	m_strMessage = in_strMessage;
	m_strCaption = in_strCaption;
}

VStringRetVal VPrintAction::GetName()
{
	return m_strCaption;
}

void VPrintAction::Execute()
{
	vout << m_strMessage.AsCString();
}

void VPrintAction::SetMessage(VStringParam in_strMessage)
{
	m_strMessage = in_strMessage;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
