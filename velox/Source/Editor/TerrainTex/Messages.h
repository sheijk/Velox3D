#ifndef V3D_MESSAGES_2004_06_18_H
#define V3D_MESSAGES_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor/IVMessage.h>

#include "VTextureStage.h"
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VTextureStageUpdated : public IVMessage
{
public:
	VTextureStageUpdated(VTextureStage& in_Stage, vuint in_nId);

	VTextureStage& GetTextureStage();

	vuint GetStageId();

private:
	VTextureStage& m_Stage;
	vuint m_nId;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_MESSAGES_2004_06_18_H
