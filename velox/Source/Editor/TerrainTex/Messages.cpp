#include "Messages.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

VTextureStageUpdated::VTextureStageUpdated(VTextureStage& in_Stage, vuint in_nId) :
	m_Stage(in_Stage),
	m_nId(in_nId)
{
}

VTextureStage& VTextureStageUpdated::GetTextureStage()
{
	return m_Stage;
}

vuint VTextureStageUpdated::GetStageId()
{
	return m_nId;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
