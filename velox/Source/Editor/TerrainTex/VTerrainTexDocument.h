#ifndef V3D_VTERRAINTEXDOCUMENT_2004_06_18_H
#define V3D_VTERRAINTEXDOCUMENT_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor/IVDocument.h>
#include <v3d/Editor/IVMessage.h>

#include <V3dLib/Graphics/Misc/VSimpleDrawList.h>

#include "VTerrainTexGenPreviewFrame.h"
#include "VTextureStage.h"

#include <vector>
#include <wx/wx.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VTerrainTexDocument : public IVDocument
{
public:
	VTerrainTexDocument(
		wxWindow* in_pParent, 
		vuint in_nWidth, 
		vuint in_nHeight);

	virtual Connection RegisterFocusListener(const FocusSlot& in_Slot);
	virtual void SetWindowMode(WindowMode in_Mode);
	virtual VMessageTreatment DeliverMessage(IVMessage& in_Message);
private:
	typedef std::vector<VTextureStage> TextureStageList;

	void Render();

	VPointer<v3d::graphics::VSimpleDrawList>::SharedPtr m_pDrawList;

	VTerrainTexGenPreviewFrame* m_pPreviewWindow;
	TextureStageList m_TextureStages;
};


//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAINTEXDOCUMENT_2004_06_18_H
